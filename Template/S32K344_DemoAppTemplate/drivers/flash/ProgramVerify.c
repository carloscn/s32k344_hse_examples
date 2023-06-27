/*********************************************************************************
*                                                                                *
* FILE NAME     : ProgramVerify.c                                                *
* FUNCTION      : ProgramVerify                                                  *
* DESCRIPTION   : This function will check whether block has been                *
*                 write.                                                         *
* PARAMETERS    : u32LogicalAddress - offset of the first sector which           *
*                 configured when init.                                          *
*                 pSourceAddressPtr   pointer to source need to be               *
*                 verified                                                       *
*                 u32Length - length need to be blank check                      *
* RETURN        : FLS_JOB_OK                - The data was verified correctly    *
*                 FLS_INPUT_PARAM_FAILED    - wrong input parameters             *
*                 FLS_PROGRAM_VERIFY_FAILED - The data was verified incorrectly  *
*                 FLS_JOB_FAILED            - Failed hardware condition          *
**********************************************************************************/
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
* @section ProgramVerify_c_REF_1
* Violates MISRA 2012 Advisory Rule 15.5, A function should have a single point of exit at the end
* This violation is not fixed since if hardware/configuration errors are detected it should return from the function
*
* @section ProgramVerify_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section ProgramVerify_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/

#include "Fls_Registers.h"
#include "Fls_Api.h"

Fls_CheckStatusType ProgramVerify(volatile uint32 u32LogicalAddress, const uint8 *pSourceAddressPtr, uint32 u32Length)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    uint32 u32SectorsNeedToBeProgramVerify = 0U;
    volatile uint32 Fls_StartAddress = 0U;
    volatile uint32 Fls_u32SourceAddressPtr;
    uint32 Fls_EndEachSectorAddress = 0U;
    uint32 u32TotalSizeProgramVerify = 0U;
    uint32 u32TempLogicalAddress = 0U;
    uint32 u32CheckSourceAddress = 0U;
    uint32 u32TempSourceAddressPtr = 0U;
    uint8 u8TempSourceAddressPtr = 0U;

    /*Check u32LogicalAddress exceed  flash area which is configured to write*/
    if (u32LogicalAddress >= (u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE))
    {
        /* Wrong input parameters*/
        /* @violates @ref ProgramVerify_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /* Total all available sizes of sectors which configured and can blank check*/
    u32TotalSizeProgramVerify = u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE;
    /* check the input parameters for bank check*/
    if ((u32Length == 0U) || (u32Length > u32TotalSizeProgramVerify) || (pSourceAddressPtr == NULL_PTR))
    {
        /* Wrong input parameters*/
        /* @violates @ref ProgramVerify_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /*Clear all error lags*/
    /*
    * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_SET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C);

    /* uint32 store Pointer to source */
    /*
    * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    Fls_u32SourceAddressPtr = (uint32)pSourceAddressPtr;
    /*Pointer to array of sectors need to be Program Verify */
    /*
    * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    u32SectorsNeedToBeProgramVerify = (uint32)pAllSectors + ((u32LogicalAddress / FLS_SECTOR_SIZE) * 4U);
    /* Start address to verify */
    /*
    * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeProgramVerify);
    /* Address of starting sectors needs to be Program Verify */
    u32TempLogicalAddress = (u32LogicalAddress % FLS_SECTOR_SIZE);
    Fls_StartAddress = (uint32)(Fls_StartAddress + u32TempLogicalAddress);
    /*Address of ending a first sector to be Program Verify */
    Fls_EndEachSectorAddress = Fls_StartAddress + (FLS_SECTOR_SIZE - u32TempLogicalAddress);
    /* start to Program Verify with sectors configured*/
    do
    {
        /* Using negative default values for status variables in a entry point */
        eReturnCode = FLS_JOB_FAILED;
        /* Checking source is align/unaligned */
        u32CheckSourceAddress = ((uint32)Fls_u32SourceAddressPtr % (uint8)FLS_SIZE_4BYTE);
        if ((0U == ((uint32)Fls_StartAddress % (uint8)FLS_SIZE_4BYTE)) && (0U == u32CheckSourceAddress) && ((uint8)FLS_SIZE_4BYTE <= u32Length))
        {
            /* Store data of source address */
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            u32TempSourceAddressPtr = *(uint32 *)Fls_u32SourceAddressPtr;
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (*(uint32 *)Fls_StartAddress == u32TempSourceAddressPtr)
            {
                Fls_StartAddress += (uint8)FLS_SIZE_4BYTE;
                Fls_u32SourceAddressPtr += (uint8)FLS_SIZE_4BYTE;
                u32Length -= (uint8)FLS_SIZE_4BYTE;
                /* Program verify successfully */
                eReturnCode = FLS_JOB_OK;
            }
            else
            {
                /* The program verify failed */
                eReturnCode = FLS_PROGRAM_VERIFY_FAILED;
            }
        }
        else /* unaligned or remain 4 bytes */
        {
            /* Store data of source address */
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            u8TempSourceAddressPtr = *(uint8*)Fls_u32SourceAddressPtr;
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (*(uint8 *)Fls_StartAddress == u8TempSourceAddressPtr)
            {
                Fls_StartAddress += (uint8)FLS_SIZE_1BYTE;
                Fls_u32SourceAddressPtr += (uint8)FLS_SIZE_1BYTE;
                u32Length -= (uint8)FLS_SIZE_1BYTE;
                /* Program verify successfully */
                eReturnCode = FLS_JOB_OK;
            }
            else
            {
                /* The program verify failed */
                eReturnCode = FLS_PROGRAM_VERIFY_FAILED;
            }
        }
        /* Check if had the errors */
        /*
        * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C))
        {
            /*Clear all error lags*/
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_BIT_SET32(FLASH_MCRS_ADDR32, FLASH_MCRS_EER_W1C | FLASH_MCRS_SBC_W1C | FLASH_MCRS_AEE_W1C | FLASH_MCRS_EEE_W1C | FLASH_MCRS_RVE_W1C | FLASH_MCRS_RRE_W1C | FLASH_MCRS_RWE_W1C);
            /* Errors */
            eReturnCode = FLS_JOB_FAILED;
        }
        if (Fls_StartAddress == Fls_EndEachSectorAddress)
        {
            u32SectorsNeedToBeProgramVerify += 4U;
            /* Address of next sectors */
            /*
            * @violates @ref ProgramVerify_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref ProgramVerify_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeProgramVerify);
            /* End address of each sector */
            Fls_EndEachSectorAddress = Fls_StartAddress + FLS_SECTOR_SIZE;
        }
    } while ((u32Length > 0U) && (FLS_JOB_OK == eReturnCode));

    return eReturnCode;
}
