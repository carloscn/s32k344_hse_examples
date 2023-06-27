/****************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011-2018               *
*                         All Rights Reserved                               *
*****************************************************************************

*****************************************************************************
*                                                                           *
*               Standard Software Driver for C40                            *
*                                                                           *
* FILE NAME     : FlashErase.c                                              *
* FUNCTION      : FlashErase                                                *
* DESCRIPTION   : This function will erase sectors which configured in      *
*                 the init function.Note: used the main interface           *
* PARAMETERS    : u32LogicalAddress - Logical address from which the write  *
*                 should be started.                                        *
*                 u32Length - Length need to be erasing                     *
*                 bEnableBlankCheckAfterErasing - Enable/disable blank      *
*                 check after erasing(STD_ON/STD_OFF).                      *
*                 u8DomainIdValue    - The current Domain value that has    *
*                 started the Program or Erase sequence.                    *
*   (Domain ID can be changed, depending on XRDCs are enabled by the user)  *
* RETURN VALUES : FLS_INPUT_PARAM_FAILED    - Wrong input parameters        *
*                 FLS_JOB_FAILED            - Failed hardware condition.    *
*                 FLS_JOB_OK                - The data was blank            *
*                 FLS_TIMEOUT_FAILED        - wait for Done bit too long    *
*                 FLS_BLANK_CHECK_FAILED    - The data was not blank        *
*****************************************************************************/
/**
* @page misra_violations MISRA-C:2012 violations
*
* @section FlashErase_c_REF_1
* Violates MISRA 2012 Advisory Rule 15.5, A function should have a single point of exit at the end
* This violation is not fixed since if hardware/configuration errors are detected it should return from the function
*
* @section FlashErase_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section FlashErase_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/

#include "Fls_Registers.h"
#include "Fls_Api.h"

Fls_CheckStatusType FlashErase(volatile uint32 u32LogicalAddress, const uint32 u32Length, boolean bEnableBlankCheckAfterErasing, uint8 u8DomainIdValue)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    volatile uint32 Fls_StartAddress;
    uint32 u32SectorsNeedToBeErased = 0U;
    uint32 u32ValueTimeOut = 0U;
    uint32 u32LengthBlankCheck = 0U;
    uint8 u8ActualDomainIDs = 0U;
    uint32 u32TempLength = 0U;
    uint32 u32MaxLength = 0U;

    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 1U;
    u8SecureCounter++;
    /* Calculating max length depends on  u32LogicalAddress and total all sectors which users configured */
    u32MaxLength = u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE;
    /*check length and u32offet should align with FLS_SECTOR_SIZE */
    /* Only application cores which can use main interface */
    if (((u32LogicalAddress % FLS_SECTOR_SIZE) != 0U) || ((u32Length % FLS_SECTOR_SIZE) != 0U) || (u32Length == 0U) || (u32Length > u32MaxLength) || (FLS_MAIN_INTERFACE != eInterfaceAccess))
    {
        /* Wrong input parameters*/
        /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /*
  * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
  * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
  */
    u32SectorsNeedToBeErased = (uint32)pAllSectors + ((u32LogicalAddress / FLS_SECTOR_SIZE) * 4U);
    u32LengthBlankCheck = u32Length;
    u32TempLength = u32Length;
    /* Checking if hackers tried to skip some instructions or not*/
    if (2U == u8SecureCounter)
    {
        u8SecureCounter++;
    }
    else
    {
        /* There were hackers who skipped some instructions */
        /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    while (u32TempLength > 0U)
    {
        /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
        u8SecureCounter = 1U;
        u8SecureCounter++;
        /* Using negative default values for status variables in a entry point */
        eReturnCode = FLS_JOB_FAILED;
        /* Verify that EHV may be set */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0UL != REG_BIT_GET32(FLASH_MCR_ADDR32, FLASH_MCR_ERS_U32 | FLASH_MCR_PGM_U32))
        {
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0UL != REG_BIT_GET32(FLASH_UT0_ADDR32, FLASH_UT0_UTE_U32))
        {
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* Clear the clock bit of this sector */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (FLS_JOB_OK != ClearLock(*(uint32 *)u32SectorsNeedToBeErased, u8DomainIdValue))
        {
            /* was the errors*/
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (FLS_WELL_KNOWN_SECURE_COUNTER == u8SecureCounter)
        {
            u8SecureCounter = 1U;
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* check the lock bits */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (FLS_UNPROTECT_SECTOR != GetLock(*(uint32 *)u32SectorsNeedToBeErased))
        {
            /* was the errors*/
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (FLS_WELL_KNOWN_SECURE_COUNTER == u8SecureCounter)
        {
            u8SecureCounter = 2U;
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* Address of sectors needs to be erased */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        Fls_StartAddress = GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeErased);
        /* set timeout value */
        u32ValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;
        /* Checking if hackers tried to skip some instructions or not*/
        if (FLS_WELL_KNOWN_SECURE_COUNTER == u8SecureCounter)
        {
            u8SecureCounter = 3U;
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* When enable the Timeout*/
        if ((boolean)STD_ON == bEnableTimeOut)
        {
            /* Checking domain ID before staring program sequence */
            do
            {
                /* Write to the sector or block address to be erased using logical address registers located in the Platform Flash Controller*/
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                REG_WRITE32(PFLASH_PFCPGM_PEADR_L_ADDR32, (uint32)Fls_StartAddress);
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                u8ActualDomainIDs = (uint8)((REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_PEID_U32) >> FLASH_MCR_PEID_SHIFT_U32);
                /*Decrease the Timeout value*/
                u32ValueTimeOut--;
            } while ((u8ActualDomainIDs != u8DomainIdValue) && (0U < u32ValueTimeOut));
            /*Errors Timeout because wait for the Done bit long time*/
            if (0U == u32ValueTimeOut)
            {
                /*Errors Timeout because wait for the Done bit long time*/
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_TIMEOUT_FAILED;
            }
            /* Checking if hackers tried to skip some instructions or not*/
            if (4U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
        }
        else
        {
            /* Checking domain ID before staring program sequence */
            do
            {
                /* Write to the sector or block address to be erased using logical address registers located in the Platform Flash Controller*/
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                REG_WRITE32(PFLASH_PFCPGM_PEADR_L_ADDR32, (uint32)Fls_StartAddress);
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                u8ActualDomainIDs = (uint8)((REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_PEID_U32) >> FLASH_MCR_PEID_SHIFT_U32);
            } while (u8ActualDomainIDs != u8DomainIdValue);
            /* Checking if hackers tried to skip some instructions or not*/
            if (4U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
        }
        /* One and only one ADATA register must also be written. This is referred to as an erase interlock write.*/
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_WRITE32(FLASH_DATAx_ADDR32, (uint32)0xFFFFFFFFU);
        /* Setup erase operation */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_SET32(FLASH_MCR_ADDR32, FLASH_MCR_ERS_U32);
        /* Flash memory erase will be on a sector */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_ESS_U32);
        /* start internal erase/program sequence */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_SET32(FLASH_MCR_ADDR32, FLASH_MCR_EHV_U32);
        /*Reset timeout value*/
        u32ValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;
        /* Checking if hackers tried to skip some instructions or not*/
        if (5U == u8SecureCounter)
        {
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
        /* When enable the Timeout*/
        if ((boolean)STD_ON == bEnableTimeOut)
        {
            /* Wait until done or abort timeout is reached */
            /*
            * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            while ((0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32)) && (0U < u32ValueTimeOut))
            {
                /*Decrease the Timeout value*/
                u32ValueTimeOut--;
            }
            /* Checking if hackers tried to skip some instructions or not*/
            if (6U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
            /* Confirm MCRS[PEG] = 1 */
            /*
            * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if ((0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PEG_U32)) && (0U != u32ValueTimeOut))
            {
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C))
                {
                    /* Previous program or erase protection error encountered or Previous program or erase sequence encountered an error*/
                    eReturnCode = FLS_JOB_FAILED;
                }
                else
                {
                    /* Erased successfully */
                    eReturnCode = FLS_JOB_OK;
                    /* Increase the pointer for the next erasing job */
                    u32SectorsNeedToBeErased += 4U;
                }
            }
            else
            {
                /* Errors regarding timeout which reached to zero */
                if (0U == u32ValueTimeOut)
                {
                    eReturnCode = FLS_TIMEOUT_FAILED;
                }
                /* Errors regarding failed hardware*/
                else
                {
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            /* Checking if hackers tried to skip some instructions or not*/
            if (7U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
        }
        /* When disable the Timeout*/
        else
        {
            /* Wait until done */
            /*
            * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            while (0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32))
            {
                /* Waiting for DONE bit without timeout */
            }
            /* Checking if hackers tried to skip some instructions or not*/
            if (6U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
            /* Confirm MCRS[PEG] = 1 */
            /*
            * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PEG_U32))
            {
                /*
                * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C))
                {
                    /* Previous program or erase protection error encountered or Previous program or erase sequence encountered an error*/
                    eReturnCode = FLS_JOB_FAILED;
                }
                else
                {
                    /* Erased successfully */
                    eReturnCode = FLS_JOB_OK;
                    /* Increase the pointer for the next erasing job */
                    u32SectorsNeedToBeErased += 4U;
                }
            }
            else
            {
                /* Errors regarding failed hardware*/
                eReturnCode = FLS_JOB_FAILED;
            }
            /* Checking if hackers tried to skip some instructions or not*/
            if (7U == u8SecureCounter)
            {
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
        }
        /* terminate erase operation */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_EHV_U32);
        /* Terminate erase operation */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_ERS_U32);
        /* if set MCR[ESS] should also be cleared (otherwise will auto-clear). */
        /*
        * @violates @ref FlashErase_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashErase_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_ESS_U32);
        /* Decrease the length*/
        u32TempLength = u32TempLength - FLS_SECTOR_SIZE;
        /* Return immediately if had errors */
        if (eReturnCode != FLS_JOB_OK)
        {
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return eReturnCode;
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (8U != u8SecureCounter)
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_JOB_FAILED;
        }
    }
    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 9U;
    u8SecureCounter++;
    /* Verify blank check after erasing the data */
    if (bEnableBlankCheckAfterErasing == (boolean)STD_ON)
    {
        if (FLS_JOB_OK != BlankCheck(u32LogicalAddress, u32LengthBlankCheck))
        {
            /* Not blank Data*/
            /* @violates @ref FlashErase_c_REF_1 A function should have a single point of exit at the end */
            return FLS_BLANK_CHECK_FAILED;
        }
    }
    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER != u8SecureCounter)
    {
        /* There were hackers who skipped some instructions */
        eReturnCode = FLS_JOB_FAILED;
    }

    return eReturnCode;
}
