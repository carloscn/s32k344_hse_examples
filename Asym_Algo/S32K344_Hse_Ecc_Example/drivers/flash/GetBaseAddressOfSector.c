/*******************************************************************************
*                                                                              *
*  FILE NAME     : GetBaseAddressOfSector.c                                    *
*  FUNCTION      : GetBaseAddressOfSector                                      *
*  DESCRIPTION   : This function will get base address corresponding to sectors*
*                  configured.                                                 *
*  PARAMETERS    : Fls_VirtualSectors - The sector need to be gotten the base  *
*                  address                                                     *
*  RETURN        : the address base corresponds to sectors                     *
*                  Note: if return 0xFFFFFFFFU it means that                   *
*                  the input parameter was wrong.                              *
*******************************************************************************/
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

#include "Fls_Registers.h"
#include "Fls_Api.h"

uint32 GetBaseAddressOfSector( uint32 Fls_VirtualSectors)
{
    volatile uint32 u32BaseAddressofSector = 0xFFFFFFFFU;    
    
    if ((uint32)Fls_VirtualSectors < VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID)
    {     
        /*This sector is Data zone: Block 4*/
        u32BaseAddressofSector = FLS_DATA_BASE_ADDRESS + ((uint32)Fls_VirtualSectors*FLS_SECTOR_SIZE);
    }    
    else if((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_ARRAY_LAST_SECTOR_ID)
    {
        u32BaseAddressofSector = FLS_CODE_BASE_ADDRESS + (((uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID)*FLS_SECTOR_SIZE);    
    }
    else if((uint32)Fls_VirtualSectors == VIRTUAL_UTEST_SECTOR_ID)
    {
        u32BaseAddressofSector = FLS_UTEST_BASE_ADDRESS;
    }    
    else
    {
        /* Errors when configure*/
        u32BaseAddressofSector = 0xFFFFFFFFU;
    }
    
    return u32BaseAddressofSector;
}
