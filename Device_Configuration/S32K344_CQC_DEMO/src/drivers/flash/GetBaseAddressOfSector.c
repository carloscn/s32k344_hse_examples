/*******************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011-2018                  *
*                         All Rights Reserved                                  *
********************************************************************************

********************************************************************************
*                                                                              *
*               Standard Software Driver for C40                               *
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

#include "Fls_Registers.h"
#include "Fls_Api.h"

uint32 GetBaseAddressOfSector(uint32 Fls_VirtualSectors)
{
    volatile uint32 u32BaseAddressofSector = 0xFFFFFFFFU;

    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 9U;
    if ((uint32)Fls_VirtualSectors < 32U)
    {
        /*This sector is Data zone: Block 4*/
        u32BaseAddressofSector = FLS_DATA_BASE_ADDRESS + ((uint32)Fls_VirtualSectors * FLS_SECTOR_SIZE);
        u8SecureCounter++;
    }
    else if ((32U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 543U))
    {
        u32BaseAddressofSector = FLS_CODE_BASE_ADDRESS + (((uint32)Fls_VirtualSectors - 32U) * FLS_SECTOR_SIZE);
        u8SecureCounter++;
    }
    else if ((uint32)Fls_VirtualSectors == 544U)
    {
        u32BaseAddressofSector = FLS_UTEST_BASE_ADDRESS;
        u8SecureCounter++;
    }
    else
    {
        /* Errors when configure*/
        u32BaseAddressofSector = 0xFFFFFFFFU;
        u8SecureCounter++;
    }
    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER != u8SecureCounter)
    {
        /* There were hackers who skipped some instructions */
        u32BaseAddressofSector = 0xFFFFFFFFU;
    }

    return u32BaseAddressofSector;
}
