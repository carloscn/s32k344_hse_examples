/**
*   @file    hse_host_wrappers.h
*

*   @brief   Wrapper function declaration.
*   @details This file contains declaration of Wrapper and helper functions.
*
*   @addtogroup host_wrappers
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

#ifndef HOST_WRAPPERS_H
#define HOST_WRAPPERS_H

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
#include "hse_common_types.h"
#include "std_typedefs.h"
#include "hse_host.h"
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

    /*==================================================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/

    /*==================================================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/

    /*==================================================================================================
                                         FUNCTION PROTOTYPES
    ==================================================================================================*/
    hseSrvResponse_t SheLoadMasterEcuKey(void);
    hseSrvResponse_t SheLoadNVMKey_ECB(void);
    hseSrvResponse_t SheLoadNVMKey_CBC(void);
    hseSrvResponse_t SheLoadNVMKey_CMAC(void);
    hseSrvResponse_t EraseAllSheKeys(void);
    hseSrvResponse_t Load_Relevant_She_Keys(void);

    hseSrvResponse_t SysAuth_User(void);
    hseSrvResponse_t HostKdf(uint32_t inputLength, const uint8_t *pInput, uint32_t *pHashLength, uint8_t *pHash, hseSGTOption_t inputSgtType);

    hseSrvResponse_t HSEConfigKeyCatalogs(void);

#ifdef __cplusplus
}
#endif

#endif /* HOST_WRAPPERS_H */

/** @} */
