/**
*   @file    hse_srv_attr.h
*
*   @brief   HSE Set/Get attribute services definition.
*   @details This file contains the Set/Get attribute services definition.
*
*   @addtogroup hse_srv_attr HSE Set/Get Attribute Services
*   @ingroup class_admin_services
*   @{
*/
/*==================================================================================================
*
*   Copyright 2019 - 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef HSE_SRV_ATTR_H
#define HSE_SRV_ATTR_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "hse_common_types.h"

#define HSE_START_PRAGMA_PACK
#include "hse_compiler_abs.h"

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

/** @brief    HSE attribute IDs.
 * @details   The following attribute types are defined:
 *            - RO-ATTR - Read-Only attribute
 *            - OTP-ATTR - One Time Progammable; can be written only once (set FUSE/UTEST area)
 *            - OTP-ADVANCE-ATTR - One Time Progammable attribute that can only be advanced (e.g. LifeCycle)
 *            - NVM-RW-ATTR - System NVM attributes; can be read or written
 *            - SET-ONCE-ATTR- Once the attribute is set, it can not be changed until next reset (e.g. can be set once at initialization time)
 *
 * @note
 * - For HSE_H, if the NVM-RW attributes were updated, the SYS-IMAGE must be published and stored in external flash.
 * - To set/update the OTP or NVM attributes (except SET-ONCE-ATTR), the host needs SuperUser rights.
 * - CMU is configured and enabled by HSE Firmware during its initialization flow and the status is available in HSE_GPR_REG_3 Bit[0]
*/
typedef uint16_t hseAttrId_t;
    /*----------------- Common (HSE-H/M/B) attributes --------------------*/
    #define HSE_NONE_ATTR_ID                         ((hseAttrId_t)0U)
    /* RO-ATTR */
    #define HSE_FW_VERSION_ATTR_ID                   ((hseAttrId_t)1U)    /**< @brief RO-ATTR; HSE FW version (see #hseAttrFwVersion_t) */
    #define HSE_CAPABILITIES_ATTR_ID                 ((hseAttrId_t)2U)    /**< @brief RO-ATTR; HSE capabilities (see #hseAttrCapabilities_t) */
    #define HSE_SMR_CORE_BOOT_STATUS_ATTR_ID         ((hseAttrId_t)3U)    /**< @brief RO-ATTR;  SMR verification & Core-boot status (see #hseAttrSmrCoreStatus_t) */
    /* OTP-ATTR & OTP-ADVANCE-ATTR*/
    #define HSE_DEBUG_AUTH_MODE_ATTR_ID              ((hseAttrId_t)10U)   /**< @brief OTP-ATTR; Debug Authorization mode (see #hseAttrDebugAuthMode_t) */
    #define HSE_APP_DEBUG_KEY_ATTR_ID                ((hseAttrId_t)11U)   /**< @brief OTP-ATTR; Application Debug Key / Password (see #hseAttrApplDebugKey_t and #hseAttrSecureApplDebugKey_t) */
    #define HSE_SECURE_LIFECYCLE_ATTR_ID             ((hseAttrId_t)12U)   /**< @brief OTP-ADVANCE-ATTR; Secure Life-cycle (see #hseAttrSecureLifecycle_t) */
    #define HSE_ENABLE_BOOT_AUTH_ATTR_ID             ((hseAttrId_t)13U)   /**< @brief OTP-ATTR; IVT/ DCD Authentication bit for HSE H and IVT Authentication bit for HSE M (see #hseAttrConfigBootAuth_t)  */

    #ifdef HSE_SPT_CUST_SEC_POLICY
    #define HSE_EXTEND_CUST_SECURITY_POLICY_ATTR_ID  ((hseAttrId_t)14U)   /**< @brief OTP-ATTR & NVM-RW-ATTR; HSE security policies extension in CUST_DEL lifecycle for user with CUST SU rights (see #hseAttrExtendCustSecurityPolicy_t).
                                                                                    Note that this attribute also enables the ADKPm in OTP (ADKP diversified with UID), along with the START_AS_USER setting for CUST_DEL lifecycle. */
    #endif /*HSE_SPT_CUST_SEC_POLICY */

    /* NVM-RW-ATTR */
    #define HSE_MU_CONFIG_ATTR_ID                    ((hseAttrId_t)20U)   /**< @brief NVM-RW-ATTR; MU configuration (see #hseAttrMUConfig_t) */

    #ifdef HSE_SPT_OEM_SEC_POLICY
    #define HSE_EXTEND_OEM_SECURITY_POLICY_ATTR_ID   ((hseAttrId_t)21U)   /**< @brief NVM-RW-ATTR; HSE security policies extension in OEM_PROD lifecycle for user with OEM SU rights  (see #hseAttrExtendOemSecurityPolicy_t) */
    #endif /* HSE_SPT_OEM_SEC_POLICY */

    #ifdef HSE_SPT_FAST_CMAC
    #define HSE_FAST_CMAC_MIN_TAG_BIT_LEN_ATTR_ID    ((hseAttrId_t)22U)   /**< @brief NVM-RW-ATTR; The minimum tag bit length that can be used for Fast CMAC verify/generate (see #hseAttrFastCmacMinTagBitLen_t) */
    #endif /* HSE_SPT_FAST_CMAC */

    #define HSE_CORE_RESET_RELEASE_ATTR_ID           ((hseAttrId_t)23U)   /**< @brief NVM-RW-ATTR; Specifies Core Reset table parsing strategy (see #hseAttrCoreResetRelease_t) */

    #ifdef HSE_SPT_KEY_MGMT_POLICIES
    #define HSE_RAM_PUB_KEY_IMPORT_POLICY_ATTR_ID    ((hseAttrId_t)24U)   /**< @brief NVM-RW-ATTR; Specifies RAM public keys import policy in advanced LCs (see #hseAttrRamPubKeyImportPolicy_t) */
    #endif /* HSE_SPT_KEY_MGMT_POLICIES */

    #ifdef HSE_SPT_RESET_SOC_ON_TAMPER_ATTR
    #define HSE_RESET_SOC_ON_TAMPER_ATTR_ID          ((hseAttrId_t)25U)  /**< @brief NVM-RW-ATTR; Reset Soc on tamper detection (see #hseResetSocOnTamper_t) */
    #endif /* HSE_SPT_RESET_SOC_ON_TAMPER_ATTR */

    #ifdef HSE_SPT_FLASHLESS_DEV
    #define HSE_OTP_ROLLBACK_PROTECTION_POLICY_ATTR_ID ((hseAttrId_t)26U)   /**< @brief NVM-RW-ATTR; Disable or enable (default) the OTP rollback protection for FW Blue Image and keystore update (see #hseOtpRollbackProtectionPolicy_t) */
    #endif /*HSE_SPT_FLASHLESS_DEV*/
    
    /* SET-ONCE-ATTR*/
    #ifdef HSE_SPT_PHYSICAL_TAMPER_CONFIG
    #define HSE_PHYSICAL_TAMPER_ATTR_ID              ((hseAttrId_t)30U)   /**< @brief SET-ONLY-ONCE-ATTR; Enables the physical tamper violation in HSE.
                                                                                Once the violation is enabled in HSE, it can not be cleared
                                                                                until next reset. There are two tamper related functions available on PADs: Input (TAMPER_IN), Output (TAMPER_OUT).
                                                                                To support protection against physical tampering, connect TAMPER_OUT to
                                                                                TAMPER_IN. Any physical tamper that breaks this connectivity sets off an alarm at
                                                                                HSE (if enabled using this attribute). User can optionally lock those pads
                                                                                configuration for further modification using virtual wrapper (refer to #hseAttrPhysicalTamper_t).
                                                                                The configuration status is provided by HSE_GPR_REG_3 Bit[1]. */
    #endif /* HSE_SPT_PHYSICAL_TAMPER_CONFIG*/

    #ifdef HSE_SPT_MEM_REGION_PROTECT
    #define HSE_MEM_REGIONS_PROTECT_ATTR_ID          ((hseAttrId_t)31U)   /**< @brief SET-ONLY-ONCE-ATTR; Configures memory regions accessible through each MU (refer to #hseAttrAllMuMemRegions_t) */
    #endif /* HSE_SPT_MEM_REGION_PROTECT */
/*------------------------ HSE-H specific attributes ------------------------*/
#if defined(HSE_H) || defined(HSE_M)
    /* RO-ATTR */
    #define HSE_FW_SIZE_ATTR_ID                      ((hseAttrId_t)100U)  /**< @brief RO-ATTR; HSE Firmware Size (see #hseAttrHseFwSize_t) */
    #define HSE_AVAIL_ANTI_ROLLBACK_COUNTER_ATTR_ID  ((hseAttrId_t)101U)  /**< @brief RO-ATTR; The anti-rollback counter updates left (see #hseAvailAntiRollbackCounter_t) */
    #define HSE_FW_PARTITION_ATTR_ID                 ((hseAttrId_t)102U)  /**< @brief RO-ATTR; The partition (primary or backup) used by BootRom to load the HSE Firmware (see #hseAttrFwPartition_t) */

    #ifdef HSE_SPT_OTFAD
    #define HSE_OTFAD_CTX_STATUS_ATTR_ID             ((hseAttrId_t)103U)  /**< @brief RO-ATTR; Otfad contexts status (see #hseOtfadContextStatus_t). */
    #endif /* HSE_SPT_OTFAD */

    /* OTP-ATTR */
    #define HSE_APP_DEBUG_DIS_ATTR_ID                ((hseAttrId_t)200U)  /**< @brief OTP-ATTR; Disable Application Debug (see #hseAttrDisableAppDebug_t) */
    #ifdef HSE_SPT_NXP_RFE_SW
    #define HSE_RFE_CORE_SW_MODE_ATTR_ID             ((hseAttrId_t)201U)  /**< @brief OTP-ATTR; Enable the NXP RFE SW in HSE (see #hseRfeCoreSwMode_t) */
    #endif /* HSE_SPT_NXP_RFE_SW */

    /* SET-ONCE-ATTR*/
    #ifdef HSE_SPT_TEMP_SENS_VIO_CONFIG
    #define HSE_TEMP_SENSOR_VIO_CONFIG_ATTR_ID       ((hseAttrId_t)400U)  /**< @brief SET-ONLY-ONCE-ATTR; Enable the temperature sensor violation in HSE (see #hseTempSensVioConfig_t) */
    #endif /* HSE_SPT_TEMP_SENS_VIO_CONFIG */
#endif /*HSE_H || HSE_M*/
/*------------------------ HSE-B specific attributes ------------------------*/
#ifdef HSE_B
    /* SET-ONCE-ATTR*/
    #define HSE_FIRC_DIVIDER_CONFIG_ATTR_ID          ((hseAttrId_t)600U)  /**< @brief RAM-RW; FIRC Divider Configuration by HSE Firmware from HSE_GPR (see #hseFircDivConfig_t) */
    /* Secure Recovery */
    #define HSE_SECURE_RECOVERY_CONFIG_ATTR_ID       ((hseAttrId_t)601U)  /**< @brief OTP-ATTR; Secure Recovery Configuration by HSE Firmware (see #hseAttrConfigSecureRecovery_t) */
    /* Flash Optimization Config Attr */
#if defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH)
    #define HSE_ENABLE_PUBLISH_KEY_STORE_RAM_TO_FLASH_ATTR_ID    ((hseAttrId_t)602U)  /**< @brief RAM-RW; Allow to publish the NVM keystore from secure NVM keystore into the data flash (see #hsePublishNvmKeystoreRamtToFlash_t) */
#endif /* defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH) */

#endif /* HSE_B */



/** @brief    Activate or not a specific configuration.
 * @details   Tells whether the HSE activate or not a specific configuration.
*/
typedef uint32_t hseAttrCfg_t;
#define HSE_CFG_NO       ((hseAttrCfg_t)(0x0UL))                    /**< @brief NO, deactivate the configuration */
#define HSE_CFG_YES      ((hseAttrCfg_t)(0xB7A5C365UL))             /**< @brief YES, activate the configuration */
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*==================================================================================================
                                 HSE SET/GET ATTRIBUTE SERVICES
==================================================================================================*/

/** @brief Set HSE attribute service.
 *         @note SuperUser rights (for NVM Configuration) are needed to perform this service.
 */
typedef struct
{
    /** @brief   INPUT: Specifies the HSE attribute ID.*/
    hseAttrId_t   attrId;
    uint8_t       reserved[2];
    /** @brief   INPUT: Specifies the attribute length (in bytes). The size of the memory location
     *                   must be equal to the length of attribute structure */
    uint32_t      attrLen;
    /** @brief   INPUT: The address of the attribute.
     *                  The attribute must have the format of the corresponding attributes structure (see attributes definition)
     *                  @note
     *                  The comment for each attribute ID provides the name for the attribute data structure.
     *                  E.g:The #HSE_MU_CONFIG_ATTR_ID definition includes the following comment: "NVM-RW-ATTR; MU configuration (see #hseAttrMUConfig_t)". */
    HOST_ADDR     pAttr;
} hseSetAttrSrv_t;

/** @brief Get HSE attribute service. */
typedef struct
{
    /** @brief   INPUT: Specifies the HSE attribute ID.*/
    hseAttrId_t   attrId;
    uint8_t       reserved[2];
    /** @brief   INPUT: Specifies the attribute length (in bytes).The size of the memory location
     *                  must be bigger than or equal to the length of attribute structure */
    uint32_t      attrLen;
    /** @brief   OUTPUT: The address where the attribute will be stored.
     *                   The attribute must be stored in the format of the corresponding attribute Id (see the attributes definition).
     *                  @note
     *                  The comment for each attribute ID provides the name for the attribute data structure.
     *                   E.g: The #HSE_FW_VERSION_ATTR_ID definition includes the following comment: "RO-ATTR; HSE FW version (see #hseAttrFwVersion_t)". */
    HOST_ADDR     pAttr;
} hseGetAttrSrv_t;



/*==================================================================================================
                                 ATTRIBUTE DEFINITION
==================================================================================================*/

/*==================================================================================================
                                 HSE FW version
==================================================================================================*/
/**
* @brief          HSE FW version attribute (HSE-H/M/B attribute).
*                 This is a READ-ONLY global attribute.
*/
typedef struct
{
    uint8_t     reserved;       /**< @brief  For HSE-B, it is used for OTA Config: 0 = Full Mem Config; 1 = AB Swap Config.
                                             For other SOC type: Reserved, expected to be 0 */
    uint8_t     socTypeId;      /**< @brief  Identifies the SoC Type ID; same as HSE_PLATFORM from hse_target.h */
    uint16_t    fwTypeId;       /**< @brief  Identifies the FW type:
                                              - 0 - Standard FW targeting all customers
                                              - 1 - Premium  FW targeting all customers
                                              - 2-7 - Reserved
                                              - 8 >= Custom1, Custom2... etc */
    uint8_t     majorVersion;   /**< @brief  Major revision
                                              - 0 - Pre-stabilization releases
                                              - 1 - at first stable interface release, and increased later if breaking changes were introduced */
    uint8_t     minorVersion;   /**< @brief  Minor revision, bumped on new compatible changes added; <br>
                                             reset to 0 on majorVersion bump, if majorVersion > 0 */
    uint16_t    patchVersion;   /**< @brief  Hotfix release (patch version, bug fix releases).<br>
                                             After majorVersion > 0, reset to 0 on majorVersion or minorVersion bump. */
} hseAttrFwVersion_t;


/*==================================================================================================
                                 HSE capabilities
==================================================================================================*/
/** @brief    HSE capabilities bits definition.
 * @details   Provides information about the capabilities of HSE security blocks (list of what algorithms are supported).
 *            Each bit specifies an supported algorithm. The index for each bit in the attribute is defined by #hseAlgoCapIdx_t.
*/
typedef uint64_t hseAttrCapabilities_t;
/** @brief    Provided the bit (used in hseAttrCapabilities_t) based on the algorithm capability index (see #hseAlgoCapIdx_t) */
#define HSE_ALGO_CAP_MASK(capIdx)  (1ULL << (capIdx))



/*==================================================================================================
                                 SMR verification & Core-boot status
==================================================================================================*/
/** @brief    The SMR and Core Boot status.
 * @details   Provides the following infomation:
 *            - SMR entry installation status corresponding to the entries present in SMR table (refer to #smrEntryInstallStatus)
 *            - SMR verification status corresponding to the entries present in SMR table (refer to #smrStatus[])
 *            - Provides Core Boot status (refer to #coreBootStatus[])
 *            - In case Basic Secure Boot (BSB) is performed, it provides the Core Boot status and the location of loaded application (primary/backup, refer to #coreBootStatus[])
 */
typedef struct
{
    uint32_t smrStatus[2U];         /**< @brief  0-31 bit will represent 32 SMR table entries (applicable when SMR is present/enabled).
                                                - smrStatus[0].bit : 0 - SMR Not verified
                                                - smrStatus[0].bit : 1 - SMR verified
                                                - smrStatus[1].bit : 0 - SMR verification fail
                                                - smrStatus[1].bit : 1 - SMR verification pass */
    uint32_t coreBootStatus[2U];   /**< @brief   0-31 bit will represent CORE-ID (0-31):
                                                - coreBootStatus[0].bit : 1 - Core booted
                                                - coreBootStatus[0].bit : 0 - Core Not booted
                                                - coreBootStatus[1].bit : 1 - Core booted with pass/primary reset address
                                                - coreBootStatus[1].bit : 0 - Core booted with alternate/backup reset address */
    uint32_t smrEntryInstallStatus;/**< @brief   0-31 bit will represent 32 SMR table entries (applicable when SMR is present/enabled).
                                                - bit : 0 - SMR entry not installed
                                                - bit : 1 - SMR entry installed */
} hseAttrSmrCoreStatus_t;

/*==================================================================================================
                                 Core Release Strategy
==================================================================================================*/
/** @brief    The Core Reset release from reset method.
 * @details   Specifies the startup method for releasing the application core from reset. */
typedef uint32_t hseAttrCoreResetRelease_t;
#define HSE_CR_RELEASE_ALL_AT_ONCE        ((hseAttrCoreResetRelease_t)0xA5556933UL)  /**< @brief Cores are released all-at-once after the pre-boot verification phase is over */
#define HSE_CR_RELEASE_ONE_BY_ONE         ((hseAttrCoreResetRelease_t)0xA5557555UL)  /**< @brief Cores are released from reset one-by-one after their respective pre-boot phase has finalized successfully
                                                                                                 (i.e. the SMR entries linked to the core via CR table have been loaded and verified). <br>
                                                                                                 The cores are released in ascending order of their indicies in the Core Reset table. <br>
                                                                                                 Flashless devices (e.g. HSE_H) limitations:
                                                                                                  - Only the first Core Reset entry can be booted from SD/MMC.
                                                                                                  - The system clocks and QSPI configurations shall not be changed by the core(s) booted until #HSE_STATUS_BOOT_OK status is set. */

#ifdef HSE_SPT_NXP_RFE_SW
/*==================================================================================================
                                 NXP Proprietary core Software Mode bit
==================================================================================================*/
/** @brief    Proprietary core Software Mode bit (SAF85xx specific attribute).
 * @details   Tells whether the NXP or the Customer SW runs on RFE Proprietary core.
*/
typedef uint8_t hseRfeCoreSwMode_t;
#define HSE_RFE_CORE_CUST_SW          ((hseRfeCoreSwMode_t)0x00U)            /**< @brief The Customer SW runs on  RFE Proprietary core. */
#define HSE_RFE_CORE_NXP_SW           ((hseRfeCoreSwMode_t)0x01U)            /**< @brief The NXP SW runs on RFE Proprietary core. This bit must be set before installing an NXP RFE image
                                                                                       (e.g. before cofiguration the CR and SMR entries)
                                                                                       @note
                                                                                       No application core could access the ITCM/DTCM space of RFE core.
                                                                                       Once this mode is enabled, it cannot be disabled.
                                                                                       Operation allowed in any life cycle. */
#endif /* HSE_SPT_NXP_RFE_SW */
/*==================================================================================================
                                 Debug Authorization Mode bit
==================================================================================================*/
/** @brief    Debug Authorization Mode bit (HSE-H/M specific attribute).
 * @details   Tells whether the Application debug authorization will be password based or challenge-response based.
*/
typedef uint8_t hseAttrDebugAuthMode_t;
#define HSE_DEBUG_AUTH_MODE_PW          ((hseAttrDebugAuthMode_t)0x0U)            /**< @brief Password based application debug authorization mode.
                                                                                     - Read: Application debug authorization will be password based.
                                                                                     - Write: Does not affect application debug authorization mode at all. */
#define HSE_DEBUG_AUTH_MODE_CR          ((hseAttrDebugAuthMode_t)0x1U)            /**< @brief Challenge-Response based application debug authorization mode.
                                                                                     - Read: Application debug authorization will be challenge-response based.
                                                                                     - Write: Enables challenge-response application debug authorization mode.
                                                                                              Once this mode is enabled, it cannot be disabled.
                                                                                              Operation allowed in CUST_DEL, OEM_PROD and IN_FIELD LCs only. */


/*==================================================================================================
                                 Application Debug Key/ Password definition-
==================================================================================================*/
/** @brief    Application Debug Key/ Password definition (HSE-H/M/B attribute).
 * @details   It is an 128-bit Application Debug Key/ Password to be set by the host in CUST_DEL LifeCycle.
 *            - Read: Not allowed if ADKP has not been written yet. After it has been written, first 16 bytes of SHA2_224(ADKP) can be requested via get ADKP attribute service.
 *            - Write: ADKP can be updated only once. The operation allowed only in CUST_DEL LifeCycle.
 */
typedef uint8_t hseAttrApplDebugKey_t[16];

/** @brief    Secure Application Debug Key/ Password definition (HSE-H/M/B attribute).
 * @details   It is the key handle referencing a key already installed in HSE. It must be an AES 128-bits key from RAM or NVM key catalogs.
 *            - Read: Allowed only as the hash over the ADKP (see Read from #hseAttrApplDebugKey_t).
 *            - Write:
 *                  - ADKP can be updated only once. The operation allowed only in CUST_DEL LifeCycle.
 *                  - The key referenced must be installed in HSE a priori. After the key is written successfully in the fuse as ADK/P, it will be erased from the RAM/NVM key catalog. 
 */
typedef hseKeyHandle_t hseAttrSecureApplDebugKey_t;

/*==================================================================================================
                                 HSE Secure Lifecycle
==================================================================================================*/
/** @brief    HSE secure lifecycle definition.
 * @details   Represents HSE secure lifecycle. The lifecycle can be advanced only in forward direction.
 *            Warnings:
 *            - The lifecycle is read/scanned by hardware during the reset phase. Hence, a reset is recommended
 *            after each LC write-advance operation.
 *            - The lifecycle can be advanced to OEM_PROD/IN_FIELD only if the #HSE_APP_DEBUG_KEY_ATTR_ID attribute was set before.
 */
typedef uint8_t hseAttrSecureLifecycle_t;
#define HSE_LC_CUST_DEL                 ((hseAttrSecureLifecycle_t)0x4U)    /**< @brief Customer Delivery Lifecycle.
                                                                                - Read: The current LC is CUST_DEL.
                                                                                - Write: Advancement to this LC is not allowed (through HSE Firmware). */
#define HSE_LC_OEM_PROD                 ((hseAttrSecureLifecycle_t)0x8U)    /**< @brief OEM Production Lifecycle.
                                                                                - Read: The current LC is OEM_PROD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL LC).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_IN_FIELD                 ((hseAttrSecureLifecycle_t)0x10U)    /**< @brief In-Field Lifecycle.
                                                                                - Read: The current LC is IN_FIELD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL, OEM_PROD LCs).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_PRE_FA                   ((hseAttrSecureLifecycle_t)0x14U)    /**< @brief Pre-Failure Analysis Lifecycle.
                                                                                - Read: The current LC is Pre-FA.
                                                                                - Write: Advancement from/to this LC is not allowed (through HSE Firmware). 
                                                                                         This lifecycle is applicable only K3 family (i.e. for flash based devices) */
