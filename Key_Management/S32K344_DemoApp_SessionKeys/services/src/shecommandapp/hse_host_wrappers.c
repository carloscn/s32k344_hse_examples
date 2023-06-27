/**
    @file        host_wrappers.c
    @version     1.0.0

    @brief       Wrapper and helper functions
    @details     This file contains Wrapper and helper functions.

    This file contains sample code only. It is not part of the production code deliverables.
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

#include "hse_she_api.h"
#include "hse_interface.h"
#include "hse_host.h"
#include "string.h"
#include "hse_memory_update_protocol.h"
#include "hse_host_test.h"
#include "hse_she_commands.h"
#include "hse_host_wrappers.h"
#include "hse_default_config.h"
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SHE_WRITE_PROT_FLAG (1U << 5U)
#define SHE_BOOT_PROT_FLAG (1U << 4U)
#define SHE_DEBUG_PROT_FLAG (1U << 3U)
#define SHE_KEY_USAGE_FLAG (1U << 2U)
#define SHE_WILDCARD_FLAG (1U << 1U)
#define SHE_VERIFY_ONLY_FLAG (1U << 0U)

    /*==================================================================================================
                                          FILE VERSION CHECKS
    ==================================================================================================*/

    /*==================================================================================================
                              LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL CONSTANTS
    ==================================================================================================*/
    uint8_t MASTER_ECU_KEY[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
#define MASTER_ECU_KEY_ID 0x01
#define NVM_KEY1_ID 0x04
#define NVM_KEY2_ID 0x05
#define NVM_KEY3_ID 0x06
#define NVM_KEY4_ID 0x07

    /*==================================================================================================
                                           LOCAL VARIABLES
    ==================================================================================================*/

    /*==================================================================================================
                                           GLOBAL CONSTANTS
    ==================================================================================================*/

    /*==================================================================================================
                                           GLOBAL VARIABLES
    ==================================================================================================*/

#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
    const hseKeyGroupCfgEntry_t SHEAppNvmCatalog[] = {HSE_SHE_NVM_KEY_CATALOG_CFG};
    const hseKeyGroupCfgEntry_t SHEAppRamCatalog[] = {HSE_SHE_RAM_KEY_CATALOG_CFG};
#endif

    /*==================================================================================================
                                       LOCAL FUNCTION PROTOTYPES
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL FUNCTIONS
    ==================================================================================================*/

    /*==================================================================================================
                                           GLOBAL FUNCTIONS
    ==================================================================================================*/

    /*******************************************************************************
     * Function:    SheLoadMasterEcuKey
     * Description: Loads the Master ECU Key, assumption is that Master ECU Key is currently empty
     ******************************************************************************/
    hseSrvResponse_t SheLoadMasterEcuKey(void)
    {
        hseSrvResponse_t hseResponse;
        MemoryUpdate_t MemUpdate;
        /*UID’ is the wildcard value 0*/
        uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*initial value of Master Ecu Key*/
        uint8_t MASTER_ECU_KEY_EMPTY[AES_BLOCK_SIZE] =
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
        memcpy(MemUpdate.KeyNew, MASTER_ECU_KEY, ARRAY_SIZE(MemUpdate.KeyNew));
        memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY_EMPTY, ARRAY_SIZE(MemUpdate.AuthKey));
        /*The key ID for the key to be updated i.e. MasterEcuKey*/
        MemUpdate.KeyId = MASTER_ECU_KEY_ID;
        /*The key ID for the Auth Key i.e. MasterEcuKey as Master EcuKey can Authenticate the same*/
        MemUpdate.AuthId = MASTER_ECU_KEY_ID;
        /*CID’*/
        MemUpdate.count_val = 0x01;
        MemUpdate.sheGroupId = 0x00;
        /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
        MemUpdate.flag_val = 0x00;
        hseResponse = MemoryUpdateProtocol(&MemUpdate);
        return hseResponse;
    }

    /*******************************************************************************
     * Function:    SheLoadNVMKey_ECB
     * Description: Loads the NVM Key1 for ECB Encryption/Decryption, No flag is set on the key
     ******************************************************************************/
    hseSrvResponse_t SheLoadNVMKey_ECB(void)
    {
        hseSrvResponse_t hseResponse;
        MemoryUpdate_t MemUpdate;
        /*UID’ is the wildcard value 0*/
        uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*The new key value to be updated*/
        uint8_t t_KeyNew[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

        memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
        memcpy(MemUpdate.KeyNew, t_KeyNew, ARRAY_SIZE(MemUpdate.KeyNew));
        memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY, ARRAY_SIZE(MemUpdate.AuthKey));

        /*The key ID for the key to be loaded.*/
        MemUpdate.KeyId = NVM_KEY1_ID;
        /*
         * The key ID for the Auth Key i.e. Master ECU Key in this case
         *
         * */
        MemUpdate.AuthId = MASTER_ECU_KEY_ID;
        /*CID’*/
        MemUpdate.count_val = 0x01;
        MemUpdate.sheGroupId = 0x00;
        /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
        MemUpdate.flag_val = 0x00;
        hseResponse = MemoryUpdateProtocol(&MemUpdate);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
        {
            goto exit;
        }
        return hseResponse;
    exit:
        return hseResponse;
    }

    /*******************************************************************************
     * Function:    SheLoadNVMKey_CBC
     * Description: Loads the SHE NVM Key2 for CBC Encryption/Decryption, No flag is set on the key
     ******************************************************************************/
    hseSrvResponse_t SheLoadNVMKey_CBC(void)
    {
        hseSrvResponse_t hseResponse;
        MemoryUpdate_t MemUpdate;
        /*UID’ is the wildcard value 0*/
        uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*The new key value to be updated*/
        uint8_t t_KeyNew[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

        memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
        memcpy(MemUpdate.KeyNew, t_KeyNew, ARRAY_SIZE(MemUpdate.KeyNew));
        memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY, ARRAY_SIZE(MemUpdate.AuthKey));

        /* The key ID for the key to be loaded */
        MemUpdate.KeyId = NVM_KEY2_ID;
        /*
         * The key ID for the Auth Key i.e. corresponding NVM Key. Since NVM key is already loaded with
         * some value , it can authenticate the corresponding keys
         *
         * */
        MemUpdate.AuthId = MASTER_ECU_KEY_ID;
        /*CID’*/
        MemUpdate.count_val = 0x01;
        MemUpdate.sheGroupId = 0x00;
        /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
        MemUpdate.flag_val = 0x00;
        hseResponse = MemoryUpdateProtocol(&MemUpdate);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
        {
            return hseResponse;
        }
        return hseResponse;
    }
    /*******************************************************************************
     * Function:    SheLoadNVMKey_CMAC
     * Description: Loads the SHE NVM Key3 for CMAC Generation/Verification, KEY_USAGE_FLAG is set for this Key
     *              to enable CMAC Generation/Verification using this key
     ******************************************************************************/
    hseSrvResponse_t SheLoadNVMKey_CMAC(void)
    {
        hseSrvResponse_t hseResponse;
        /*int resp;*/
        MemoryUpdate_t MemUpdate;
        /*UID’ is the wildcard value 0*/
        uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*The new key value to be updated*/
        uint8_t t_KeyNew[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

        memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
        memcpy(MemUpdate.KeyNew, t_KeyNew, ARRAY_SIZE(MemUpdate.KeyNew));
        memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY, ARRAY_SIZE(MemUpdate.AuthKey));

        /*The key ID for the key to be loaded.*/
        MemUpdate.KeyId = NVM_KEY3_ID;
        /*
         * Auth Key ID */
        MemUpdate.AuthId = MASTER_ECU_KEY_ID;
        /*CID’*/
        MemUpdate.count_val = 0x01;
        MemUpdate.sheGroupId = 0x00;
        /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
        MemUpdate.flag_val = SHE_KEY_USAGE_FLAG;
        hseResponse = MemoryUpdateProtocol(&MemUpdate);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
        {
            return hseResponse;
        }
        return hseResponse;
    }
    /*******************************************************************************
     * Function:    EraseAllSheKeys
     * Description: This function erases all SHE Keys.
     ******************************************************************************/
    hseSrvResponse_t EraseAllSheKeys(void)
    {
        hseSrvResponse_t hseResponse;
        /* Run Debug Challenge and Authentication Command
         * In this step Authentication is performed to ensure successful Erase
         */
        hseResponse = cmd_debug_chal_auth();
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
            return hseResponse;
        /* Check key erase operations - after SYS_AUTH with SHE key */
        /* Erase all NVM KEYS assigned to MU Interface on which the erase service is sent*/
        hseResponse = EraseKeyReq(HSE_INVALID_KEY_HANDLE, HSE_ERASE_ALL_NVM_KEYS_ON_MU_IF);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
            return hseResponse;
        return hseResponse;
    }

    /******************************************************************************/
    hseSrvResponse_t SheLoadBootMacKey(void)
    {
        hseSrvResponse_t hseResponse;
        MemoryUpdate_t MemUpdate;
        /*UID’ is the wildcard value 0*/
        uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /*The new key value to be updated*/
        uint8_t t_KeyNew_1[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
        /*initial value of Master Ecu Key*/
        memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
        memcpy(MemUpdate.KeyNew, t_KeyNew_1, ARRAY_SIZE(MemUpdate.KeyNew));
        memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY, ARRAY_SIZE(MemUpdate.AuthKey));
        /*The key ID for the key to be updated i.e. MasterEcuKey*/
        MemUpdate.KeyId = 0x02;
        /*The key ID for the Auth Key i.e. MasterEcuKey as Master EcuKey can Authenticate the same*/
        MemUpdate.AuthId = MASTER_ECU_KEY_ID;
        /*CID’*/
        MemUpdate.count_val = 0x01;
        MemUpdate.sheGroupId = 0x00;
        /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
        MemUpdate.flag_val = 0x00;
        hseResponse = MemoryUpdateProtocol(&MemUpdate);
        // ASSERT( HSE_SRV_RSP_OK==hseResponse);
        return hseResponse;
    }

    /*******************************************************************************
     * Function:    Load_Relevant_Keys
     * Description: Loads the SHE Keys to be used to verify different SHE commands
     ******************************************************************************/
    hseSrvResponse_t Load_Relevant_She_Keys(void)
    {
        hseSrvResponse_t srvResponse;
        /*
         * 1. Load the Master ECU Key, which will be later used to authenticate the other keys
         */
        srvResponse = SheLoadMasterEcuKey();
        /*
         * If the response is not OK, it means Master ECU Key is already loaded
         * If so, perform Erase Keys and try again Loading the Master ECU Key
         */
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            srvResponse = EraseAllSheKeys();
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
            srvResponse = SheLoadMasterEcuKey();
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }

        srvResponse = SheLoadBootMacKey();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
        /* Load NVM Key1 for ECB Encrption/Decryption */
        srvResponse = SheLoadNVMKey_ECB();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
        /* Load NVM Key2 for CBC Encrption/Decryption */
        srvResponse = SheLoadNVMKey_CBC();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
        /* Load NVM Key3 for CMAC Generation/Verification */
        srvResponse = SheLoadNVMKey_CMAC();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
        return srvResponse;
    exit:
        return srvResponse;
    }

    /*******************************************************************************
     * Function:    SysAuth_User
     * Description: This function is a wrapper for sneding Sys Authorisation Request for User
     ******************************************************************************/
    hseSrvResponse_t SysAuth_User(void)
    {
        /* Switch to IN_FIELD User */
        return SysAuthorizationReq(HSE_SYS_AUTH_ALL, HSE_RIGHTS_USER, 0UL, NULL, NULL);
    }

    /*******************************************************************************
     * Function:    HostKdf
     * Description: Miyaguchi Preneel Key generation Wrapper functions
     ******************************************************************************/
    hseSrvResponse_t HostKdf(uint32_t inputLength, const uint8_t *pInput, uint32_t *pHashLength,
                             uint8_t *pHash, hseSGTOption_t inputSgtType)
    {
        hseHashAlgo_t hashAlgo = HSE_HASH_ALGO_MP;
        return Hash_Req(HSE_ACCESS_MODE_ONE_PASS, hashAlgo, 0,
                        inputLength, pInput, pHashLength, pHash, inputSgtType);
    }

    /*******************************************************************************
     * Function:    HSE_ConfigKeyCatalogs
     * Description: Formatting the Key Catalogs (where KeyCatalogue formatting is available)
     ******************************************************************************/
    hseSrvResponse_t HSEConfigKeyCatalogs(void)
    {
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[0U][1U];
        hseFormatKeyCatalogsSrv_t *pFormatKeyCatalogsReq = &pHseSrvDesc->hseSrv.formatKeyCatalogsReq;
        hseSrvResponse_t status;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        // Use the same default catalog configurations to re-format the NVM and RAM catalogs
        pHseSrvDesc->srvId = HSE_SRV_ID_FORMAT_KEY_CATALOGS;
        pFormatKeyCatalogsReq->pNvmKeyCatalogCfg = (HOST_ADDR)SHEAppNvmCatalog;
        pFormatKeyCatalogsReq->pRamKeyCatalogCfg = (HOST_ADDR)SHEAppRamCatalog;

        status = HSE_Send(0U, 1U, gSyncTxOption, pHseSrvDesc);

        return status;
#else

    return HSE_SRV_RSP_NOT_SUPPORTED;

#endif
    }
