/**
 *   @file    global_types.h
 *
 *   @brief   Contains the global defined types.
 *
 *   @addtogroup security_installer
 *   @{
 */
/*==================================================================================================
*
*    Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H

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

#include "std_typedefs.h"

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

    /*==================================================================================================
    *                                             ENUMS
    ==================================================================================================*/

    typedef enum
    {
        NOT_RUN = 0U,
        RUNNING,
        PASSED,
        FAILED,
    } exampleState_t;

    /*==================================================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/

    typedef struct
    {
        uint32_t IVT_header;       /**< @brief IVT header marker */
        uint32_t bootCfgWord;      /**< @brief Boot Configuration Word */
        uint32_t reserved1;        /**< @brief 4 bytes reserved */
        uint32_t pAppImg_addr_0;   /**< @brief Application address for Boot Target 0 */
        uint32_t reserved2;        /**< @brief 4 bytes reserved */
        uint32_t pAppImg_addr_1;   /**< @brief Application address for Boot Target 1 */
        uint32_t reserved3;        /**< @brief 4 bytes reserved */
        uint32_t pAppImg_addr_2;   /**< @brief Application address for Boot Target 2 */
        uint32_t reserved4;        /**< @brief 4 bytes reserved */
        uint32_t LCCfgWord;        /**< @brief Life-Cycle configuration word */
        uint32_t cyrstalOscConfig; /**< @brief DEBUG Config */
        uint32_t pHSE;             /**< @brief pointer to HSE image */
        uint32_t reserved5[45];    /**< @brief 192 bytes reserved */
        uint32_t GMAC[7];          /**< @brief GMAC TAG over the IVT image */
    } ivt_t;

    typedef struct
    {
        uint8_t tag;    /**< Tag field */
        uint8_t len[2]; /**< Length field in bytes (big-endian) */
        uint8_t par;    /**< Parameters field */
    } hseIvtDcdHdr_t;

    /*==================================================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/

    /*==================================================================================================
                                         FUNCTION PROTOTYPES
    ==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* GLOBAL_TYPES_H */

/** @} */
