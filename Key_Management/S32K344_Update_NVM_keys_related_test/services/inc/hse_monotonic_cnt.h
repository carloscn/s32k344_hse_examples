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
  ============================================================================*/
/**
 *   @file    hse_monotonic_cnt.h
 *
 *   @brief   This is a monotonic counter wrapper file.
 */
#ifndef MONOTONIC_COUNTER_H
#define MONOTONIC_COUNTER_H
/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/
#include "hse_common_types.h"
#include "hse_srv_monotonic_cnt.h"
#include "hse_srv_responses.h"
/*=============================================================================
                                 MACROS
  ============================================================================*/

/*=============================================================================
 *                               TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

/*=============================================================================
                                 GLOBAL FUNCTION
  ============================================================================*/

hseSrvResponse_t MonotonicCnt_Increment(uint32_t CounterIndex,
                                        uint32_t CounterNewValue);
hseSrvResponse_t MonotonicCnt_Read(uint32_t CounterIndex,
                                   HOST_ADDR CounterValue);
hseSrvResponse_t MonotonicCnt_Config(uint32_t CounterIndex,
                                     uint8_t RPBitSize);
void monotonicCounterService(void);
hseSrvResponse_t monotonicCounterserviceSelect(void);

#endif /* MONOTONIC_COUNTER_H */
