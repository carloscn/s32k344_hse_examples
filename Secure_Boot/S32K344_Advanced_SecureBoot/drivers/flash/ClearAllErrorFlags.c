/*******************************************************************************
*                                                                              *
*  FILE NAME     : ClearAllErrorFlags.c                                        *
*  FUNCTION      : ClearAllErrorFlags                                          *
*  DESCRIPTION   : This function will clear all error flags of                 *
*                  main interface.                               *
*                                                                              *
*  RETURN        : FLS_JOB_OK       - All error flags were clear successfully  *
*                : FLS_JOB_FAILED   - All error flags were clear unsuccessfully*
********************************************************************************/
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
/**
* @page misra_violations MISRA-C:2012 violations
*
* @section ClearAllErrorFlags_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section ClearAllErrorFlags_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/
#include "Fls_Registers.h"
#include "Fls_Api.h"

Fls_CheckStatusType ClearAllErrorFlags(void)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */

    
    /** Clear all error lags for main interface */
    /*
    * @violates @ref ClearAllErrorFlags_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref ClearAllErrorFlags_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_SET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C | FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C);
    
    /** make sure that if all error flags were clear successfully*/
        /*
        * @violates @ref ClearAllErrorFlags_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref ClearAllErrorFlags_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C | FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C))
        {
            /* Clear error flags is not successful*/
            eReturnCode = FLS_JOB_FAILED;
        }
        else
        {
            /* All error flags were clear successfully */
            eReturnCode = FLS_JOB_OK;
        }

    return eReturnCode;
}
