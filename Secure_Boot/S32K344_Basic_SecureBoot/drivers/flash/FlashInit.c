/************************************************************************************
*                                                                                   *
*  FILE NAME     : FlashInit.c                                                      *
*  FUNCTION      : FlashInit                                                        *
*  DESCRIPTION   : This function will initialize the flash pConfig structure.       *
*  PARAMETERS    : pConfig - Flash driver configuration structure                   *
*                                                                                   *
*  RETURN        : FLS_JOB_OK              - Initialized successfully               *
*                : FLS_JOB_FAILED          - Failed hardware condition              *
*                : FLS_INPUT_PARAM_FAILED  - Wrong input parameters.                *
*                : FLS_TIMEOUT_FAILED      - Failed (Waiting for Done bit too long) *
*************************************************************************************/
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
* @section FlashInit_c_REF_1
* Violates MISRA 2012 Advisory Rule 15.5, A function should have a single point of exit at the end
* This violation is not fixed since if hardware/configuration errors are detected it should return from the function
*
* @section FlashInit_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section FlashInit_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/
#include "Fls_Registers.h"
#include "Fls_Api.h"
/*==================================================================================================
*                                    GLOBAL VARIABLES
==================================================================================================*/
boolean bEnableTimeOut;
uint32 u32ValueWaitDoneBitOrDomainIDsTimeOut;
const uint32 *pAllSectors;
uint32 u32NumberOfconfiguredSectors;

Fls_InterfaceAccessType eInterfaceAccess;
/*==================================================================================================
*                                    INIT FUNCTION
==================================================================================================*/
Fls_CheckStatusType FlashInit(const FLASH_CONFIG *pConfig)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    uint32 u32MainValueTimeOut = 0U;
    uint32 u32XpressValueTimeOut = 0U;
    uint32 u32PgmOrApgmBitsValue = 0U;

    /* Init all the global necessary variables for flash*/
    bEnableTimeOut = pConfig->Fls_bEnableTimeOut;
    u32ValueWaitDoneBitOrDomainIDsTimeOut = pConfig->Fls_u32ValueWaitDoneBitOrDomainIDsTimeOut;
    pAllSectors = pConfig->Fls_pAllSectors;
    u32NumberOfconfiguredSectors = pConfig->Fls_u32NumberOfconfiguredSectors;
    eInterfaceAccess = pConfig->Fls_InterfaceAccess;

    /* Check Pointer to the SSD Configuration Structure */
    /* Total of flash area have FLS_TOTAL_SECTORS sectors*/
    if ((NULL_PTR == pConfig) || (FLS_TOTAL_SECTORS < u32NumberOfconfiguredSectors))
    {
        /* was the errors*/
        /* @violates @ref FlashInit_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    else
    {
        /* Correct inputs */
        eReturnCode = FLS_JOB_OK;
    }
    /*update the timeout value of main interface in initiation */
    u32MainValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;
    /*update the timeout value of express interface in initiation */
    u32XpressValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;

    /* Clear all error flags */
    if (FLS_JOB_FAILED == ClearAllErrorFlags())
    {
        /* error flags were not clear */
        /* @violates @ref FlashInit_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    
    /** Init with Main interface **/
    if (FLS_MAIN_INTERFACE == eInterfaceAccess)
    {
        /* Job is still ongoing. Abort possible pending normal erase/program operation */
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        u32PgmOrApgmBitsValue = (REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_PGM_U32);
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if ((0U != (REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_ERS_U32)) || (0U != u32PgmOrApgmBitsValue))
        {
            /* Disable HV to finalize/abort the operation */
            /*
            * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_EHV_U32);
            /* When enable the Timeout*/
            if ((boolean)STD_ON == bEnableTimeOut)
            {
                /* Wait until done or abort timeout is reached */
                /*
                * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                while ((0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32)) && (0U < u32MainValueTimeOut))
                {
                    /*Decrease the Timeout value*/
                    u32MainValueTimeOut--;
                }
                /*Errors Timeout because wait for the Done bit long time*/
                if (0U == u32MainValueTimeOut)
                {
                    /*Errors Timeout because wait for the Done bit long time*/
                    /* @violates @ref FlashInit_c_REF_1 A function should have a single point of exit at the end */
                    return FLS_TIMEOUT_FAILED;
                }
            }
            else
            {
                /*
                * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                while (0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32))
                {
                    /* Waiting for DONE bit without timeout */
                }
            }
            /*Clear ERS and PGM bits */
            /*
            * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_ERS_U32 | FLASH_MCR_PGM_U32);
        }
        /* Watchdog interrupt is not enabled  */
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_WDIE_U32);
        /* An interrupt request will not be generated when the DONE flag is set*/
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_PECIE_U32);

        /** Init with Flash Express Program interface **/
        /* Job is still ongoing. Abort possible pending normal erase/program operation */
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != (REG_READ32(FLASH_XMCR_ADDR32) & FLASH_XMCR_XPGM_U32))
        {
            /* Disable HV to finalize/abort the operation */
            /*
            * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_CLEAR32(FLASH_XMCR_ADDR32, FLASH_XMCR_XEHV_U32);
            /* When enable the Timeout*/
            if ((boolean)STD_ON == bEnableTimeOut)
            {
                /* Wait until done or abort timeout is reached */
                /*
                * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                while ((0U == REG_BIT_GET32(FLASH_XMCR_ADDR32, FLASH_XMCR_XDONE_U32)) && (0U < u32XpressValueTimeOut))
                {
                    /*Decrease the Timeout value*/
                    u32XpressValueTimeOut--;
                }
                if (0U == u32XpressValueTimeOut)
                {
                    /*Errors Timeout because wait for the Done bit long time*/
                    /* @violates @ref FlashInit_c_REF_1 A function should have a single point of exit at the end */
                    return FLS_TIMEOUT_FAILED;
                }
            }
            else
            {
                /*
                * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                while (0U == REG_BIT_GET32(FLASH_XMCR_ADDR32, FLASH_XMCR_XDONE_U32))
                {
                    /* Waiting for DONE bit without timeout */
                }
            }
            /*Clear XPGM bits */
            /*
            * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_CLEAR32(FLASH_XMCR_ADDR32, FLASH_XMCR_XPGM_U32);
        }
        /* Alternate Watchdog interrupt is not enabled  */
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_XMCR_ADDR32, FLASH_XMCR_XWDIE_U32);
        /*Normal Operation, Watchdog Timer has not expired*/
        /*
        * @violates @ref FlashInit_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashInit_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_XMCR_ADDR32, FLASH_XMCR_XWDI_U32);
    }
    else
    {
        eReturnCode = FLS_INPUT_PARAM_FAILED;
    }

    return eReturnCode;
}
