/**
 *   @file    hse_fw_update.c
 *
 *   @brief   HSE FW update services.
 *   @details Updates the HSE FW (generating the blue image from a new image / running image).
 *
 *   @addtogroup [APP_HSE_FW_UPDATE]
 *   @{
 */
/*==================================================================================================
*
*   Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*==================================================================================================
    *                                        INCLUDE FILES
    * 1) system and project includes
    * 2) needed interfaces from external units
    * 3) internal and external interfaces from this unit
    ==================================================================================================*/

#include "hse_global_variables.h"
#include "hse_host_attrs.h"
#include "hse_host_boot.h"
#include "hse_demo_app_services.h"
#include "hse_mu.h"
#include "hse_host.h"
#include "hse_host_flashSrv.h"
#include <string.h>
#include "hse_host_flash.h"

    /*=============================================================================
     *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
     * ==========================================================================*/
    typedef struct hseFwHdr_tag
    {
        uint8_t tag;    /* Tag field */
        uint8_t len[2]; /* Length field in bytes */
        uint8_t par;    /* Parameters field */
    } hseFwHdr_t;

    /**
     * @brief   The HSE imager additional data.
     * @details The additional data is formed from the image header,
     *          image entry point, code length & FW version.*/

    typedef struct hseFWImageAAD_tag
    {
        hseFwHdr_t hdr; /* Header Data */
        uint8_t reserved0[4];
        uint32_t reserved1;  /* Absolute address of the first instruction to execute from the image*/
        uint32_t CodeLength; /* Length of HSE FW*/
        uint32_t reserved2[5];
        uint32_t reserved3;              /* Key Slector Value which will use to update FSK, its value may lie between 0-15*/
        hseAttrFwVersion_t hseFwVersion; /* Hse Fw Version*/
        uint8_t reserved4[16];
    } hseFWImageAAD_t;

    typedef enum
    {
        ONE_SHOT = 0,
        STREAMING
    } data_transfer_mode_t;

    typedef enum
    {
        NOT_ERASED = 0,
        ERASED
    } erase_status_t;

    typedef enum
    {
        ERASE_RSP_ERROR = 0,
        FLASHING_RSP_ERROR,
        FW_UPDATE_RSP_COMMAND_START_ERROR,
        FW_UPDATE_RSP_COMMAND_UPDATE_ERROR,
        FW_UPDATE_RSP_COMMAND_FINISH_ERROR,
        INVALID_CHANNEL_ERROR,
        INVALID_ERROR = 0xFF
    } streaming_mode_err_t;
/*=============================================================================
 *                                       LOCAL MACROS
 * ==========================================================================*/
#define HSE_BASE_VERSION (0x60UL)
#define HSE_FW_HDR_SIZE (0x40)
#define CODE_LENGTH_ADDR_OFFSET (0x0CUL)
#define MULTIPLE_OF_64_BYTES (64UL)
#define SIZE_OF_ONE_SECTOR (uint32_t)(8192U)
#define NUM_OF_SECTORS_IN_120KB 15U
#define SIZE_120KB (NUM_OF_SECTORS_IN_120KB * SIZE_OF_ONE_SECTOR)
#define GET_SIZE_IN_MULTIPLE_OF_64_BYTES(x) ((x)*MULTIPLE_OF_64_BYTES)
#define GET_SIZE_IN_BYTES(x, y) ((x)*GET_SIZE_IN_MULTIPLE_OF_64_BYTES(y))
/*=============================================================================
 *                                      LOCAL CONSTANTS
 * ==========================================================================*/
