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
#ifndef HSE_HOST_SYS_AUTHORIZATION_H
#define HSE_HOST_SYS_AUTHORIZATION_H

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

    /*************************************************************************************************
     * Description:  Performs a system authorization request
     ************************************************************************************************/
    hseSrvResponse_t HSE_SysAuthorizationReq(
        const hseSysAuthOption_t sysAuthOption,
        const hseSysRights_t sysAccess,
        const hseKeyHandle_t authorizationKeyHandle,
        const hseAuthScheme_t *pAuthScheme,
        uint8_t *pChallenge);

    /*************************************************************************************************
     * Description:  Sends the system authorization response
     ************************************************************************************************/
    hseSrvResponse_t HSE_SysAuthorizationResp(
        const uint8_t *pSign0,
        const uint8_t *pSign1,
        const uint16_t sign0Length,
        const uint16_t sign1Length);

#ifdef __cplusplus
}
#endif

#endif /* HSE_HOST_SYS_AUTHORIZATION_H */

/** @} */
