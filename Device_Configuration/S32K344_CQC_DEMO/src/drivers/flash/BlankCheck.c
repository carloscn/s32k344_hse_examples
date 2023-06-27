/****************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011-2018               *
*                         All Rights Reserved                               *
*****************************************************************************
                                                                            *
*****************************************************************************
*                                                                           *
*                 Standard Software Driver for C40                          *
*                                                                           *
* FILE NAME     : BlankCheck.c                                              *
* FUNCTION      : BlankCheck                                                *
* DESCRIPTION   : This function will check whether block has been           *
*                 erased.                                                   *
* PARAMETERS    : u32LogicalAddress - offset of the first sector which      *
*                 configured in init.                                       *
*                 u32Length - length need to be blank check                 *
* RETURN        : FLS_INPUT_PARAM_FAILED   - The wrong input parameters.    *
*                 FLS_BLANK_CHECK_FAILED   - The date was not blank         *
*                 FLS_JOB_FAILED           - Because of the failed hardware *
*                 FLS_JOB_OK               - The data was blank             *
*****************************************************************************/
/**
* @page misra_violations MISRA-C:2012 violations
*
* @section BlankCheck_c_REF_1
* Violates MISRA 2012 Advisory Rule 15.5, A function should have a single point of exit at the end
* This violation is not fixed since if hardware/configuration errors are detected it should return from the function
*
* @section BlankCheck_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section BlankCheck_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/
#include "Fls_Registers.h"
#include "Fls_Api.h"

Fls_CheckStatusType BlankCheck(volatile uint32 u32LogicalAddress, uint32 u32Length)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    uint32 u32SectorsNeedToBeBlankCheck;
    volatile uint32 Fls_StartAddress = 0U;
    uint32 Fls_EndEachSectorAddress = 0U;
    uint32 u32TotalSizeBlankCheck = 0U;
    uint32 u32TempLogicalAddress = 0U;

    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 1U;
    u8SecureCounter++;
    /*Check u32LogicalAddress exceed  flash area which is configured to write*/
    if (u32LogicalAddress >= (u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE))
    {
        /* Wrong input parameters*/
        /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /* Total all available sizes of sectors which configured and can blank check*/
    u32TotalSizeBlankCheck = u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE;
    /* check the input parameters for bank check*/
    if ((u32Length == 0U) || (u32Length > u32TotalSizeBlankCheck))
    {
        /* Wrong input parameters*/
        /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /*Clear all error lags*/
    /*
    * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_SET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C);
    /* Checking if hackers tried to skip some instructions or not*/
    if (2U == u8SecureCounter)
    {
        u8SecureCounter++;
    }
    else
    {
        /* There were hackers who skipped some instructions */
        /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    /*Pointer to array of sectors need to be blank check */
    /*
    * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    u32SectorsNeedToBeBlankCheck = (uint32)pAllSectors + ((u32LogicalAddress / FLS_SECTOR_SIZE) * 4U);
    /* Start address to verify */
    /*
    * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeBlankCheck);
    /* Address of starting sectors needs to be blank check */
    u32TempLogicalAddress = (u32LogicalAddress % FLS_SECTOR_SIZE);
    Fls_StartAddress = (uint32)(Fls_StartAddress + u32TempLogicalAddress);
    /*Address of ending a first sector to be blank check */
    Fls_EndEachSectorAddress = Fls_StartAddress + (FLS_SECTOR_SIZE - u32TempLogicalAddress);
    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER == u8SecureCounter)
    {
        u8SecureCounter++;
    }
    else
    {
        /* There were hackers who skipped some instructions */
        /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    /* start to Verify blank check with fist sector*/
    do
    {
        /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
        u8SecureCounter = 1U;
        /* Using negative default values for status variables in a entry point */
        eReturnCode = FLS_JOB_FAILED;
        if ((0U == ((uint32)Fls_StartAddress % (uint8)FLS_SIZE_4BYTE)) && ((uint8)FLS_SIZE_4BYTE <= u32Length))
        {
            u8SecureCounter++;
            /*
            * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (*(uint32 *)Fls_StartAddress == (uint32)FLS_VERIFY4BYTE_BLANK_CHECK)
            {
                Fls_StartAddress += (uint8)FLS_SIZE_4BYTE;
                u32Length -= (uint8)FLS_SIZE_4BYTE;
                /* Blank check successfully */
                eReturnCode = FLS_JOB_OK;
            }
            else
            {
                /* Blank check failed */
                eReturnCode = FLS_BLANK_CHECK_FAILED;
            }
        }
        else /* At least one of the buffers is unaligned or there are less than 4 bytes left. */
        {
            u8SecureCounter++;
            /*
            * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (*(uint8 *)Fls_StartAddress == (uint8)FLS_VERIFY1BYTE_BLANK_CHECK)
            {
                Fls_StartAddress += (uint8)FLS_SIZE_1BYTE;
                u32Length -= (uint8)FLS_SIZE_1BYTE;
                /* Blank check successfully */
                eReturnCode = FLS_JOB_OK;
            }
            else
            {
                /* Blank check failed */
                eReturnCode = FLS_BLANK_CHECK_FAILED;
            }
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (2U == u8SecureCounter)
        {
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            eReturnCode = FLS_JOB_FAILED;
        }
        /* Check if had the errors */
        /*
        * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C))
        {
            /*Clear all error lags*/
            /*
            * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_SET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C);
            /* Errors */
            eReturnCode = FLS_JOB_FAILED;
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (3U == u8SecureCounter)
        {
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            eReturnCode = FLS_JOB_FAILED;
        }
        if (Fls_StartAddress == Fls_EndEachSectorAddress)
        {
            u32SectorsNeedToBeBlankCheck += 4U;
            /* Address of next sectors */
            /*
            * @violates @ref BlankCheck_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref BlankCheck_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeBlankCheck);
            /* End address of each sector */
            Fls_EndEachSectorAddress = Fls_StartAddress + FLS_SECTOR_SIZE;
            /* Checking if hackers tried to skip some instructions or not*/
            if (FLS_WELL_KNOWN_SECURE_COUNTER == u8SecureCounter)
            {
                u8SecureCounter = 3U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
                eReturnCode = FLS_JOB_FAILED;
            }
        }
        /* Checking if hackers tried to skip some instructions or not*/
        if (4U == u8SecureCounter)
        {
            u8SecureCounter = 9U;
            u8SecureCounter++;
        }
        else
        {
            /* There were hackers who skipped some instructions */
            /* @violates @ref BlankCheck_c_REF_1 A function should have a single point of exit at the end */
            eReturnCode = FLS_JOB_FAILED;
        }
    } while ((u32Length > 0U) && (eReturnCode == FLS_JOB_OK));
    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER != u8SecureCounter)
    {
        /* There were hackers who skipped some instructions */
        eReturnCode = FLS_JOB_FAILED;
    }

    return eReturnCode;
}
