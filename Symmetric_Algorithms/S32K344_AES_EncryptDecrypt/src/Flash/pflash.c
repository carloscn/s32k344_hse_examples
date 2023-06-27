/******************************************************************************
 * (c) Copyright 2018-2020, NXP Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pflash.c
 * @brief     Platform Flash Memory Controller (PFLASH) driver source code.
 ******************************************************************************/
#include "S32K344_COMMON.h"
#include "pflash.h"


/******************************************************************************
 * Function and variable placement defines                                    *
 *********************volatile *********************************************************/
#define __tcm(attr)     __attribute__((section(".tcm.$" #attr)))     /* attributes - func|data|zero         */
#define __ram(attr)     __attribute__((section(".ram.$" #attr)))     /* attributes - func|data|zero|standby */
#define __dflash(attr)  __attribute__((section(".dflash.$" #attr)))  /* attributes - func|data              */
#define __pflash(attr)  __attribute__((section(".pflash.$" #attr)))  /* attributes - func|data              */
#define __flash(attr)  __attribute__((section(".flash.$" #attr)))  /* attributes - func|data              */
#define __NOINIT(mem) __attribute__((section(".noinit.$" #mem))) // mem = DFLASH|RAM|DTCM


/******************************************************************************
 * public function definitions                                                *
 ******************************************************************************/
__tcm(func) void PFLASH_SetPFCR (uint8_t ports, uint32_t code, uint32_t data)
{
  if (ports & PFLASH_P0) { PFLASH_PFCR0 = code|data; }
  if (ports & PFLASH_P1) { PFLASH_PFCR1 = code|data; }
  #if PFLASH_PFCRI_COUNT > 2
  	  if (ports & PFLASH_P2) { PFLASH_PFCR2 = code|data; }
  #endif
  #if PFLASH_PFCRI_COUNT > 3
  	  if (ports & PFLASH_P3) { PFLASH_PFCR3 = code|data; }
  #endif
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
