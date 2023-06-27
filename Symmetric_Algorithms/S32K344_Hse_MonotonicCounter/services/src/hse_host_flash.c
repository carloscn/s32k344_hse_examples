/*============================================================================*/

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
/*============================================================================*/

/*=============================================================================
  Description
  ============================================================================*/
/**
 *   @file    host_flash.c
 *
 *   @brief   This is a host flash driver wrapper file.
 */

/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/
#include "hse_host_flash.h"
#include "hse_host_flashSrv.h"
#include "Fls_Api.h"

/*=============================================================================
  LOCAL MACROS
  ============================================================================*/

#define FLASH_INITIALIZED (0x55AAU)

/*=============================================================================
 *                  LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/
const uint32_t Utest_Sector_Array[] = {UTEST_FLASH_SEC};
const uint32_t DataF_Sector_Array[] = {DATA_FLASH_SEC};
const uint32_t Block0_Sector_Array[] = {BLOCK_0_SEC};
const uint32_t Block1_Sector_Array[] = {BLOCK_1_SEC};
const uint32_t Block2_Sector_Array[] = {BLOCK_2_SEC};
const uint32_t Block3_Sector_Array[] = {BLOCK_3_SEC};
/*=============================================================================
                  LOCAL CONSTANTS
  ============================================================================*/
static uint8_t Fls_DomainIDValue = 0;

/*=============================================================================
 *                               LOCAL VARIABLES
 =============================================================================*/

static const uint32_t FlashSectorsMemoryMap[] = {
    UTEST_FLASH_SEC,
    DATA_FLASH_SEC,
    BLOCK_0_SEC,
    BLOCK_1_SEC,
    BLOCK_2_SEC,
    BLOCK_3_SEC,
};

static const uint32_t LogicalStartAddressMemoryType[MEMORY_TYPE_MAX] =
{
    UTEST_MEMORY_LOGICAL_ADDR,
    APP_DATA_FLASH_MEMORY_LOGICAL_ADDR,
    HOST_BLK0_FLASH_MEMORY_LOGICAL_ADDR,
    HOST_BLK1_FLASH_MEMORY_LOGICAL_ADDR,
    HOST_BLK2_FLASH_MEMORY_LOGICAL_ADDR,
    HOST_BLK3_FLASH_MEMORY_LOGICAL_ADDR,
};
static const uint32_t PhysicalEndAddressMemoryType[MEMORY_TYPE_MAX] =
{
    UTEST_MEMORY_PHYSICAL_END_ADDR,
    APP_DATA_FLASH_MEMORY_PHYSICAL_END_ADDR,
    HOST_BLOCK0_MEMORY_PHYSICAL_END_ADDR,
    HOST_BLOCK1_MEMORY_PHYSICAL_END_ADDR,
    HOST_BLOCK2_MEMORY_PHYSICAL_END_ADDR,
    HOST_BLOCK3_MEMORY_PHYSICAL_END_ADDR,
};
static const uint32_t PhysicalStartAddressMemoryType[MEMORY_TYPE_MAX] =
{
    UTEST_MEMORY_PHYSICAL_START_ADDR,
    CODE_DATA_FLASH_PHYSICAL_START_ADDR,
    HOST_BLOCK0_MEMORY_PHYSICAL_START_ADDR,
    HOST_BLOCK1_MEMORY_PHYSICAL_START_ADDR,
    HOST_BLOCK2_MEMORY_PHYSICAL_START_ADDR,
    HOST_BLOCK3_MEMORY_PHYSICAL_START_ADDR,

};

#define NUMBER_OF_SECTORS NUM_OF_ELEMS(FlashSectorsMemoryMap)

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/
/* FlsConfigRandomsector */
const FLASH_CONFIG FlsConfigBAFsector =
    {
        (boolean)STD_ON,
        (uint32)1000000U,
        (const uint32 *)FlashSectorsMemoryMap,
        (uint32)NUMBER_OF_SECTORS,
        (Fls_InterfaceAccessType)FLS_MAIN_INTERFACE};

/*=============================================================================
  LOCAL FUNCTION PROTOTYPES
  ============================================================================*/

/*=============================================================================
  GLOBAL FUNCTION PROTOTYPES
  ============================================================================*/
/* FUNCTION NAME: HostFlash_Init
 *
 * DESCRIPTION:
 * This function initializes flash driver.
 */
