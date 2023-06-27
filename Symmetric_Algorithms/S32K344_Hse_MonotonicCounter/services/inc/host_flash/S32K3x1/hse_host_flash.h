/*============================================================================*/

/*    Copyright 2020 NXP.

* This software is owned or controlled by NXP and may only be used strictly in
* accordance  with the applicable license  terms.  By expressly accepting such
* terms or by  downloading,  installing, activating and/or otherwise using the
* software, you are agreeing that  you have read, and that you agree to comply
* with and are bound by,such license terms. If you do not agree to be bound by
* the applicable  license terms, then you may not retain, install, activate or
* otherwise use the software.
*/
/*============================================================================*/

/*=============================================================================
                                   Description
==============================================================================*/
/**
 *   @file    hse_host_flash.h
 *
 *   @brief   This file contains host flash api.
 */

#ifndef HSE_HOST_FLASH_H
#define HSE_HOST_FLASH_H
/*=============================================================================
 *                                 INCLUDE FILES
 =============================================================================*/
#include "hse_common_types.h"
#include "Fls_Registers.h"
#include "Fls_Api.h"
/*=============================================================================
                                      MACROS
==============================================================================*/

/*=============================================================================
 *                        TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/


/*=============================================================================
                                     CONSTANTS
==============================================================================*/
#define HOST_CODE_MEMORY_TYPE					HOST_BLOCK1_CODE_MEMORY
#define BACKUP_ADDRESS_OFFSET					(0x00080000UL)

#define UTEST_FLASH_SEC               			FLS_UTEST_ARRAY_0_S000
#define DATA_FLASH_SEC                			FLS_UTEST_ARRAY_0_S000

#define BLOCK_0_SEC                   			FLS_CODE_ARRAY_0_BLOCK_0_S000 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S001 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S002 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S003 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S004 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S005 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S006 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S007 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S008 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S009 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S010 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S011 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S012 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S013 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S014 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S015 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S016 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S017 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S018 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S019 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S020 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S021 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S022 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S023 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S024 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S025 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S026 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S027 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S028 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S029 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S030 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S031 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S032 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S033 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S034 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S035 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S036 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S037 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S038 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S039 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S040 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S041 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S042 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S043 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S044 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S045 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S046 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S047 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S048 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S049 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S050 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S051 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S052 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S053 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S054 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S055 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S056 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S057 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S058 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S059 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S060 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S061 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S062 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S063

#define BLOCK_1_SEC                   			FLS_CODE_ARRAY_0_BLOCK_1_S064 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S065 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S066 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S067 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S068 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S069 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S070 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S071 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S072 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S073 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S074 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S075 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S076 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S077 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S078 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S079 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S080 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S081 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S082 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S083 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S084 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S085 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S086 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S087 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S088 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S089 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S090 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S091 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S092 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S093 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S094 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S095 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S096 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S097 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S098 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S099 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S100 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S101 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S102 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S103 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S104 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S105 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S106 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S107 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S108 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S109 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S110 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S111 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S112 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S113 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S114 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S115 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S116 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S117 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S118 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S119 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S120 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S121 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S122 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S123 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S124 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S125 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S126 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S127

/* Block 2 of Flash */
/*
* This is a dummy section added here, as in this SOC variant, this block is not programmed by Firmware.
*/
#define BLOCK_2_SEC             				FLS_UTEST_ARRAY_0_S000

/* Block 3 of Flash */
/*
* This is a dummy section added here, as in this SOC variant, this block is not programmed by Firmware.
*/
#define BLOCK_3_SEC                             FLS_UTEST_ARRAY_0_S000

#define SIZE_OF_FLASH_BLOCK                         (512U*1024U)

/* Data Flash Registers */
#define PFLASH_DFLASHBLK_SPELOCK_ADDR32             (PFLASH_PFCBLK2_SPELOCK_ADDR32)
#define PFLASH_DFLASHBLK_SSPELOCK_ADDR32            (PFLASH_PFCBLK2_SSPELOCK_ADDR32)
#define PFLASH_DFLASHBLK_SETSLOCK_ADDR32            (PFLASH_PFCBLK2_SETSLOCK_ADDR32)
#define PFLASH_DFLASHBLK_SSETSLOCK_ADDR32           (PFLASH_PFCBLK2_SSETSLOCK_ADDR32)
#define PFLASH_DFLASHBLK_LOCKMASTER_S0_ADDR32       (PFLASH_PFCBLK2_LOCKMASTER_S0_ADDR32)
#define PFLASH_DFLASHBLK_LOCKMASTER_SS0_ADDR32      (PFLASH_PFCBLK2_LOCKMASTER_SS0_ADDR32)


/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

/*=============================================================================
                                FUNCTION PROTOTYPES
==============================================================================*/

#endif /* HSE_HOST_FLASH_H */
