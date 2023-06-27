/*****************************************************************************
*                                                                            *
* FILE NAME     : FlashProgram.c                                             *
* FUNCTION      : FlashProgram                                               *
* DESCRIPTION   : This function will program used main program               *
* PARAMETERS    : u32LogicalAddress - Logical address from which the write   *
*                 should be started.                                         *
*                 pSourceAddressPtr - pointer to data which need to          *
*                 be written                                                 *
*                 u32Length - Length need to be written                      *
*                 bEnableBlankCheckBeforeWriting - Enable/disable blank      *
*                 check before writing(STD_ON/STD_OFF).                      *
*                 bProgramVerifyAfterWriting - Enable/disable program        *
*                 verify after writing(STD_ON/STD_OFF).                      *
*                 u8DomainIdValue    - The current Domain value that has     *
*                 started the Program or Erase sequence.                     *
*   (Domain ID can be changed, depending on XRDCs are enabled by the user)   *
* RETURN VALUES : FLS_JOB_OK                - The data was written correctly *
*                 FLS_INPUT_PARAM_FAILED    - Wrong input parameters         *
*                 FLS_BLANK_CHECK_FAILED    - The data was not blank         *
*                 FLS_JOB_FAILED            - Failed hardware condition.     *
*                 FLS_PROGRAM_VERIFY_FAILED - The program verification       *
*                 after write operation failed                               *
******************************************************************************/
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
* @section FlashProgram_c_REF_1
* Violates MISRA 2012 Advisory Rule 15.5, A function should have a single point of exit at the end
* This violation is not fixed since if hardware/configuration errors are detected it should return from the function
*
* @section FlashProgram_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section FlashProgram_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
* @section FlashProgram_c_REF_4
* Violates MISRA 2012 Required Rule 10.8, The value of a composite expression shall no be cast to a different essential type category or a wider essential type.
* The cast is used to access memory mapped registers.
*
*/

#include "Fls_Registers.h"
#include "Fls_Api.h"

static uint16 FlashProgrambytes(uint32 u32StartAddress, Fls_ProgSizeType eWriteMode, uint8 u8DomainIdValue);

static volatile uint32 Fls_u32SourceAddressPtr = 0U;
/*Actual start location needs to be written to DATA registers*/
static uint8 Fls_u8LocationWritesDataRegs = 0U;