#define HSE_LC_SIMULATED_OEM_PROD       ((hseAttrSecureLifecycle_t)0xA6U)   /**< @brief Simulated OEM_PROD to avoid writing in FUSE/UTEST. A system reset will revert LC to FUSE/UTEST value.
                                                                                - Read: The current LC is OEM_PROD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL LC).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_SIMULATED_IN_FIELD       ((hseAttrSecureLifecycle_t)0xA7U)   /**< @brief Simulated IN_FIELD to avoid writing in FUSE/UTEST. A system reset will revert LC to FUSE/UTEST value.
                                                                                - Read: The current LC is IN_FIELD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL, SIMULATED_OEM_PROD LCs).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */


/*==================================================================================================
                                 IVT Boot Authentication configuration
==================================================================================================*/
/** @brief    Boot Authentication bit.
 * @details   Value used by Boot ROM to check whether the IVT data needs be authenticated.
*/
typedef uint8_t hseAttrConfigBootAuth_t;
#define HSE_IVT_NO_AUTH             ((hseAttrConfigBootAuth_t)0x0U)            /**< @brief
                                                                                    For HSE-H/M, the IVT/DCD/ST is not authenticated by BootROM:
                                                                                     - Read: IVT/DCD/ST is not authenticated by BootROM.
                                                                                     - Write: Does not affect IVT/ DCD authentication value at all.

                                                                                    For HSE-B, the IVT configuration is not authenticated by Secure BAF:
                                                                                     - Read: IVT is not authenticated by Secure BAF.
                                                                                     - Write: Does not affect IVT configuration authentication value at all.
                                                                               */
