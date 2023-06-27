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
==============================================================================*/
/**
 *   @file    hse_host_flashSrv.h
 *
 *   @brief   This file contains host flash api.
 */

#ifndef HOST_FLASHSRV_H
#define HOST_FLASHSRV_H
/*=============================================================================
 *                                 INCLUDE FILES
 =============================================================================*/
#include <stdint.h>
#include "Fls_Type.h"
/*=============================================================================
                                      MACROS
==============================================================================*/
#define UTEST_MEMORY_PHYSICAL_START_ADDR                    (0x1B000000U)
#define ADDRESS_HSE_FIRMWARE_USAGE_FEATURE                  (UTEST_MEMORY_PHYSICAL_START_ADDR)
#define ADDRESS_HSE_FIRMWARE_USAGE_FEATURE_SNAPSHOT         (UTEST_MEMORY_PHYSICAL_START_ADDR+0x210U)

#define WITH_HSE_FIRMWARE_USAGE_VALUE                       (0xAABBCCDDDDCCBBAAULL)
#define WITHOUT_HSE_FIRMWARE_USAGE_VALUE                    (0xFFFFFFFFFFFFFFFFULL)

#define CODE_FLASH_START_ADDRESS                            (0x00400000U)
#define APP_DATA_FLASH_MEMORY_PHYSICAL_START_ADDR           (0x10000000U)
#define UTEST_MEMORY_PHYSICAL_END_ADDR                      (0x1B001FFFU)

/** Data Flash memory addresses. */
#define HSE_FW_DATA_FLASH_BACKUP_END_ADDR                   (0x10036000UL)
#define APP_DATA_FLASH_MEMORY_PHYSICAL_END_ADDR             (0x1003FFFFUL)

#define SIZE_OF_BLOCK(x)                                    ((sizeof(x)/4U)*8192U)

typedef uint8_t MEMORY_TYPE;
#define UTEST_MEMORY                                        ((MEMORY_TYPE)0x00U)
#define HOST_DATA_FLASH_MEMORY                              ((MEMORY_TYPE)0x01U)
#define HOST_BLOCK0_CODE_MEMORY                             ((MEMORY_TYPE)0x02U)
#define HOST_BLOCK1_CODE_MEMORY                             ((MEMORY_TYPE)0x03U)
#define HOST_BLOCK2_CODE_MEMORY                             ((MEMORY_TYPE)0x04U)
#define HOST_BLOCK3_CODE_MEMORY                             ((MEMORY_TYPE)0x05U)
#define MEMORY_TYPE_MAX                                     ((MEMORY_TYPE)0x06U)

#define SECTOR_SIZE                                         (8192U)
#define SECTOR_SIZE_MASK                                    (0xFFFFE000U)

/*Virtual Start Address of Different memory type */
#define UTEST_MEMORY_LOGICAL_ADDR                           (0U * SECTOR_SIZE)

/*
 * Block Number = Logical Address of Previous Block + (Number of Blocks taken by Previous Memory Type)* Sector Size
 */
#define APP_DATA_FLASH_MEMORY_LOGICAL_ADDR                  (SIZE_OF_BLOCK(Utest_Sector_Array))

#define HOST_BLK0_FLASH_MEMORY_LOGICAL_ADDR                 (APP_DATA_FLASH_MEMORY_LOGICAL_ADDR+\
                                                            SIZE_OF_BLOCK(DataF_Sector_Array))

#define HOST_BLK1_FLASH_MEMORY_LOGICAL_ADDR                 (HOST_BLK0_FLASH_MEMORY_LOGICAL_ADDR+\
                                                            SIZE_OF_BLOCK(Block0_Sector_Array))
 
#define HOST_BLK2_FLASH_MEMORY_LOGICAL_ADDR                 (HOST_BLK1_FLASH_MEMORY_LOGICAL_ADDR+\
                                                            SIZE_OF_BLOCK(Block1_Sector_Array))
 
#define HOST_BLK3_FLASH_MEMORY_LOGICAL_ADDR                 (HOST_BLK2_FLASH_MEMORY_LOGICAL_ADDR+\
                                                            SIZE_OF_BLOCK(Block2_Sector_Array))

