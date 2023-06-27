/*******************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011-2018                  *
*                         All Rights Reserved                                  *
********************************************************************************

********************************************************************************
*                                                                              *
*               Standard Software Driver for C40                               *
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

Fls_GetStatusLockBitType GetLock(uint32 Fls_VirtualSectors)
{
    Fls_GetStatusLockBitType eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR; /* return code */
    uint32 SectorId;

    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 1U;
    u8SecureCounter++;
    /*Sector is in the Data Block _ Block 4*/
    if ((uint32)Fls_VirtualSectors < 32U)
    {
        SectorId = (uint32)Fls_VirtualSectors;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK4_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 0*/
    else if ((32U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 127U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 32U) / 8U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 0*/
    else if ((128U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 159U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 128U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 1*/
    else if ((160U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 255U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 160U) / 8U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 1*/
    else if ((256U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 287U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 256U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 2*/
    else if ((288U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 383U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 288U) / 8U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 2*/
    else if ((384U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 415U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 384U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 3*/
    else if ((416U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 511U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 416U) / 8U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 3*/
    else if ((512U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 543U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 512U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    /* Sector is in Utest*/
    else if ((uint32)Fls_VirtualSectors == 544U)
    {
        SectorId = (uint32)Fls_VirtualSectors - 544U;
        /*
        * @violates @ref GetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref GetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLKU_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_UNPROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
        else
        {
            /* Checking if hackers tried to skip some instructions or not*/
            if (2U == u8SecureCounter)
            {
                eReturnCode = FLS_PROTECT_SECTOR;
                u8SecureCounter = 9U;
                u8SecureCounter++;
            }
            else
            {
                /* There were hackers who skipped some instructions */
                eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
            }
        }
    }
    else
    {
        eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
    }

    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER != u8SecureCounter)
    {
        /* There were hackers who skipped some instructions */
        eReturnCode = FLS_NO_CHECK_PROTECT_SECTOR;
    }

    return eReturnCode;
}