Fls_CheckStatusType HostFlash_Init(void)
{
    Fls_CheckStatusType ReturnCode = FLS_INPUT_PARAM_FAILED;
    static uint32_t IsFlashInitialized;
    (void)ReturnCode; /* MISRA-C:2012/AMD1 R.2.2 */
    if (FLASH_INITIALIZED == IsFlashInitialized)
    {
        ReturnCode = FLS_JOB_OK;
        goto END;
    }

    volatile uint32_t *FlashRamAddr;
    volatile uint32_t *FlashSrcAddr;
    volatile uint32_t *FlashSrcEndAddr;
    uint32_t i;

    FlashRamAddr = FLASH_DRIVER_RAM_DST_START_ADDRESS;
    FlashSrcAddr = FLASH_DRIVER_FLASH_SRC_START_ADDRESS;
    FlashSrcEndAddr = FLASH_DRIVER_FLASH_SRC_END_ADDRESS;

    /*Copying the UnsecureBAF Code from flash to RAM to avoid read while write
     *  violation */
    for (i = 0U; i < (((uint32_t)FlashSrcEndAddr - (uint32_t)FlashSrcAddr) / 4U); i++)
    {
        FlashRamAddr[i] = FlashSrcAddr[i];
    }

    ReturnCode = FlashInit(&FlsConfigBAFsector);
    if (FLS_JOB_OK != ReturnCode)
    {
        goto END;
    }

    ReturnCode = FLS_JOB_OK;
    IsFlashInitialized = FLASH_INITIALIZED;
END:
    return ReturnCode;
}

/* FUNCTION NAME: HostFlash_Program
 *
 * DESCRIPTION:
 * This function Programs Bytes in Flash memory.
 * length must be multiple of 8 Bytes.
 */
Fls_CheckStatusType HostFlash_Program(MEMORY_TYPE MemoryType, uint32_t Address,
                                      uint8_t *SourceAddress, uint32_t length)
{
    uint32_t AddrOffset;
    uint32_t LogicalAddr;
    uint32_t VirtualSectorStartAddr;
    uint32_t PhysicalSectorStartAddr;
    Fls_CheckStatusType Status = FLS_JOB_FAILED;

    (void)Status; /* MISRA-C:2012/AMD1 R.2.2 */

    Status = HostFlash_Init();
    if (FLS_JOB_OK != Status)
    {
        goto END;
    }
    Status = FLS_JOB_FAILED;

    if (MemoryType >= MEMORY_TYPE_MAX)
    {
        goto END;
    }
    if ((((((uint64_t)Address)) <
          ((uint64_t)PhysicalStartAddressMemoryType[MemoryType])) ||
         (((uint64_t)Address + ((uint64_t)(length))) >
          ((uint64_t)PhysicalEndAddressMemoryType[MemoryType] + 1U))))
    {
        goto END;
    }
    /*Calculating the offset address with respect to sector boundary */

    VirtualSectorStartAddr = LogicalStartAddressMemoryType[MemoryType];
    PhysicalSectorStartAddr = PhysicalStartAddressMemoryType[MemoryType];

    AddrOffset = Address - PhysicalSectorStartAddr;
    /*Calculating the logical addrss that will be passed to flash driver */
    LogicalAddr = VirtualSectorStartAddr + AddrOffset;

    /*Program the required number of bytes at the location
      on main interface)*/
    Status=FlashProgram(
        LogicalAddr,
        (const uint8_t *)(SourceAddress),
        length,
        (boolean)STD_ON,
        (boolean)STD_ON,
        Fls_DomainIDValue);
    if (FLS_JOB_OK != Status)
    {
        goto END;
    }

END:
    return Status;
}

/* FUNCTION NAME: HostFlash_Erase
 *
 * DESCRIPTION:
 * This function Erases Sectors in Flash memory.
 */