#define HSE_IVT_AUTH                ((hseAttrConfigBootAuth_t)0x1U)            /**< @brief
                                                                                    For HSE-H/M, the IVT/DCD/ST to be authenticated by BootROM:
                                                                                    - Read: IVT/DCD/ST is authenticated by BootROM.
                                                                                    - Write: Sets IVT/DCD/ST authentication value.
                                                                                    Once this value is set, it cannot be cleared back.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only.

                                                                                    For HSE-B, the IVT to be authenticated by Secure BAF:
                                                                                     - Read: IVT will be authenticated by Secure BAF.
                                                                                     - Write: Sets IVT authentication value.
                                                                                    Once this value is set, it cannot be cleared back.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only.
                                                                               */
/*==================================================================================================
                                 MU Configuration and XRDC configuration
==================================================================================================*/
/** @brief    MU configuration byte (HSE-H specific attribute).
 * @details   Tells whether the HSE enables the receive interrupt on the configured MU interface.
*/
typedef uint8_t hseMUConfig_t;
#define HSE_MU_ACTIVATED       ((hseMUConfig_t)(0xA5U))                   /**< @brief HSE enables the receive interrupt on the MU interface. */
#define HSE_MU_DEACTIVATED     ((hseMUConfig_t)(0x5AU))                   /**< @brief HSE disables the receive interrupt on the MU interface. */

