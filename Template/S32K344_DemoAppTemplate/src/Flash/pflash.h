/******************************************************************************
 * (c) Copyright 2018-2020, NXP Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pflash.h
 * @brief     Platform Flash Memory Controller (PFLASH) driver header file.
 ******************************************************************************/
#ifndef __PFLASH_H
#define __PFLASH_H

#include "pflash_private.h"   /* include private definitions                  */

/******************************************************************************
* Flash controller ports
*
*//*! @addtogroup pflash_ports
* @{
*******************************************************************************/
#define PFLASH_ALL_P  (uint8_t)~0       ///< All ports
#define PFLASH_P0     (uint8_t)(1 << 0) ///< Assigned to M7_0 instruction and data bus
#define PFLASH_P1     (uint8_t)(1 << 1) ///< Assigned to M7_1 instruction and data bus
#define PFLASH_P2     (uint8_t)(1 << 2) ///< Assigned to HSE instruction and data bus as well as eDMA
//#define PFLASH_P3     (uint8_t)(1 << 3) ///< Assigned to M7_2 instruction and data bus
/*! @} End of pflash_ports                                                    */

/******************************************************************************
* Flash blocks
*
*//*! @addtogroup pflash_blocks
* @{
* @details The following table lists flash blocks, memory map, number of protection elements and protection granularity:
* |Flash block|Type      |Size [KB]|Address range        |# Super Sectors [64KB]|# Sectors [8KB]|
* |:---------:|:--------:|:-------:|:-------------------:|:--------------------:|:-------------:|
* |PFLASH_BL0 |code flash|1024     |0x00000000-0x000FFFFF|12 (..-0x000C0000)    |32             |
* |PFLASH_BL1 |code flash|1024     |0x00100000-0x001FFFFF|12 (..-0x001C0000)    |32             |
* |PFLASH_BL2 |code flash|1024     |0x00200000-0x002FFFFF|12 (..-0x002C0000)    |32             |
* |PFLASH_BL3 |code flash|1024     |0x00300000-0x003FFFFF|12 (..-0x003C0000)    |32             |
* |PFLASH_BL4 |data flash|256      |0x10000000-0x1003FFFF|-                     |32             |
*******************************************************************************/
#define PFLASH_ALL_BL (uint8_t)~0       ///< All flash blocks
#define PFLASH_BL0    (uint8_t)(1 << 0) ///< Flash block 0
#define PFLASH_BL1    (uint8_t)(1 << 1) ///< Flash block 1
#define PFLASH_BL2    (uint8_t)(1 << 2) ///< Flash block 2
#define PFLASH_BL3    (uint8_t)(1 << 3) ///< Flash block 3
#define PFLASH_BL4    (uint8_t)(1 << 4) ///< Flash block 4
#define PFLASH_BL5    (uint8_t)(1 << 5) ///< Flash block 4
/*! @} End of pflash_blocks                                                   */

