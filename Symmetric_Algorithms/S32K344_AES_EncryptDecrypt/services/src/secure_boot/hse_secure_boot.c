/**
 *   @file    hse_secure_boot.c
 *
 *   @brief   Secure Boot configuration.
 *   @details Contains definitions of HSE services used for configuring (Advanced/Basic) Secure Boot.
 *
 *   @addtogroup [SECURE_BOOT]
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
#include "hse_b_catalog_formatting.h"
#include "hse_host_attrs.h"
#include "hse_host_boot.h"
#include "hse_host_format_key_catalogs.h"
#include "hse_host_import_key.h"
#include "hse_host_mac.h"
#include "hse_host_sign.h"
#include "hse_mu.h"
#include "hse_demo_app_services.h"
#include "hse_host_flashSrv.h"
#include "hse_b_catalog_formatting.h"

/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

/*
 * ============================================================================
 *                             LOCAL MACROS
 * ============================================================================
 */
#define HEADER_APP_TAG 0xD5U
#define APP_HEADER_LENGTH 0x40U
#define APP_TEMP_ADDRESS 0x2100FFFFUL // 0x2100F000UL
#define CMAC_TAG_CODE_FLASH_ADDRESS 0x00454000UL
#define GMAC_TAG_CODE_FLASH_ADDRESS 0x00454020UL
#define HMAC_TAG_CODE_FLASH_ADDRESS 0x00454040UL
#define ECC_TAG1_CODE_FLASH_ADDRESS 0x00454090UL
#define ECC_TAG2_CODE_FLASH_ADDRESS 0x004540C0UL
#define RSA_TAG_CODE_FLASH_ADDRESS 0x00454100UL
#define SMR_CONFIGURED 5U
#define SALT_LENGTH (20UL)
#define SIGN_LENGTH (512UL)
    /*
     * ============================================================================
     *                               LOCAL CONSTANTS
     * ============================================================================
     */

    /*
     * ============================================================================
     *                               LOCAL VARIABLES
     * ============================================================================
     */

#ifdef HSE_SPT_BSB
    static uint8_t ReadAppDebugKey[ADKP_LENGTH] = {0U};
