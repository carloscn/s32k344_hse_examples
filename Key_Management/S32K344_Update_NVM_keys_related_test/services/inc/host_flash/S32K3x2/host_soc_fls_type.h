/*==================================================================================================
 *
 *   Copyright 2021 NXP.
 *
 *   This software is owned or controlled by NXP and may only be used strictly in accordance with
 *   the applicable license terms. By expressly accepting such terms or by downloading, installing,
 *   activating and/or otherwise using the software, you are agreeing that you have read, and that
 *   you agree to comply with and are bound by, such license terms. If you do not agree to
 *   be bound by the applicable license terms, then you may not retain, install, activate or
 *   otherwise use the software.
 *  ==============================================================================================*/

/**
*   @file    host_soc_fls_type.h
*
*   @brief   HOST SOC Fls Type.H file containing all the information Related Flash Sectors and Addressing
*/

#ifndef HOST_SOC_FLS_TYPE_H
#define HOST_SOC_FLS_TYPE_H

#include <stdint.h>

/*==================================================================================================
 *                               INCLUDE FILES
 *  ==============================================================================================*/

/*=============================================================================
                                      MACROS
==============================================================================*/
#define FLS_SECTOR_SIZE                 (8192U)         /* (each sector has 8k size) */
#define FLS_TOTAL_SECTORS               (289U)
#define FLS_VERIFY4BYTE_BLANK_CHECK     (0xFFFFFFFFU)
#define FLS_VERIFY1BYTE_BLANK_CHECK     (0xFFU)
#define FLS_CODE_BASE_ADDRESS           (0x00400000U)
#define FLS_DATA_BASE_ADDRESS           (0x10000000U)
#define FLS_UTEST_BASE_ADDRESS          (0x1B000000U)
#define FLS_DATA_SIZE_BYTES_U32         (128U)          /* Program Data Register (DATA0 - DATA31) */
#define C55_USER_TEST_PASSWORD          (0xF9F99999U)   /* For UTE bit, the password 0xF9F9_9999 must be written to the UT0 register, and this must be a 32bit write */
#define FLS_WELL_KNOWN_SECURE_COUNTER   (10U)           /* This well-known secure counter will help to determine the attack */

/** 
 *   Code flash Block 0 and Block 1 are available in all variants 
 *   K3X1 only has Block 0 and Block 1 of 512 KB each.
 *   K3X2 only has Block 0 and Block 1 of 1 MB each.
 *   K3X4 has Block 0, Block 1, Block 2 and Block 3 of 1 MB each.
 *   K3X6 has Block 0, Block 1 and Block 2 of 2 MB each.
 *   K3X8 has Block 0, Block 1, Block 2 and Block 3 of 2 MB each.
 */

/*-------------------------- Sector ID for different regions ---------------------*/
#define VIRTUAL_UTEST_SECTOR_ID                                (288U)      /* FLS_UTEST_ARRAY_0_S000 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID                (32U)       /* FLS_CODE_ARRAY_0_BLOCK_0_S000 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_SSEC_REGION_LAST_SEC_ID     (127U)      /* FLS_CODE_ARRAY_0_BLOCK_0_S095 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_SEC_REGION_FIRST_SEC_ID     (128U)      /* FLS_CODE_ARRAY_0_BLOCK_0_S096 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_LAST_SEC_ID                 (159U)      /* FLS_CODE_ARRAY_0_BLOCK_0_S127 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_FIRST_SEC_ID                (160U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S128 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_SSEC_REGION_LAST_SEC_ID     (255U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S223 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_SEC_REGION_FIRST_SEC_ID     (256U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S224 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_LAST_SEC_ID                 (287U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S255 */
#define VIRTUAL_CODE_FLASH_ARRAY_LAST_SECTOR_ID                (VIRTUAL_CODE_FLASH_BLOCK_1_LAST_SEC_ID)   


