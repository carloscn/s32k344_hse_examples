/*******************************************************************************
*                                                                              *
*  FILE NAME     : GetLock.c                                                   *
*  FUNCTION      : GetLock                                                     *
*  DESCRIPTION   : This function will get the lock bit which corresponded to   *
*                  that sector.                                                *
*  PARAMETERS    : pConfig - Flash driver configuration structure              *
*                                                                              *
*  RETURN        : FLS_UNPROTECT_SECTOR         - The sector was unprotected   *
*                : FLS_PROTECT_SECTOR           - The sector was protected     *
*                : FLS_NO_CHECK_PROTECT_SECTOR  - Not check because of wrong   *
*                  parameters                                                  *
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
/**
* @page misra_violations MISRA-C:2012 violations
*
* @section GetLock_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section GetLock_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/
#include "Fls_Registers.h"
#include "Fls_Api.h"
#include "hse_host_flash.h"

Fls_GetStatusLockBitType GetLock( uint32 Fls_VirtualSectors )
{
    Fls_GetStatusLockBitType eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;     /* return code */
    uint32 SectorId;
    
    /*Sector is in the Data Block _ Block 4*/
    if ((uint32)Fls_VirtualSectors < VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID)
    {
        SectorId=(uint32)Fls_VirtualSectors;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_DFLASHBLK_SPELOCK_ADDR32,(1U << SectorId)))
        { 
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else 
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }
    }  
    /*Sector is in the Super Sector zone _ Block 0*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_0_SSEC_REGION_LAST_SEC_ID))
    {
        SectorId = ((uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID)/8U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */        
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SSPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }    
    }
    /*Sector is in the 8KB Sector zone _ Block 0*/
    else if ((VIRTUAL_CODE_FLASH_BLOCK_0_SEC_REGION_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_0_LAST_SEC_ID))
    {
        SectorId = (uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_0_SEC_REGION_FIRST_SEC_ID; 
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */        
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }
    }
    /*Sector is in the Super Sector zone _ Block 1*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_1_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_1_SSEC_REGION_LAST_SEC_ID))
    {
        SectorId = ((uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_1_FIRST_SEC_ID)/8U;   
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SSPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        } 
    }
    /*Sector is in the 8KB Sector zone _ Block 1*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_1_SEC_REGION_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_1_LAST_SEC_ID))
    {
        SectorId = (uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_1_SEC_REGION_FIRST_SEC_ID;    
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }     
    }
#ifdef CODE_FLASH_BLOCK_2_AVAILABLE
    /*Sector is in the Super Sector zone _ Block 2*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_2_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors ) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_2_SSEC_REGION_LAST_SEC_ID))
    {
        SectorId = ((uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_2_FIRST_SEC_ID)/8U;     
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */ 
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SSPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 2*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_2_SEC_REGION_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_2_LAST_SEC_ID))
    {
        SectorId = (uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_2_SEC_REGION_FIRST_SEC_ID;    
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
           eReturnCode = FLS_PROTECT_SECTOR;
        }                         
    }
#ifdef CODE_FLASH_BLOCK_3_AVAILABLE
    /*Sector is in the Super Sector zone _ Block 3*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_3_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_BLOCK_3_SSEC_REGION_LAST_SEC_ID))
    {
        SectorId = ((uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_3_FIRST_SEC_ID)/8U;   
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SSPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }  
    }
    /*Sector is in the 8KB Sector zone _ Block 3*/
    else if((VIRTUAL_CODE_FLASH_BLOCK_3_SEC_REGION_FIRST_SEC_ID <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= VIRTUAL_CODE_FLASH_ARRAY_LAST_SECTOR_ID))
    {
        SectorId = (uint32)Fls_VirtualSectors - VIRTUAL_CODE_FLASH_BLOCK_3_SEC_REGION_FIRST_SEC_ID;     
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }
    }
#endif
#endif
    /* Sector is in Utest*/
    else if((uint32)Fls_VirtualSectors == VIRTUAL_UTEST_SECTOR_ID)
    {
        SectorId = (uint32)Fls_VirtualSectors - VIRTUAL_UTEST_SECTOR_ID;   
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */         
        if (0U == REG_BIT_GET32(PFLASH_PFCBLKU_SPELOCK_ADDR32,(1U << SectorId)))
        {
            eReturnCode = FLS_UNPROTECT_SECTOR;
        }
        else
        {
            eReturnCode = FLS_PROTECT_SECTOR;
        }
    }
    else
    {
        eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
    }
   
    return eReturnCode;
}
