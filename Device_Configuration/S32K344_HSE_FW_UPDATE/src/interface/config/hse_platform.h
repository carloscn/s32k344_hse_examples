/**
*   @file    hse_platform.h
*
*   @brief   HSE platform options.
*   @details This file contains macros used for platform compiler options.
*
*   @addtogroup hse_platform HSE Platform
*   @ingroup class_features_impl
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

#ifndef HSE_PLATFORM_H
#define HSE_PLATFORM_H


#ifdef __cplusplus
extern "C"{
#endif

#include "hse_target.h"

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
/* ENABLE SPECIFIC FEATURES HERE */
#if (HSE_PLATFORM == HSE_S32G2XX)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_PHYSICAL_TAMPER_CONFIG      /**< @brief HSE supports the physical tamper configuration. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32G3XX)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_PHYSICAL_TAMPER_CONFIG      /**< @brief HSE supports the physical tamper configuration. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32R45X)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32S2XX)
    #define HSE_H

#elif (HSE_PLATFORM == HSE_S32ZE)
    #define HSE_H
    #define HSE_SPT_HW_SHA3                     /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_NUM_OF_MU_INSTANCES       (8U)  /**< @brief The maxim number of MU interfaces */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_MSC_KEYSTORE                    /**< @brief Support "Managed Security Component" (MSC) keystore (e.g. ACE key store)*/
    #define HSE_SPT_TRIM_PASSWORD_PROVISION         /**< @brief Support trim password provision */
    /**< \defdisable{#define,HSE_SPT_IEE_DDR_FLASH}*/   /**< @brief Support In Line Decryption of LPDDR4 Flash */
    #ifdef HSE_SPT_IEE_DDR_FLASH
    #define HSE_NUM_OF_IEE_DDR_ENTRIES    (8U)  /**< @brief The supported number of IEE_DDR entries/contexts */
    #endif
#elif (HSE_PLATFORM == HSE_S32R41X)
    #define HSE_M
    #define HSE_SPT_HW_SHA3                     /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_TMU_REG_CONFIG              /**< @brief Support TMU registers configuration  */
#elif (HSE_PLATFORM == HSE_SAF85XX)
    #define HSE_M
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_HW_SHA3                     /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_SPT_NXP_RFE_SW                  /**< @brief HSE supports proprietary SW loading to RFE. */
    #define HSE_SPT_TMU_REG_CONFIG              /**< @brief Support TMU registers configuration. */
#elif ((HSE_PLATFORM == HSE_S32K3X1)||(HSE_PLATFORM == HSE_S32K3X2)||(HSE_PLATFORM == HSE_S32K3X4)||(HSE_PLATFORM == HSE_S32K3X6)||(HSE_PLATFORM == HSE_S32K3X8))
    #define HSE_B
#else
    #error "No platform is selected. At least one platform should be selected."
#endif


#if defined(HSE_H)
    #include "hse_h_config.h"
#elif defined(HSE_M)
    #include "hse_m_config.h"
#elif defined(HSE_B)
    #include "hse_b_config.h"
#else
    #error "No HSE HW variant is selected. At least one HSE HW variant should be selected."
#endif


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* HSE_PLATFORM_H */

/** @} */