/******************************************************************************
* Super Sectors
*
*//*! @addtogroup pflash_ssectors
* @{
* @details The following table summarizes memory ranges within each flash block that are protected by super sectors:
* |Super sector|PFLASH_BL0           |PFLASH_BL1           |PFLASH_BL2           |PFLASH_BL3           |PFLASH_BL4|
* |:----------:|:-------------------:|:-------------------:|:-------------------:|:-------------------:|:--------:|
* |PFLASH_SS0  |0x00000000-0x0000FFFF|0x00100000-0x0010FFFF|0x00200000-0x0020FFFF|0x00300000-0x0000FFFF|N/A       |
* |PFLASH_SS1  |0x00010000-0x0001FFFF|0x00110000-0x0011FFFF|0x00210000-0x0021FFFF|0x00310000-0x0001FFFF|N/A       |
* |PFLASH_SS2  |0x00020000-0x0002FFFF|0x00120000-0x0012FFFF|0x00220000-0x0022FFFF|0x00320000-0x0002FFFF|N/A       |
* |PFLASH_SS3  |0x00030000-0x0003FFFF|0x00130000-0x0013FFFF|0x00230000-0x0023FFFF|0x00330000-0x0003FFFF|N/A       |
* |PFLASH_SS4  |0x00040000-0x0004FFFF|0x00140000-0x0014FFFF|0x00240000-0x0024FFFF|0x00340000-0x0004FFFF|N/A       |
* |PFLASH_SS5  |0x00050000-0x0005FFFF|0x00150000-0x0015FFFF|0x00250000-0x0025FFFF|0x00350000-0x0005FFFF|N/A       |
* |PFLASH_SS6  |0x00060000-0x0006FFFF|0x00160000-0x0016FFFF|0x00260000-0x0026FFFF|0x00360000-0x0006FFFF|N/A       |
* |PFLASH_SS7  |0x00070000-0x0007FFFF|0x00170000-0x0017FFFF|0x00270000-0x0027FFFF|0x00370000-0x0007FFFF|N/A       |
* |PFLASH_SS8  |0x00080000-0x0008FFFF|0x00180000-0x0018FFFF|0x00280000-0x0028FFFF|0x00380000-0x0008FFFF|N/A       |
* |PFLASH_SS9  |0x00090000-0x0009FFFF|0x00190000-0x0019FFFF|0x00290000-0x0029FFFF|0x00390000-0x0009FFFF|N/A       |
* |PFLASH_SS10 |0x000A0000-0x000AFFFF|0x001A0000-0x001AFFFF|0x002A0000-0x002AFFFF|0x003A0000-0x000AFFFF|N/A       |
* |PFLASH_SS11 |0x000B0000-0x000BFFFF|0x001B0000-0x001BFFFF|0x002B0000-0x002BFFFF|0x003B0000-0x000BFFFF|N/A       |
*******************************************************************************/
#define PFLASH_ALL_SS (uint32_t)~0UL      ///< All 64KB sectors
#define PFLASH_SS0    (uint32_t)(1 << 0 ) ///< 64 KB super sector 0
#define PFLASH_SS1    (uint32_t)(1 << 1 ) ///< 64 KB super sector 1
#define PFLASH_SS2    (uint32_t)(1 << 2 ) ///< 64 KB super sector 2
#define PFLASH_SS3    (uint32_t)(1 << 3 ) ///< 64 KB super sector 3
#define PFLASH_SS4    (uint32_t)(1 << 4 ) ///< 64 KB super sector 4
#define PFLASH_SS5    (uint32_t)(1 << 5 ) ///< 64 KB super sector 5
#define PFLASH_SS6    (uint32_t)(1 << 6 ) ///< 64 KB super sector 6
#define PFLASH_SS7    (uint32_t)(1 << 7 ) ///< 64 KB super sector 7
#define PFLASH_SS8    (uint32_t)(1 << 8 ) ///< 64 KB super sector 8
#define PFLASH_SS9    (uint32_t)(1 << 9 ) ///< 64 KB super sector 9
#define PFLASH_SS10   (uint32_t)(1 << 10) ///< 64 KB super sector 10
#define PFLASH_SS11   (uint32_t)(1 << 11) ///< 64 KB super sector 11
/*! @} End of pflash_ssectors                                                 */