/*==================================================================================================
                                 ENUM TYPEDEFS
==================================================================================================*/
/** 
    For flash area : Code flash : Start 0000_0000h -> 003F_FFFFh and Data Flash: 1000_0000h -> 1003_FFFFh and Utest Flash :  1B00_0000h -> 1B00_1FFFh
    @brief Sector Physical List.
*/
typedef enum
{
   FLS_DATA_ARRAY_0_BLOCK_4_S000 = 0U,   /*0x10000000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S001 ,       /*0x10002000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S002 ,       /*0x10004000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S003 ,       /*0x10006000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S004 ,       /*0x10008000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S005 ,       /*0x1000A000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S006 ,       /*0x1000C000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S007 ,       /*0x1000E000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S008 ,       /*0x10010000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S009 ,       /*0x10012000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S010 ,       /*0x10014000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S011 ,       /*0x10016000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S012 ,       /*0x10018000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S013 ,       /*0x1001A000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S014 ,       /*0x1001C000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S015 ,       /*0x1001E000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S016 ,       /*0x10020000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S017 ,       /*0x10022000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S018 ,       /*0x10024000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S019 ,       /*0x10026000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S020 ,       /*0x10028000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S021 ,       /*0x1002A000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S022 ,       /*0x1002C000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S023 ,       /*0x1002E000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S024 ,       /*0x10030000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S025 ,       /*0x10032000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S026 ,       /*0x10034000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S027 ,       /*0x10036000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S028 ,       /*0x10038000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S029 ,       /*0x1003A000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S030 ,       /*0x1003C000*/
   FLS_DATA_ARRAY_0_BLOCK_4_S031 ,       /*0x1003E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S000 ,       /*0x00400000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S001 ,       /*0x00402000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S002 ,       /*0x00404000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S003 ,       /*0x00406000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S004 ,       /*0x00408000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S005 ,       /*0x0040A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S006 ,       /*0x0040C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S007 ,       /*0x0040E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S008 ,       /*0x00410000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S009 ,       /*0x00412000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S010 ,       /*0x00414000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S011 ,       /*0x00416000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S012 ,       /*0x00418000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S013 ,       /*0x0041A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S014 ,       /*0x0041C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S015 ,       /*0x0041E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S016 ,       /*0x00420000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S017 ,       /*0x00422000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S018 ,       /*0x00424000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S019 ,       /*0x00426000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S020 ,       /*0x00428000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S021 ,       /*0x0042A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S022 ,       /*0x0042C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S023 ,       /*0x0042E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S024 ,       /*0x00430000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S025 ,       /*0x00432000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S026 ,       /*0x00434000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S027 ,       /*0x00436000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S028 ,       /*0x00438000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S029 ,       /*0x0043A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S030 ,       /*0x0043C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S031 ,       /*0x0043E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S032 ,       /*0x00440000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S033 ,       /*0x00442000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S034 ,       /*0x00444000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S035 ,       /*0x00446000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S036 ,       /*0x00448000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S037 ,       /*0x0044A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S038 ,       /*0x0044C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S039 ,       /*0x0044E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S040 ,       /*0x00450000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S041 ,       /*0x00452000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S042 ,       /*0x00454000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S043 ,       /*0x00456000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S044 ,       /*0x00458000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S045 ,       /*0x0045A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S046 ,       /*0x0045C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S047 ,       /*0x0045E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S048 ,       /*0x00460000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S049 ,       /*0x00462000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S050 ,       /*0x00464000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S051 ,       /*0x00466000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S052 ,       /*0x0046800*/
   FLS_CODE_ARRAY_0_BLOCK_0_S053 ,       /*0x0046A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S054 ,       /*0x0046C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S055 ,       /*0x0046E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S056 ,       /*0x00470000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S057 ,       /*0x00472000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S058 ,       /*0x00474000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S059 ,       /*0x00476000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S060 ,       /*0x00478000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S061 ,       /*0x0047A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S062 ,       /*0x0047C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S063 ,       /*0x0047E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S064 ,       /*0x00480000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S065 ,       /*0x00482000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S066 ,       /*0x00484000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S067 ,       /*0x00486000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S068 ,       /*0x00488000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S069 ,       /*0x0048A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S070 ,       /*0x0048C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S071 ,       /*0x0048E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S072 ,       /*0x00490000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S073 ,       /*0x00492000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S074 ,       /*0x00494000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S075 ,       /*0x00496000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S076 ,       /*0x00498000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S077 ,       /*0x0049A000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S078 ,       /*0x0049C000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S079 ,       /*0x0049E000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S080 ,       /*0x004A0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S081 ,       /*0x004A2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S082 ,       /*0x004A4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S083 ,       /*0x004A6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S084 ,       /*0x004A8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S085 ,       /*0x004AA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S086 ,       /*0x004AC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S087 ,       /*0x004AE000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S088 ,       /*0x004B0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S089 ,       /*0x004B2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S090 ,       /*0x004B4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S091 ,       /*0x004B6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S092 ,       /*0x004B8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S093 ,       /*0x004BA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S094 ,       /*0x004BC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S095 ,       /*0x004BE000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S096 ,       /*0x004C0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S097 ,       /*0x004C2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S098 ,       /*0x004C4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S099 ,       /*0x004C6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S100 ,       /*0x004C8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S101 ,       /*0x004CA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S102 ,       /*0x004CC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S103 ,       /*0x004CE000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S104 ,       /*0x004D0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S105 ,       /*0x004D2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S106 ,       /*0x004D4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S107 ,       /*0x004D6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S108 ,       /*0x004D8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S109 ,       /*0x004DA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S110 ,       /*0x004DC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S111 ,       /*0x004DE000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S112 ,       /*0x004E0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S113 ,       /*0x004E2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S114 ,       /*0x004E4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S115 ,       /*0x004E6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S116 ,       /*0x004E8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S117 ,       /*0x004EA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S118 ,       /*0x004EC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S119 ,       /*0x004EE000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S120 ,       /*0x004F0000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S121 ,       /*0x004F2000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S122 ,       /*0x004F4000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S123 ,       /*0x004F6000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S124 ,       /*0x004F8000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S125 ,       /*0x004FA000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S126 ,       /*0x004FC000*/
   FLS_CODE_ARRAY_0_BLOCK_0_S127 ,       /*0x004FE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S128 ,       /*0x00500000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S129 ,       /*0x00502000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S130 ,       /*0x00504000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S131 ,       /*0x00506000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S132 ,       /*0x00508000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S133 ,       /*0x0050A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S134 ,       /*0x0050C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S135 ,       /*0x0050E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S136 ,       /*0x00510000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S137 ,       /*0x00512000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S138 ,       /*0x00514000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S139 ,       /*0x00516000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S140 ,       /*0x00518000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S141 ,       /*0x0051A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S142 ,       /*0x0051C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S143 ,       /*0x0051E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S144 ,       /*0x00520000*/      
   FLS_CODE_ARRAY_0_BLOCK_1_S145 ,       /*0x00522000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S146 ,       /*0x00524000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S147 ,       /*0x00526000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S148 ,       /*0x00528000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S149 ,       /*0x0052A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S150 ,       /*0x0052C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S151 ,       /*0x0052E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S152 ,       /*0x00530000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S153 ,       /*0x00532000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S154 ,       /*0x00534000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S155 ,       /*0x00536000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S156 ,       /*0x00538000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S157 ,       /*0x0053A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S158 ,       /*0x0053C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S159 ,       /*0x0053E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S160 ,       /*0x00540000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S161 ,       /*0x00542000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S162 ,       /*0x00544000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S163 ,       /*0x00546000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S164 ,       /*0x00548000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S165 ,       /*0x0054A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S166 ,       /*0x0054C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S167 ,       /*0x0054E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S168 ,       /*0x00550000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S169 ,       /*0x00552000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S170 ,       /*0x00554000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S171 ,       /*0x00556000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S172 ,       /*0x00558000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S173 ,       /*0x0055A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S174 ,       /*0x0055C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S175 ,       /*0x0055E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S176 ,       /*0x00560000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S177 ,       /*0x00562000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S178 ,       /*0x00564000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S179 ,       /*0x00566000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S180 ,       /*0x00568000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S181 ,       /*0x0056A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S182 ,       /*0x0056C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S183 ,       /*0x0056E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S184 ,       /*0x00570000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S185 ,       /*0x00572000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S186 ,       /*0x00574000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S187 ,       /*0x00576000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S188 ,       /*0x00578000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S189 ,       /*0x0057A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S190 ,       /*0x0057C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S191 ,       /*0x0057E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S192 ,       /*0x00580000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S193 ,       /*0x00582000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S194 ,       /*0x00584000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S195 ,       /*0x00586000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S196 ,       /*0x00588000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S197 ,       /*0x0058A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S198 ,       /*0x0058C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S199 ,       /*0x0058E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S200 ,       /*0x00590000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S201 ,       /*0x00592000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S202 ,       /*0x00594000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S203 ,       /*0x00596000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S204 ,       /*0x00598000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S205 ,       /*0x0059A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S206 ,       /*0x0059C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S207 ,       /*0x0059E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S208 ,       /*0x005A0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S209 ,       /*0x005A2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S210 ,       /*0x005A4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S211 ,       /*0x005A6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S212 ,       /*0x005A8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S213 ,       /*0x005AA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S214 ,       /*0x005AC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S215 ,       /*0x005AE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S216 ,       /*0x005B0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S217 ,       /*0x005B2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S218 ,       /*0x005B4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S219 ,       /*0x005B6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S220 ,       /*0x005B8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S221 ,       /*0x005BA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S222 ,       /*0x005BC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S223 ,       /*0x005BE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S224 ,       /*0x005C0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S225 ,       /*0x005C2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S226 ,       /*0x005C4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S227 ,       /*0x005C6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S228 ,       /*0x005C8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S229 ,       /*0x005CA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S230 ,       /*0x005CC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S231 ,       /*0x005CE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S232 ,       /*0x005D0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S233 ,       /*0x005D2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S234 ,       /*0x005D4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S235 ,       /*0x005D6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S236 ,       /*0x005D8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S237 ,       /*0x005DA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S238 ,       /*0x005DC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S239 ,       /*0x005DE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S240 ,       /*0x005E0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S241 ,       /*0x005E2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S242 ,       /*0x005E4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S243 ,       /*0x005E6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S244 ,       /*0x005E8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S245 ,       /*0x005EA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S246 ,       /*0x005EC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S247 ,       /*0x005EE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S248 ,       /*0x005F0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S249 ,       /*0x005F2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S250 ,       /*0x005F4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S251 ,       /*0x005F6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S252 ,       /*0x005F8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S253 ,       /*0x005FA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S254 ,       /*0x005FC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S255 ,       /*0x005FE000*/
   FLS_UTEST_ARRAY_0_S000                /*0x1B000000*/
} Fls_VirtualListType;    


#endif /* HOST_SOC_FLS_TYPE_H */

