/**
*   @file    hse_global_variables.h
*
*   @brief   Contains the global variables.
*   @details This file contains the definitions for global variables
             used to install the security features on a device.
*
*   @addtogroup security_installer
*   @{
*/
/*==================================================================================================
*
*   Copyright 2022 NXP.*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

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
#include "global_defs.h"
#include "hse_global_types.h"
#include "hse_demo_app_services.h"
    /*=============================================================================
    *                              SOURCE FILE VERSION INFORMATION
    =============================================================================*/

    /*=============================================================================
    *                                     FILE VERSION CHECKS
    =============================================================================*/

    /*=============================================================================
    *                                          CONSTANTS
    =============================================================================*/

    /*=============================================================================
    *                                      DEFINES AND MACROS
    =============================================================================*/

    /*=============================================================================
    *                                             ENUMS
    =============================================================================*/
    typedef enum
    {
        NO_TEST_EXECUTED = 0x00000000,
        GET_VERSION_DONE = 0x00000001,
        KEY_CATALOGS_FORMATTED = 0x00000002,
        CRYPTOGRAPHIC_SERVICES_SUCCESS = 0x00000004,
        FW_UPDATE_SUCCESS = 0x00000008,
        CR_DEBUG_AUTH_MODE = 0x00000010,
        ADKP_PROGRAMMING_SUCCESS = 0x00000020,
        LIFECYCLE_ADVANCED_TO_INFIELD = 0x00000040,
        IVT_AUTHENTICATION_ENABLED = 0x00000080,
        SECURE_BOOT_CONFIGURATION_DONE = 0x00000100,
        NVM_DATA_ERASED = 0x00000200,
        MONOTONIC_CNT_DONE = 0x00000400,
        HSE_FW_USAGE_ENABLED = 0x00000800,
        EXTEND_CUST_SECURE_POLICY_ENABLED = 0x00001000,
        ACTIVATE_PASSIVE_BLOCK_SUCCESSFUL = 0x00002000,
        LIFECYCLE_ADVANCED_TO_OEM_PROD = 0x00004000,
        ADKP_KEY_VERIFIED = 0x00008000,
        SHE_SERVICES_SUCCESS = 0x00010000,
        PROGRAMMING_AVAILBLE_REQ_SUCCESS = 0x00020000,
        HEADER_VERIFICATION_SUCCESS = 0x00040000,
        DATA_TRANSFER_SUCCESSFUL = 0x00080000,
        ECU_PARAMETERS_PROGRAMMED = 0x00100000,
        KEY_IMPORT_FAILED = 0x00200000
    } testStatus_t;

    typedef enum
    {
        CRYPTO_SERVICE_NONE = 0,
        AES_EXAMPLE_STARTED = 1,
        HASH_EXAMPLE_STARTED = 2,
        ECC_KEYS_EXAMPLE_STARTED = 4,
        SESSION_KEY_EXAMPLE_STARTED = 8,
        FAST_CMAC_WITH_COUNTER_EXAMPLE_STARTED = 16,
        BURMESTER_DESMEDT_EXAMPLE_STARTED = 32,
        SYS_AUTHORIZATION_EXAMPLE_STARTED = 64,
        UPDATE_NVM_KEY_EXAMPLE_STARTED = 128,
        ECC_EXPORT_PUBLIC_KEY_STARTED = 256,
        ECC_IMPORT_PUBLIC_KEY_SIGNATURE_VERIFICATION_STARTED = 512
    } CryptoServicesTestStartedStatus_t;

    typedef enum
    {
        CRYPTO_SERVICE_SUCCESS_NONE = 0,
        AES_EXAMPLES_SUCCESS = 1,
        HASH_EXAMPLES_SUCCESS = 2,
        ECC_KEYS_EXAMPLES_SUCCESS = 4,
        SESSION_KEY_EXAMPLES_SUCCESS = 8,
        FAST_CMAC_WITH_COUNTER_EXAMPLES_SUCCESS = 16,
        BURMESTER_DESMEDT_EXAMPLES_SUCCESS = 32,
        SYS_AUTHORIZATION_EXAMPLE_SUCCESS = 64,
        UPDATE_NVM_KEY_EXAMPLE_SUCCESS = 128,
        ECC_EXPORT_PUBLIC_KEY_SUCCESS = 256,
        ECC_IMPORT_PUBLIC_KEY_SIGNATURE_VERIFICATION_SUCCESS = 512
    } CryptoServicesTestStatus_t;

    typedef enum
    {
        FW_NOT_INSTALLED = 0,
        FW_INSTALLED
    } fwteststatus_t;

   

    /*=============================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    =============================================================================*/

    /*=============================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    =============================================================================*/

    extern volatile CryptoServicesTestStatus_t gCryptoServicesExecuted;
    /**< @brief secure boot type */
    extern volatile uint8_t gRunSecureBootType;
    /**< @brief current test status */
    extern testStatus_t testStatus;
    /**< @brief response of key formatting */
    extern hseSrvResponse_t formatkey_srvResponse;

    /**< @brief IVT */
    extern ivt_t IVT;

    /**< @brief Global FW version before and after FW update */
    extern hseAttrFwVersion_t fwversion[2];
   // extern volatile eHSEFWAttributes gEnableIVTAuthBit;
    extern int16_t gRunExampleTest;
    /**< @brief Application Debug key password */
    extern volatile uint8_t applicationDebugKeyPassword[];

    /**< @brief Global response */
    extern volatile hseSrvResponse_t KeyReadSrvResponse;

    /**< @brief test completed */
    extern char allTestExecuted;

    /**< @brief Global AES 128 Provision Key Info */
    extern hseKeyInfo_t gAES128ProvisionKeyInfo;

    /**< @brief Global AES 128 Authorization Key */
    extern uint8_t gAES128AuthorizationKey[16];

    /**< @brief Global AES 128 Authorization Key Info */
    extern hseKeyInfo_t gAES128AuthorizationKeyInfo;

    /**< @brief Global ECC P256 Boot Key Pair */
    extern uint8_t gEccP256BootKeyPub[];
    extern uint8_t gEccP256BootKeyPriv[];

    /**< @brief Global AES 128 Boot Key */
    extern uint8_t gAES128BootKey[16];
    /**< @brief Global AES 128 Boot Key Info */
    extern hseKeyInfo_t gAES128BootKeyInfo;
    
    extern volatile uint8_t programmed_appdebugkey[16];
    extern volatile uint8_t adkp_hash[16];

    /*=============================================================================
                                         FUNCTION PROTOTYPES
    =============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* GLOBAL_VARIABLES_H */

/** @} */
