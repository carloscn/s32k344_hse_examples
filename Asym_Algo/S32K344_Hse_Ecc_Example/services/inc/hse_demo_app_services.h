/**
*   @file    hse_demo_app_services.h
*

*   @brief   demo application services.
*   @details This file contains function declaration used for demo app services.
*
*   @addtogroup demo_app_services
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

#ifndef HSE_B_SERVICE_CALLS_H
#define HSE_B_SERVICE_CALLS_H

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
#include "hse_srv_attr.h"
#include "std_typedefs.h"
#include "hse_dcm_register.h"
#include "hse_global_variables.h"
#include "hse_interface.h"
    /*==================================================================================================
    *                              SOURCE FILE VERSION INFORMATION
    ==================================================================================================*/

    /*==================================================================================================
    *                                     FILE VERSION CHECKS
    ==================================================================================================*/

    /*==================================================================================================
    *                                          CONSTANTS
    ==================================================================================================*/

    /*==================================================================================================
    *                                      DEFINES AND MACROS
    ==================================================================================================*/
    /**< @brief HSE FW pink image is in primary location (specified in IVT, currently running) */

#define MU0 (0U)
#define MU1 (1U)
#define MU2 (2U)
#define MU3 (3U)

#define CH0 (0U)
#define CH1 (1U)

#define PTR_TO_HOST_ADDR(ptr) ((HOST_ADDR)(uintptr_t)(ptr))

#define BOOT_IMG_TAG_LEN (28UL)
#define FLASH_SECTOR_SIZE_ALIGNMENT 4U

#define USE_SHE_BASED_SECURE_BOOT 3U
#define USE_ADVANCED_SECURE_BOOT 2U
#define USE_BASIC_SECURE_BOOT 1U

