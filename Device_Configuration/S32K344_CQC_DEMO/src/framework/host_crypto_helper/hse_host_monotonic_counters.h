/**
*   @file    hse_host_monotonic_counters.h
*
*   @brief   Function definitions for monotonic counter services tests.
*   @details
*
*/
/*==================================================================================================
*
*   Copyright 2020-2021 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef _HSE_HOST_MONOTONIC_COUNTERS_H_
#define _HSE_HOST_MONOTONIC_COUNTERS_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "hse_srv_monotonic_cnt.h"

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

hseSrvResponse_t IncCounterReq(uint32_t ind, uint32_t value);

hseSrvResponse_t ReadCounterReq(uint32_t ind, uint64_t *pValue);
#ifdef HSE_H
hseSrvResponse_t PublishLoadCntTblReq(hseNvmCntTblAction_t action, uint8_t *pCntTblContainer);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _HSE_HOST_MONOTONIC_COUNTERS_H_ */

/** @} */