/** @brief    MU Configuration and XRDC configuration definition for a MU interface.
 * @details   Configures a MU interface and XRDC configuration for the HOST Interface Memory.
 *            @note
 *                  If the device does have (or use) any Host Interface memory, the xrdcDomainId and
 *                  sharedMemChunkSize can be set zero.
 */
typedef struct
{
    hseMUConfig_t muConfig;                 /**< @brief    This value specifies MU interface state.
                                                           - #HSE_MU_ACTIVATED:      MU interface activated
                                                           - #HSE_MU_DEACTIVATED:    MU interface deactivated
                                                           @note It is not allowed to deactivate the MU0 interface */

    uint8_t xrdcDomainId;                   /**< @brief    Domain Id to access the Host Interface memory chunk reserved for
                                                           the MU interface. Must have a value between interval [0, 7].
                                                           The xrdcDomainId field is not taken into account when the
                                                           #sharedMemChunkSize field is equal to 0. */
    uint16_t sharedMemChunkSize;            /**< @brief    Specifies what chunk of host interface memory to reserve for
                                                           the specific MU interface.
                                                           For a value of 0 there is no memory reserved for the MU interface.
                                                           If the #sharedMemChunkSize field is equal to 0 for all MU interfaces,
                                                           the XRDC is disabled and there are no restrictions on the host
                                                           interface memory. */
    uint8_t reserved[60];
} hseAttrMUInstanceConfig_t;

