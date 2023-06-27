/**
 *   @file    host_compiler_api.h
 *
 *   @version 1.0.0
 *   @brief   HOST Compiler configurations.
 *   @details This file contains compiler configurations for all host apps.
 *
 */
/*==================================================================================================
*
*   Copyright 2020-2021 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifndef HOST_COMPILER_API_H
#define HOST_COMPILER_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
*  ===============================================================================================*/

/**
 * @file           host_compiler_api.h
 */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
*  ===============================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
*  ===============================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
*  ===============================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
*  ===============================================================================================*/
#ifdef __ghs__
#define HSE_NO_INLINE __attribute__((noinline))
#else
#define HSE_NO_INLINE
#endif

/*==================================================================================================
*                                             ENUMS
*  ===============================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
*  ===============================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
*  ===============================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
*  ===============================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* HOST_COMPILER_API_H */

/** @} */
