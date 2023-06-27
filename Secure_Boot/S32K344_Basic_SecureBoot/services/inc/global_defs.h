/**
 *   @file    global_defs.h
 *
 *   @brief   Contains the global defined macros.
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

#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

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
#include "hse_global_types.h"
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

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define ASSERT(condition) \
    do                    \
    {                     \
        if (!(condition)) \
            while (1)     \
                ;         \
    } while (0)

#define ASSERT_RETRY(condition) \
    while (!(condition))        \
        ;

#ifdef DEBUG
#define DEBUG_LOOP(var) while (!(var))
#else
#define DEBUG_LOOP(var)
#endif

#define ALIGN(value, alignment) (((value) + (alignment)-1) & (~((alignment)-1)))
#define ADDR_NOT_NULL(addr) ((0x0UL != (uintptr_t)(addr)) && (0xFFFFFFFFUL != (uintptr_t)(addr)))

#define MU0 (0U)
#define MU1 (1U)
#define MU2 (2U)
#define MU3 (3U)

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

#endif /* GLOBAL_DEFS_H */

/** @} */
