/**
 *   @file    hse_get_version.c
 *
 *   @brief   Example of HSE service - get version
 *   @details Example of simplest HSE service - get FW version.
 *
 *   @addtogroup [HSE_GET_VERSION]
 *   @{
 */
/*=============================================================================
*
*   Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
=============================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*=============================================================================
    *                              INCLUDE FILES
    * 1) system and project includes
    * 2) needed interfaces from external units
    * 3) internal and external interfaces from this unit
    =============================================================================*/

#include "hse_global_variables.h"


    /*=============================================================================
     *              LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
     * ==========================================================================*/
    extern volatile hseSrvResponse_t gsrvResponse;
/*=============================================================================
 *                        LOCAL MACROS
 * ==========================================================================*/
#define HSE_CAPABILITY_LENGTH 8U
    /*=============================================================================
     *                       LOCAL CONSTANTS
     * ==========================================================================*/

    /*=============================================================================
     *                      LOCAL VARIABLES
     * ==========================================================================*/

    /*=============================================================================
     *                     GLOBAL CONSTANTS
     * ==========================================================================*/

    /*=============================================================================
     *                      GLOBAL VARIABLES
     * ==========================================================================*/

    /*=============================================================================
     *                      LOCAL FUNCTION PROTOTYPES
     * ==========================================================================*/

    /*=============================================================================
     *                       LOCAL FUNCTIONS
     * ==========================================================================*/

    /*=============================================================================
     *                       GLOBAL FUNCTIONS
     * ==========================================================================*/

    /******************************************************************************
     * Function:    HSE_GetCapabilities_Example
     * Description: Example of HSE service - get HSE FW capabilities
     ******************************************************************************/
    void HSE_GetCapabilities_Example(uint8_t *phseCapabilites)
    {
        gsrvResponse = Get_Attr(HSE_CAPABILITIES_ATTR_ID, HSE_CAPABILITY_LENGTH,
                                phseCapabilites);
        ASSERT(HSE_SRV_RSP_OK == gsrvResponse);
    }

#ifdef __cplusplus
}
#endif

/** @} */