/** @brief    MU Configurations and XRDC configuration definition.
 * @details   Configures the MU interfaces and XRDC configurations for the HOST Interface Memory.
 *
 */
typedef struct
{
    hseAttrMUInstanceConfig_t muInstances[HSE_NUM_OF_MU_INSTANCES];   /**< @brief   Contains the configurations for all MU interfaces */
} hseAttrMUConfig_t;


/*==================================================================================================
                                 HSE Memory region
==================================================================================================*/
#ifdef HSE_SPT_MEM_REGION_PROTECT
/** @brief Maximum number of memory regions configurable through #HSE_SPT_MEM_REGION_PROTECT service */
#define HSE_MAX_NUM_OF_MEM_REGIONS     (6U)

/** @brief Access types for #HSE_SPT_MEM_REGION_PROTECT service regions */
typedef uint32_t hseMemRegAccess_t;
#define HSE_MEM_REG_ACCESS_MASK_IN     ((hseMemRegAccess_t)(0x00003C96UL))
#define HSE_MEM_REG_ACCESS_MASK_OUT    ((hseMemRegAccess_t)(0x5A690000UL))
#define HSE_MEM_REG_ACCESS_MASK_INOUT  ((hseMemRegAccess_t)(HSE_MEM_REG_ACCESS_MASK_IN | HSE_MEM_REG_ACCESS_MASK_OUT))

/**
* @brief        HSE Memory region
* @details      Defines base address and length of a region
*/
typedef struct
{
    /** @brief     INPUT: Access type on which the region applies */
    hseMemRegAccess_t accessType;

    /** @brief     INPUT: Length of memory region */
    uint32_t          length;

    /** @brief     INPUT: Start address of memory region */
    HOST_ADDR         pBaseAddr;
} hseAttrMemRegion_t;

/**
* @brief        HSE Memory region attribute for a single MU.
* @details      Defines the number of regions and their start address
*               and sizes for a single MU
*/
typedef struct
{
    /** @brief     INPUT: Specify the number of memory regions for one MU.
     *             @note
     *             Set to zero if not used
     */
    uint8_t            numofMemRegions;

    uint8_t            reserved[3];

    /** @brief     INPUT: Specifies the memory regions for one MU */
    hseAttrMemRegion_t memRegionList[HSE_MAX_NUM_OF_MEM_REGIONS];
} hseAttrMuMemRegions_t;

/**
* @brief        HSE Memory regions protection attribute for all HSE MUs.
* @details      HSE Memory regions protection is a service used to prevent memory accesses
*               between disallowed bus masters through HSE MUs.
*               HSE uses these regions to validate the input/output parameters
*               for each service received on the corresponding MU.
*               @note
*                 The attribute is not persistent and can only be set once. <br>
*                 A reset is necessary for this configuration to be settable again.
*/
typedef struct
{
    /** @brief     INPUT: Array with memory regions for all MUs */
    hseAttrMuMemRegions_t muMemRegions[HSE_NUM_OF_MU_INSTANCES];
} hseAttrAllMuMemRegions_t;
#endif /* HSE_SPT_MEM_REGION_PROTECT */

/*==================================================================================================
                                HSE key management policies
==================================================================================================*/
#ifdef HSE_SPT_KEY_MGMT_POLICIES

/** @brief    HSE key management policy regarding RAM public keys import.
 *  @details  Determines whether public keys can be imported without authentication in advanced LCs. <br>
 *            Default value is HSE_KM_POLICY_DEFAULT, i.e. HSE does not allow public key import in RAM, when having User rights, if they are not an authenticated key container. <br>
 *            Otherwise, if set to HSE_KM_POLICY_ALLOW_RAM_PUB_KEY_IMPORT, RAM public keys are allowed to be imported without authentication, regardless of the access rights. <br>
 *            SU access rights with configuration privileges are required to update this attribute value.
*/
typedef uint32_t hseAttrRamPubKeyImportPolicy_t;
#define HSE_KM_POLICY_DEFAULT                   ((hseAttrRamPubKeyImportPolicy_t)(0x4E8BD124UL))
#define HSE_KM_POLICY_ALLOW_RAM_PUB_KEY_IMPORT  ((hseAttrRamPubKeyImportPolicy_t)(0xB1742EDBUL))

#endif /* HSE_SPT_KEY_MGMT_POLICIES */

/*==================================================================================================
                                 HSE extend CUST security policies
==================================================================================================*/
#ifdef HSE_SPT_CUST_SEC_POLICY
/** @brief    HSE extend CUST security policies attribute definition.
 * @details   Determines whether certain security policies are extended in HSE Firmware or not; applies only for CUST_DEL LC.
 *            - Read: Tells which extended security policies are set or not.
 *            - Write:
 *                   - If a given policy is not set to be TRUE, there is no change on security policy extension.
 *                   - If a given policy is set to be TRUE, security policy is extended on successful operation.
 *                   - Write operation is allowed only for users with CUST SU rights in CUST_DEL LC.
 */
typedef struct
{
    bool_t  enableADKm;      /**< @brief Application Debug Key/Password (attribute) diversified with UID before
                                        being written in fuse. The supplied 128-bit value for ADK/P attribute
                                        will be interpreted as ADKPm (customer's master key/ password). If needed,
                                        this policy must be set before setting ADK/P attribute.<br>
                                        Applicable for HSE-H (S32G2XX onwards).<br>
                                        If set, the following logic must be used at customer's end for debug-authorization:
                                         - hUID = SHA2_256(UID)
                                         - hADKPm = SHA2_256(ADKPm)
                                         - ADKP {for debugger} = AES256-ECB(hUID(16 bytes..0 to 15)), key = hADKPm;  {ADKPm = customer's master key/ password}.
                                         The hash of ADKPm (set using ADKP attribute) will be used as the key in the derivation of the application password.
                                         An error will be returned if the value of this attribute is given as 0 from host interface*/
    bool_t  startAsUser;     /**< @brief Host starts with User rights in LC = CUST_DEL.
                                        @note Setting this attribute will take effect only after publishing the SYS Image and issuing a reset. */
    uint8_t reserved[2];     /**< @brief HSE reserved */
} hseAttrExtendCustSecurityPolicy_t;
#endif /*HSE_SPT_CUST_SEC_POLICY*/