Fls_CheckStatusType HostFlash_Erase(MEMORY_TYPE MemoryType, uint32_t Address,
                                    uint32_t NoOfSectors)
{
    uint32_t VirtualSectorStartAddr;
    uint32_t PhysicalSectorStartAddr;
    uint32_t AddrOffset;
    uint32_t LogicalAddr;
    Fls_CheckStatusType Status = FLS_JOB_FAILED;

    (void)Status; /* MISRA-C:2012/AMD1 R.2.2 */

    Status = HostFlash_Init();
    if (FLS_JOB_OK != Status)
    {
        goto END;
    }
    Status = FLS_JOB_FAILED;

    if (MemoryType >= MEMORY_TYPE_MAX)
    {
        goto END;
    }

    /*Calculating the offset address with respect to sector boundary */

    VirtualSectorStartAddr = LogicalStartAddressMemoryType[MemoryType];
    PhysicalSectorStartAddr = PhysicalStartAddressMemoryType[MemoryType];

    AddrOffset = Address - PhysicalSectorStartAddr;
    /*Calculating the logical addrss that will be passed to flash driver */
    LogicalAddr = VirtualSectorStartAddr + AddrOffset;
    LogicalAddr = LogicalAddr / SECTOR_SIZE;
    LogicalAddr = LogicalAddr * SECTOR_SIZE;

    if (((((((uint64_t)PhysicalSectorStartAddr)) <
           (uint64_t)PhysicalStartAddressMemoryType[MemoryType]) ||
          (((uint64_t)PhysicalSectorStartAddr + ((uint64_t)(NoOfSectors * SECTOR_SIZE))) >
           ((uint64_t)PhysicalEndAddressMemoryType[MemoryType] + 1U)))))
    {
        goto END;
    }

    /*Erasing the sectors on main interface first before writing */
    Status=FlashErase(LogicalAddr,(uint32_t)(SECTOR_SIZE*NoOfSectors),
            (boolean)STD_OFF,Fls_DomainIDValue);
    if(FLS_JOB_OK!=Status)
    {
        goto END;
    }
END:
    return Status;
}

/* FUNCTION NAME: HostFlash_ProgramHseFwFeatureFlag
 *
 * DESCRIPTION:
 * This function programs hse fw feature flag and its snapshot in UTEST.
 */
Fls_CheckStatusType HostFlash_ProgramHseFwFeatureFlag(void)
{
    Fls_CheckStatusType FlashStatus = FLS_JOB_FAILED;
    uint64_t HSEFWFeatureFlagActivate = WITH_HSE_FIRMWARE_USAGE_VALUE;
    uint64_t *HSEFWUsageFeatureFlag = (uint64_t *)ADDRESS_HSE_FIRMWARE_USAGE_FEATURE;
    uint64_t *HSEFWUsageFeatureFlagSnap =
        (uint64_t *)ADDRESS_HSE_FIRMWARE_USAGE_FEATURE_SNAPSHOT;

    if ((WITHOUT_HSE_FIRMWARE_USAGE_VALUE == *HSEFWUsageFeatureFlag) &&
        (WITHOUT_HSE_FIRMWARE_USAGE_VALUE == *HSEFWUsageFeatureFlagSnap))
    {
        /* Program the HSE Firmware Snapshot Location to Enable HSE Firmware */
        FlashStatus = HostFlash_Program(UTEST_MEMORY,                                 /* Type of flash memory*/
                                        (uint32_t)ADDRESS_HSE_FIRMWARE_USAGE_FEATURE, /* Physical memory start address*/
                                        (uint8_t *)&HSEFWFeatureFlagActivate,         /* Source Address */
                                        0x8U);                                        /* Length of data to copy in bytes */

        if (FLS_JOB_OK != FlashStatus)
        {
            /* Status Flag ERROR */
            goto RETURN_ERROR;
        }

        FlashStatus = FLS_JOB_FAILED;
        /* Program the HSE Firmware Snapshot Location to Enable HSE Firmware */
        FlashStatus = HostFlash_Program(UTEST_MEMORY,                                          /* Type of flash memory*/
                                        (uint32_t)ADDRESS_HSE_FIRMWARE_USAGE_FEATURE_SNAPSHOT, /* Physical memory start address*/
                                        (uint8_t *)&HSEFWFeatureFlagActivate,                  /* Source Address */
                                        0x8U);                                                 /* Length of data to copy in bytes */

        if (FLS_JOB_OK != FlashStatus)
        {
            /* Status Flag ERROR */
            goto RETURN_ERROR;
        }

        /* Verify programmed data */
        if ((WITH_HSE_FIRMWARE_USAGE_VALUE != *HSEFWUsageFeatureFlag) ||
            (WITH_HSE_FIRMWARE_USAGE_VALUE != *HSEFWUsageFeatureFlagSnap))
        {
            /* Status Flag ERROR */
            FlashStatus = FLS_JOB_FAILED;
        }
        else
        {
            /* Status Flag SUCCESS */
            FlashStatus = FLS_JOB_OK;
        }
    }
RETURN_ERROR:
    return FlashStatus;
}
