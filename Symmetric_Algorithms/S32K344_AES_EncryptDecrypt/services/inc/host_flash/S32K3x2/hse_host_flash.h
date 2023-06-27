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
#define HOST_CODE_MEMORY_TYPE					HOST_BLOCK1_CODE_MEMORY
#define BACKUP_ADDRESS_OFFSET					(0x00100000UL)

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
												FLS_CODE_ARRAY_0_BLOCK_0_S063 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S064 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S065 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S066 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S067 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S068 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S069 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S070 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S071 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S072 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S073 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S074 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S075 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S076 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S077 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S078 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S079 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S080 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S081 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S082 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S083 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S084 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S085 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S086 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S087 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S088 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S089 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S090 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S091 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S092 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S093 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S094 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S095 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S096 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S097 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S098 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S099 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S100 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S101 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S102 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S103 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S104 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S105 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S106 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S107 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S108 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S109 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S110 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S111 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S112 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S113 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S114 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S115 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S116 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S117 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S118 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S119 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S120 ,  \
												FLS_CODE_ARRAY_0_BLOCK_0_S121 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S122 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S123 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S124 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S125 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S126 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_0_S127
																			      
#define BLOCK_1_SEC             	            FLS_CODE_ARRAY_0_BLOCK_1_S128 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S129 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S130 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S131 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S132 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S133 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S134 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S135 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S136 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S137 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S138 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S139 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S140 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S141 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S142 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S143 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S144 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S145 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S146 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S147 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S148 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S149 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S150 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S151 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S152 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S153 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S154 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S155 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S156 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S157 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S158 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S159 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S160 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S161 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S162 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S163 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S164 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S165 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S166 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S167 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S168 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S169 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S170 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S171 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S172 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S173 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S174 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S175 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S176 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S177 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S178 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S179 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S180 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S181 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S182 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S183 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S184 ,  \
												FLS_CODE_ARRAY_0_BLOCK_1_S185 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S186 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S187 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S188 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S189 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S190 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S191 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S192 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S193 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S194 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S195 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S196 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S197 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S198 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S199 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S200 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S201 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S202 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S203 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S204 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S205 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S206 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S207 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S208 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S209 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S210 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S211 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S212 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S213 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S214 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S215 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S216 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S217 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S218 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S219 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S220 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S221 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S222 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S223 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S224 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S225 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S226 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S227 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S228 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S229 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S230 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S231 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S232 ,  \
   												FLS_CODE_ARRAY_0_BLOCK_1_S233 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S234 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S235 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S236 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S237 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S238 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S239 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S240 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S241 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S242 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S243 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S244 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S245 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S246 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S247 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S248 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S249 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S250 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S251 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S252 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S253 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S254 ,  \
                                                FLS_CODE_ARRAY_0_BLOCK_1_S255

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

#define SIZE_OF_FLASH_BLOCK                         (1024U*1024U)

/* Data Flash Registers */
#define PFLASH_DFLASHBLK_SPELOCK_ADDR32             (PFLASH_PFCBLK2_SPELOCK_ADDR32)
#define PFLASH_DFLASHBLK_SSPELOCK_ADDR32            (PFLASH_PFCBLK2_SSPELOCK_ADDR32)
#define PFLASH_DFLASHBLK_SETSLOCK_ADDR32            (PFLASH_PFCBLK2_SETSLOCK_ADDR32)
#define PFLASH_DFLASHBLK_SSETSLOCK_ADDR32           (PFLASH_PFCBLK2_SSETSLOCK_ADDR32)
#define PFLASH_DFLASHBLK_LOCKMASTER_S0_ADDR32       (PFLASH_PFCBLK2_LOCKMASTER_S0_ADDR32)
#define PFLASH_DFLASHBLK_LOCKMASTER_SS0_ADDR32      (PFLASH_PFCBLK2_LOCKMASTER_SS0_ADDR32)

/*=============================================================================
 *                        TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/


/*=============================================================================
                                     CONSTANTS
==============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

/*=============================================================================
                                FUNCTION PROTOTYPES
==============================================================================*/

#endif /* HOST_FLASH_H */
