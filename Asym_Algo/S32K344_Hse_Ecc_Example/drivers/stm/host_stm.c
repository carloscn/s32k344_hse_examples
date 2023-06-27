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
 *   @file    stm.c
 *
 *   @brief   This file contains functions to enable/disable STM.
 */

/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/
#include "host_stm.h"
#include "std_typedefs.h"
/*LDRA_NOANALYSIS*/
/******************************************************************************
 * Local Constants/Macors
 *****************************************************************************/
#define STM_CNT_RESET_VALUE (0x0)

/* STM Control Register */
#define STM_CR_TEN_ENABLE (0x1U) /* Enable STM */
#define STM_CR_FRZ_ENABLE (0x2U) /* Freeze STM in Debug Mode */
#define STM_CR_DISABLE (0x0)     /* Disable STM */

#define STM_CR_CPS_SHIFT (8U)
/******************************************************************************
 * Local Typedefs (Structures, Unions, Enums)
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
/* Stores the time taken by any command */
static uint32_t timeTaken = 0;

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 * Extern Functions
 *****************************************************************************/

/******************************************************************************
 * FUNCTION:        EnableStm
 *
 * DESCRIPTION:
 *   This function Enables STM for measuring the time for an operation
 *
 * Parameters:
 *      None
 *  
 * RETURN VALUE:    None
 *
 * NOTES:           None
 *
 *****************************************************************************/
void EnableStm(void)
{
    vuint32_t *stmBaseAddr = NULL;
    vuint32_t *stmCounter = NULL;

    stmBaseAddr = (vuint32_t *)(STM_0_CR_ADDRESS);
    stmCounter = (vuint32_t *)(STM_0_CNT_ADDRESS);
    *stmCounter = (uint32_t)STM_CNT_RESET_VALUE;
    *stmBaseAddr = (uint32_t)(STM_CR_TEN_ENABLE | STM_CR_FRZ_ENABLE);
}

/******************************************************************************
 * FUNCTION:        DisbleStm
 *
 * DESCRIPTION:
 *   This function disables STM and stops the STM timer 
 *
 * Parameters:
 *      None
 *  
 * RETURN VALUE:    None
 *
 * NOTES:           None
 *
 *****************************************************************************/
void DisbleStm(void)
{
    vuint32_t *stmBaseAddr = NULL;
    stmBaseAddr = (vuint32_t *)(STM_0_CR_ADDRESS);
    *stmBaseAddr = (uint32_t)STM_CR_DISABLE;
}

/******************************************************************************
 * FUNCTION:        MeasureStm
 *
 * DESCRIPTION:
 *   This function returns the time measured for an operation
 *
 * Parameters:
 *      None
 *  
 * RETURN VALUE:    None
 *
 * NOTES:           None
 *
 *****************************************************************************/
uint32_t MeasureStm(void)
{
    timeTaken = (vuint32_t) * ((vuint32_t *)STM_0_CNT_ADDRESS);
    return (timeTaken);
}

/******************************************************************************
 * FUNCTION:        GetTimer
 *
 * DESCRIPTION:
 *   This function returns the time taken by any command. It is the total time
 *   when the command was sent to the time when command interrupt from SHE was
 *   received
 *
 * Parameters:
 *      None
 *  
 * RETURN VALUE:    None
 *
 * NOTES:
 *   For this to work, MeasureStm must be called before Disabling STM
 *
 *****************************************************************************/
uint32_t GetTimer(void)
{
    return (timeTaken);
}

/******************************************************************************
 * FUNCTION:        EnableStmDiv
 *
 * DESCRIPTION:
 *   This function Enables STM for measuring the time for an operation.
 *   The input clock for STM is divided by given value.
 *
 * Parameters:
 *      div: The input clock to stm is divide by value div + 1.
 *
 * RETURN VALUE:    None
 *
 * NOTES:           None
 *
 *****************************************************************************/
void EnableStmDiv(uint32_t div)
{
    vuint32_t *stmBaseAddr = NULL;
    vuint32_t *stmCounter = NULL;

    stmBaseAddr = (vuint32_t *)(STM_0_CR_ADDRESS);
    stmCounter = (vuint32_t *)(STM_0_CNT_ADDRESS);
    *stmCounter = (uint32_t)STM_CNT_RESET_VALUE;
    *stmBaseAddr = (uint32_t)(STM_CR_TEN_ENABLE | STM_CR_FRZ_ENABLE | (div << STM_CR_CPS_SHIFT));
}

/******************************************************************************
 * FUNCTION:        DelayStm
 *
 * DESCRIPTION:
 *   This function gives delay for given time
 *
 * Parameters:
 *      delay: required delay time
 *
 * RETURN VALUE:    None
 *
 * NOTES:           None
 *
 *****************************************************************************/
void DelayStm(uint32_t delay)
{
    EnableStm();
    while (MeasureStm() < delay)
    {
        ; /* Do Nothing */
    }
    DisbleStm();
}

/*LDRA_ANALYSIS*/
