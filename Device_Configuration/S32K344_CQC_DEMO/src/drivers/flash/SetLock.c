/*******************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011-2018                  *
*                         All Rights Reserved                                  *
********************************************************************************

********************************************************************************
*                                                                              *
*               Standard Software Driver for C40                               *
*                                                                              *
*  FILE NAME     : SetLock.c                                                   *
*  FUNCTION      : SetLock                                                     *
*  DESCRIPTION   : This function will set the lock bit which corresponded to   *
*                  that sector.                                                *
*  PARAMETERS    : Fls_VirtualSectors - The sector need to be cleared          *
*                  u8DomainIdValue    - The current Domain value                *
*     (Domain ID can be changed, depending on XRDCs are enabled by the user)   *
*                                                                              *
*  RETURN        : FLS_JOB_OK         - Set successfully                       *
*                : FLS_JOB_FAILED     - Set unsuccessfully                     *
********************************************************************************/
/**
* @page misra_violations MISRA-C:2012 violations
*
* @section SetLock_c_REF_2
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object and an integer type.
* The cast is used to access memory mapped registers.
*
* @section SetLock_c_REF_3
* Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between pointer to void and an arithmetic type.
* This violation is due to casting unsigned long to pointer and access these addresses for updating  contents in that address.
*
*/
#include "Fls_Registers.h"
#include "Fls_Api.h"

Fls_CheckStatusType SetLock(uint32 Fls_VirtualSectors, uint8 u8DomainIdValue)
{
    Fls_CheckStatusType eReturnCode = FLS_JOB_FAILED; /* return code */
    uint32 SectorId = 0U;
    uint8 u8LockDomainIDValue = 0U;
    uint32 u32TempLockMasterRegister = 0U;

    /* A secure counter will help to determine the attack if any hacker trying to skipping some instructions */
    u8SecureCounter = 1U;
    u8SecureCounter++;
    /*Sector is in the Data Block _ Block 4*/
    if ((uint32)Fls_VirtualSectors < 32U)
    {
        SectorId = (uint32)Fls_VirtualSectors;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK4_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK4_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK4_LOCKMASTER_S0_ADDR32 + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*Set lock bit */
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK4_SPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*Set lock bit */
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK4_SPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 0*/
    else if ((32U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 127U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 32U) / 8U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK0_SSETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32 + 0x00U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*Set lock bit */
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK0_SSPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*Set lock bit */
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK0_SSPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 0*/
    else if ((128U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 159U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 128U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK0_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK0_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32 + 0x0U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK0_SPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK0_SPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 1*/
    else if ((160U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 255U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 160U) / 8U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK1_SSETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32 + 0x10U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK1_SSPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK1_SSPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 1*/
    else if ((256U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 287U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 256U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK1_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK1_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32 + 0x20U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK1_SPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK1_SPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 2*/
    else if ((288U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 383U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 288U) / 8U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Lock bit is owned by the masters having the domain id mentioned */
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK2_SSETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32 + 0x20U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK2_SSPELOCK_ADDR32, 1U << SectorId);
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK2_SSPELOCK_ADDR32, 1U << SectorId);
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 2*/
    else if ((384U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 415U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 384U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK2_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /* Lock bit is owned by the masters having the domain id mentioned */
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK2_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32 + 0x40U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK2_SPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK2_SPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the Super Sector zone _ Block 3*/
    else if ((416U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 511U))
    {
        SectorId = ((uint32)Fls_VirtualSectors - 416U) / 8U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SSPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK3_SSETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32 + 0x30U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK3_SSPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK3_SSPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in the 8KB Sector zone _ Block 3*/
    else if ((512U <= (uint32)Fls_VirtualSectors) && ((uint32)Fls_VirtualSectors <= 543U))
    {
        SectorId = (uint32)Fls_VirtualSectors - 512U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLK3_SPELOCK_ADDR32, (1U << SectorId)))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLK3_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    u32TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32 + 0x60U + ((SectorId / 4U) * 4U);
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)((REG_READ32(u32TempLockMasterRegister) >> ((SectorId - ((SectorId / 4U) * 4U)) * 8U)) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLK3_SPELOCK_ADDR32, (1U << SectorId));
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLK3_SPELOCK_ADDR32, (1U << SectorId));
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    /*Sector is in Utest*/
    else if ((uint32)Fls_VirtualSectors == 544U)
    {
        SectorId = (uint32)Fls_VirtualSectors - 544U;
        /*
        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
        */
        if (0U == REG_BIT_GET32(PFLASH_PFCBLKU_SPELOCK_ADDR32, PFLASH_PFCBLKU_SPELOCK_SLCK00_U32))
        {
            /*
            * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
            * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
            */
            if (0U != REG_BIT_GET32(PFLASH_PFCBLKU_SETSLOCK_ADDR32, 1U << SectorId))
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    u8LockDomainIDValue = (uint8)(REG_READ32(PFLASH_PFCBLKU_LOCKMASTER_S_ADDR32) & 0xFFU);
                    /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                    if (u8LockDomainIDValue != u8DomainIdValue)
                    {
                        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
                        eReturnCode = FLS_JOB_FAILED;
                    }
                    /* the lock bits can be modified because it same domain ID*/
                    else
                    {
                        /*
                        * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                        * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                        */
                        REG_BIT_SET32(PFLASH_PFCBLKU_SPELOCK_ADDR32, PFLASH_PFCBLKU_SPELOCK_SLCK00_U32);
                        /* The lock bit was set successfully */
                        eReturnCode = FLS_JOB_OK;
                    }
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
            else
            {
                /* Checking if hackers tried to skip some instructions or not*/
                if (2U == u8SecureCounter)
                {
                    u8SecureCounter = 9U;
                    u8SecureCounter++;
                    /*
                    * @violates @ref SetLock_c_REF_2 A conversion should not be performed between a pointer to object and an integer type
                    * @violates @ref SetLock_c_REF_3 A cast shall not be performed between pointer to void and an arithmetic type
                    */
                    REG_BIT_SET32(PFLASH_PFCBLKU_SPELOCK_ADDR32, PFLASH_PFCBLKU_SPELOCK_SLCK00_U32);
                    /* The lock bit was set successfully */
                    eReturnCode = FLS_JOB_OK;
                }
                else
                {
                    /* There were hackers who skipped some instructions */
                    eReturnCode = FLS_JOB_FAILED;
                }
            }
        }
    }
    else
    {
        eReturnCode = FLS_JOB_FAILED;
    }
    /* Checking if hackers tried to skip some instructions or not*/
    if (FLS_WELL_KNOWN_SECURE_COUNTER != u8SecureCounter)
    {
        /* There were hackers who skipped some instructions */
        eReturnCode = FLS_JOB_FAILED;
    }

    return eReturnCode;
}