#endif
    // IV example (used for AES CBC and AEAD example)
    static const uint8_t gmac_iv[] =
        {0xff, 0xbc, 0x51, 0x6a, 0x8f, 0xbe, 0x61, 0x52, 0xaa, 0x42, 0x8c, 0xdd};

    static const uint32_t tag_addr[2U][5U] =
        {
            {CMAC_TAG_CODE_FLASH_ADDRESS, GMAC_TAG_CODE_FLASH_ADDRESS, HMAC_TAG_CODE_FLASH_ADDRESS, ECC_TAG1_CODE_FLASH_ADDRESS, RSA_TAG_CODE_FLASH_ADDRESS},
            {0, 0, 0, ECC_TAG2_CODE_FLASH_ADDRESS, 0}};

    static const uint32_t tag_len[] =
        {
            16U, 16U, 16U, 32U, 256U};

    /*
     * ============================================================================
     *                               GLOBAL CONSTANTS
     * ============================================================================
     */
    /*AES ECB Data*/
    const uint8_t aesEcbKey[] =
        {
            0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    const uint32_t aesEcbKeyLength = ARRAY_SIZE(aesEcbKey);
    /*
     * ============================================================================
     *                               GLOBAL VARIABLES
     * ============================================================================
     */

    hseSmrEntry_t smrEntry[10] = {0U};
    hseCrEntry_t crEntry[2U] = {0U};

    /* Data to be signed */
    uint8_t CmacTag[BITS_TO_BYTES(128)] = {0U};
    uint8_t HmacTag[BITS_TO_BYTES(256)] = {0U};
    volatile hseSrvResponse_t KeyReadSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    uint32_t signLength = (uint32_t)SIGN_LENGTH;
    uint8_t outputSig[SIGN_LENGTH] = {0};
    uint32_t signRLength = (uint32_t)SIGN_LENGTH;
    uint8_t outputSigR[BITS_TO_BYTES(SIGN_LENGTH)] = {0};
    uint32_t signSLength = (uint32_t)SIGN_LENGTH;
    uint8_t outputSigS[BITS_TO_BYTES(SIGN_LENGTH)] = {0};
    bool_t IsTagLocationErased = FALSE;
    extern volatile hseSrvResponse_t gsrvResponse;

    /*
     * ============================================================================
     *                        LOCAL FUNCTION PROTOTYPES
     * ============================================================================
     */
    static hseSrvResponse_t ConfigureSHESecureBoot(void);
#ifdef HSE_SPT_BSB
    static hseSrvResponse_t Check_DebugKey_status(void);
    static hseSrvResponse_t ConfigureBasicSecureBoot(void);
    static void HSE_SignImages(
        const uint8_t headerTag,
        const uint32_t pImg,
        const uint32_t *pImgTagAddr,
        const uint32_t CodeLength);
#endif
    static hseSrvResponse_t InstallSMR(uint8_t Index);
    static hseSrvResponse_t VerifyKeys(uint8_t Index);
    static hseSrvResponse_t ConfigureAdvancedSecureBoot(void);
    static void ConfigureSMR(hseApplHeader_t *ptr_AppHeader, uint32_t AppAddress);
    /* ============================================================================
     *                              GLOBAL FUNCTIONS
     * ============================================================================
     */

    /******************************************************************************
     * Function:    SecureBootConfiguration
     * Description: HSE secure boot configuration - ASB/BSB
     *****************************************************************************/
    hseSrvResponse_t SecureBootConfiguration(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        if ((USE_SHE_BASED_SECURE_BOOT == gRunSecureBootType) && (KEY_CATALOGS_FORMATTED == (testStatus & KEY_CATALOGS_FORMATTED)))
        {
            /* Install SHE SMR/CR entries */
            srvResponse = ConfigureSHESecureBoot();
        }
        else if ((USE_ADVANCED_SECURE_BOOT == gRunSecureBootType) && (KEY_CATALOGS_FORMATTED == (testStatus & KEY_CATALOGS_FORMATTED)))
        {
            /* Install SMR/CR entries */
            srvResponse = ConfigureAdvancedSecureBoot();
        }
        else if (USE_BASIC_SECURE_BOOT == gRunSecureBootType)
        {
/* Sign the application image using a device specific key */
#ifdef HSE_SPT_BSB
            srvResponse = ConfigureBasicSecureBoot();
#endif
        }
        return srvResponse;
    }

    void SecureBootService()
    {
        /* Always Erase NVM before Secure Boot */
        gsrvResponse = HSE_EraseKeys();
        if (HSE_SRV_RSP_OK == gsrvResponse)
        {
            /* Wait for HSE to initialize(read status bits) after installation */
            while ((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0)
                ;
            testStatus |= NVM_DATA_ERASED;
            /* Format Key Catalogs after NVM Erase */
            formatkey_srvResponse = FormatKeyCatalog();
            if (HSE_SRV_RSP_OK == formatkey_srvResponse)
            {
                testStatus |= KEY_CATALOGS_FORMATTED;
                /* Import keys for cryptographic operation and secure boot */
                ASSERT(HSE_SRV_RSP_OK == ImportSymmetricKeys());
            }
        }

        /* configure secure boot first */
        gsrvResponse = SecureBootConfiguration();
        ASSERT(HSE_SRV_RSP_OK == gsrvResponse);

        /* enable secure boot */
        gsrvResponse = UpdateIvt(SECURE_IVT);
        ASSERT(HSE_SRV_RSP_OK == gsrvResponse);
        testStatus |= SECURE_BOOT_CONFIGURATION_DONE;
    }

    /* ============================================================================
     *                              LOCAL FUNCTIONS
     * ============================================================================
     */

    /******************************************************************************
     * Function:    ConfigureAdvancedSecureBoot
     * Description: SMR/CR entries done for Advanced secure boot
     *****************************************************************************/
    static hseSrvResponse_t ConfigureAdvancedSecureBoot(void)
    {
        uint8_t smr; /* Will use SMR#1 */
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        /* S32K3xx has maximum 3 Cores */
        hseApplHeader_t *pAppHeader[HSE_APP_CORE3];
        hseAppCore_t app_core = HSE_APP_CORE0;
        /* Address where the code starts */
        uint32_t pAppCodeStart[HSE_APP_CORE10] = {0U};
        uint8_t i;

        /*Marking the tag location erased as false so that tag sector can be flashed again */
        IsTagLocationErased = FALSE;

        /* Steps for configuring secure boot is as followed.
         * Note:Single app is configure for ASB to demonstrate in this demo app.
         * The app is assumed to be flashed at BLOCK4 from where secure boot will
         * happen. App configured as below is only for secure boot purpose.
         */
        /* 1)copy IVT of length 256B from BLOCK0 section to data flash section */
        memcpy(
            (void *)&IVT,
            (const void *)BLOCK0_IVT_ADDRESS,
            0x100);

        /*
         * 2)copy start address of app from IVT in local variable.
         *   In case of SHE secure boot, SMR#0 shall be configured so app address
         *   is copied in local variable.
         */
        smr = 0U;
        pAppHeader[HSE_APP_CORE0] = (hseApplHeader_t *)IVT.pAppImg_addr_1;
        pAppCodeStart[HSE_APP_CORE0] = IVT.pAppImg_addr_1 + (uint32_t)sizeof(hseApplHeader_t);

        ConfigureSMR(pAppHeader[HSE_APP_CORE0], pAppCodeStart[HSE_APP_CORE0]);

        /* Configure CR entry */
        crEntry[app_core].coreId = app_core; /* Define the behavior for core 0 - M33_0, core 1 - M33_1 */
        for (i = 0; i < SMR_CONFIGURED; i++)
        {
            crEntry[app_core].preBootSmrMap |= authentication_type[i] << i; /* Tie it to the verification of SMR defined above (index 0) */
        }
        crEntry[app_core].pPassReset = pAppHeader[smr]->pAppStartEntry; /* Entry point - address of the first instruction */
        crEntry[app_core].crSanction = HSE_CR_SANCTION_DIS_ALL_KEYS;    /* Sanction in case SMR verification fails - keep core in reset */
        crEntry[app_core].altPreBootSmrMap = 0x0UL;                     /* Not used here - configuration in case boot fails */
        crEntry[app_core].pAltReset = pAppHeader[smr]->pAppStartEntry;  /* Alternate Reset should not be NULL or 0xFFFFFFFF */
        crEntry[app_core].startOption = HSE_CR_AUTO_START;

        /*
         * 5) Generate and verify the tag so as to confirm
         * that application is verified for secure boot
         */
        for (i = 0; i < SMR_CONFIGURED; i++)
        {
            if (TRUE == authentication_type[i])
            {
                /* generate TAG for all verification scheme. */
                srvResponse = VerifyKeys(i);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);

                /* Install SMR Entry */
                srvResponse = InstallSMR(i);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
            }
        }

        /* Install CR Entry */
        srvResponse = HSE_InstallCoreResetEntry(app_core, &(crEntry[app_core]));
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* verify if secure boot is success */
        hseAttrSmrCoreStatus_t smrCoreStatus_Get;
        srvResponse = Get_Attr(
            HSE_SMR_CORE_BOOT_STATUS_ATTR_ID,
            sizeof(hseAttrSmrCoreStatus_t),
            (void *)(&smrCoreStatus_Get));
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        
        /*Marking the tag location erased as false so that tag sector can be flashed again */
        IsTagLocationErased = FALSE;

        /*
         * 7) Now application is configured for secure boot,
         * final step is to enable secure boot by setting BOOT_SEQ = 1 in IVT
         */
        return srvResponse;
    }

    /******************************************************************************
     * Function:    ConfigureSHESecureBoot
     * Description: SMR/CR entries done for SHE secure boot
     *****************************************************************************/
    static hseSrvResponse_t ConfigureSHESecureBoot(void)
    {
        uint8_t smr; /* Will use SMR#1 */
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        hseApplHeader_t *pAppHeader[HSE_APP_CORE10];
        hseAppCore_t app_core = HSE_APP_CORE0;

        /* Steps for configuring secure boot is as followed.
         * Note:Single app is configure for ASB to demonstrate in this demo app.
         * The app is assumed to be flashed at BLOCK4 from where secure boot will
         * happen. App configured as below is only for secure boot purpose.
         */
        /* 1)copy IVT of length 256B from BLOCK0 section to data flash section */
        memcpy((void *)&IVT, (const void *)BLOCK0_IVT_ADDRESS, 0x100);

        /*
         * 2)copy start address of app from IVT in local variable.
         *   In case of SHE secure boot, SMR#0 shall be configured so app address
         *   is copied in local variable.
         */
        smr = 0U;
        pAppHeader[HSE_APP_CORE0] = (hseApplHeader_t *)IVT.pAppImg_addr_1;

        smrEntry[smr].configFlags = HSE_SMR_CFG_FLAG_INSTALL_AUTH; /* Indicate that verification should be done on provided signature */
        smrEntry[smr].pSmrDest = 0U;                               /* destination address shall be NULL for flashed based devices */
        smrEntry[smr].checkPeriod = 0U;
        smrEntry[smr].pSmrSrc = pAppHeader[smr]->pAppStartEntry; /* Start of APP code */
        smrEntry[smr].smrSize = 1024UL;                          /* Length of APP code */
        smrEntry[smr].authKeyHandle = HSE_DEMO_NVM_SHE_AES128_BOOT_KEY;
        smrEntry[smr].authScheme.macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
        smrEntry[smr].authScheme.macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
        smrEntry[smr].pInstAuthTag[0] = (uint32_t)NULL; /* NR for SHE */
        smrEntry[smr].pInstAuthTag[1] = (uint32_t)NULL; /* NR for SHE */

        /* Configure CR entry */
        crEntry[app_core].coreId = app_core;                            /* Define the behavior for core 0 - M33_0, core 1 - M33_1 */
        crEntry[app_core].preBootSmrMap = HSE_KF_SMR_0;                 /* Tie it to the verification of SMR defined above (index 0) */
        crEntry[app_core].pPassReset = pAppHeader[smr]->pAppStartEntry; /* Entry point - address of the first instruction */
        crEntry[app_core].crSanction = HSE_CR_SANCTION_DIS_INDIV_KEYS;    /* Sanction in case SMR verification fails - keep core in reset */
        crEntry[app_core].altPreBootSmrMap = 0x0UL;                     /* Not used here - configuration in case boot fails */
        crEntry[app_core].pAltReset = pAppHeader[smr]->pAppStartEntry;
        crEntry[app_core].startOption = HSE_CR_AUTO_START;

        /* import keys and Install SMR Entry */
        srvResponse = HSE_InstallSmrEntry(
            smr,
            (const hseSmrEntry_t *)&smrEntry[smr],
            (const uint8_t *)smrEntry[smr].pSmrSrc,
            smrEntry[smr].smrSize,
            (const uint8_t *)NULL,
            (const uint8_t *)NULL,
            0U,
            0U);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* Install CR Entry */
        srvResponse = HSE_InstallCoreResetEntry(smr, &(crEntry[app_core]));
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* verify if secure boot is success */
        hseAttrSmrCoreStatus_t smrCoreStatus_Get;
        srvResponse = Get_Attr(
            HSE_SMR_CORE_BOOT_STATUS_ATTR_ID,
            sizeof(hseAttrSmrCoreStatus_t),
            (void *)(&smrCoreStatus_Get));
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /*
         * 7) Now application is configured for secure boot,
         * final step is to enable secure boot by setting BOOT_SEQ = 1 in IVT
         */
        return srvResponse;
    }

    /******************************************************************************
     * Function:     VerifyKeys
     * Description:  Verify imported keys for Advanced secure boot for all SMR's
     ******************************************************************************/
    static hseSrvResponse_t VerifyKeys(uint8_t Index)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint32_t outputLen = 0U;
        Fls_CheckStatusType write_status = FLS_JOB_FAILED;
        hseSGTOption_t optionSGT = HSE_SGT_OPTION_NONE;

        /* Erasing Tag Locations so new Tags can be programmed here. */
        if (TRUE != IsTagLocationErased)
        {
            IsTagLocationErased = TRUE;
            ASSERT(FLS_JOB_OK == HostFlash_Erase(HOST_BLOCK0_CODE_MEMORY, CMAC_TAG_CODE_FLASH_ADDRESS, 1U));
        }
  
        /* flash cmac in code flash */
        outputLen = sizeof(CmacTag);
        if (0U == Index) /* AES-CMAC */
        {
            /* Generate CMAC tag */
            srvResponse = AesCmacGenerate(HSE_DEMO_NVM_AES128_PROVISION_KEY, smrEntry[Index].smrSize, (const uint8_t *)smrEntry[Index].pSmrSrc, &outputLen, CmacTag, 0U);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)CMAC_TAG_CODE_FLASH_ADDRESS,
                                             (uint8_t *)CmacTag,
                                             sizeof(CmacTag));

            ASSERT(FLS_JOB_OK == write_status);

            /* verify tag */
            srvResponse = AesCmacVerify(HSE_DEMO_NVM_AES128_BOOT_KEY,
                                        smrEntry[Index].smrSize,
                                        (const uint8_t *)smrEntry[Index].pSmrSrc,
                                        &outputLen,
                                        (const uint8 *)CMAC_TAG_CODE_FLASH_ADDRESS,
                                        0U);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);
        }
        else if (1U == Index) /* AES-GMAC */
        {
            srvResponse = AesGmacGenerate(HSE_DEMO_NVM_AES128_PROVISION_KEY,
                                          sizeof(gmac_iv),
                                          gmac_iv,
                                          smrEntry[Index].smrSize,
                                          (const uint8_t *)smrEntry[Index].pSmrSrc,
                                          &outputLen,
                                          CmacTag,
                                          HSE_SGT_OPTION_NONE);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)GMAC_TAG_CODE_FLASH_ADDRESS,
                                             (uint8_t *)CmacTag,
                                             sizeof(CmacTag));

            ASSERT(FLS_JOB_OK == write_status);

            /* verify tag */
            srvResponse = AesGmacVerify(HSE_DEMO_NVM_AES128_BOOT_KEY,
                                        sizeof(gmac_iv),
                                        gmac_iv,
                                        smrEntry[Index].smrSize,
                                        (const uint8_t *)smrEntry[Index].pSmrSrc,
                                        &outputLen,
                                        (const uint8 *)GMAC_TAG_CODE_FLASH_ADDRESS,
                                        optionSGT);

            ASSERT(HSE_SRV_RSP_OK == srvResponse);
        }
        else if (2U == Index) /* HMAC */
        {
            outputLen = sizeof(HmacTag);
            srvResponse = HmacGenerate(HSE_DEMO_NVM_HMAC_KEY0,
                                       HSE_HASH_ALGO_SHA2_256,
                                       smrEntry[Index].smrSize,
                                       (const uint8_t *)smrEntry[Index].pSmrSrc,
                                       &outputLen,
                                       HmacTag,
                                       optionSGT);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)HMAC_TAG_CODE_FLASH_ADDRESS,
                                             (uint8_t *)HmacTag,
                                             sizeof(HmacTag));

            ASSERT(FLS_JOB_OK == write_status);

            /* verify tag */
            srvResponse = HmacVerify(HSE_DEMO_NVM_HMAC_KEY1,
                                     HSE_HASH_ALGO_SHA2_256,
                                     smrEntry[Index].smrSize,
                                     (const uint8_t *)smrEntry[Index].pSmrSrc,
                                     &outputLen,
                                     (const uint8 *)HMAC_TAG_CODE_FLASH_ADDRESS);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);
        }

        else if (3U == Index) /* ECC */
        {
            srvResponse = EcdsaSign(HSE_DEMO_NVM_ECC_KEY_HANDLE,
                                    HSE_HASH_ALGO_SHA2_256,
                                    smrEntry[Index].smrSize,
                                    (const uint8_t *)smrEntry[Index].pSmrSrc,
                                    FALSE,
                                    0U,
                                    &signRLength,
                                    outputSigR,
                                    &signSLength,
                                    outputSigS);

            ASSERT(HSE_SRV_RSP_OK == srvResponse);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)ECC_TAG1_CODE_FLASH_ADDRESS,
                                             (uint8_t *)outputSigR,
                                             signRLength);

            ASSERT(FLS_JOB_OK == write_status);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)ECC_TAG2_CODE_FLASH_ADDRESS,
                                             (uint8_t *)outputSigS,
                                             signSLength);

            ASSERT(FLS_JOB_OK == write_status);

            /* Program */
            srvResponse = EcdsaVerify(
                HSE_DEMO_NVM_ECC_KEY_HANDLE_PUBLIC,
                HSE_HASH_ALGO_SHA2_256,
                smrEntry[Index].smrSize,
                (const uint8_t *)smrEntry[Index].pSmrSrc,
                FALSE,
                0U,
                &signRLength,
                (const uint8_t *)ECC_TAG1_CODE_FLASH_ADDRESS,
                &signSLength,
                (const uint8_t *)(ECC_TAG2_CODE_FLASH_ADDRESS));

            ASSERT(HSE_SRV_RSP_OK == srvResponse);
        }
        else
        {
            /**** RSA ****/
            srvResponse = RsaPssSignSrv(
                HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0,
                SALT_LENGTH,
                HSE_HASH_ALGO_SHA2_256,
                smrEntry[Index].smrSize,
                (const uint8_t *)smrEntry[Index].pSmrSrc,
                FALSE,
                0U,
                &signLength,
                outputSig);

            ASSERT(HSE_SRV_RSP_OK == srvResponse);

            write_status = HostFlash_Program(HOST_BLOCK0_CODE_MEMORY,
                                             (uint32_t)RSA_TAG_CODE_FLASH_ADDRESS,
                                             (uint8_t *)outputSig,
                                             SIGN_LENGTH);

            ASSERT(FLS_JOB_OK == write_status);

            srvResponse = RsaPssVerSrv(
                HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE0,
                SALT_LENGTH,
                HSE_HASH_ALGO_SHA2_256,
                smrEntry[Index].smrSize,
                (const uint8_t *)smrEntry[Index].pSmrSrc,
                FALSE,
                0U,
                &signLength,
                (const uint8_t *)RSA_TAG_CODE_FLASH_ADDRESS);

            ASSERT(HSE_SRV_RSP_OK == srvResponse);
        }
        return srvResponse;
    }

    /******************************************************************************
     * Function:     InstallSMR
     * Description:  Installs SMR for Advanced secure boot and SHE secure boot
     ******************************************************************************/
    static hseSrvResponse_t InstallSMR(uint8_t Index)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

        /* 6) Finally, install SMR and CR entry and verify SMR install */
        srvResponse = HSE_InstallSmrEntry((Index),
                                          (const hseSmrEntry_t *)&smrEntry[Index],
                                          (const uint8_t *)smrEntry[Index].pSmrSrc,
                                          smrEntry[Index].smrSize,
                                          (const uint8 *)tag_addr[0][Index],
                                          (const uint8 *)tag_addr[1][Index],
                                          tag_len[Index],
                                          tag_len[Index]);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* verify SMR entry - SMR verify is not allowed for SHE boot,
            only on next cycle could it be verified if BOOT_SEQ=0 */
        srvResponse = smrVerifyTest(Index);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        return srvResponse;
    }

