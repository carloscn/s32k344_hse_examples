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
    *                                        INCLUDE FILES
    * 1) system and project includes
    * 2) needed interfaces from external units
    * 3) internal and external interfaces from this unit
    =============================================================================*/

#include "hse_global_variables.h"
#include "hse_host_attrs.h"


    /*=============================================================================
    *                 LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
    =============================================================================*/

    /*=============================================================================
    *                         LOCAL MACROS
    =============================================================================*/

    /*=============================================================================
    *                         LOCAL CONSTANTS
    =============================================================================*/

    /*=============================================================================
    *                         LOCAL VARIABLES
    =============================================================================*/

    /*=============================================================================
    *                         GLOBAL CONSTANTS
    =============================================================================*/

    /*=============================================================================
    *                         GLOBAL VARIABLES
    =============================================================================*/
    extern hseAttrFwVersion_t gHseFwVersion;
    /*=============================================================================
     *                        GLOBAL FUNCTIONS
     * ==========================================================================*/

    /******************************************************************************
     * Function:    HSE_GetVersion_Example
     * Description: Example of HSE service - get FW version
     ******************************************************************************/
    hseSrvResponse_t HSE_GetVersion_Example(hseAttrFwVersion_t *pHseFwVersion)
    {
        hseSrvResponse_t srvResponse;
        srvResponse = Get_Attr(
            HSE_FW_VERSION_ATTR_ID,
            sizeof(hseAttrFwVersion_t),
            pHseFwVersion);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        return srvResponse;
    }

    /******************************************************************************
     * Function:    HSE_SaveVersion
     * Description: saves the firmware version
     ******************************************************************************/
    void HSE_SaveVersion(
        hseAttrFwVersion_t *pOldHseFwVersion,
        hseAttrFwVersion_t *pHseFwVersion)
    {
        pOldHseFwVersion->fwTypeId = pHseFwVersion->fwTypeId;
        pOldHseFwVersion->socTypeId = pHseFwVersion->socTypeId;
        pOldHseFwVersion->majorVersion = pHseFwVersion->majorVersion;
        pOldHseFwVersion->minorVersion = pHseFwVersion->minorVersion;
        pOldHseFwVersion->patchVersion = pHseFwVersion->patchVersion;
    }

    /******************************************************************************
     * Function:    HSE_CompareVersion
     * Description: compares the two firmware versions
     ******************************************************************************/
    bool_t HSE_CompareVersion(
        hseAttrFwVersion_t *pOldHseFwVersion,
        hseAttrFwVersion_t *pHseFwVersion)
    {
        bool_t flag_versionupdated = FALSE;
        if (
            (pOldHseFwVersion->majorVersion <= pHseFwVersion->majorVersion) ||
            (pOldHseFwVersion->minorVersion <= pHseFwVersion->minorVersion) ||
            (pOldHseFwVersion->patchVersion <= pHseFwVersion->patchVersion) ||
            (pOldHseFwVersion->fwTypeId <= pHseFwVersion->fwTypeId) ||
            (pOldHseFwVersion->socTypeId <= pHseFwVersion->socTypeId))
        {
            flag_versionupdated = TRUE;
        }
        return flag_versionupdated;
    }

    void getFwVersionService(void)
    {
        hseSrvResponse_t gSresponse = HSE_SRV_RSP_GENERAL_ERROR;
        gSresponse = HSE_GetVersion_Example(&gHseFwVersion);
        if (HSE_SRV_RSP_OK == gSresponse)
            testStatus |= GET_VERSION_DONE;
    }

#ifdef __cplusplus
}
#endif

/** @} */
