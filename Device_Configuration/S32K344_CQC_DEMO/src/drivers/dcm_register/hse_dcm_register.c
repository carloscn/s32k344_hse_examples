/*============================================================================*/

/*    Copyright 2018 NXP.

* This software is owned or controlled by NXP and may only be used strictly in
* accordance  with the applicable license  terms.  By expressly accepting such
* terms or by  downloading,  installing, activating and/or otherwise using the
* software, you are agreeing that  you have read, and that you agree to comply
* with and are bound by,such license terms. If you do not agree to be bound by
* the applicable  license terms, then you may not retain, install, activate or
* otherwise use the software.
*/
/*============================================================================*/

/*=============================================================================
                                 Description
==============================================================================*/
/**
 *   @file    dcm_register.c
 *
 *   @brief   This file contains dcm register functions.
 */

/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/
#include "hse_dcm_register.h"
/*=============================================================================
                                 LOCAL MACROS
==============================================================================*/

/*=============================================================================
 *                  LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/

/*=============================================================================
                                 LOCAL CONSTANTS
==============================================================================*/

/*=============================================================================
 *                               LOCAL VARIABLES
 =============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

/*=============================================================================
                            LOCAL FUNCTION PROTOTYPES
==============================================================================*/

/*=============================================================================
                            GLOBAL FUNCTION PROTOTYPES
==============================================================================*/

/*=============================================================================
                                 LOCAL FUNCTIONS
==============================================================================*/

/*=============================================================================
                                 GLOBAL FUNCTIONS
==============================================================================*/

/*=============================================================================
  FUNCTION: Dcm_GetCurrentLifecycle
  DESCRIPTION: this function returns current lifecycle value reading from dcm bit.
  ARGUMENTS PASSED: None
  RETURN VALUE: Lifecycle value as DCM_LIFECYCLE_T
  ============================================================================*/
DCM_LIFECYCLE_T Dcm_GetCurrentLifecycle(void)
{
    DCM_LIFECYCLE_T lifecycle;
    DCM_REGISTER_T *dcm = NULL;
    /* Get Base Address of DCM */
    dcm = (DCM_REGISTER_T *)DCM_STATUS_REGISTER_BASE;
    /* Get current lifecycle */
    lifecycle = dcm->dcmlcc.Bit.dcmclc;
    return lifecycle;
}

/*=============================================================================
  FUNCTION: Dcm_GetBitStatusDcmrwp6
  DESCRIPTION: this function returns DCM register WP6 values. These values can
  be programmed by customer if he wants to release reset duirng application
  core boot.
  ARGUMENTS PASSED: None
  RETURN VALUE: Bit value of DCM WP6
  ============================================================================*/
uint32_t Dcm_GetBitStatusDcmrwp6(DCMRWP6_BIT_POSITION_T position)
{
    DCMRWP6_REGISTER_T *dcm = NULL;
    /* Get Base Address of DCM Reg WP6*/
    dcm = (DCMRWP6_REGISTER_T *)DCM_GPR_POR_DCMRWP6_ADDRESS;
    uint32_t result = 0;

    /* Get bit status for respective cores */
    switch (position)
    {
    case DCMRWP6_BIT_CM330:
        result = dcm->Bit.cm330;
        break;
    case DCMRWP6_BIT_CM331:
        result = dcm->Bit.cm331;
        break;
    case DCMRWP6_BIT_CM7:
        result = dcm->Bit.cm7;
        break;

    default:
        /* DEFAULT CASE */
        break;
    }
    return result;
}

/*=============================================================================
  FUNCTION: Dcm_StatusScanning
  DESCRIPTION: this function returns DCM scanning status.
  ARGUMENTS PASSED: None
  RETURN VALUE: Scanning status as DCM_BIT_STATUS_SCANNING_T
  ============================================================================*/
DCM_BIT_STATUS_SCANNING_T Dcm_StatusScanning(void)
{
    DCM_BIT_STATUS_SCANNING_T ScanningStatus = 0U;
    DCM_REGISTER_T *dcm = NULL;
    /* Get Base Address of DCM */
    dcm = (DCM_REGISTER_T *)DCM_STATUS_REGISTER_BASE;
    /* Get DCM Scanning status */
    ScanningStatus = dcm->dcmstat.Bit.dcmdone;
    return ScanningStatus;
}

/*=============================================================================
  FUNCTION: Dcm_StatusIsOTAEnabled
  DESCRIPTION: this function returns status of OTA Activation.
  ARGUMENTS PASSED: None
  RETURN VALUE: OTA activation status as DCM_BIT_STATUS_OTA_T
  ============================================================================*/
DCM_BIT_STATUS_OTA_T Dcm_StatusIsOTAEnabled(void)
{
    DCM_BIT_STATUS_OTA_T OTAstatus = 0U;
    DCM_REGISTER_T *dcm = NULL;
    /* Get Base Address of DCM */
    dcm = (DCM_REGISTER_T *)DCM_STATUS_REGISTER_BASE;
    /* Get DCM OTA active status */
    OTAstatus = dcm->dcmstat.Bit.dcmotaa;
    return OTAstatus;
}

/*=============================================================================
  FUNCTION: Dcm_OTAActiveAddress
  DESCRIPTION: this function returns OTA active region.
  ARGUMENTS PASSED: None
  RETURN VALUE: OTA active address region as DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T
  ============================================================================*/
DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T Dcm_ActiveAddressOTARegion(void)
{
    DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T activeAddressRegion = DCM_BIT_HIGH_ADDRESS_OTA_ACTIVE;
    DCM_REGISTER_T *dcm = NULL;
    /* Get Base Address of DCM */
    dcm = (DCM_REGISTER_T *)DCM_STATUS_REGISTER_BASE;
    /* Get OTA Active region */
    if (dcm->dcmstat.Bit.dcmotar)
    {
        activeAddressRegion = DCM_BIT_LOW_ADDRESS_OTA_ACTIVE;
    }

    return activeAddressRegion;
}