/*==================================================================================================
                                 HSE extend OEM security policies
==================================================================================================*/
#ifdef HSE_SPT_OEM_SEC_POLICY
/** @brief    HSE extend OEM security policies attribute definition (HSE-H specific attribute).
 * @details   Determines whether certain security policies are extended in HSE Firmware or not in OEM_PROD LC.
 *            - Read: Tells which extended security policies are set or not.
 *            - Write:
 *                   - If a given policy is not set to be TRUE, there is no change on security policy extension.
 *                   - If a given policy is set to be TRUE, security policy is extended on successful operation.
 *                   - Write operation is allowed only for users with OEM SU rights in OEM_PROD LC.
 */
typedef struct
{
    bool_t startAsUser;     /**< @brief Host starts with User rights in LC = OEM_PROD.
                                        @note Setting this attribute will take effect only after publishing the SYS Image and issuing a reset. */
    uint8_t reserved[3];    /**< @brief HSE reserved */
} hseAttrExtendOemSecurityPolicy_t;
#endif /* HSE_SPT_OEM_SEC_POLICY */


/*==================================================================================================
                                 Minimal tag bit length for Fast CMAC
==================================================================================================*/
#ifdef HSE_SPT_FAST_CMAC
/** @brief  Minimal tag bit length for Fast CMAC service.
 *  @details By default, the minimal tag bit length that can be used for the Fast CMAC service (see hseFastCMACSrv_t) is 64 bits.
 *           This attribute can be set to be able to use the Fast CMAC service with the tag bit length less than 64 bits.
 *           The value to be set must be provided in bits. */
typedef uint8_t hseAttrFastCmacMinTagBitLen_t;
#endif /* HSE_SPT_FAST_CMAC */


/*==================================================================================================
                                 External Tamper Configuration
==================================================================================================*/
#ifdef HSE_SPT_PHYSICAL_TAMPER_CONFIG

/** @brief    Activate or Deactivate a tamper
 * @details   Tells whether tamper needs to be activated or deactivated.
*/
typedef uint8_t hseTamperConfig_t;
#define HSE_TAMPER_CONFIG_DEACTIVATE        ((hseTamperConfig_t)(0U))            /**< @brief HSE Tamper Deactivate */
#define HSE_TAMPER_CONFIG_ACTIVATE          ((hseTamperConfig_t)(1U))            /**< @brief HSE Tamper Activate */

/** @brief    Tamper Polarity
 * @details   Specifies the polarity to activate the tamper. This configuration is applicable only
 * for passive tamper configuration. User must set the default state of the tamper input pin accordingly on the board.
 * For example: If the tamper polarity is set "ACTIVE_HIGH" then the default state on the tamper input pin must be "ACTIVE LOW".
*/
typedef uint8_t hseTamperPolarity_t;
#define HSE_TAMPER_POL_ACTIVE_LOW           ((hseTamperPolarity_t)(0U))           /**< @brief HSE Tamper Active low polarity*/
#define HSE_TAMPER_POL_ACTIVE_HIGH          ((hseTamperPolarity_t)(1U))           /**< @brief HSE Tamper Active high polarity*/

/** @brief     Filter Duration
  * @details   This macro describes the maximum filter duration that is possible for the physical tamper.
  *            The clock frequency used in the glitch filter is 32 KHz.
  */
#define HSE_FILTER_DURATION_MAX             ((uint32_t)128U)

/** @brief    Tamper routing configuration
 * @details   This configuration defines the type of tamper (i.e. active or passive).
 *  - In case of active tamper, the clock is derived on GPIO pad which should be routed back to
 * the input tamper pin on the ECU. User must configure the altenate functionality of
 * GPIO pin to tamper output so that the clock can be routed on that pin.
 *  - In case of passive tamper, HSE senses the change in polarity of the input pin. In this case, there is
 * no need to configure the active tamper pin. Only external tamper pin should be configured.
 *  - User is recommended to refer the SIUL chapter in SOC reference manual to configure the
 * correct GPIO pin.
 * For some SOC types, only one active tamper can be
 * supported. Please refer to #HSE_NUM_OF_PHYSICAL_TAMPER_INSTANCES to see how many active tamper are supported.
 * @note #HSE_TAMPER_ACTIVE_TWO is not valid for devices - S32G2, S32K3xx
 * */
typedef uint8_t hseOutputPinConfig_t;
#define HSE_TAMPER_PASSIVE                  ((hseOutputPinConfig_t)(0U))
#define HSE_TAMPER_ACTIVE_ONE               ((hseOutputPinConfig_t)(1U))
#define HSE_TAMPER_ACTIVE_TWO               ((hseOutputPinConfig_t)(2U))

/** @brief    Tamper clock that needs to be driven on the tamper output pad
 * @details   Tamper clock that needs to be driven on the tamper output pad.
 *  Please note that the alternate functionality of GPIO pin must be configured
 *  (for the tamper functionality) so that below the mentioned clock can be
 *  driven on that pad. Not applicable for passive tamper configuration
*/
typedef uint8_t hseTamperOutputClock_t;
#define HSE_TAMPER_ACTIVE_CLOCK_16HZ        ((hseTamperOutputClock_t)(0U))
#define HSE_TAMPER_ACTIVE_CLOCK_8HZ         ((hseTamperOutputClock_t)(1U))
#define HSE_TAMPER_ACTIVE_CLOCK_4HZ         ((hseTamperOutputClock_t)(2U))
#define HSE_TAMPER_ACTIVE_CLOCK_2HZ         ((hseTamperOutputClock_t)(3U))

/** @brief    Enables the tamper violation in HSE subsystem for all physical tampers supported by the SOC.
 * @details   This service only enables the  tamper violation in HSE subsystem for all physical tampers supported by the SOC.
 * Once violation is active it cannot be disabled until next reset. <br>
 * Physical tamper feature can be configured in following two ways:
 * 1. Active Tamper Configuration
 * 2. Passive tamper configuration
 *  @note User must configure the GPIO pins for tamper functionality before calling this service; otherwise,
 *        a false violation can be triggered by HSE. User is also recommended to protect the tamper GPIO configuration
 *        using register protection, virtual wrapper and XRDC configuration agains further modification by any application running on host side.
 */
typedef struct
{
    hseTamperConfig_t   tamperConfig;               /**< @brief This field indicates the tamper configuration to be enable or not. */

    hseOutputPinConfig_t tamperOutputConfig;        /**< @brief This parameter tells which type (Active or Passive) of input is connected to external tamper input.
                                                            If it is an active input, up to 2 tamper options can be selected as input source for external
                                                            tamper input. Based on the value of this parameter, the clock will be driven on this pad by HSE */

    uint8_t filterDuration;                         /**< @brief Configures the length of the digital glitch filter for the external tamper
                                                            pin between 128 and 32640 SIRC clock cycles. Any assertion on external tamper that is
                                                            equal to or less than the value of the digital glitch filter is ignored.
                                                            The length of the glitches filtered out is:
                                                            -  128 + ((FilterDuration - 1) x 256), where FilterDuration = 1, ... , 128. <br>
                                                            If the FilterDuration value is 0, then the glitch filter will not be enabled.
                                                            Filter Duration is a must requirement for Active Tamper and optional for Passive Tamper. */

    hseTamperPolarity_t tamperPolarity;             /**< @brief This field indicates the polarity of the tamper to be be configured.
                                                            It can be "Active LOW" or "Active HIGH".  This parameter is
                                                            considered only when the tamper source in tamperOutputConfig is selected as passive */

    hseTamperOutputClock_t tamperActiveClock;       /**< @brief Determines the clock to be driven on the output pad of the tamper. This parameter is
                                                            considered only when the tamper source in tamperOutputConfig is selected as active */

    uint8_t reserved[3];                            /**< @brief HSE reserved */
} hseAttrPhysicalTamper_t;

