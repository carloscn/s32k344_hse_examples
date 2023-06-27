/**
 *   @file    hse_config.c
 *
 *   @brief   Example of HSE configuration
 *   @details Example of services used for configuring HSE persistent attributes and key catalogs.
 *
 *   @addtogroup [HSE_CONFIG]
 *   @{
 */

/*=============================================================================
*
*   Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
=============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

/*=============================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=============================================================================*/
#include "hse_demo_app_services.h"
#include "hse_host_attrs.h"
#include "hse_host_boot.h"
#include "hse_host_format_key_catalogs.h"
#include "hse_host_import_key.h"
#include "hse_host_mac.h"
#include "hse_mu.h"
#include "hse_srv_attr.h"
#include "hse_host.h"
#include "hse_host_ecc.h"
#include "hse_host_sign.h"
#include "hse_she_commands.h"
#include "hse_host_wrappers.h"
#include "hse_b_catalog_formatting.h"
#include <string.h>

    /*=============================================================================
     *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
     * ==========================================================================*/

    /*=============================================================================
     *                                       LOCAL MACROS
     * ==========================================================================*/

    /*=============================================================================
     *                                      LOCAL CONSTANTS
     * ==========================================================================*/

    /*============================================================================
     *                                      LOCAL VARIABLES
     * =========================================================================*/

    /*=============================================================================
     *                                      GLOBAL CONSTANTS
     * ==========================================================================*/

    /*=============================================================================
     *                                      GLOBAL VARIABLES
     * ==========================================================================*/
    hseKeyHandle_t aesCmacKeyHandle = HSE_INVALID_KEY_HANDLE;
    hseKeyHandle_t AesNVMKeyHandle = HSE_DEMO_NVM_AES256_KEY2;
    /*=============================================================================
     *                                   LOCAL FUNCTION PROTOTYPES
     * ==========================================================================*/
    hseSrvResponse_t HSE_ConfigKeyCatalogs(void);
    /*=============================================================================
     *                                       LOCAL FUNCTIONS
     * ==========================================================================*/

    /*
        Function: HSE_ConfigKeyCatalogs
        @brief    Format key catalogs
        @detailed Example of key catalog for SHE and SB format HSE service
                  which defines the layout of the Key store memory space:
                  (number of slots, number of keys/slot, key types,
                  usage/MU and ownership).
                  Key catalogs format will be part of the SYS_IMG
                  that provides persistency of HSE configuration
     */
    hseSrvResponse_t HSE_ConfigKeyCatalogs(void)
    {
        hseSrvResponse_t srvResponse;
        // Format HSE key catalogs
        srvResponse = FormatKeyCatalogs_();
        return srvResponse;
    }

    /*
        Function: HSE_InstallNvmKeys
        @brief    NVM keys installation example
        @detailed Example of key catalog format HSE service which defines the
                  layout of the Key store memory space:
                  (number of slots, number of keys/slot, key types, usage/MU
                  and ownership).NVM keys will be part of the SYS_IMG.
     */
    static hseSrvResponse_t HSE_InstallNvmKeys(void)
    {
        hseSrvResponse_t srvResponse;
        hseKeyHandle_t aesNVMAuthKeyHandle = HSE_DEMO_NVM_AES128_AUTHORIZATION_KEY;
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
         If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(gAES128AuthorizationKey, &aesNVMAuthKeyHandle);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /* Import Authorization key */
            srvResponse = ImportPlainSymKeyReq(
                HSE_DEMO_NVM_AES128_AUTHORIZATION_KEY,
                HSE_KEY_TYPE_AES,
                (
                    HSE_KF_USAGE_AUTHORIZATION |
                    HSE_KF_USAGE_VERIFY),
                ARRAY_SIZE(gAES128AuthorizationKey),
                gAES128AuthorizationKey, 0U);
            if (HSE_SRV_RSP_OK != srvResponse)
                goto exit;
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }
    exit:
        return srvResponse;
    }

    hseSrvResponse_t ImportAsymmetricKeys()
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
#ifdef HSE_SPT_KEY_DERIVE
        hseKeyHandle_t DHSharedSecretRamKeyHandle = HSE_DEMO_DH_SHARED_SECRET_HANDLE;