/******************************************************************************
 * Function:    Check_DebugKey_status
 * Description: provisions device specific key for basic secure boot
 *****************************************************************************/
#ifdef HSE_SPT_BSB
    static hseSrvResponse_t Check_DebugKey_status(void)
    {
        /*Check if ADKP is already programmed, if yes, then NOT_ALLOWED response is
         * expected from HSE else ADKP hash will be read
         */
        return HSE_ReadAdkp(&ReadAppDebugKey[0U]);
    }
#endif
/******************************************************************************
 * Function:     ConfigureBasicSecureBoot
 * Description:  Generates APP TAG for BSB,
 *               Authenticate the application using a device specific key
 *****************************************************************************/
#ifdef HSE_SPT_BSB
    static hseSrvResponse_t ConfigureBasicSecureBoot(void)
    {
        /* RAM address for GMAC */
        uint32_t temp_addr_of_app_image[32] = {0xFF};
        KeyReadSrvResponse = Check_DebugKey_status();
        if (HSE_SRV_RSP_OK != KeyReadSrvResponse)
        {
            goto exit;
        }
        /*Marking the tag location erased as false so that tag sector can be flashed again */
        IsTagLocationErased = FALSE;
        
        memcpy(&IVT, (const void *)BLOCK0_IVT_ADDRESS, 0x100);
        /* Sign application using BootData Sign/Verify services */
        HSE_SignImages(
            HEADER_APP_TAG,
            IVT.pAppImg_addr_1,
            temp_addr_of_app_image,
            (((hseApplHeader_t *)IVT.pAppImg_addr_1)->codeLength));

        /*Marking the tag location erased as false so that tag sector can be flashed again */
        IsTagLocationErased = FALSE;
    exit:
        return KeyReadSrvResponse;
    }