/******************************************************************************
* Sectors
*
*//*! @addtogroup pflash_sectors
* @{
* @details The following table summarizes memory ranges within each flash block that are protected by sectors:
* |Super sector|PFLASH_BL0           |PFLASH_BL1           |PFLASH_BL2           |PFLASH_BL3           |PFLASH_BL4           |
* |:----------:|:-------------------:|:-------------------:|:-------------------:|:-------------------:|:-------------------:|
* |PFLASH_S0   |0x000C0000-0x000C1FFF|0x001C0000-0x001C1FFF|0x002C0000-0x002C1FFF|0x003C0000-0x003C1FFF|0x10000000-0x10001FFF|
* |PFLASH_S1   |0x000C2000-0x000C3FFF|0x001C2000-0x001C3FFF|0x002C2000-0x002C3FFF|0x003C2000-0x003C3FFF|0x10002000-0x10003FFF|
* |PFLASH_S2   |0x000C4000-0x000C5FFF|0x001C4000-0x001C5FFF|0x002C4000-0x002C5FFF|0x003C4000-0x003C5FFF|0x10004000-0x10005FFF|
* |PFLASH_S3   |0x000C6000-0x000C7FFF|0x001C6000-0x001C7FFF|0x002C6000-0x002C7FFF|0x003C6000-0x003C7FFF|0x10006000-0x10007FFF|
* |PFLASH_S4   |0x000C8000-0x000C9FFF|0x001C8000-0x001C9FFF|0x002C8000-0x002C9FFF|0x003C8000-0x003C9FFF|0x10008000-0x10009FFF|
* |PFLASH_S5   |0x000CA000-0x000CBFFF|0x001CA000-0x001CBFFF|0x002CA000-0x002CBFFF|0x003CA000-0x003CBFFF|0x1000A000-0x1000BFFF|
* |PFLASH_S6   |0x000CC000-0x000CDFFF|0x001CC000-0x001CDFFF|0x002CC000-0x002CDFFF|0x003CC000-0x003CDFFF|0x1000C000-0x1000DFFF|
* |PFLASH_S7   |0x000CE000-0x000CFFFF|0x001CE000-0x001CFFFF|0x002CE000-0x002CFFFF|0x003CE000-0x003CFFFF|0x1000E000-0x1000FFFF|
* |PFLASH_S8   |0x000D0000-0x000D1FFF|0x001D0000-0x001D1FFF|0x002D0000-0x002D1FFF|0x003D0000-0x003D1FFF|0x10010000-0x10011FFF|
* |PFLASH_S9   |0x000D2000-0x000D3FFF|0x001D2000-0x001D3FFF|0x002D2000-0x002D3FFF|0x003D2000-0x003D3FFF|0x10012000-0x10013FFF|
* |PFLASH_S10  |0x000D4000-0x000D5FFF|0x001D4000-0x001D5FFF|0x002D4000-0x002D5FFF|0x003D4000-0x003D5FFF|0x10014000-0x10015FFF|
* |PFLASH_S11  |0x000D6000-0x000D7FFF|0x001D6000-0x001D7FFF|0x002D6000-0x002D7FFF|0x003D6000-0x003D7FFF|0x10016000-0x10017FFF|
* |PFLASH_S12  |0x000D8000-0x000D9FFF|0x001D8000-0x001D9FFF|0x002D8000-0x002D9FFF|0x003D8000-0x003D9FFF|0x10018000-0x10019FFF|
* |PFLASH_S13  |0x000DA000-0x000DBFFF|0x001DA000-0x001DBFFF|0x002DA000-0x002DBFFF|0x003DA000-0x003DBFFF|0x1001A000-0x1001BFFF|
* |PFLASH_S14  |0x000DC000-0x000DDFFF|0x001DC000-0x001DDFFF|0x002DC000-0x002DDFFF|0x003DC000-0x003DDFFF|0x1001C000-0x1001DFFF|
* |PFLASH_S15  |0x000DE000-0x000DFFFF|0x001DE000-0x001DFFFF|0x002DE000-0x002DFFFF|0x003DE000-0x003DFFFF|0x1001E000-0x1001FFFF|
* |PFLASH_S16  |0x000E0000-0x000E1FFF|0x001E0000-0x001E1FFF|0x002E0000-0x002E1FFF|0x003E0000-0x003E1FFF|0x10020000-0x10021FFF|
* |PFLASH_S17  |0x000E2000-0x000E3FFF|0x001E2000-0x001E3FFF|0x002E2000-0x002E3FFF|0x003E2000-0x003E3FFF|0x10022000-0x10023FFF|
* |PFLASH_S18  |0x000E4000-0x000E5FFF|0x001E4000-0x001E5FFF|0x002E4000-0x002E5FFF|0x003E4000-0x003E5FFF|0x10024000-0x10025FFF|
* |PFLASH_S19  |0x000E6000-0x000E7FFF|0x001E6000-0x001E7FFF|0x002E6000-0x002E7FFF|0x003E6000-0x003E7FFF|0x10026000-0x10027FFF|
* |PFLASH_S20  |0x000E8000-0x000E9FFF|0x001E8000-0x001E9FFF|0x002E8000-0x002E9FFF|0x003E8000-0x003E9FFF|0x10028000-0x10029FFF|
* |PFLASH_S21  |0x000EA000-0x000EBFFF|0x001EA000-0x001EBFFF|0x002EA000-0x002EBFFF|0x003EA000-0x003EBFFF|0x1002A000-0x1002BFFF|
* |PFLASH_S22  |0x000EC000-0x000EDFFF|0x001EC000-0x001EDFFF|0x002EC000-0x002EDFFF|0x003EC000-0x003EDFFF|0x1002C000-0x1002DFFF|
* |PFLASH_S23  |0x000EE000-0x000EFFFF|0x001EE000-0x001EFFFF|0x002EE000-0x002EFFFF|0x003EE000-0x003EFFFF|0x1002E000-0x1002FFFF|
* |PFLASH_S24  |0x000F0000-0x000F1FFF|0x001F0000-0x001F1FFF|0x002F0000-0x002F1FFF|0x003F0000-0x003F1FFF|0x10030000-0x10031FFF|
* |PFLASH_S25  |0x000F2000-0x000F3FFF|0x001F2000-0x001F3FFF|0x002F2000-0x002F3FFF|0x003F2000-0x003F3FFF|0x10032000-0x10033FFF|
* |PFLASH_S26  |0x000F4000-0x000F5FFF|0x001F4000-0x001F5FFF|0x002F4000-0x002F5FFF|0x003F4000-0x003F5FFF|0x10034000-0x10035FFF|
* |PFLASH_S27  |0x000F6000-0x000F7FFF|0x001F6000-0x001F7FFF|0x002F6000-0x002F7FFF|0x003F6000-0x003F7FFF|0x10036000-0x10037FFF|
* |PFLASH_S28  |0x000F8000-0x000F9FFF|0x001F8000-0x001F9FFF|0x002F8000-0x002F9FFF|0x003F8000-0x003F9FFF|0x10038000-0x10039FFF|
* |PFLASH_S29  |0x000FA000-0x000FBFFF|0x001FA000-0x001FBFFF|0x002FA000-0x002FBFFF|0x003FA000-0x003FBFFF|0x1003A000-0x1003BFFF|
* |PFLASH_S30  |0x000FC000-0x000FDFFF|0x001FC000-0x001FDFFF|0x002FC000-0x002FDFFF|0x003FC000-0x003FDFFF|0x1003C000-0x1003DFFF|
* |PFLASH_S31  |0x000FE000-0x000FFFFF|0x001FE000-0x001FFFFF|0x002FE000-0x002FFFFF|0x003FE000-0x003FFFFF|0x1003E000-0x1003FFFF|
*******************************************************************************/
#define PFLASH_ALL_S  (uint32_t)~0UL      ///< All 8KB sectors
#define PFLASH_S0     (uint32_t)(1 << 0 ) ///< 8KB sector 0
#define PFLASH_S1     (uint32_t)(1 << 1 ) ///< 8KB sector 1
#define PFLASH_S2     (uint32_t)(1 << 2 ) ///< 8KB sector 2
#define PFLASH_S3     (uint32_t)(1 << 3 ) ///< 8KB sector 3
#define PFLASH_S4     (uint32_t)(1 << 4 ) ///< 8KB sector 4
#define PFLASH_S5     (uint32_t)(1 << 5 ) ///< 8KB sector 5
#define PFLASH_S6     (uint32_t)(1 << 6 ) ///< 8KB sector 6
#define PFLASH_S7     (uint32_t)(1 << 7 ) ///< 8KB sector 7
#define PFLASH_S8     (uint32_t)(1 << 8 ) ///< 8KB sector 8
#define PFLASH_S9     (uint32_t)(1 << 9 ) ///< 8KB sector 9
#define PFLASH_S10    (uint32_t)(1 << 10) ///< 8KB sector 10
#define PFLASH_S11    (uint32_t)(1 << 11) ///< 8KB sector 11
#define PFLASH_S12    (uint32_t)(1 << 12) ///< 8KB sector 12
#define PFLASH_S13    (uint32_t)(1 << 13) ///< 8KB sector 13
#define PFLASH_S14    (uint32_t)(1 << 14) ///< 8KB sector 14
#define PFLASH_S15    (uint32_t)(1 << 15) ///< 8KB sector 15
#define PFLASH_S16    (uint32_t)(1 << 16) ///< 8KB sector 16
#define PFLASH_S17    (uint32_t)(1 << 17) ///< 8KB sector 17
#define PFLASH_S18    (uint32_t)(1 << 18) ///< 8KB sector 18
#define PFLASH_S19    (uint32_t)(1 << 19) ///< 8KB sector 19
#define PFLASH_S20    (uint32_t)(1 << 20) ///< 8KB sector 20
#define PFLASH_S21    (uint32_t)(1 << 21) ///< 8KB sector 21
#define PFLASH_S22    (uint32_t)(1 << 22) ///< 8KB sector 22
#define PFLASH_S23    (uint32_t)(1 << 23) ///< 8KB sector 23
#define PFLASH_S24    (uint32_t)(1 << 24) ///< 8KB sector 24
#define PFLASH_S25    (uint32_t)(1 << 25) ///< 8KB sector 25
#define PFLASH_S26    (uint32_t)(1 << 26) ///< 8KB sector 26
#define PFLASH_S27    (uint32_t)(1 << 27) ///< 8KB sector 27
#define PFLASH_S28    (uint32_t)(1 << 28) ///< 8KB sector 28
#define PFLASH_S29    (uint32_t)(1 << 29) ///< 8KB sector 29
#define PFLASH_S30    (uint32_t)(1 << 30) ///< 8KB sector 30
#define PFLASH_S31    (uint32_t)(1 << 31) ///< 8KB sector 31
/*! @} End of pflash_sectors                                                  */