#endif
        hseKeyHandle_t eccKeyPairRAMKeyHandle = HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE;
        /* import keys for ECC operation before calling HSE_Ecdsa_Example fn*/
        srvResponse = ImportEccKeyReq(
            HSE_DEMO_NVM_ECC_KEY_HANDLE,
            HSE_KEY_TYPE_ECC_PAIR,
            (HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY),
            HSE_EC_SEC_SECP256R1,
            KeyBitLen(HSE_EC_SEC_SECP256R1),
            eccP256PubKey,
            eccP256PrivKey);
        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;
        srvResponse = ImportEccKeyReq(
            HSE_DEMO_NVM_ECC_KEY_HANDLE_PUBLIC,
            HSE_KEY_TYPE_ECC_PUB,
            (HSE_KF_USAGE_VERIFY),
            HSE_EC_SEC_SECP256R1,
            KeyBitLen(HSE_EC_SEC_SECP256R1),
            eccP256PubKey,
            NULL);
        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;
        /* import session keys before calling HSE_SessionKeys_Example fn */
        /*Generate an ECC key pair in RAM (ephemeral ECDH)*/
        srvResponse = GenerateEccKey(
            &eccKeyPairRAMKeyHandle,
            RAM_KEY,
            HSE_EC_SEC_SECP256R1,
            HSE_KF_USAGE_EXCHANGE);
        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;
        /*Import the peer public key*/
        srvResponse = ImportEccKeyReq(
            HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, HSE_KEY_TYPE_ECC_PUB,
            HSE_KF_USAGE_EXCHANGE, HSE_EC_SEC_SECP256R1,
            KeyBitLen(HSE_EC_SEC_SECP256R1), eccP256PubKey, NULL);
        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;
            /*Compute DH Shared Secret (ECDH)*/
#ifdef HSE_SPT_KEY_DERIVE
        srvResponse = DHSharedSecretCompute(
            HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE,
            HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
            &DHSharedSecretRamKeyHandle,
            RAM_KEY,
            KeyBitLen(HSE_EC_SEC_SECP256R1));

        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;
#endif

#ifdef HSE_SPT_RSA
        srvResponse = SetCustAuthorizationKey();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
#endif
        /* import keys before calling HSE_SysAuthorization_Example fn */
        srvResponse = cmd_debug_chal_auth();
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }

    exit:
        return srvResponse;
    }

    /*=============================================================================
     *                                       GLOBAL FUNCTIONS
     * ==========================================================================*/
    /******************************************************************************
     * Function:    HSE_Config
     * Description: Configure NVM attributes, key catalogs and install NVM keys
     *****************************************************************************/
    hseSrvResponse_t FormatKeyCatalog(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

        /* check if the user have SU rights or not, if not then request for it */
        srvResponse = Sys_Auth();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        /* format keys */
        srvResponse = HSE_ConfigKeyCatalogs();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        srvResponse = Load_Relevant_She_Keys();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        srvResponse = ImportAsymmetricKeys();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        return srvResponse;
    }

    /******************************************************************************
     * Function:    ImportKeys
     * Description: Import all NVM keys required for crypto services and secure boot
     *****************************************************************************/
    hseSrvResponse_t ImportSymmetricKeys(void)
    {
        hseSrvResponse_t srvResponse;
#ifdef HSE_SPT_HMAC
        hseKeyHandle_t hmacNVMKeyHandle0 = HSE_DEMO_NVM_HMAC_KEY0;
        hseKeyHandle_t hmacNVMKeyHandle1 = HSE_DEMO_NVM_HMAC_KEY1;
#endif
        hseKeyHandle_t aesNVMProvisionKeyHandle = HSE_DEMO_NVM_AES128_PROVISION_KEY;
        hseKeyHandle_t aesNVMBootKeyHandle = HSE_DEMO_NVM_AES128_BOOT_KEY;

        srvResponse = ParseKeyCatalogs();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        /* import keys */
        srvResponse = HSE_InstallNvmKeys();
        if (HSE_SRV_RSP_OK != srvResponse)
            goto exit;

        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
        If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(aesEcbKey, &AesNVMKeyHandle);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /* load AES keys for FAST CMAC operation */
            srvResponse = LoadAesKey(&AesNVMKeyHandle, 1U, aesEcbKeyLength, aesEcbKey);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
       If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(aesEcbKey, &aesCmacKeyHandle);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /* load AES keys for operation*/
            srvResponse = LoadAesKey(&aesCmacKeyHandle, NVM_KEY, aesEcbKeyLength, aesEcbKey);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }

#ifdef HSE_SPT_HMAC
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
        If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(hmacKeyInitial, &hmacNVMKeyHandle0);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /* import keys before calling HSE_UpdateNvmKey_Example fn */
            srvResponse = ImportPlainSymKeyReq(hmacNVMKeyHandle0, HSE_KEY_TYPE_HMAC,
                                               HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY, hmacKeyInitialLength, hmacKeyInitial, 0U);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
        If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(hmacKeyInitial, &hmacNVMKeyHandle1);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            srvResponse = ImportPlainSymKeyReq(hmacNVMKeyHandle1, HSE_KEY_TYPE_HMAC,
                                               HSE_KF_USAGE_VERIFY, hmacKeyInitialLength, hmacKeyInitial, 0U);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }
#endif

        srvResponse = ImportPlainSymKeyReq(
            HSE_DEMO_RAM_AES128_KEY1,
            HSE_KEY_TYPE_AES,
            HSE_KF_USAGE_SIGN,
            gAESProvisionKeyLength,
            gAES128ProvisionKey,
            0U);
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            goto exit;
        }
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
        If the Tag is not found then import the respective key*/
        srvResponse = VerifySHA(aesEcbKey, &aesNVMProvisionKeyHandle);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /* load keys for Advanced secure boot */
            srvResponse = ImportPlainSymKeyReqMuChannel(
                MU0,
                1U,
                aesNVMProvisionKeyHandle,
                HSE_KEY_TYPE_AES,
                (HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY),
                0U,
                aesEcbKeyLength,
                aesEcbKey,
                TRUE,
                0U);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }
        /*Calling the Key Verify service and check the tag of SHA256 computed from stored key
        If the Tag is not found then import the respective key*/

        srvResponse = VerifySHA(aesEcbKey, &aesNVMBootKeyHandle);
        if (HSE_SRV_RSP_KEY_EMPTY == srvResponse)
        {
            /*Import key linked with SMR#0*/
            srvResponse = ImportPlainSymKeyReqMuChannel(
                MU0,
                1U,
                aesNVMBootKeyHandle,
                HSE_KEY_TYPE_AES,
                HSE_KF_USAGE_VERIFY,
                0U,
                aesEcbKeyLength,
                aesEcbKey,
                TRUE,
                0);
            if (HSE_SRV_RSP_OK != srvResponse)
            {
                goto exit;
            }
        }
        else if (HSE_SRV_RSP_OK != srvResponse)
        {
            testStatus |= KEY_IMPORT_FAILED;
        }

    exit:
        return srvResponse;
    }

    /******************************************************************************
     * Function:    HSE_EraseKeys
     * Description: Erase NVM attributes, key catalogs and NVM keys
     *****************************************************************************/
    hseSrvResponse_t HSE_EraseKeys(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[0U][1U];

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        // re-format the NVM and RAM catalogs
        pHseSrvDesc->srvId = HSE_SRV_ID_ERASE_HSE_NVM_DATA;
        srvResponse = HSE_Send(0U, 1U, gSyncTxOption, pHseSrvDesc);

        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        return srvResponse;
    }

    /******************************************************************************
     * Function:    Sys_Auth
     * Description: Grant Super user rights to user
     *****************************************************************************/
    hseSrvResponse_t Sys_Auth(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        /* read LC first */
        if (HSE_STATUS_CUST_SUPER_USER & HSE_MU_GetHseStatus(MU0))
        {
            /* user already have SU rights */
            srvResponse = HSE_SRV_RSP_OK;
            goto exit;
        }
        else
        {
#ifdef HSE_SPT_RSA
            srvResponse = Grant_SuperUser_Rights();
#endif
        }
    exit:
        return srvResponse;
    }
#ifdef __cplusplus
}
#endif

/** @} */