#endif

/******************************************************************************
 * Function:     HSE_SignImages
 * Description:  Helper for signing and verifying boot images(App in this case)
 ******************************************************************************/
#ifdef HSE_SPT_BSB
    static void HSE_SignImages(
        const uint8_t headerTag,
        const uint32_t pImg,
        const uint32_t *pImgTagAddr,
        const uint32_t CodeLength)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        /* Check if PRIMARY image is set */
        if (ADDR_NOT_NULL(pImg))
        {
            uint8_t header_tag = *(volatile uint8_t *)pImg;
            /* Header tag sanity check */
            ASSERT(headerTag == header_tag);
            /* Erasing Tag Locations so new Tags can be programmed here. */
            if (TRUE != IsTagLocationErased)
            {
                IsTagLocationErased = TRUE;
                ASSERT(FLS_JOB_OK == HostFlash_Erase(HOST_BLOCK0_CODE_MEMORY, (uint32_t)(pImg + APP_HEADER_LENGTH + CodeLength), BOOT_IMG_TAG_LEN));
            }
            
            /* Sign the primary image - 16 bytes MAC */
            srvResponse = HSE_SignBootImage(
                (uint8_t *)pImg,
                BOOT_IMG_TAG_LEN,
                (uint8_t *)pImgTagAddr);
            ASSERT(HSE_SRV_RSP_OK == srvResponse);
            /* write IVT with GMAC appended at the offset 0xF0 of IVT location */
            {
                ASSERT(HostFlash_Program(
                           HOST_BLOCK0_CODE_MEMORY,
                           (uint32_t)(pImg + APP_HEADER_LENGTH + CodeLength),
                           (uint8_t *)pImgTagAddr,
                           BOOT_IMG_TAG_LEN + FLASH_SECTOR_SIZE_ALIGNMENT) == FLS_JOB_OK);
            }
            /* Verify the Tag was generated and programmed correctly */
            if (HEADER_APP_TAG == headerTag)
            {
                srvResponse = HSE_VerifyBootImage((uint8_t *)pImg);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
            }
        }
    }
