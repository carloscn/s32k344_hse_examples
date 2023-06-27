/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011 -2018          *
*                        All Rights Reserved                            *
*************************************************************************

*************************************************************************
*                                                                       *
*   Freescale reserves the right to make changes without further notice *
*   to any product herein to improve reliability, function or design.   *
*   Freescale does not assume any liability arising out of the          *
*   application or use of any product, circuit, or software described   *
*   herein; neither does it convey any license under its patent rights  *
*   nor the rights of others.                                           *
*                                                                       *
*   Freescale products are not designed, intended, or authorized for    *
*   use as components in systems intended for surgical implant into     *
*   the body, or other applications intended to support life, or for    *
*   any other application in which the failure of the Freescale product *
*   could create a situation where personal injury or death may occur.  *
*                                                                       *
*   Should Buyer purchase or use Freescale products for any such        */
#ifndef _Fls_REGISTERS_H_
#define _Fls_REGISTERS_H_

#include "Platform_Types.h"
#include "StdRegMacros.h"

/*************************************************************************/
/*    Defining Alternate Registers for both FLASH and PFLASH             */
/*************************************************************************/
/* The register base addresses of Flash and PFlash  */
#define FLASH_BASEADDR                 ((uint32)0x402EC000UL)   /** @brief Flash register base address of flash  */
#define FLASH_ALTER_BASEADDR           ((uint32)0x402F0000UL)   /* Base address alter Flash*/
#define PFLASH_BASEADDR                ((uint32)0x40268000UL)   /** @brief PFlash register base address of Pflash  */
#define PFLASH_ALTER_BASEADDR          ((uint32)0x4026C000UL)   /* Base address alter PFlash*/

/* Memory array control/configuration registers of Flash*/
#define FLASH_MCR_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0x00UL))  /**< @brief Module Configuration Register (MCR) */
#define FLASH_MCRS_ADDR32           ((uint32)(FLASH_BASEADDR + (uint32)0x04UL))  /**< @brief Module Configuration Status Register (MCRS)*/ 
#define FLASH_MCRE_ADDR32           ((uint32)(FLASH_BASEADDR + (uint32)0x08UL))  /**< @brief Extended Module Configuration Register (MCRE) */
#define FLASH_CTL_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0x0CUL))  /**< @brief Module Control Register (CTL) */  
#define FLASH_ADR_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0x10UL))  /**< @brief Address register (ADR) */
#define FLASH_PEADR_ADDR32          ((uint32)(FLASH_BASEADDR + (uint32)0x14UL))  /**< @brief Program and Erase Address register (PEADR) */
#define FLASH_AMCR_ADDR32           ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x20UL))  /**< @brief  Alternate Module Configuration Register (AMCR) */
#define FLASH_AMCRS_ADDR32          ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x24UL))  /**< @brief Alternate Module Configuration Status Register (AMCRS) */
#define FLASH_APEADR_ADDR32         ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x28UL))  /**< @brief Alternate Program and Erase Address register (APEADR) */
#define FLASH_ADATAx_ADDR32         ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x30UL))  /**< @brief Alternate Program Data Register (ADATA0 - ADATA7) */
#define FLASH_SPELOCK_ADDR32        ((uint32)(FLASH_BASEADDR + (uint32)0x50UL))  /**< @brief Sector Program and Erase Hardware Lock register (SPELOCK) */
#define FLASH_SSPELOCK_ADDR32       ((uint32)(FLASH_BASEADDR + (uint32)0x54UL))  /**< @brief Super Sector Program and Erase Hardware Lock register (SSPELOCK) */
#define FLASH_ASPELOCK_ADDR32       ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x60UL))  /**< @brief Alternate Sector Program and Erase Hardware Lock register (ASPELOCK) */
#define FLASH_ASSELOCK_ADDR32       ((uint32)(FLASH_ALTER_BASEADDR + (uint32)0x64UL))  /**< @brief Alternate Super Sector Program and Erase Hardware Lock register(ASSELOCK) */
#define FLASH_XSPELOCK_ADDR32       ((uint32)(FLASH_BASEADDR + (uint32)0x70UL))  /**< @brief Express Sector Program and Erase Hardware Lock register (XSPELOCK)*/
#define FLASH_XSSPELOCK_ADDR32      ((uint32)(FLASH_BASEADDR + (uint32)0x74UL))  /**< @brief Express Super Sector Program and Erase Hardware Lock register(XSSPELOCK)*/
#define FLASH_UT0_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0x94UL))  /**< @brief EUTest 0 register (UT0)*/
#define FLASH_UMx_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0x98UL))  /**< @brief UMISRn register*/
#define FLASH_UM9_ADDR32            ((uint32)(FLASH_BASEADDR + (uint32)0xBCUL))  /**< @brief UMISR9 register (UM9)*/
#define FLASH_XMCR_ADDR32           ((uint32)(FLASH_BASEADDR + (uint32)0xF0UL))  /**< @brief Express Module Configuration Register (XMCR)*/
#define FLASH_XPEADR_ADDR32         ((uint32)(FLASH_BASEADDR + (uint32)0xF4UL))  /**< @brief Express Program Address register (XPEADR)*/
#define FLASH_DATAx_ADDR32          ((uint32)(FLASH_BASEADDR + (uint32)0x100UL)) /**< @brief  Program Data Register (DATA0 - DATA31)*/