#define ADKP_LENGTH (uint8_t)16U
#define UINT64_MAX_VAL 0xFFFFFFFFFFFFFFFFUL
#define HSEFWFEATUREFLAG_ENABLED_VALUE 0xAABBCCDDDDCCBBAAUL
#define UTEST_BASE_ADDRESS 0x1B000000UL
#define IVT_GMAC_FLAG_OFFSET 0x208UL
#define UID_OFFSET 0x40UL
#define BLOCK0_IVT_ADDRESS 0x00400000U
#define IVT_BOOT_CFG_WORD_BOOT_SEQ_POS (3UL)
#define IVT_BOOT_CFG_WORD_BOOT_SEQ (1UL << IVT_BOOT_CFG_WORD_BOOT_SEQ_POS)
#define MU_REG_WRITE64(address, value) ((*(volatile uint64_t *)(address)) = (value))
#define MU_REG_READ64(address) (*(volatile uint64_t *)(address))

    /*==================================================================================================
    *                                             ENUMS
    ==================================================================================================*/
    typedef enum
    {
        APP_NO_TEST_RUNNING = 0,
        APP_PROGRAM_HSE_ATTRIBUTE = 1,
        APP_RUN_HSE_CRYPTOGRAPHIC_SERVICES = 2,
        APP_HSE_FW_UPDATE = 4,
        APP_SECURE_BOOT_CONFIGURED = 8,
        APP_ENABLE_HSE_IVT_AUTH = 16,
        APP_ERASE_NVM_KEYS = 32
    } eRunExmapleTests;

 typedef enum
    {
        NO_ATTRIBUTE_PROGRAMMED = 0,
        READ_HSE_VERSION = 0x1,
        READ_HSE_CAPABILITIES = 0x2,
        PROGRAM_APPLICATION_DEBUG_AUTH_KEY = 0x4,
        PROGRAM_DEBUG_AUTH = 0x8,
        ADVANCE_LC = 0x10,
        ENABLE_AUTH_MODE = 0x20,
        CONFIG_MU = 0x40,
        PROGRAM_EXTEND_CUST_SECURITY_POLICY = 0x80,
        ERASE_KEYS = 0x100,
        MONOTONIC_COUNTER = 0x200,
        UTEST_PROGRAM = 0x400,
        SHE_COMMAND_APP_SERVICE = 0X800,
        INVALID_ATTRIBUTE = 0xFF,
    } eHSEFWAttributes;

    typedef enum
    {
        NON_SECURE_IVT = 0,
        SECURE_IVT
    } ivt_type_t;

    typedef enum
    {
        ADVANCED_SECURE_BOOT = 0,
        SHE_BASED_SECURE_BOOT = 1
    } eSecureBootType;

    typedef enum
    {
        AES128 = 1,
        AES256 = 2,
        HMAC = 4,
        ECC = 8,
        RSA = 16
    } secureboot_authtypes_t;

    /*==================================================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/

    /*==================================================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/
    extern const uint8_t aesEcbCiphertext[];
    extern const uint8_t aesEcbPlaintext[];
    extern const uint8_t aesEcbKey[];
    extern const uint32_t aesEcbKeyLength;
    extern const uint32_t aesEcbPlaintextLength;
    extern const uint32_t aesEcbCiphertextLength;
    extern const uint16_t gAESProvisionKeyLength;
    extern const uint8_t eccP256PubKey[];
    extern const uint8_t eccP256PrivKey[];
    extern const uint8_t message[];
    extern const uint8_t hmacKeyUpdated[];
    extern const uint8_t gAES128ProvisionKey[];
    extern const uint8_t rsa2048CustAuthKeyModulus[];
    extern const uint8_t rsa2048CustAuthKeyPubExp[];
    extern const uint8_t rsa2048CustAuthKeyPrivExp[];
    extern const uint8_t hmacKeyInitial[];
    extern const uint32_t hmacKeyInitialLength;
    extern volatile bool_t authentication_type[];

    /*==================================================================================================
                                         FUNCTION PROTOTYPES
    ==================================================================================================*/
    void HSE_CMAC_Calculation_Testing(void);
    void HSE_Status(void);

    /*
        Function: HSE_GetVersion_Example

        @brief    Get HSE version example
        @detailed Simplest HSE request used for confirmation of running HSE
     */
    hseSrvResponse_t HSE_GetVersion_Example(hseAttrFwVersion_t *pHseFwVersion);

    /*
        Function: HSE_GetVersion_Service

        @brief    Get HSE version example
        @detailed Simplest HSE request used for confirmation of running HSE*/

    void getFwVersionService(void);
    /*
        Function: HSE_SaveVersion_Example

        @brief    save version number
        @detailed save version number in global var of running HSE FW in the device
     */
    void HSE_SaveVersion(hseAttrFwVersion_t *pOldHseFwVersion, hseAttrFwVersion_t *pHseFwVersion);
    /*
        Function: HSE_Config

        @brief    Example of configuring HSE services
        @detailed Configure NVM attributes, key catalogs, install NVM keys and handle SYS_IMG
     */
    hseSrvResponse_t FormatKeyCatalog(void);
    /*
        Function: HSE_Crypto

        @brief    HSE crypto services examples
        @detailed Examples of symmetric/asymmetric, sync/async HSE crypto operations and SYS authorization
     */
    hseSrvResponse_t HSE_Crypto(void);

    /*
        Function: SetCustAuthorizationKey

        @brief    Import keys for sys authorization
        @detailed Example of importing keys for SYS authorization
     */
    hseSrvResponse_t SetCustAuthorizationKey(void);

    /*
        Function: DoHseFwUpdate

        @brief    Returns whether FW update is applicable or not
     */
    bool_t DoHseFwUpdate(void);
    /*
        Function: HSE_UpdateFW

        @brief    HSE FW update example
        @detailed Example of FW Blue Image generation from new/current FW pink image
     */
    void HSE_UpdateFW(void);

    /*
        Function: IsSecureBootEnabled

        @brief    Returns whether Secure Boot is enabled or not (in IVT)
     */
    bool_t IsSecureBootEnabled(void);
    /*
        Function: HSE_EnableSecureBoot

        @brief    Secure Boot configuration examples
        @detailed Example HSE services usage for secure boot enablement (SMR/CR entries install / BSB tag generation,
                  DCD/SelfTest images signing of FW Blue Image generation from new/current FW pink image)
     */
    hseSrvResponse_t HSE_EnableSecureBoot(void);
    /*
        Function: HSE_CompareVersion

        @brief    Compares hse fw version before and after firmware updated
        @detailed this function is used after firmware update request is completed by HSE and expected is version is
                  also updated. hence it will compare version of updated hse with hse running before fw update. If
                  version is greater or equal to, then fw update is considered successful.
     */
    bool_t HSE_CompareVersion(hseAttrFwVersion_t *pOldHseFwVersion, hseAttrFwVersion_t *pHseFwVersion);
    /*
        Function: HSE_CompareAdkp

        @brief    Compares ADKP hash that is calculated with the one that is read
        @detailed
     */
    bool_t HSE_CompareAdkp(uint8_t *pDebugKey, uint8_t *pAdkpHash);
    /*
        Function: HSE_ProgramAdkp

        @brief    Programs ADKP key in UTEST area
        @detailed
     */
    hseSrvResponse_t HSE_ProgramAdkp(void);
    /*
        Function: HSE_ReadAdkp

        @brief    Reads ADKP hash from UTEST area
        @detailed
     */
    hseSrvResponse_t HSE_ReadAdkp(uint8_t *pDebugKey);
    /*
        Function: HSE_CalculateHASH

        @brief    calculates hash of ADKP that is programmed
        @detailed
     */
    hseSrvResponse_t HSE_CalculateHASH(uint8_t *pAdkpHash);
    /*
        Function: HSE_FwUpdateExample

        @brief    firmware update request
        @detailed
     */
    void HSE_FwUpdateExample(uint32_t newHseFwaddress);
    /*
        Function: HSE_ActivatePassiveBlock

        @brief    Activates Passive Block for OTA-E FW udpate
        @detailed
     */
    hseSrvResponse_t HSE_ActivatePassiveBlock(void);

    /*
        Function: SecureBootConfiguration

        @brief    Configures secure boot depending upon secure boot type
        @detailed
     */
    hseSrvResponse_t SecureBootConfiguration(void);
    /*
        Function: HSE_EnableIVTAuthentication

        @brief    Enables boot authentication bit in UTEST area
        @detailed
     */
    hseSrvResponse_t HSE_EnableIVTAuthentication(void);
    /*
        Function: HSE_GetIVTauthbit

        @brief    Reads boot authentication bit programmed in UTEST area
        @detailed
     */
    hseSrvResponse_t HSE_GetIVTauthbit(hseAttrConfigBootAuth_t *pIvtValue);
    /*
        Function: HSE_CompareAdkp

        @brief    Advances lifecycle from CUST_DEL
        @detailed
     */
    void HSE_AdvanceLifecycle(hseAttrSecureLifecycle_t targetLifeCycle);
    /*
        Function: HSE_ReadLifecycle

        @brief    returns current LC of the device
        @detailed
     */
    hseSrvResponse_t HSE_ReadLifecycle(hseAttrSecureLifecycle_t *plifecycle);
    /*
        Function: HSE_GetCapabilities_Example

        @brief    returns HSE FW capabilities
        @detailed
     */
    void HSE_GetCapabilities_Example(uint8_t *phseCapabilites);
    /*
        Function: HSE_ConfigDebugAuthorization

        @brief    updates debug auth mode to CR
        @detailed enabling Challenge-Response debug auth
     */
    void HSE_ConfigDebugAuthorization(void);

    /**
       Function      HSE_SetDebugAuthModeToChalResp
       @brief         Set debug-authorization mode bit to Challenge Response.
       @details       Needed for debug-authorization protocol in OEM_PROD & INFIELD lifecycles.
    */
    hseSrvResponse_t HSE_SetDebugAuthModeToChalResp(void);
    /*
        Function: HSE_ReadAttrExtendCustSecurityPolicy

        @brief
        @detailed
     */
    hseSrvResponse_t HSE_ReadAttrExtendCustSecurityPolicy(hseAttrExtendCustSecurityPolicy_t *pSecurityPolicy);
    /*
        Function: HSE_GetDebugAuthMode

        @brief    reads current debug auth mode
        @detailed
     */
    hseSrvResponse_t HSE_GetDebugAuthMode(hseAttrDebugAuthMode_t *pDebugAuthValue);
    /*
        Function: HSE_AttrExtendCustSecurityPolicy

        @brief    enables extend cust security policy
        @detailed
     */
    hseSrvResponse_t HSE_AttrExtendCustSecurityPolicy(bool_t EnableAdkmBit, bool_t StartAsUserBit);
    /*
        Function: HSE_ConfigNvmAttributes

        @brief    configures NVM attributes
        @detailed
     */
    hseSrvResponse_t HSE_ConfigNvmAttributes(hseMUConfig_t gMuConfig);
    /*
        Function: HSE_GetMUAttribute

        @brief    reads current NVM attribute
        @detailed
     */
    hseSrvResponse_t HSE_GetMUAttribute(hseAttrMUConfig_t *pMuConfigValue);

    /*
        Function: EnableHSEFWUsage

        @brief    Enables HSE FW usage flag in UTEST
        @detailed
     */
    hseSrvResponse_t EnableHSEFWUsage(void);

    bool_t checkHseFwFeatureFlagEnabled(void);
    /*
        Function: HSE_SignBootImage

        @brief    Signs IVT or app image for Basic Secure Boot (AppBSB)
        @detailed
     */
    hseSrvResponse_t HSE_SignBootImage(
        const uint8_t *pInImage,
        const uint32_t inTagLength,
        uint8_t *pOutTagAddr);
    /*
        Function: HSE_HashDataNonBlocking

        @brief    Non blocking hash calculation example
        @detailed
     */
    hseSrvResponse_t HSE_HashDataNonBlocking(
        uint8_t u8MuInstance,
        hseAccessMode_t accessMode,
        uint32_t streamId,
        hseHashAlgo_t hashAlgo,
        const uint8_t *pInput,
        uint32_t inputLength,
        uint8_t *pHash,
        uint32_t *pHashLength);
    /*
        Function: check_debug_password_programmed_status

        @brief    check if debug password is already programmed
        @detailed
     */
    bool_t check_debug_password_programmed_status(void);

    void ProgramADKPService(void);

    void Debug_Auth_Service(void);

    void ExtendCustomerSecurityPolicyService(void);

    void Advance_LifeCycle_Service(void);

    void IVT_Auth_Service(void);

    void MU_EnablementService(void);

    void firmwareUpdateService(void);

    void SecureBootService(void);

    void attributeProgrammingService(eHSEFWAttributes gProgramAttribute);

    hseSrvResponse_t SHE_CommandApp_Service(void);

    /*
        Function: Grant_SuperUser_Rights

        @brief    Does sys authorization for formatting SHE keys
        @detailed
     */

    hseSrvResponse_t Grant_SuperUser_Rights(void);
    /*
        Function: HSE_EraseKeys

        @brief    Erases nvm data
        @detailed
     */
    hseSrvResponse_t HSE_EraseKeys(void);
    /*
        Function: Sys_Auth

        @brief    do sys authorization when LC is advanced to OEM
        @detailed
     */
    hseSrvResponse_t Sys_Auth(void);
    hseSrvResponse_t LoadBootMacKey(void);
    hseSrvResponse_t ImportSymmetricKeys(void);
    hseSrvResponse_t ImportAsymmetricKeys(void);
    hseSrvResponse_t UpdateIvt(ivt_type_t IvtType);
    hseSrvResponse_t HSE_HashDataBlocking(
        uint8_t u8MuInstance,
        hseAccessMode_t accessMode,
        uint32_t streamId,
        hseHashAlgo_t hashAlgo,
        const uint8_t *pInput,
        uint32_t inputLength,
        uint8_t *pHash,
        uint32_t *pHashLength);
    void WaitandSetFWEnablefeatureflag(void);
    void WaitForHSEFWInitToFinish(void);
    void HSE_DemoAppConfigKeys(void);
    hseSrvResponse_t Get_Attr(
        hseAttrId_t attrId,
        uint32_t attrLen,
        void *pAttr);
#ifdef __cplusplus
}
#endif

#endif /* DEMO_APP_SERVICES_H */

/** @} */