#endif

    /******************************************************************************
     * Function:     UpdateIvt
     * Description:  Enable Secure Boot by signing IVT and by setting BOOT_SEQ bit
     ******************************************************************************/
    hseSrvResponse_t UpdateIvt(ivt_type_t IvtType)
    {
        memcpy((void *)&IVT, (void *)BLOCK0_IVT_ADDRESS, 0xEF);
        /* erase IVT location */
        ASSERT(HostFlash_Erase(
                   HOST_BLOCK0_CODE_MEMORY,
                   BLOCK0_IVT_ADDRESS,
                   1U) == FLS_JOB_OK);
        if (NON_SECURE_IVT == IvtType)
        {
            /*copy IVT from 0x420000 location to block 0 ivt address */
            ASSERT(HostFlash_Program(
                       HOST_BLOCK0_CODE_MEMORY,
                       (uint32_t)BLOCK0_IVT_ADDRESS,
                       (uint8_t *)(BLOCK0_IVT_ADDRESS + NON_SECURE_IVT_BACKUPADDR_OFFSET),
                       (uint32_t)0x100U) == FLS_JOB_OK);
        }
        else
        {
            if (MU_REG_READ64(UTEST_BASE_ADDRESS + IVT_GMAC_FLAG_OFFSET) == UINT64_MAX_VAL)
            {
                IVT.bootCfgWord |= IVT_BOOT_CFG_WORD_BOOT_SEQ;
                /* update IVT */
                ASSERT(HostFlash_Program(
                           HOST_BLOCK0_CODE_MEMORY,
                           (uint32_t)BLOCK0_IVT_ADDRESS,
                           (uint8_t *)&IVT,
                           (uint32_t)0x100U) == FLS_JOB_OK);
            }
            else
            {
                /*copy IVT from 0x402200 location to block 0 ivt address */
                ASSERT(HostFlash_Program(
                           HOST_BLOCK0_CODE_MEMORY,
                           (uint32_t)BLOCK0_IVT_ADDRESS,
                           (uint8_t *)(BLOCK0_IVT_ADDRESS + SECURE_IVT_BACKUPADDR_OFFSET),
                           (uint32_t)0x100U) == FLS_JOB_OK);
            }
        }
        return HSE_SRV_RSP_OK;
    }

    static void ConfigureSMR(hseApplHeader_t *ptr_AppHeader, uint32_t AppAddress)
    {
        uint8_t i;
        for (i = 0; i < 5; i++)
        {
            if (TRUE == authentication_type[i])
            {
                smrEntry[i].configFlags = HSE_SMR_CFG_FLAG_INSTALL_AUTH; /* Indicate that verification should be done on provided signature */
                smrEntry[i].pSmrDest = 0U;                               /* destination address shall be NULL for flashed based devices */
                smrEntry[i].checkPeriod = 0U;
                if (0U == i) /* AES-CMAC */
                {
                    smrEntry[i].pSmrSrc = AppAddress; /* Start of APP code */
                    smrEntry[i].smrSize = 1024UL;     /* Length of APP code */
                    smrEntry[i].authKeyHandle = HSE_DEMO_NVM_AES128_BOOT_KEY;
                    smrEntry[i].authScheme.macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
                    smrEntry[i].authScheme.macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
                    smrEntry[i].pInstAuthTag[0] = CMAC_TAG_CODE_FLASH_ADDRESS; /* signature tag address */
                    smrEntry[i].pInstAuthTag[1] = (uint32_t)NULL;              /* In this example, AES keys is used hence 2nd tag address is NULL */
                }
                else if (1U == i) /* AES-GMAC */
                {
                    smrEntry[i].pSmrSrc = AppAddress; /* Start of APP code */
                    smrEntry[i].smrSize = 1024UL;     /* Length of APP code */
                    smrEntry[i].authKeyHandle = HSE_DEMO_NVM_AES128_BOOT_KEY;
                    smrEntry[i].authScheme.macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
                    smrEntry[i].authScheme.macScheme.sch.gmac.pIV = (HOST_ADDR)gmac_iv;
                    smrEntry[i].authScheme.macScheme.sch.gmac.ivLength = sizeof(gmac_iv);
                    smrEntry[i].pInstAuthTag[0] = GMAC_TAG_CODE_FLASH_ADDRESS; /* signature tag address */
                    smrEntry[i].pInstAuthTag[1] = (uint32_t)NULL;              /* In this example, AES keys is used hence 2nd tag address is NULL */
                }
                else if (2U == i) /* HMAC */
                {
                    smrEntry[i].pSmrSrc = AppAddress; /* Start of APP code */
                    smrEntry[i].smrSize = 1024UL;     /* Length of APP code */
                    smrEntry[i].authKeyHandle = HSE_DEMO_NVM_HMAC_KEY1;
                    smrEntry[i].authScheme.macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
                    smrEntry[i].authScheme.macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
                    smrEntry[i].pInstAuthTag[0] = HMAC_TAG_CODE_FLASH_ADDRESS; /* signature tag address */
                    smrEntry[i].pInstAuthTag[1] = (uint32_t)NULL;              /* In this example, AES keys is used hence 2nd tag address is NULL */
                }
                else if (3U == i) /* ECC */
                {
                    smrEntry[i].pSmrSrc = AppAddress; /* Start of APP code */
                    smrEntry[i].smrSize = 1024UL;     /* Length of APP code */
                    smrEntry[i].authKeyHandle = HSE_DEMO_NVM_ECC_KEY_HANDLE_PUBLIC;
                    smrEntry[i].authScheme.sigScheme.signSch = HSE_SIGN_ECDSA;
                    smrEntry[i].authScheme.sigScheme.sch.ecdsa.hashAlgo = HSE_HASH_ALGO_SHA2_256;
                    smrEntry[i].pInstAuthTag[0] = ECC_TAG1_CODE_FLASH_ADDRESS; /* signature tag address */
                    smrEntry[i].pInstAuthTag[1] = ECC_TAG2_CODE_FLASH_ADDRESS; /* signature tag address */
                }
                else /* RSA */
                {
                    smrEntry[i].pSmrSrc = AppAddress; /* Start of APP code */
                    smrEntry[i].smrSize = 1024UL;     /* Length of APP code */
                    smrEntry[i].authKeyHandle = HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE0;
                    smrEntry[i].authScheme.sigScheme.signSch = HSE_SIGN_RSASSA_PSS;
                    smrEntry[i].authScheme.sigScheme.sch.rsaPss.hashAlgo = HSE_HASH_ALGO_SHA2_256;
                    smrEntry[i].authScheme.sigScheme.sch.rsaPss.saltLength = SALT_LENGTH;
                    smrEntry[i].pInstAuthTag[0] = RSA_TAG_CODE_FLASH_ADDRESS; /* signature tag address */
                    smrEntry[i].pInstAuthTag[1] = (uint32_t)NULL;             /* In this example, AES keys is used hence 2nd tag address is NULL */
                }
            }
        }
    }
#ifdef __cplusplus
}
#endif

/** @} */