#define CODE_FLASH_BLOCK_0                                  (CODE_FLASH_START_ADDRESS)
#define CODE_FLASH_BLOCK_1                                  (CODE_FLASH_BLOCK_0 + SIZE_OF_FLASH_BLOCK)
#define CODE_FLASH_BLOCK_2                                  (CODE_FLASH_BLOCK_1 + SIZE_OF_FLASH_BLOCK)
#define CODE_FLASH_BLOCK_3                                  (CODE_FLASH_BLOCK_2 + SIZE_OF_FLASH_BLOCK)
#define CODE_FLASH_BLOCK_4                                  (CODE_FLASH_BLOCK_3 + SIZE_OF_FLASH_BLOCK)

#define HOST_BLOCK0_MEMORY_PHYSICAL_END_ADDR                (CODE_FLASH_BLOCK_1 - 1U)
#define HOST_BLOCK1_MEMORY_PHYSICAL_END_ADDR                (CODE_FLASH_BLOCK_2 - 1U)
#define HOST_BLOCK2_MEMORY_PHYSICAL_END_ADDR                (CODE_FLASH_BLOCK_3 - 1U)
#define HOST_BLOCK3_MEMORY_PHYSICAL_END_ADDR                (CODE_FLASH_BLOCK_4 - 1U)

#define GET_PHYSICAL_START_ADDRESS(EndAddress,SubArray)     (EndAddress + 1U - SIZE_OF_BLOCK(SubArray))                  

#define CODE_DATA_FLASH_PHYSICAL_START_ADDR                 (GET_PHYSICAL_START_ADDRESS(APP_DATA_FLASH_MEMORY_PHYSICAL_END_ADDR,DataF_Sector_Array))

#define HOST_BLOCK0_MEMORY_PHYSICAL_START_ADDR              ((GET_PHYSICAL_START_ADDRESS(HOST_BLOCK0_MEMORY_PHYSICAL_END_ADDR,Block0_Sector_Array)))
#define HOST_BLOCK1_MEMORY_PHYSICAL_START_ADDR              ((GET_PHYSICAL_START_ADDRESS(HOST_BLOCK1_MEMORY_PHYSICAL_END_ADDR,Block1_Sector_Array)))
#define HOST_BLOCK2_MEMORY_PHYSICAL_START_ADDR              ((GET_PHYSICAL_START_ADDRESS(HOST_BLOCK2_MEMORY_PHYSICAL_END_ADDR,Block2_Sector_Array)))
#define HOST_BLOCK3_MEMORY_PHYSICAL_START_ADDR              ((GET_PHYSICAL_START_ADDRESS(HOST_BLOCK3_MEMORY_PHYSICAL_END_ADDR,Block3_Sector_Array)))

/*=============================================================================
 *                        TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/

/*=============================================================================
                                     CONSTANTS
==============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/
extern uint32_t FLASH_DRIVER_RAM_DST_START_ADDRESS[];
extern uint32_t FLASH_DRIVER_FLASH_SRC_START_ADDRESS[];
extern uint32_t FLASH_DRIVER_FLASH_SRC_END_ADDRESS[];

extern const uint32_t Utest_Sector_Array[];
extern const uint32_t DataF_Sector_Array[];
extern const uint32_t Block0_Sector_Array[];
extern const uint32_t Block1_Sector_Array[];
extern const uint32_t Block2_Sector_Array[];
extern const uint32_t Block3_Sector_Array[];
/*=============================================================================
                                FUNCTION PROTOTYPES
==============================================================================*/

extern Fls_CheckStatusType HostFlash_Init(void);
extern Fls_CheckStatusType HostFlash_Program(MEMORY_TYPE MemoryType, uint32_t DestAddress, uint8_t* SourceAddress, uint32_t length);
extern Fls_CheckStatusType HostFlash_Erase(MEMORY_TYPE MemoryType, uint32_t DestAddress, uint32_t NoOfSectors);
extern Fls_CheckStatusType HostFlash_ProgramHseFwFeatureFlag(void);

#endif /* HOST_FLASHSRV_H */