/** @brief    Physical Tamper Configurations.
 * @details   Configures all available physical tamper instances.
 */
typedef struct
{
    hseAttrPhysicalTamper_t tamperInstances[HSE_NUM_OF_PHYSICAL_TAMPER_INSTANCES];   /**< @brief Contains the configuration for all the physical temper interfaces */
} hseAttrPhysicalTamperConfig_t;

#endif /* HSE_SPT_PHYSICAL_TAMPER_CONFIG */

/*==================================================================================================
                                 HSE_H/M specific attributes
==================================================================================================*/
#if defined (HSE_H) || defined (HSE_M)
/*==================================================================================================
                                 HSE-Firmware Size
==================================================================================================*/
/** @brief    HSE-Firmware Size.
 * @details   Size of HSE-Firmware in bytes.
 */
typedef uint32_t hseAttrHseFwSize_t;


/*==================================================================================================
                                 Anti-rollback counter updates left
==================================================================================================*/
/** @brief    Anti-rollback counter updates left.
 * @details   There are available 158 anti-rollback counter updates (fuses) for the key store and HSE firmware.
 *            After 158 updates, the key store and HSE firmware are not protected against rollbacks.
 */
typedef uint32_t hseAvailAntiRollbackCounter_t;


/*==================================================================================================
                                 HSE-Firmware used partition on load
==================================================================================================*/
/** @brief    HSE-Firmware used partition on load.
 * @details   Specified the partition (primary or backup) used by BootRom to load the HSE Firmware.
 */
typedef uint8_t hseAttrFwPartition_t;
#define HSE_FW_PARTITION_PRIMARY        ((hseAttrFwPartition_t)0x1U)           /**< @brief HSE firmware was loaded from primary partition */
#define HSE_FW_PARTITION_BACKUP         ((hseAttrFwPartition_t)0x2U)           /**< @brief HSE firmware was loaded from back-up partition */


/*==================================================================================================
                                 Application debug disable
==================================================================================================*/
/** @brief    Application debug disable.
 * @details   Tells if the Application debug is disabled or not for OEM_PROD and/or IN_FIELD life-cycles.
*/
typedef uint8_t hseAttrDisableAppDebug_t;
#define HSE_APP_DEBUG_DIS_NONE          ((hseAttrDisableAppDebug_t)0x0U)       /**< @brief Application Debug not disabled.
                                                                                    - Read: Application Debug is not disabled for OEM_PROD/ IN_FIELD LC.
                                                                                    Application debug can be opened in OEM_PROD/ IN_FIELD LC using the debug
                                                                                    authorization mechanism.
                                                                                    - Write: Does not disable the application debug. */
#define HSE_APP_DEBUG_DIS_OEM           ((hseAttrDisableAppDebug_t)0x1U)       /**< @brief Application Debug disabled for OEM_PROD LC.
                                                                                    - Read: Application Debug is disabled for OEM_PROD LC.
                                                                                    Application debug can never be opened in OEM_PROD LC.
                                                                                    - Write: Disables application debug for OEM_PROD LC only.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */
#define HSE_APP_DEBUG_DIS_FLD           ((hseAttrDisableAppDebug_t)0x2U)       /**< @brief Application Debug disabled for IN_FIELD LC.
                                                                                    - Read: Application Debug is disabled for IN_FIELD LC.
                                                                                    Application debug can never be opened in IN_FIELD LC.
                                                                                    - Write: Disables application debug for IN_FIELD LC only.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */
#define HSE_APP_DEBUG_DIS_OEM_FLD       ((hseAttrDisableAppDebug_t)0x3U)       /**< @brief Application Debug disabled for both OEM_PROD & IN_FIELD LCs.
                                                                                    - Read: Application Debug is disabled for both OEM_PROD & IN_FIELD LCs.
                                                                                    Application debug can never be opened in OEM_PROD & IN_FIELD LCs.
                                                                                     -Write: Disables application debug for both OEM_PROD & IN_FIELD LCs.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */


/*==================================================================================================
                                 Temperature Sensor violation configuration
==================================================================================================*/
#ifdef HSE_SPT_TEMP_SENS_VIO_CONFIG
/** @brief    Temperature Sensor violation configuration byte.
 * @details   Once the violation is enabled in HSE, it can not be cleared
 *            until next reset. User must configure the Temperature Monitoring Unit (TMU)
 *            before giving the attribute. It can also be configured via DCD configuration.
 *            The HSE Firmware signals an Fatal error (see hseError_t bits) if this tamper is detected.
 *            User is recommended to protect the TMU Registers (see REG_PROT on Soc) after the configuration.
 *            The tamper configuration status is available in HSE_GPR_REG_3 Bit[1] (see hseTamperConfigStatus_t).
 *            Four TMU Monitors are mapped to HSE: Average High Critical Temperature TMU Monitor,
 *            Average Low Critical Temperature TMU Monitor, Rising Rate Critical Temperature TMU Monitor,
 *            Falling Rate Critical Temperature TMU Monitor.
 *
*/
typedef uint8_t hseTempSensVioConfig_t;
#define HSE_TEMP_SENS_VIO_ACTIVATED       ((hseTempSensVioConfig_t)(0xA5U))  /**< @brief HSE enables the temperature sensor violation in SNVS. */
#define HSE_TEMP_SENS_VIO_DEACTIVATED     ((hseTempSensVioConfig_t)(0x5AU))  /**< @brief HSE disables the temperature sensor violation in SNVS.  */
#endif /* HSE_SPT_TEMP_SENS_VIO_CONFIG */


/*==================================================================================================
                                 OTFAD context status
==================================================================================================*/
#ifdef HSE_SPT_OTFAD
/** @brief   OTFAD context status.
 *  @details After installation of the otfad context, the OTFAD region may be activated or deactivated.
 *           The OTFAD region may be deactivated because the #HSE_OTFAD_CTX_ACTIVE_ON_BOOT flag is not set during
 *           installation or due to a configuration error. */
typedef uint8_t hseOtfadContextStatus_t;
#define HSE_OTFAD_CTX_NOT_INSTALLED       ((hseOtfadContextStatus_t)(0x00U))    /**< @brief OTFAD context not installed. */
#define HSE_OTFAD_CTX_INSTALLED           ((hseOtfadContextStatus_t)(0xCAU))    /**< @brief OTFAD context installed but not configured. */
#define HSE_OTFAD_CTX_ACTIVE              ((hseOtfadContextStatus_t)(0xACU))    /**< @brief OTFAD context configured and active. */
#define HSE_OTFAD_CTX_INACTIVE            ((hseOtfadContextStatus_t)(0xDEU))    /**< @brief OTFAD context configured but not active. */