/* Memory array control/configuration registers of PFlash*/
#define PFLASH_PFCPGM_PEADR_L_ADDR32            ((uint32)(PFLASH_BASEADDR + (uint32)0x300UL))  /**< @brief Platform Flash Program Erase Address Logical (PFCPGM_PEADR_L) */
#define PFLASH_PFCPGM_PEADR_P_ADDR32            ((uint32)(PFLASH_BASEADDR + (uint32)0x304UL))  /**< @brief Platform Flash Program Erase Address Physical (PFCPGM_PEADR_P) */
#define PFLASH_PFCPGM_XPEADR_L_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x308UL))  /**< @brief Platform Flash Program Erase Address Logical (PFCPGM_XPEADR_L) */
#define PFLASH_PFCPGM_XPEADR_P_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x30CUL))  /**< @brief Platform Flash Express Program Erase Address Physical (PFCPGM_XPEADR_P)*/
#define PFLASH_PFCPGM_APEADR_L_ADDR32           ((uint32)(PFLASH_ALTER_BASEADDR + (uint32)0x310UL))  /**< @brief Platform Flash Alternate Program Erase Address Logical (PFCPGM_APEADR_L)*/
#define PFLASH_PFCPGM_APEADR_P_ADDR32           ((uint32)(PFLASH_ALTER_BASEADDR + (uint32)0x314UL))  /**< @brief Platform Flash Alternate Program Erase Address Physical (PFCPGM_APEADR_P)*/
#define PFLASH_PFCBLK0_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x340UL)) /**< @brief  Block n Sector Program Erase Lock */
#define PFLASH_PFCBLK1_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x344UL)) /**< @brief  Block n Sector Program Erase Lock */
#define PFLASH_PFCBLK2_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x348UL)) /**< @brief  Block n Sector Program Erase Lock */
#define PFLASH_PFCBLK3_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x34CUL)) /**< @brief  Block n Sector Program Erase Lock */
#define PFLASH_PFCBLK4_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x350UL)) /**< @brief  Block n Sector Program Erase Lock */
#define PFLASH_PFCBLKU_SPELOCK_ADDR32           ((uint32)(PFLASH_BASEADDR + (uint32)0x358UL)) /**< @brief  Block UTEST Sector Program Erase Lock */
#define PFLASH_PFCBLK0_SSPELOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x35CUL)) /**< @brief  Block n Super Sector Program Erase Lock */
#define PFLASH_PFCBLK1_SSPELOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x360UL)) /**< @brief  Block n Super Sector Program Erase Lock */
#define PFLASH_PFCBLK2_SSPELOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x364UL)) /**< @brief  Block n Super Sector Program Erase Lock */
#define PFLASH_PFCBLK3_SSPELOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x368UL)) /**< @brief  Block n Super Sector Program Erase Lock */
#define PFLASH_PFCBLK4_SSPELOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x36CUL)) /**< @brief  Block n Super Sector Program Erase Lock */
#define PFLASH_PFCBLK0_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x380UL)) /**< @brief  Block n Set Sector Lock */
#define PFLASH_PFCBLK1_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x384UL)) /**< @brief  Block n Set Sector Lock */
#define PFLASH_PFCBLK2_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x388UL)) /**< @brief  Block n Set Sector Lock */
#define PFLASH_PFCBLK3_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x38CUL)) /**< @brief  Block n Set Sector Lock */
#define PFLASH_PFCBLK4_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x390UL)) /**< @brief  Block n Set Sector Lock */
#define PFLASH_PFCBLKU_SETSLOCK_ADDR32          ((uint32)(PFLASH_BASEADDR + (uint32)0x398UL)) /**< @brief  Block UTEST Set Sector Lock */
#define PFLASH_PFCBLK0_SSETSLOCK_ADDR32         ((uint32)(PFLASH_BASEADDR + (uint32)0x39CUL)) /**< @brief  Block n Set Super Sector Lock */
#define PFLASH_PFCBLK1_SSETSLOCK_ADDR32         ((uint32)(PFLASH_BASEADDR + (uint32)0x3A0UL)) /**< @brief  Block n Set Super Sector Lock */
#define PFLASH_PFCBLK2_SSETSLOCK_ADDR32         ((uint32)(PFLASH_BASEADDR + (uint32)0x3A4UL)) /**< @brief  Block n Set Super Sector Lock */
#define PFLASH_PFCBLK3_SSETSLOCK_ADDR32         ((uint32)(PFLASH_BASEADDR + (uint32)0x3A8UL)) /**< @brief  Block n Set Super Sector Lock */
#define PFLASH_PFCBLK4_SSETSLOCK_ADDR32         ((uint32)(PFLASH_BASEADDR + (uint32)0x3ACUL)) /**< @brief  Block n Set Super Sector Lock */
#define PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32     ((uint32)(PFLASH_BASEADDR + (uint32)0x3C0UL)) /**< @brief  Block a Lock Master Sectorb  */
#define PFLASH_PFCBLK4_LOCKMASTER_S0_ADDR32     ((uint32)(PFLASH_BASEADDR + (uint32)0x440UL)) /**< @brief  Block a Lock Master Sectorb  */
#define PFLASH_PFCBLKU_LOCKMASTER_S_ADDR32      ((uint32)(PFLASH_BASEADDR + (uint32)0x480UL)) /**< @brief  Block UTEST Lock Master Sector  */
#define PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32    ((uint32)(PFLASH_BASEADDR + (uint32)0x484UL)) /**< @brief  Block a Lock Master Super Sectorb   */
#define PFLASH_PFCBLK4_LOCKMASTER_SS0_ADDR32    ((uint32)(PFLASH_BASEADDR + (uint32)0x4C4UL)) /**< @brief  Block a Lock Master Super Sectorb  */
/******************************************************Main registers *******************************************************/
/* MCR register bits */
#define FLASH_MCR_PEID_U32            ((uint32)0x00FF0000UL)  /**< @brief PEID[16-23]:Program and Erase Master/Domain ID (Only Read)*/
#define FLASH_MCR_PEID_SHIFT_U32      (16U)                   /**< @brief PEID[16-23]:Program and Erase Master/Domain ID (Only Read)*/
#define FLASH_MCR_PECIE_U32           ((uint32)0x00008000UL)  /**< @brief PECIE[15]:  Program/Erase Complete Interrupt Enable */
#define FLASH_MCR_WDIE_U32            ((uint32)0x00001000UL)  /**< @brief WDIE[12]:   Watch Dog Interrupt Enable */
#define FLASH_MCR_PGM_U32             ((uint32)0x00000100UL)  /**< @brief PGM[8]:     Program (Read/Write) */
#define FLASH_MCR_ESS_U32             ((uint32)0x00000020UL)  /**< @brief ESS[5]:     Erase Size Select (Read/Write) */
#define FLASH_MCR_ERS_U32             ((uint32)0x00000010UL)  /**< @brief ERS[4]:     Erase (Read/Write) */
#define FLASH_MCR_EHV_U32             ((uint32)0x00000001UL)  /**< @brief EHV[0]:     Enable High Voltage (Read/Write)*/