#define HSE_FW_NXP_HEADER_LENGTH (0x1050U)
#define HSE_RSA_MOD_LEN (0x100U)
#define FW_IMAGE_GMAC (0x10U)
    /*=============================================================================
     *                                      LOCAL VARIABLES
     * ==========================================================================*/

    /*=============================================================================
     *                                      GLOBAL CONSTANTS
     * ==========================================================================*/

    /*=============================================================================
     *                                      GLOBAL VARIABLES
     * ==========================================================================*/
    volatile uint8_t factor = 0U;
    volatile uint32_t temporary_address;
    volatile data_transfer_mode_t selected_mode = ONE_SHOT;
    uint32_t pink_image_length = 0UL;
    /* added for debbugging */
    volatile streaming_mode_err_t error_type = INVALID_ERROR;
    extern volatile hseSrvResponse_t gsrvResponse;
    extern volatile bool_t fwudpate_only;
    volatile fwteststatus_t gInstallNewHSEFwTest = FW_NOT_INSTALLED;
    extern volatile bool_t ActivatePassiveBlock;
    extern hseAttrFwVersion_t gHseFwVersion;
    // this address is same as also in fw_update.cmm, for fw update demonstration, address is set to BLOCK0 address, update this if address in fw_update.cmm is changed.
    volatile uint32_t gNewHseFwAddress;
    /*=============================================================================
     *                                   LOCAL FUNCTION PROTOTYPES
     * ==========================================================================*/
    static hseSrvResponse_t Host_SendFwUpdateReqOneShotMode(hseSrvDescriptor_t *pHseSrvDesc);
    static hseSrvResponse_t Host_SendFwUpdateReqStreamingMode(hseSrvDescriptor_t *pHseSrvDesc);
    /*=============================================================================
     *                                       LOCAL FUNCTIONS
     * ==========================================================================*/
    static void BackUp(void);
/*=============================================================================
 *                                       GLOBAL FUNCTIONS
 * ==========================================================================*/

/******************************************************************************
 * Description:  Example of Fw Update request sent by the host.
 * Operation:    HSE FW Update.
 ******************************************************************************/
#ifdef HSE_SPT_OTA_FIRMWARE_UPDATE
    void HSE_FwUpdateExample(uint32_t newHseFwaddress)
    {
        hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
        hseFWImageAAD_t newhseFwHdr = {0UL};
        hseFirmwareUpdateSrv_t *pFwUpdateSrv;
        hseSrvDescriptor_t *pHseSrvDesc;
        uint8_t u8MuChannel;

        /* Copy the header of the new pink image */
        (void)memcpy(&newhseFwHdr, (void *)newHseFwaddress, HSE_FW_HDR_SIZE);

        /* Get a free channel on u8MuInstance */
        u8MuChannel = HSE_MU_GetFreeChannel(MU0);
        if (HSE_INVALID_CHANNEL == u8MuChannel)
        {
            goto exit;
        }

        pHseSrvDesc = &gHseSrvDesc[MU0][u8MuChannel];
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        pHseSrvDesc->srvId = HSE_SRV_ID_FIRMWARE_UPDATE;
        pFwUpdateSrv = &(pHseSrvDesc->hseSrv.firmwareUpdateReq);
        pFwUpdateSrv->pInFwFile = (HOST_ADDR)newHseFwaddress;
        /*NOTE: New image should be put above 64KB space - > 0x10000*/

        if (ONE_SHOT == selected_mode)
        {
            hseStatus = Host_SendFwUpdateReqOneShotMode(pHseSrvDesc);
        }
        else
        {
            hseStatus = Host_SendFwUpdateReqStreamingMode(pHseSrvDesc);
        }

        /*check if fw install successful, if not then enter while(1) loop*/
        ASSERT(HSE_SRV_RSP_OK == hseStatus);
    exit:
        return;
    }

#endif

    hseSrvResponse_t HSE_ActivatePassiveBlock(void)
    {
        hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t u8MuChannel = CH1;
        hseSrvDescriptor_t *pHseSrvDesc;

        pHseSrvDesc = &gHseSrvDesc[MU0][u8MuChannel];
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        pHseSrvDesc->srvId = HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK;
        hseStatus = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);

        /* wait for positive response */
        ASSERT(HSE_SRV_RSP_OK == hseStatus);
        return hseStatus;
    }

#ifdef HSE_SPT_OTA_FIRMWARE_UPDATE
    static hseSrvResponse_t Host_SendFwUpdateReqOneShotMode(hseSrvDescriptor_t *pHseSrvDesc)
    {
        hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
        pHseSrvDesc->hseSrv.firmwareUpdateReq.accessMode = HSE_ACCESS_MODE_ONE_PASS;
        /* Get a free channel on u8MuInstance */
        uint8_t u8MuChannel = HSE_MU_GetFreeChannel(MU0);
        if (HSE_INVALID_CHANNEL == u8MuChannel)
            goto exit;
        hseStatus = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);
    exit:
        return hseStatus;
    }