/******************************************************************************
* Flash function and macro definitions
*
*//*! @addtogroup pflash_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Locks sectors and super sectors.
 * @details This macro locks sectors and super sectors within flash blocks.
 * @param   blocks    Mask of @ref pflash_blocks.
 * @param   ssectors  Mask of @ref pflash_ssectors.
 * @param   sectors   Mask of @ref pflash_sectors.
 * @note    Implemented as an inline function.
 * @see     @ref PFLASH_Unlock
 ******************************************************************************/
#define PFLASH_Lock(blocks,ssectors,sectors)                                                \
({                                                                                          \
  register uint32_t __t1=blocks,__t2=ssectors,__t3=sectors;                                 \
  if (__t1 & PFLASH_BL0) { PFLASH_PFCBLK0_SSPELOCK|= __t2; PFLASH_PFCBLK0_SPELOCK = __t3; } \
  if (__t1 & PFLASH_BL1) { PFLASH_PFCBLK1_SSPELOCK|= __t2; PFLASH_PFCBLK1_SPELOCK = __t3; } \
  if (__t1 & PFLASH_BL2) { PFLASH_PFCBLK2_SSPELOCK|= __t2; PFLASH_PFCBLK2_SPELOCK = __t3; } \
  if (__t1 & PFLASH_BL3) { PFLASH_PFCBLK3_SSPELOCK|= __t2; PFLASH_PFCBLK3_SPELOCK = __t3; } \
  if (__t1 & PFLASH_BL4) {                                 PFLASH_PFCBLK4_SPELOCK = __t3; } \
})