/** @brief   OTFAD context status.
 *  @details The OTFAD context status for all OTFAD entries. */
typedef struct
{
    hseOtfadContextStatus_t OtfadCtxStatus[HSE_NUM_OF_OTFAD_INSTANCES][HSE_NUM_OF_OTFAD_ENTRIES];   /**< @brief Contains the status for all OTFAD region. */
} hseOtfadCtxStatus_t;
#endif /* HSE_SPT_OTFAD */


/** @brief   Disable the OTP rollback protection when updating the FW Blue Image and/or NVM keystore.
 *  @details After updating the new FW Blue Image or SYS-IMG (NVM keystore) in external flash, a system reset is needed to update the antirollback
 *           counter in OTP area (fuses). To be able to update the fuse counter, the VDD_EFUSE must be always powered or
 *           can be powered at start-up by HSE FW (if the VDD_EFUSE configuration word from IVT is supported; refer to the HSE Firmware Reference Manual). 
 *           @note
 *           - Anti-rollback protection on FW-IMG is provided only when it is re-encrypted with a device specific key 
 *            (only when the so called FW Blue Image is used).
 *           - SuperUser rights are needed to configure this attribute. */
typedef struct
{
    /** @brief This field controls the rollback protection for FW Blue Image  and/or NVM keystore (SYS-IMG) update:
     *         - HSE_CFG_NO (default configuration): the OTP rollback protection is enabled. 
     *           At boot time, HSE updates the OTP counter (the VDD_EFUSE must be powered).
     *         - HSE_CFG_YES: disable the OTP rollback protection. */
    hseAttrCfg_t disableOtpRollbackProtect;
    /** @brief Prevents the firmware from running if it was loading from a Pink FW Image.
     *         This configuration is ignored for non-secure boot.
     *         - HSE_CFG_NO (default configuration): allow HSE to run if the firmware was loading from a Pink or Blue FW Image. 
     *         - HSE_CFG_YES: disallow HSE to run if firmware was loading from a Pink FW Image. 
     *           Only the FW Blue Image can be used after setting this field to HSE_CFG_YES. 
     *         @note
     *         - Only the Blue FW image provides the rollback protection.
     *         - For secure-boot use care, if disableNVMKeyStoreRollbackProtect == HSE_CFG_YES and the firmware was loaded from PINK FW image , 
     *           HSE performs a function reset; otherwise, it shall continue its execution.
     *         - For non-secure boot, this configuration is ignored. */
    hseAttrCfg_t disallowRunningFromPinkFWImage;
} hseOtpRollbackProtectionPolicy_t;

#endif /* HSE_H || HSE_M*/



/*==================================================================================================
                                 HSE_B specific attributes
==================================================================================================*/
#ifdef HSE_B
/*==================================================================================================
                                 FIRC Divider Configuration
==================================================================================================*/
/** @brief  FIRC Divider Configuration by HSE Firmware from HSE GPR.*/
typedef uint8_t hseFircDivConfig_t;
#define HSE_FIRC_NO_CONFIG                ((hseFircDivConfig_t)0U)       /**< @brief No Configuration. */
#define HSE_FIRC_DIV_BY_1_CONFIG          ((hseFircDivConfig_t)1U)       /**< @brief HSE enables the FIRC divider by 1. */
#define HSE_FIRC_DIV_BY_2_CONFIG          ((hseFircDivConfig_t)2U)       /**< @brief HSE enables the FIRC divider by 2. */
#define HSE_FIRC_DIV_BY_16_CONFIG         ((hseFircDivConfig_t)16U)      /**< @brief HSE enables the FIRC divider by 16. */


/*==================================================================================================
                                 HSE-B Configure Secure Recovery
==================================================================================================*/
/** @brief    Secure Recovery bit.
 * @details   This setting is used by SecureBAF/HSE Firmware to check whether the firmware enters in the Secure Recovery state or not.
*/
typedef uint8_t hseAttrConfigSecureRecovery_t;
#define HSE_SECURE_RECOVERY_DISABLE             ((hseAttrConfigSecureRecovery_t)0x0U)            /**< @brief
                                                                                                  * - Secure Recovery is disabled by HSE Firmware.
                                                                                                  * - Write: It does not affect the value at all.
                                                                                                  */

#define HSE_SECURE_RECOVERY_ENABLE              ((hseAttrConfigSecureRecovery_t)0x1U)            /**< @brief
                                                                                                  * - Secure Recovery is enabled by HSE Firmware.
                                                                                                  * - Write: It enables the Secure Recovery mode.
                                                                                                  */

/*==================================================================================================
                                 HSE-B Publish NVM Keystore RAM to FLASH
==================================================================================================*/
#if defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH)
/** @brief HSE Publish NVM Keystore RAM to Flash
* @details This service can be used to reduce the number of write operations in the data flash, and increase the performance when the key store is updated.
* At start-up, the HSE FW loads the NVM key from data flash into the secure RAM (NVM keys are mirrored in RAM).
* After loading, the NVM keys are used only from RAM memory. At key update/erase, both the mirrored RAM area and the data flash for the keys are updated.
*
* - By default, the attribute is set to #HSE_CFG_NO; this means that during key import (or load key) service,
* HSE updates the NVM keys to both the mirrored RAM area and the data flash.
* - By setting this attribute to #HSE_CFG_YES, the HSE FW will update the NVM keys only in the mirror RAM memory.
* To perform the flash write operation, the application must call the #HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH service.
*
* @note
* This attribute is available in Cust-Del and Oem-Prod LC only.
*/
typedef hseAttrCfg_t hsePublishNvmKeystoreRamtToFlash_t;
#endif /* defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH) */

#endif /* HSE_B */

/*==================================================================================================
                                 RESET_SOC_ON_TAMPER Attribute
==================================================================================================*/
#ifdef HSE_SPT_RESET_SOC_ON_TAMPER_ATTR
/** @brief   HSE Reset Soc on tamper detection.
 *  @details By default HSE does not reset the Soc on tamper detection (this attribute is configured as #HSE_CFG_NO),
 *           Instead it signals an HSE error (see #hseError_t) and enter shutdown mode.
 *           To reset the Soc, the host application must set this attribute to #HSE_CFG_YES and publish SYS-IMG.
 *           On next boot, HSE configures the attribute.
 *  @note
 *  The Application must have SU rights to configure this attribute.*/
typedef hseAttrCfg_t hseResetSocOnTamper_t;
#endif /* HSE_SPT_TAMPER_REACTION_CONFIG */

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define HSE_STOP_PRAGMA_PACK
#include "hse_compiler_abs.h"

#ifdef __cplusplus
}
#endif

#endif /* HSE_SRV_ATTR_H */

/** @} */