#endif

#ifdef HSE_SPT_OTA_FIRMWARE_UPDATE
    static hseSrvResponse_t Host_SendFwUpdateReqStreamingMode(hseSrvDescriptor_t *pHseSrvDesc)
    {
        hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
        hseFWImageAAD_t *FwHeader = (hseFWImageAAD_t *)temporary_address;
        uint32_t chunk_size = 0UL;
        uint32_t total_no_of_chunks = 0UL;
        hseFirmwareUpdateSrv_t *pFwUpdateSrv = &(pHseSrvDesc->hseSrv.firmwareUpdateReq);
        uint8_t u8MuChannel = 0U;
        uint32_t src_address = temporary_address;
        uint8_t chunkdata[1024U] = {0U};
        uint32_t pending_size = 0U;

        /*calculate total pink image length */
        pink_image_length = (HSE_FW_NXP_HEADER_LENGTH + FwHeader->CodeLength + HSE_RSA_MOD_LEN + FW_IMAGE_GMAC);

        /* Calculate maximum number of chunks of data that has to be sent in streaming mode,
         * This App contains a provision to configure the streaming size upto 640B */
        total_no_of_chunks = (pink_image_length / GET_SIZE_IN_MULTIPLE_OF_64_BYTES(factor));

        /*Step 1: Set mode to START */
        pFwUpdateSrv->accessMode = HSE_ACCESS_MODE_START;

        /* Calculate destination and source address for flashing image in chunks at new address for firmware update */
        pFwUpdateSrv->pInFwFile = (HOST_ADDR)(chunkdata);
        pFwUpdateSrv->streamLength = GET_SIZE_IN_MULTIPLE_OF_64_BYTES(factor);

        /* Check if all data is transferred */
        while (total_no_of_chunks > chunk_size)
        {
            /* Copy Firmware Code to SRAM */
            memcpy((void *)chunkdata, (void *)src_address, GET_SIZE_IN_MULTIPLE_OF_64_BYTES(factor));

            /* Get a free channel on u8MuInstance */
            u8MuChannel = HSE_MU_GetFreeChannel(MU0);
            if (HSE_INVALID_CHANNEL == u8MuChannel)
            {
                error_type = INVALID_CHANNEL_ERROR;
                goto exit;
            }

            /* Send Request */
            if (HSE_SRV_RSP_OK != HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc))
            {
                if (0U != chunk_size)
                    error_type = FW_UPDATE_RSP_COMMAND_UPDATE_ERROR;
                else
                    error_type = FW_UPDATE_RSP_COMMAND_START_ERROR;
                break;
            }

            if (pFwUpdateSrv->accessMode != HSE_ACCESS_MODE_UPDATE)
            {
                /*Step 2: Set mode to UPDATE, this mode is set multiple times*/
                pFwUpdateSrv->accessMode = HSE_ACCESS_MODE_UPDATE;
            }

            /* Moving on to next chunk */
            chunk_size++;

            /* Source Address Update w.r.t chunk_size */
            src_address += GET_SIZE_IN_MULTIPLE_OF_64_BYTES(factor);
        }

        if (total_no_of_chunks != chunk_size)
        {
            goto exit;
        }

        pending_size = pink_image_length - (total_no_of_chunks * GET_SIZE_IN_MULTIPLE_OF_64_BYTES(factor));

        /* Copy Firmware Code to SRAM */
        memcpy((void *)chunkdata, (void *)src_address, pending_size);

        /* calculate remainder length,firmware address */
        pFwUpdateSrv->streamLength = pending_size;
        pFwUpdateSrv->pInFwFile = (HOST_ADDR)(chunkdata);

        /* Step 3: Set mode to FINISH, last step in fw update */
        pFwUpdateSrv->accessMode = HSE_ACCESS_MODE_FINISH;

        /* Get a free channel on u8MuInstance */
        u8MuChannel = HSE_MU_GetFreeChannel(MU0);
        if (HSE_INVALID_CHANNEL == u8MuChannel)
        {
            error_type = INVALID_CHANNEL_ERROR;
            goto exit;
        }

        hseStatus = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);
        if (HSE_SRV_RSP_OK != hseStatus)
            error_type = FW_UPDATE_RSP_COMMAND_FINISH_ERROR;

    exit:
        return hseStatus;
    }