Fls_CheckStatusType FlashProgram(
    volatile uint32 u32LogicalAddress, const uint8 *pSourceAddressPtr, uint32 u32Length, boolean bEnableBlankCheckBeforeWriting, boolean bProgramVerifyAfterWriting, uint8 u8DomainIdValue)
{
    uint32 u32TotalSizeWrite = 0U;
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    volatile uint32 Fls_StartAddress = 0U;
    uint32 u32LogicalAddressProgramVerify = 0U;
    uint32 u32LengthProgramVerify = 0U;
    uint32 Fls_EndEachSectorAddress = 0U;
    uint32 u32SectorsNeedToBeWritten = 0U;
    uint32 u32TempLogicalAddress = 0U;
    uint16 u16StatusProgram = 0U;
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    u32SectorsNeedToBeWritten = (uint32)pAllSectors + ((u32LogicalAddress / FLS_SECTOR_SIZE) * 4U);
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    Fls_u32SourceAddressPtr = (uint32)pSourceAddressPtr;
    /* store to support for progam verify*/
    u32LogicalAddressProgramVerify = u32LogicalAddress;
    /* store to support for progam verify*/
    u32LengthProgramVerify = u32Length;
    /* Check u32LogicalAddress exceed  flash area which is configured to write*/
    /* Only application cores which can use main interface */
    if (u32LogicalAddress >= (u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE) || (FLS_MAIN_INTERFACE != eInterfaceAccess))
    {
        /* Wrong 
         input parameters*/
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /* Total all available sizes of sectors which configured and can write*/
    u32TotalSizeWrite = u32NumberOfconfiguredSectors * FLS_SECTOR_SIZE;
    /*check length and u32offet should align with FLS_WRITE_DOUBLE_WORD */
    if (((u32LogicalAddress % (uint8)FLS_WRITE_DOUBLE_WORD) != 0U) || ((u32Length % (uint8)FLS_WRITE_DOUBLE_WORD) != 0U) || (u32Length == 0U) || (u32Length > u32TotalSizeWrite) || (pSourceAddressPtr == NULL_PTR))
    {
        /* Wrong input parameters*/
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
        return FLS_INPUT_PARAM_FAILED;
    }
    /* Verify that EHV may be set */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    if (0UL != REG_BIT_GET32(FLASH_MCR_ADDR32, FLASH_MCR_ERS_U32 | FLASH_MCR_PGM_U32))
    {
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    if (0UL != REG_BIT_GET32(FLASH_UT0_ADDR32, FLASH_UT0_UTE_U32))
    {
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
       return FLS_JOB_FAILED;
    }
    /* Verify blank check before writing the data */
    if (bEnableBlankCheckBeforeWriting == (boolean)STD_ON)
    {
        if (FLS_JOB_OK != BlankCheck(u32LogicalAddress, u32Length))
        {
            /* Not blank Data*/
            /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
           return FLS_BLANK_CHECK_FAILED;
        }
    }
    /* Clear the clock bit of this sector */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    if (FLS_JOB_OK != ClearLock(*(uint32 *)u32SectorsNeedToBeWritten, u8DomainIdValue))
    {
        /* was the errors*/
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    /*Check lock bit of the first sector */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    if (FLS_UNPROTECT_SECTOR != GetLock(*(uint32 *)u32SectorsNeedToBeWritten))
    {
        /* was the errors*/
        /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
        return FLS_JOB_FAILED;
    }
    /* The numerical order of Sector Offset Address based on (calculated by) PageSize in a block of write buffer size (128 bytes in case of main interface)*/
    Fls_u8LocationWritesDataRegs = ((uint8)(u32LogicalAddress % FLS_DATA_SIZE_BYTES_U32) / (uint8)FLS_WRITE_DOUBLE_WORD);
    /* 
    * Actual start location needs to be written to DATA registers (DATA[0], DATA[1] ..) 
    * Ex: if u32LogicalAddress = 0 it means that data will be written starting from the DATA[0] register.
    *     if u32LogicalAddress = 8 it means that data will be written starting from the DATA[2] register.
    */
    Fls_u8LocationWritesDataRegs = (Fls_u8LocationWritesDataRegs * (uint8)((uint8)FLS_WRITE_DOUBLE_WORD / 4U));
    /* Address of first sectors */
    /*
  * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
  * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
  */
    Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeWritten);
    /* Address of starting sectors needs to be written */
    u32TempLogicalAddress = (u32LogicalAddress % FLS_SECTOR_SIZE);
    Fls_StartAddress = (uint32)(Fls_StartAddress + u32TempLogicalAddress);
    /*Address of ending a first sector to be written */
    Fls_EndEachSectorAddress = Fls_StartAddress + (FLS_SECTOR_SIZE - u32TempLogicalAddress);
    /*Write to sectors configured*/
    while (u32Length > 0U)
    {
        /* Using negative default values for status variables in a entry point */
        eReturnCode = FLS_JOB_FAILED;
        /* Start address has to align with 128 and length >= 128 bytes*/
        if ((Fls_u8LocationWritesDataRegs == 0U) && (u32Length >= 128U))
        {
            /* Reading status of program */
            u16StatusProgram = FlashProgrambytes(Fls_StartAddress, FLS_WRITE_QPAGE, u8DomainIdValue);
            if ((uint16)FLS_JOB_OK != (uint16)u16StatusProgram)
            {
                /*had Errors when write*/
                /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
                return (Fls_CheckStatusType)u16StatusProgram;
            }
            else
            {
                /* Writing successfully */
                eReturnCode = FLS_JOB_OK;
            }
            Fls_StartAddress += (uint8)FLS_WRITE_QPAGE;
            u32Length -= (uint8)FLS_WRITE_QPAGE;
        }
        /* Start address has to align with 32 and length >= 32 bytes*/
        else if (((Fls_u8LocationWritesDataRegs % 8U) == 0U) && (u32Length >= 32U))
        {
            /* Reading status of program */
            u16StatusProgram = FlashProgrambytes(Fls_StartAddress, FLS_WRITE_PAGE, u8DomainIdValue);
            if ((uint16)FLS_JOB_OK != (uint16)u16StatusProgram)
            {
                /*had Errors when write*/
                /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
              return (Fls_CheckStatusType)u16StatusProgram;
            }
            else
            {
                /* Writing successfully */
                eReturnCode = FLS_JOB_OK;
            }
            Fls_StartAddress += (uint8)FLS_WRITE_PAGE;
            u32Length -= (uint8)FLS_WRITE_PAGE;
        }
        else
        {
            /* Reading status of program */
            u16StatusProgram = FlashProgrambytes(Fls_StartAddress, FLS_WRITE_DOUBLE_WORD, u8DomainIdValue);
            if ((uint16)FLS_JOB_OK != (uint16)u16StatusProgram)
            {
                /*had Errors when write*/
                /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
                return (Fls_CheckStatusType)u16StatusProgram;
            }
            else
            {
                /* Writing successfully */
                eReturnCode = FLS_JOB_OK;
            }
            Fls_StartAddress += (uint8)FLS_WRITE_DOUBLE_WORD;
            u32Length -= (uint8)FLS_WRITE_DOUBLE_WORD;
        }
        /*write to next sector */
        if ((Fls_StartAddress == Fls_EndEachSectorAddress) && (0U != u32Length))
        {
            u32SectorsNeedToBeWritten += 4U;
            /* Clear the clock bit of next sector */
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (FLS_JOB_OK != ClearLock(*(uint32 *)u32SectorsNeedToBeWritten, u8DomainIdValue))
            {
                /* was the errors*/
                /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
            /*Check lock bit of the next sector */
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (FLS_UNPROTECT_SECTOR != GetLock(*(uint32 *)u32SectorsNeedToBeWritten))
            {
                /* was the errors*/
                /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
                return FLS_JOB_FAILED;
            }
            /* Address of next sectors */
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            Fls_StartAddress = (uint32)GetBaseAddressOfSector(*(uint32 *)u32SectorsNeedToBeWritten);
            /* End address of each sector */
            Fls_EndEachSectorAddress = Fls_StartAddress + FLS_SECTOR_SIZE;
        }
    }
    /* Verify write then writing the data */
    if (bProgramVerifyAfterWriting == (boolean)STD_ON)
    {
        if (FLS_JOB_OK != ProgramVerify(u32LogicalAddressProgramVerify, pSourceAddressPtr, u32LengthProgramVerify))
        {
            /* Not blank Data*/
            /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
            return FLS_PROGRAM_VERIFY_FAILED;
        }
    }

    return eReturnCode;
}
static uint16 FlashProgrambytes(uint32 u32StartAddress, Fls_ProgSizeType eWriteMode, uint8 u8DomainIdValue)
{
    uint16 u16ReturnCode = 0U; /* return code */
    uint32 u32ValueTimeOut = 0U;
    uint32 u32Counter = 0U;
    uint8 u8Counter1 = 0U;
    uint32 u32DatasWrite = 0U;
    uint8 u8ActualDomainIDs = 0U;
    uint8 u8TmpData = 0U;

    /* Update timeout value*/
    u32ValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;
    /* When enable the Timeout*/
    if ((boolean)STD_ON == bEnableTimeOut)
    {
        /* Checking domain ID before staring program sequence */
        do
        {
            /* Write the address to be programmed using logical address registers located in the Platform Flash Controller */
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_WRITE32(PFLASH_PFCPGM_PEADR_L_ADDR32, (uint32)u32StartAddress);
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            u8ActualDomainIDs = (uint8)((REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_PEID_U32) >> FLASH_MCR_PEID_SHIFT_U32);
            /*Decrease the Timeout value*/
            u32ValueTimeOut--;
        } while ((u8ActualDomainIDs != u8DomainIdValue) && (0U < u32ValueTimeOut));
        /*Errors Timeout because wait for the Done bit long time*/
        if (0U == u32ValueTimeOut)
        {
            /*Errors Timeout because wait for the Done bit long time*/
            /* @violates @ref FlashProgram_c_REF_1 A function should have a single point of exit at the end */
            return (uint16)FLS_TIMEOUT_FAILED;
        }
    }
    else
    {
        /* Checking domain ID before staring program sequence */
        do
        {
            /* Write the address to be programmed using logical address registers located in the Platform Flash Controller */
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            REG_WRITE32(PFLASH_PFCPGM_PEADR_L_ADDR32, (uint32)u32StartAddress);
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            u8ActualDomainIDs = (uint8)((REG_READ32(FLASH_MCR_ADDR32) & FLASH_MCR_PEID_U32) >> FLASH_MCR_PEID_SHIFT_U32);
        } while (u8ActualDomainIDs != u8DomainIdValue);
    }
    /* Data to be programmed must be written in the appropriate DATAX register */
    for (u32Counter = 0UL; u32Counter < ((uint32)(eWriteMode) / 4U); u32Counter++)
    {
        u32DatasWrite = 0U;
        /* Checking source address was not aligned*/
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != ((uint32)Fls_u32SourceAddressPtr % 4U))
        {
            for (u8Counter1 = 0; u8Counter1 < 4U; u8Counter1++)
            {
                /* Read 1 separate byte for source address */
                /*
                * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                */
                u8TmpData = *(uint8 *)Fls_u32SourceAddressPtr;
                u32DatasWrite = u32DatasWrite | (uint32)((uint32)u8TmpData << ((uint32)u8Counter1 * 8UL));
                Fls_u32SourceAddressPtr += 1U;
            }
        }
        /* source address was aligned */
        else
        {
            /* Read 4bytes for source address*/
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            u32DatasWrite = *(uint32 *)Fls_u32SourceAddressPtr;
            /* Increase the source address pointer*/
            Fls_u32SourceAddressPtr += 4U;
        }
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        * @violates @ref FlashProgram_c_REF_4 The value of a composite expression shall no be cast to a different essential type category or a wider essential type
        */
        REG_WRITE32(FLASH_DATAx_ADDR32 + (uint32)(Fls_u8LocationWritesDataRegs * 4U), u32DatasWrite);
        /* Increase the written data registers */
        Fls_u8LocationWritesDataRegs += 1U;
        /* Reset when touching the maximum (DATA0 - DATA31)*/
        if ((FLS_DATA_SIZE_BYTES_U32 / 4U) == Fls_u8LocationWritesDataRegs)
        {
            Fls_u8LocationWritesDataRegs = 0U;
        }
    }
    /* setup program operation */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_SET32(FLASH_MCR_ADDR32, FLASH_MCR_PGM_U32);
    /* start internal erase/program sequence */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_SET32(FLASH_MCR_ADDR32, FLASH_MCR_EHV_U32);
    /* Reset the timeout */
    u32ValueTimeOut = u32ValueWaitDoneBitOrDomainIDsTimeOut;
    /* When enable the Timeout*/
    if ((boolean)STD_ON == bEnableTimeOut)
    {
        /* Wait until done or abort timeout is reached */
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        while ((0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32)) && (0U < u32ValueTimeOut))
        {
            /*Decrease the Timeout value*/
            u32ValueTimeOut--;
        }
        /* Confirm MCRS[PEG] = 1 and timeout value */
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if ((0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PEG_U32)) && (0U != u32ValueTimeOut))
        {
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C))
            {
                /* Previous program or erase protection error encountered or Previous program or erase sequence encountered an error*/
                u16ReturnCode = (uint16)FLS_JOB_FAILED;
            }
            else
            {
                /* Programed successfully */
                u16ReturnCode = (uint16)FLS_JOB_OK;
            }
        }
        else
        {
            /* Errors regarding timeout which reached to zero */
            if (0U == u32ValueTimeOut)
            {
                u16ReturnCode = (uint16)FLS_TIMEOUT_FAILED;
            }
            /* Errors regarding failed hardware*/
            else
            {
                u16ReturnCode = (uint16)FLS_JOB_FAILED;
            }
        }
    }
    else
    {
        /* Wait until done or abort timeout is reached */
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        while (0U == REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_DONE_U32))
        {
            /* Waiting for DONE bit without timeout */
        }
        /* Confirm MCRS[PEG] = 1 */
        /*
        * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PEG_U32))
        {
            /*
            * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(FLASH_MCRS_ADDR32, FLASH_MCRS_PES_W1C | FLASH_MCRS_PEP_W1C))
            {
                /* Previous program or erase protection error encountered or Previous program or erase sequence encountered an error*/
                u16ReturnCode = (uint16)FLS_JOB_FAILED;
            }
            else
            {
                /* Programed successfully */
                u16ReturnCode = (uint16)FLS_JOB_OK;
            }
        }
        else
        {
            /* Errors regarding failed hardware*/
            u16ReturnCode = (uint16)FLS_JOB_FAILED;
        }
    }
    /* Terminate erase operation */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_EHV_U32);
    /* Terminate erase operation */
    /*
    * @violates @ref FlashProgram_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
    * @violates @ref FlashProgram_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
    */
    REG_BIT_CLEAR32(FLASH_MCR_ADDR32, FLASH_MCR_PGM_U32);

    return u16ReturnCode;
}
