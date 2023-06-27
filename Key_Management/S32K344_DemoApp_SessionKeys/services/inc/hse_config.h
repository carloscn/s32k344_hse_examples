/**
 *   @file    config.h
 *
 *   @brief   Contains the configuration file for security installer.
 *   @details This file contains the configuration for security installer.
 *
 *   @addtogroup security_installer
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

#ifndef CONFIG_H
#define CONFIG_H

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
#include "hse_target.h"

#if (HSE_PLATFORM == HSE_S32G2XX)
#include "S32G274A.h"
#elif (HSE_PLATFORM == HSE_S32R45X)
#include "S32R45X.h"
#elif (HSE_PLATFORM == HSE_S32S2XX)
#include "S32S247TV.h"
#endif

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

#define USE_BASIC_SECURE_BOOT 1U
#define USE_ADVANCED_SECURE_BOOT 2U
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

#endif

    /** @} */
