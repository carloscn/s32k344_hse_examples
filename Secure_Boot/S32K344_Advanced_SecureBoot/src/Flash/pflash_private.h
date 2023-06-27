/******************************************************************************
 * (c) Copyright 2018-2020, NXP Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pflash_private.h
 * @brief     Platform Flash Memory Controller (PFLASH) private definitions.
 ******************************************************************************/
#ifndef __PFLASH_PRIVATE_H
#define __PFLASH_PRIVATE_H

#include "S32K344_PFLASH.h"

/******************************************************************************
 * PFLASH registers for driver implementation
 ******************************************************************************/
#define PFLASH_PFCR0  IP_PFLASH->PFCR[0]
#define PFLASH_PFCR1  IP_PFLASH->PFCR[1]
#define PFLASH_PFCR2  IP_PFLASH->PFCR[2]
#define PFLASH_PFCR3  IP_PFLASH->PFCR[3]

#define PFLASH_PFCBLK0_SSPELOCK   IP_PFLASH->PFCBLK_SSPELOCK[0]
#define PFLASH_PFCBLK1_SSPELOCK   IP_PFLASH->PFCBLK_SSPELOCK[1]
#define PFLASH_PFCBLK2_SSPELOCK   IP_PFLASH->PFCBLK_SSPELOCK[2]
#define PFLASH_PFCBLK3_SSPELOCK   IP_PFLASH->PFCBLK_SSPELOCK[3]

#define PFLASH_PFCBLK0_SPELOCK    IP_PFLASH->PFCBLK_SPELOCK[0]
#define PFLASH_PFCBLK1_SPELOCK    IP_PFLASH->PFCBLK_SPELOCK[1]
#define PFLASH_PFCBLK2_SPELOCK    IP_PFLASH->PFCBLK_SPELOCK[2]
#define PFLASH_PFCBLK3_SPELOCK    IP_PFLASH->PFCBLK_SPELOCK[3]
#define PFLASH_PFCBLK4_SPELOCK    IP_PFLASH->PFCBLK_SPELOCK[4]
#define PFLASH_PFCBLK5_SPELOCK    IP_PFLASH->PFCBLKU_SPELOCK[0]

#define PFLASH_PFCBLK0_SSETSLOCK  IP_PFLASH->PFCBLK_SSETSLOCK[0]
#define PFLASH_PFCBLK1_SSETSLOCK  IP_PFLASH->PFCBLK_SSETSLOCK[1]
#define PFLASH_PFCBLK2_SSETSLOCK  IP_PFLASH->PFCBLK_SSETSLOCK[2]
#define PFLASH_PFCBLK3_SSETSLOCK  IP_PFLASH->PFCBLK_SSETSLOCK[3]

#define PFLASH_PFCBLK0_SETSLOCK   IP_PFLASH->PFCBLK_SETSLOCK[0]
#define PFLASH_PFCBLK1_SETSLOCK   IP_PFLASH->PFCBLK_SETSLOCK[1]
#define PFLASH_PFCBLK2_SETSLOCK   IP_PFLASH->PFCBLK_SETSLOCK[2]
#define PFLASH_PFCBLK3_SETSLOCK   IP_PFLASH->PFCBLK_SETSLOCK[3]
#define PFLASH_PFCBLK4_SETSLOCK   IP_PFLASH->PFCBLK_SETSLOCK[4]

#endif /* __PFLASH_PRIVATE_H */