/***************************************************************************//*!
 * @brief   Unlocks flash blocks sectors and super sectors.
 * @details This macro unlocks sectors and super sectors within flash blocks.
 * @param   blocks    Mask of @ref pflash_blocks.
 * @param   ssectors  Mask of @ref pflash_ssectors.
 * @param   sectors   Mask of @ref pflash_sectors.
 * @note    Implemented as an inline function.
 * @see     @ref PFLASH_Lock
 ******************************************************************************/
#define PFLASH_Unlock(blocks,ssectors,sectors)                                              \
({                                                                                          \
  register uint32_t __t1=blocks,__t2=ssectors,__t3=sectors;                                 \
  if (__t1 & PFLASH_BL0) { PFLASH_PFCBLK0_SSPELOCK&=~__t2; PFLASH_PFCBLK0_SPELOCK&=~__t3; } \
  if (__t1 & PFLASH_BL1) { PFLASH_PFCBLK1_SSPELOCK&=~__t2; PFLASH_PFCBLK1_SPELOCK&=~__t3; } \
  if (__t1 & PFLASH_BL2) { PFLASH_PFCBLK2_SSPELOCK&=~__t2; PFLASH_PFCBLK2_SPELOCK&=~__t3; } \
  if (__t1 & PFLASH_BL3) { PFLASH_PFCBLK3_SSPELOCK&=~__t2; PFLASH_PFCBLK3_SPELOCK&=~__t3; } \
  if (__t1 & PFLASH_BL4) {                                 PFLASH_PFCBLK4_SPELOCK&=~__t3; } \
  if (__t1 & PFLASH_BL5) {                                 PFLASH_PFCBLK5_SPELOCK&=~__t3; } \
})

