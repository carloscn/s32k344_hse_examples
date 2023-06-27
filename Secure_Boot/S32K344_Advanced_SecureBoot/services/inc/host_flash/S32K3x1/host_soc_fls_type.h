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
#define FLS_TOTAL_SECTORS               (161U)
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
#define VIRTUAL_UTEST_SECTOR_ID                                (160U)      /* FLS_UTEST_ARRAY_0_S000 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_FIRST_SEC_ID                (32U)       /* FLS_CODE_ARRAY_0_BLOCK_0_S000 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_SSEC_REGION_LAST_SEC_ID     (63U)       /* FLS_CODE_ARRAY_0_BLOCK_0_S031 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_SEC_REGION_FIRST_SEC_ID     (64U)       /* FLS_CODE_ARRAY_0_BLOCK_0_S032 */
#define VIRTUAL_CODE_FLASH_BLOCK_0_LAST_SEC_ID                 (95U)       /* FLS_CODE_ARRAY_0_BLOCK_0_S063 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_FIRST_SEC_ID                (96U)       /* FLS_CODE_ARRAY_0_BLOCK_1_S064 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_SSEC_REGION_LAST_SEC_ID     (127U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S095 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_SEC_REGION_FIRST_SEC_ID     (128U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S096 */
#define VIRTUAL_CODE_FLASH_BLOCK_1_LAST_SEC_ID                 (159U)      /* FLS_CODE_ARRAY_0_BLOCK_1_S127 */
#define VIRTUAL_CODE_FLASH_ARRAY_LAST_SECTOR_ID                (VIRTUAL_CODE_FLASH_BLOCK_1_LAST_SEC_ID)  


/*==================================================================================================
                                 ENUM TYPEDEFS
==================================================================================================*/
/** 
    For flash area : Code flash : Start 0000_0000h -> 000F_FFFFh and Data Flash: 1000_0000h -> 1003_FFFFh and Utest Flash :  1B00_0000h -> 1B00_1FFFh
    @brief Sector Physical List.
*/
typedef enum
{
   FLS_DATA_ARRAY_0_BLOCK_2_S000 = 0U,   /*0x10000000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S001 ,       /*0x10002000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S002 ,       /*0x10004000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S003 ,       /*0x10006000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S004 ,       /*0x10008000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S005 ,       /*0x1000A000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S006 ,       /*0x1000C000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S007 ,       /*0x1000E000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S008 ,       /*0x10010000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S009 ,       /*0x10012000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S010 ,       /*0x10014000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S011 ,       /*0x10016000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S012 ,       /*0x10018000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S013 ,       /*0x1001A000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S014 ,       /*0x1001C000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S015 ,       /*0x1001E000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S016 ,       /*0x10020000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S017 ,       /*0x10022000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S018 ,       /*0x10024000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S019 ,       /*0x10026000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S020 ,       /*0x10028000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S021 ,       /*0x1002A000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S022 ,       /*0x1002C000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S023 ,       /*0x1002E000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S024 ,       /*0x10030000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S025 ,       /*0x10032000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S026 ,       /*0x10034000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S027 ,       /*0x10036000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S028 ,       /*0x10038000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S029 ,       /*0x1003A000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S030 ,       /*0x1003C000*/
   FLS_DATA_ARRAY_0_BLOCK_2_S031 ,       /*0x1003E000*/
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
   FLS_CODE_ARRAY_0_BLOCK_0_S052 ,       /*0x00468000*/
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
   FLS_CODE_ARRAY_0_BLOCK_1_S064 ,       /*0x00480000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S065 ,       /*0x00482000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S066 ,       /*0x00484000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S067 ,       /*0x00486000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S068 ,       /*0x00488000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S069 ,       /*0x0048A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S070 ,       /*0x0048C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S071 ,       /*0x0048E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S072 ,       /*0x00490000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S073 ,       /*0x00492000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S074 ,       /*0x00494000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S075 ,       /*0x00496000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S076 ,       /*0x00498000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S077 ,       /*0x0049A000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S078 ,       /*0x0049C000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S079 ,       /*0x0049E000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S080 ,       /*0x004A0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S081 ,       /*0x004A2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S082 ,       /*0x004A4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S083 ,       /*0x004A6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S084 ,       /*0x004A8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S085 ,       /*0x004AA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S086 ,       /*0x004AC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S087 ,       /*0x004AE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S088 ,       /*0x004B0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S089 ,       /*0x004B2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S090 ,       /*0x004B4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S091 ,       /*0x004B6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S092 ,       /*0x004B8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S093 ,       /*0x004BA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S094 ,       /*0x004BC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S095 ,       /*0x004BE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S096 ,       /*0x004C0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S097 ,       /*0x004C2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S098 ,       /*0x004C4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S099 ,       /*0x004C6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S100 ,       /*0x004C8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S101 ,       /*0x004CA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S102 ,       /*0x004CC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S103 ,       /*0x004CE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S104 ,       /*0x004D0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S105 ,       /*0x004D2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S106 ,       /*0x004D4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S107 ,       /*0x004D6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S108 ,       /*0x004D8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S109 ,       /*0x004DA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S110 ,       /*0x004DC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S111 ,       /*0x004DE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S112 ,       /*0x004E0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S113 ,       /*0x004E2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S114 ,       /*0x004E4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S115 ,       /*0x004E6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S116 ,       /*0x004E8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S117 ,       /*0x004EA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S118 ,       /*0x004EC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S119 ,       /*0x004EE000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S120 ,       /*0x004F0000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S121 ,       /*0x004F2000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S122 ,       /*0x004F4000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S123 ,       /*0x004F6000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S124 ,       /*0x004F8000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S125 ,       /*0x004FA000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S126 ,       /*0x004FC000*/
   FLS_CODE_ARRAY_0_BLOCK_1_S127 ,       /*0x004FE000*/
   FLS_UTEST_ARRAY_0_S000                /*0x1B000000*/
} Fls_VirtualListType;    



#endif /* HOST_SOC_FLS_TYPE_H */

