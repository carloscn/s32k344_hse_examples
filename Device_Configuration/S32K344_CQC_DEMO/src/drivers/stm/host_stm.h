/*============================================================================*/

/*    Copyright 2018 NXP.

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
 *   @file    stm.c
 *
 *   @brief   This file contains function prototype to enable/disable STM.
 */


/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/

#ifndef HOST_STM_H
#define HOST_STM_H

/******************************************************************************
 * Global Include Files
 *****************************************************************************/
#include "std_typedefs.h"
/******************************************************************************
 * Local Include Files
 *****************************************************************************/

/******************************************************************************
 * Macros
// *****************************************************************************/
#define STM_0_CR_ADDRESS            (0x40274000U)
#define STM_0_CNT_ADDRESS           (0x40274004U)

/* FIRC DIV 1 @ 48 MHz */
#define AIPS_PLAT_CLOCK_PLL_48MHZ  (48U)
#define FIRC_DIV_1_DELAY_1USEC     (AIPS_PLAT_CLOCK_PLL_48MHZ)
#define FIRC_DIV_1_DELAY_8USEC     ((8U) * FIRC_DIV_1_DELAY_1USEC)
#define FIRC_DIV_1_DELAY_10USEC    ((10U) * FIRC_DIV_1_DELAY_1USEC)
#define FIRC_DIV_1_DELAY_20USEC    ((20U) * FIRC_DIV_1_DELAY_1USEC)
#define FIRC_DIV_1_DELAY_1MSEC     ((1000U) * FIRC_DIV_1_DELAY_1USEC)
#define FIRC_DIV_1_DELAY_2MSEC     ((2U) * FIRC_DIV_1_DELAY_1MSEC)
#define FIRC_DIV_1_DELAY_4MSEC     ((4U) * FIRC_DIV_1_DELAY_1MSEC)
#define FIRC_DIV_1_DELAY_20MSEC    ((20U) * FIRC_DIV_1_DELAY_1MSEC)
#define FIRC_DIV_1_DELAY_1SEC      ((1000U) * FIRC_DIV_1_DELAY_1MSEC)
#define FIRC_DIV_1_DELAY_5SEC      ((5U) * FIRC_DIV_1_DELAY_1SEC)
#define FIRC_DIV_1_DELAY_30SEC     ((30U) * FIRC_DIV_1_DELAY_1SEC)
#define FIRC_DIV_1_DELAY_60SEC     ((60U) * FIRC_DIV_1_DELAY_1SEC)
#define FIRC_DIV_1_DELAY_90SEC     ((90U) * FIRC_DIV_1_DELAY_1SEC)
/******************************************************************************
 * Structures/Enums
 *****************************************************************************/

/******************************************************************************
 * Global Variables Definition
 *****************************************************************************/

/******************************************************************************
 * Extern Functions
 *****************************************************************************/
/* This function Enables STM for measuring the time for an operation */
extern void EnableStm(void);

/* This function disables STM and stops the STM timer */
extern void DisbleStm(void);

/* This function returns the time measured for an operation */
extern uint32_t MeasureStm(void);

/* This function returns the time taken by any command. It is the total time
 * when the command was sent to the time when command interrupt from SHE was
 * received
 */
extern uint32_t GetTimer(void);
extern void EnableStmDiv(uint32_t divide);
extern void DelayStm(uint32_t delay);



#endif /* HSE__STM_H */