/***************************************************************************//*!
 * @brief   Assigns flash blocks sectors and super sectors to the domain ID of
 * the caller.
 * @details This macro assigns sectors and super sectors within flash blocks to
 * the domain ID of the caller.
 * @param   blocks    Mask of @ref pflash_blocks.
 * @param   ssectors  Mask of @ref pflash_ssectors.
 * @param   sectors   Mask of @ref pflash_sectors.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define PFLASH_SetLock(blocks,ssectors,sectors)                                             \
({                                                                                          \
  register uint32_t __t1=blocks,__t2=ssectors,__t3=sectors;                                 \
  if (__t1 & PFLASH_BL0) { PFLASH_PFCBLK0_SETSSLOCK|=__t2; PFLASH_PFCBLK0_SETSLOCK|=__t3; } \
  if (__t1 & PFLASH_BL1) { PFLASH_PFCBLK1_SETSSLOCK|=__t2; PFLASH_PFCBLK1_SETSLOCK|=__t3; } \
  if (__t1 & PFLASH_BL2) { PFLASH_PFCBLK2_SETSSLOCK|=__t2; PFLASH_PFCBLK2_SETSLOCK|=__t3; } \
  if (__t1 & PFLASH_BL3) { PFLASH_PFCBLK3_SETSSLOCK|=__t2; PFLASH_PFCBLK3_SETSLOCK|=__t3; } \
  if (__t1 & PFLASH_BL4) {                                 PFLASH_PFCBLK4_SETSLOCK|=__t3; } \
})

/***************************************************************************//*!
 * @brief   Enables code and data line and prefetch buffers (64 bytes).
 * @details This macro enables code and data line and prefetch buffers (64 bytes)
 * on selected ports.
 * @param   ports    Mask of @ref pflash_ports.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define PFLASH_Enable64ByteBuffers(ports)                                    \
  PFLASH_SetPFCR(ports, PFLASH_PFCR_P0_CBFEN_MASK|PFLASH_PFCR_P0_CPFEN_MASK, \
                    PFLASH_PFCR_P0_DBFEN_MASK|PFLASH_PFCR_P0_DPFEN_MASK)

/***************************************************************************//*!
 * @brief   Enables code and data line buffers (32 bytes).
 * @details This macro enables code and data line buffers (32 bytes) on selected
 * ports. A flash array line buffer (first 32B buffer) fetch is initiated if the
 * data is not already resident in a line buffer. This is default configuration.
 * @param   ports    Mask of @ref pflash_ports.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define PFLASH_Enable32ByteBuffers(ports)                                  \
  PFLASH_SetPFCR(ports, PFLASH_PFCR_P0_CBFEN_MASK|PFLASH_PFCR_P0_DBFEN_MASK)

/***************************************************************************//*!
 * @brief   Disable code and data line and prefetch buffers.
 * @details This macro disables code and data line and prefetch buffers on selected
 * ports.
 * @param   ports    Mask of @ref pflash_ports.
 * @note    Implemented as an inline function.
 ******************************************************************************/
#define PFLASH_DisableBuffer(ports) PFLASH_SetPFCR(ports,0U,0U)
/*! @} End of pflash_macro                                                    */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern void PFLASH_SetPFCR (uint8_t ports, uint32_t code, uint32_t data);

#endif /* __PFLASH_H */