/* MCRS register bits */
#define FLASH_MCRS_EER_W1C       ((uint32)0x80000000UL)  /**< @brief EER[31]: ECC Event Error (W1C) */
#define FLASH_MCRS_SBC_W1C       ((uint32)0x40000000UL)  /**< @brief SBC[30]: Single Bit Correction (W1C) */
#define FLASH_MCRS_AEE_W1C       ((uint32)0x20000000UL)  /**< @brief AEE[29]: Address Encode Error (W1C) */
#define FLASH_MCRS_EEE_W1C       ((uint32)0x10000000UL)  /**< @brief EEE[28]: EDC after ECC Error (W1C) */
#define FLASH_MCRS_RVE_W1C       ((uint32)0x02000000UL)  /**< @brief RVE[25]: Read Voltage Error (W1C) */
#define FLASH_MCRS_RRE_W1C       ((uint32)0x01000000UL)  /**< @brief RVE[24]: Read Reference Error(W1C) */
#define FLASH_MCRS_RWE_W1C       ((uint32)0x00100000UL)  /**< @brief RWE[20]: Read-While-Write Event Error(W1C) */
#define FLASH_MCRS_PEP_W1C       ((uint32)0x00020000UL)  /**< @brief PEP[17]: Program and Erase Protection Error(W1C) */
#define FLASH_MCRS_PES_W1C       ((uint32)0x00010000UL)  /**< @brief PES[16]: Program and Erase Sequence Error(W1C) */
#define FLASH_MCRS_DONE_U32      ((uint32)0x00008000UL)  /**< @brief DONE[15]:State Machine Status(Only Read) */
#define FLASH_MCRS_PEG_U32       ((uint32)0x00004000UL)  /**< @brief PEG[14]: Program/Erase Good(Only Read) */
#define FLASH_MCRS_TSPELOCK_U32  ((uint32)0x00000100UL)  /**< @brief PEG[8]:  UTest NVM Program and Erase Lock(Only Read) */
#define FLASH_MCRS_RE_U32        ((uint32)0x00000001UL)  /**< @brief RE[0]:   Reset Error(Only Read) */
/* Block n Sector Program Erase Lock PFCBLK0_SPELOCK - PFCBLK4_SPELOCK register bits */
#define PFLASH_PFCBLKx_SPELOCK_SLCK31_U32     ((uint32)0x80000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK30_U32     ((uint32)0x40000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK29_U32     ((uint32)0x20000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK28_U32     ((uint32)0x10000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK27_U32     ((uint32)0x08000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK26_U32     ((uint32)0x04000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK25_U32     ((uint32)0x02000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK24_U32     ((uint32)0x01000000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK23_U32     ((uint32)0x00800000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK22_U32     ((uint32)0x00400000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK21_U32     ((uint32)0x00200000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK20_U32     ((uint32)0x00100000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK19_U32     ((uint32)0x00080000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK18_U32     ((uint32)0x00040000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK17_U32     ((uint32)0x00020000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK16_U32     ((uint32)0x00010000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK15_U32     ((uint32)0x00008000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK14_U32     ((uint32)0x00004000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK13_U32     ((uint32)0x00002000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK12_U32     ((uint32)0x00001000UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK11_U32     ((uint32)0x00000800UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK10_U32     ((uint32)0x00000400UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK9_U32      ((uint32)0x00000200UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK8_U32      ((uint32)0x00000100UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK7_U32      ((uint32)0x00000080UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK6_U32      ((uint32)0x00000040UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK5_U32      ((uint32)0x00000020UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK4_U32      ((uint32)0x00000010UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK3_U32      ((uint32)0x00000008UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK2_U32      ((uint32)0x00000004UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK1_U32      ((uint32)0x00000002UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SPELOCK_SLCK0_U32      ((uint32)0x00000001UL)  /**< @brief SLCK[0-31] Sector is available for program and erase operation 31-0 (Read/Write) */
/* PFCBLKU_SPELOCK register bits */ 
#define PFLASH_PFCBLKU_SPELOCK_SLCK00_U32     ((uint32)0x00000001UL)  /**< @brief SLCK[0] Sector is available for program and erase operation 0(Read/Write) */
/*Block n Super Sector Program Erase Lock (PFCBLK0_SSPELOCK - PFCBLK4_SSPELOCK)*/
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK31_U32     ((uint32)0x80000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK30_U32     ((uint32)0x40000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK29_U32     ((uint32)0x20000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK28_U32     ((uint32)0x10000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK27_U32     ((uint32)0x08000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK26_U32     ((uint32)0x04000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK25_U32     ((uint32)0x02000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK24_U32     ((uint32)0x01000000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK23_U32     ((uint32)0x00800000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK22_U32     ((uint32)0x00400000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK21_U32     ((uint32)0x00200000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK20_U32     ((uint32)0x00100000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK19_U32     ((uint32)0x00080000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK18_U32     ((uint32)0x00040000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK17_U32     ((uint32)0x00020000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK16_U32     ((uint32)0x00010000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK15_U32     ((uint32)0x00008000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK14_U32     ((uint32)0x00004000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK13_U32     ((uint32)0x00002000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK12_U32     ((uint32)0x00001000UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK11_U32     ((uint32)0x00000800UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK10_U32     ((uint32)0x00000400UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK9_U32      ((uint32)0x00000200UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK8_U32      ((uint32)0x00000100UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK7_U32      ((uint32)0x00000080UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK6_U32      ((uint32)0x00000040UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK5_U32      ((uint32)0x00000020UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK4_U32      ((uint32)0x00000010UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK3_U32      ((uint32)0x00000008UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK2_U32      ((uint32)0x00000004UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK1_U32      ((uint32)0x00000002UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSPELOCK_SSLCK0_U32      ((uint32)0x00000001UL)  /**< @brief SSLCK[0-31] Super Sector is available for program and erase operation 31-0 (Read/Write) */
/* Block n Set Sector Lock (PFCBLK0_SETSLOCK - PFCBLK4_SETSLOCK) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK31_U32     ((uint32)0x80000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK30_U32     ((uint32)0x40000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK29_U32     ((uint32)0x20000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK28_U32     ((uint32)0x10000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK27_U32     ((uint32)0x08000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK26_U32     ((uint32)0x04000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK25_U32     ((uint32)0x02000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK24_U32     ((uint32)0x01000000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK23_U32     ((uint32)0x00800000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK22_U32     ((uint32)0x00400000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK21_U32     ((uint32)0x00200000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK20_U32     ((uint32)0x00100000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK19_U32     ((uint32)0x00080000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK18_U32     ((uint32)0x00040000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK17_U32     ((uint32)0x00020000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK16_U32     ((uint32)0x00010000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK15_U32     ((uint32)0x00008000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK14_U32     ((uint32)0x00004000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK13_U32     ((uint32)0x00002000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK12_U32     ((uint32)0x00001000UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK11_U32     ((uint32)0x00000800UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK10_U32     ((uint32)0x00000400UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK9_U32      ((uint32)0x00000200UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK8_U32      ((uint32)0x00000100UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK7_U32      ((uint32)0x00000080UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK6_U32      ((uint32)0x00000040UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK5_U32      ((uint32)0x00000020UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK4_U32      ((uint32)0x00000010UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK3_U32      ((uint32)0x00000008UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK2_U32      ((uint32)0x00000004UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK1_U32      ((uint32)0x00000002UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SETSLOCK_SETSLCK0_U32      ((uint32)0x00000001UL)  /**< @brief SLCK[0-31]  Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
/* Block UTEST Set Sector Lock (PFCBLKU_SETSLOCK) */ 
#define PFLASH_PFCBLKU_SETSLOCK_SETSLCK00_U32     ((uint32)0x00000001UL)  /**< @brief SLCK[0] Corresponding lock bit is owned by any master 0(Read/Write) */
/*Block n Set Super Sector Lock (PFCBLK0_SSETSLOCK - PFCBLK4_SSETSLOCK)*/
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK31_U32     ((uint32)0x80000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK30_U32     ((uint32)0x40000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK29_U32     ((uint32)0x20000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK28_U32     ((uint32)0x10000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK27_U32     ((uint32)0x08000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK26_U32     ((uint32)0x04000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK25_U32     ((uint32)0x02000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK24_U32     ((uint32)0x01000000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK23_U32     ((uint32)0x00800000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK22_U32     ((uint32)0x00400000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK21_U32     ((uint32)0x00200000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK20_U32     ((uint32)0x00100000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK19_U32     ((uint32)0x00080000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK18_U32     ((uint32)0x00040000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK17_U32     ((uint32)0x00020000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK16_U32     ((uint32)0x00010000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK15_U32     ((uint32)0x00008000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK14_U32     ((uint32)0x00004000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK13_U32     ((uint32)0x00002000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK12_U32     ((uint32)0x00001000UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK11_U32     ((uint32)0x00000800UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK10_U32     ((uint32)0x00000400UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK9_U32      ((uint32)0x00000200UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK8_U32      ((uint32)0x00000100UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK7_U32      ((uint32)0x00000080UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK6_U32      ((uint32)0x00000040UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK5_U32      ((uint32)0x00000020UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK4_U32      ((uint32)0x00000010UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK3_U32      ((uint32)0x00000008UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK2_U32      ((uint32)0x00000004UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK1_U32      ((uint32)0x00000002UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */
#define PFLASH_PFCBLKx_SSETSLOCK_SSETSLCK0_U32      ((uint32)0x00000001UL)  /**< @brief SSLCK[0-31] Corresponding lock bit is owned by any master. 31-0 (Read/Write) */

/******************************************************Alternate registers *******************************************************/
/* AMCR register bits */
#define FLASH_AMCR_AWDD_U32        ((uint32)0x20000000UL)  /**< @brief APEID[29]: Watch Dog Disable*/
#define FLASH_AMCR_APEID_U32       ((uint32)0x00FF0000UL)  /**< @brief APEID[16-23]:Program and Erase Master/Domain ID (Only Read)*/
#define FLASH_AMCR_APEID_SHIFT_U32 (16U)                   /**< @brief APEID[16-23]:Program and Erase Master/Domain ID (Only Read)*/
#define FLASH_AMCR_AWDIE_U32       ((uint32)0x00001000UL)  /**< @brief APEID[12]: Alternate Program and Erase Master/Domain ID (Only Read)*/
#define FLASH_AMCR_APGM_U32        ((uint32)0x00000100UL)  /**< @brief APGM[8]:      Alternate Program (Read/Write) */
#define FLASH_AMCR_AESS_U32        ((uint32)0x00000020UL)  /**< @brief AESS[5]:      Alternate Erase Size Select (Read/Write) */
#define FLASH_AMCR_AERS_U32        ((uint32)0x00000010UL)  /**< @brief AERS[4]:      Alternate Erase (Read/Write) */
#define FLASH_AMCR_AEHV_U32        ((uint32)0x00000001UL)  /**< @brief AEHV[0]:      Alternate Enable High Voltage (Read/Write)*/

/* AMCRS register bits */
#define FLASH_AMCRS_APEP_W1C       ((uint32)0x00020000UL)  /**< @brief APEP[17]: Program and Erase Protection Error(W1C) */
#define FLASH_AMCRS_APES_W1C       ((uint32)0x00010000UL)  /**< @brief APES[16]: Program and Erase Sequence Error(W1C) */
#define FLASH_AMCRS_ADONE_U32      ((uint32)0x00008000UL)  /**< @brief ADONE[15]:State Machine Status(Only Read) */
#define FLASH_AMCRS_APEG_U32       ((uint32)0x00004000UL)  /**< @brief APEG[14]: Program/Erase Good(Only Read) */
#define FLASH_AMCRS_ATSPELOCK_U32  ((uint32)0x00000100UL)  /**< @brief APEG[8]:  UTest NVM Program and Erase Lock(Only Read) */
#define FLASH_AMCRS_ARE_U32        ((uint32)0x00000001UL)  /**< @brief ARE[0]:   Reset Error(Only Read) */
/* UT0 register bits */
#define FLASH_UT0_UTE_U32          ((uint32)0x80000000UL)  /**< @brief UTE[31]: U-Test Enable (Read/Write) */
#define FLASH_UT0_SBCE_U32         ((uint32)0x40000000UL)  /**< @brief SBCE[30]: Single Bit Corrections observation (Read/Write) */
#define FLASH_UT0_NAIBP_U32        ((uint32)0x00000200UL)  /**< @brief NAIBP[9]: S Array Integrity state machine (Read/Write) */
#define FLASH_UT0_AIBPE_U32        ((uint32)0x00000100UL)  /**< @brief AIBPE[8]: Array Integrity breakpoints (Read/Write) */
#define FLASH_UT0_AIS_U32          ((uint32)0x00000004UL)  /**< @brief AIS[2]: Array integrity sequence is proprietary/sequential sequence. (Read/Write) */
#define FLASH_UT0_AIE_U32          ((uint32)0x00000002UL)  /**< @brief AIE[1]: Array Integrity Enable */
#define FLASH_UT0_AID_U32          ((uint32)0x00000001UL)  /**< @brief AID[0]: Array Integrity Done */

/* Express program XMCR*/
#define FLASH_XMCR_XPEID_U32      ((uint32)0x00FF0000UL)  /**< @brief APEID[16-23]: Express Program Master/Domain ID*/
#define FLASH_MCR_XPEID_SHIFT_U32 (16U)  /**< @brief APEID[16-23]: Express Program Master/Domain ID*/
#define FLASH_XMCR_XDONE_U32      ((uint32)0x00008000UL)  /**< @brief XDONE[15]: Express State Machine Status*/
#define FLASH_XMCR_XPEG_U32       ((uint32)0x00004000UL)  /**< @brief APEID[14]: Express Program Good*/
#define FLASH_XMCR_XDOK_U32       ((uint32)0x00002000UL)  /**< @brief XPEG[13]: Express Data OK*/
#define FLASH_XMCR_XWDI_U32       ((uint32)0x00001000UL)  /**< @brief XWDI[12]: Express Watch Dog Interrupt*/
#define FLASH_XMCR_XWDIE_U32      ((uint32)0x00000800UL)  /**< @brief XWDIE[11]: Express Watch Dog Interrupt Enable*/
#define FLASH_XMCR_XPGM_U32       ((uint32)0x00000100UL)  /**< @brief APGM[8]: Express Program */
#define FLASH_XMCR_XEHV_U32       ((uint32)0x00000001UL)  /**< @brief AEHV[0]: Express Enable High Voltage*/


#endif /* _Fls_REGISTERS_H_ */