#endif

    static void BackUp(void)
    {
        Fls_CheckStatusType fls_status = FLS_JOB_FAILED;
        // copy IVT
        memcpy((void *)&IVT, (void *)BLOCK0_IVT_ADDRESS, 0x100);
        // Take backup of following sections

        // 1)IVT
        fls_status = HostFlash_Erase(
            HOST_CODE_MEMORY_TYPE,
            (BLOCK0_IVT_ADDRESS + BACKUP_ADDRESS_OFFSET),
            1U);
        ASSERT(fls_status == FLS_JOB_OK);

        fls_status = HostFlash_Program(
            HOST_CODE_MEMORY_TYPE,
            (BLOCK0_IVT_ADDRESS + BACKUP_ADDRESS_OFFSET),
            (uint8_t *)BLOCK0_IVT_ADDRESS,
            0x2000UL);

        fls_status = HostFlash_Erase(
            HOST_CODE_MEMORY_TYPE,
            ((IVT.pAppImg_addr_0) + BACKUP_ADDRESS_OFFSET),
            12U);
        ASSERT(fls_status == FLS_JOB_OK);
        // 1) demo app code
        fls_status = HostFlash_Program(
            HOST_CODE_MEMORY_TYPE,
            ((IVT.pAppImg_addr_0) + BACKUP_ADDRESS_OFFSET),
            (uint8_t *)(IVT.pAppImg_addr_0),
            0x18000UL);
        ASSERT(fls_status == FLS_JOB_OK);
        // 2) IVT for BaseSB and secure boot app code and xrdc
        fls_status = HostFlash_Erase(
            HOST_CODE_MEMORY_TYPE,
            ((IVT.pAppImg_addr_1 - 0x0FC0UL) + BACKUP_ADDRESS_OFFSET),
            3U);
        ASSERT(fls_status == FLS_JOB_OK);
        fls_status = HostFlash_Program(
            HOST_CODE_MEMORY_TYPE,
            ((IVT.pAppImg_addr_1 - 0x0FC0UL) + BACKUP_ADDRESS_OFFSET),
            (uint8_t *)(IVT.pAppImg_addr_1 - 0x0FC0UL), /* secure boot application */
            0x6000UL);
        ASSERT(fls_status == FLS_JOB_OK);
    }
#ifdef HSE_SPT_OTA_FIRMWARE_UPDATE
    void firmwareUpdateService(void)
    {
        gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        memset((void *)fwversion, 0, 0x20);
        /* Get the HSE version before requesting for FW update */
        (void)HSE_GetVersion_Example(&fwversion[0]);
        if (fwudpate_only == TRUE)
        {
            HSE_FwUpdateExample(gNewHseFwAddress);
            /* Wait for HSE to initialize(read status bits) after successful update */
            while ((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0U)) == 0U)
            {
                gInstallNewHSEFwTest = FW_NOT_INSTALLED;
            }
            gInstallNewHSEFwTest = FW_INSTALLED;
            /* Get the HSE version after requesting for FW update */
            (void)HSE_GetVersion_Example(&fwversion[1]);
            testStatus |= FW_UPDATE_SUCCESS;
        }
        else if (TRUE == ActivatePassiveBlock)
        {
            /* Take backup if Active Passive switch is requested */
            if (gHseFwVersion.reserved == 1)
            {
                /* Take backup of demo app, secure boot and IVT for BSB */
                BackUp();
            }
            gsrvResponse = HSE_ActivatePassiveBlock();
            if (HSE_SRV_RSP_OK == gsrvResponse)
            {
                testStatus |= ACTIVATE_PASSIVE_BLOCK_SUCCESSFUL;
            }
        }
    }
#endif /* HSE_SPT_OTA_FIRMWARE_UPDATE */
#ifdef __cplusplus
}
#endif

/** @} */
