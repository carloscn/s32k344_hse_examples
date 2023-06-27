/**
 *   @file    hse_tracing.h
 *
 *
 *   @brief   HSE-Host common variables for tracing
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

#ifndef HSE_TRACING_H
#define HSE_TRACING_H


#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *  ==============================================================================================*/

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *  ==============================================================================================*/

/*==================================================================================================
 *                                     FILE VERSION CHECKS
 *  ==============================================================================================*/

/*==================================================================================================
 *                                          CONSTANTS
 *  ==============================================================================================*/

/*==================================================================================================
 *                                      DEFINES AND MACROS
 *  ==============================================================================================*/

/* Activate/Deactivate HSE tracing */
// #define HSE_TRACING

/* The number of requests to be traced */
#define NUMBER_OF_REQ   2U

/*==================================================================================================
 *                                             ENUMS
 *  ==============================================================================================*/

/*==================================================================================================
 *                                STRUCTURES AND OTHER TYPEDEFS
 *  ==============================================================================================*/

/*==================================================================================================
 *                                GLOBAL VARIABLE DECLARATIONS
 *  ==============================================================================================*/


/*==================================================================================================
 *                                    FUNCTION PROTOTYPES
 *  ==============================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* HSE_TRACING_H */

/** @} */
