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
 *   @file    monotonic_cnt.c
 *
 *   @brief   This is a monotonic counter wrapper file.
 */

/*=============================================================================
 *                               INCLUDE FILES
 =============================================================================*/
#include "hse_monotonic_cnt.h"
#include "hse_interface.h"
#include "hse_mu.h"
#include "global_defs.h"
#include "hse_host.h"
#include "string.h"
#include "hse_global_variables.h"
/*=============================================================================
                                 LOCAL MACROS
  ============================================================================*/

/*=============================================================================
 *                               LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/

typedef enum
{
    MONOTONIC_CNT_NOT_SELECTED = 0,
    MONOTONIC_CNT_CONFIGURE,
    MONOTONIC_CNT_INCREMENT,
    MONOTONIC_CNT_READ,
} monoTonicCounter_Selection_t;

/*=============================================================================
 *                               LOCAL VARIABLES
 =============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

volatile monoTonicCounter_Selection_t monotonic_cnt_select = MONOTONIC_CNT_NOT_SELECTED;
volatile uint32_t MonotonicCntIndex = 0xFFU;
volatile HOST_ADDR MonotonicCntReadValue = 0U;
volatile uint32_t MonotonicCntIncrementValue = 0U;
volatile uint8_t MonotonicCntRPBitSize = 0xFFU;
hseSrvResponse_t MonotonicCntResponse = HSE_SRV_RSP_GENERAL_ERROR;

/*=============================================================================
                                LOCAL FUNCTION
  ============================================================================*/

/*=============================================================================
                                GLOBAL FUNCTION
  ============================================================================*/
#ifdef HSE_SPT_MONOTONIC_COUNTERS
/* FUNCTION NAME: MonotonicCnt_Increment
 *
 * DESCRIPTION:
 * This function Increment monotonic counter.
 */
hseSrvResponse_t MonotonicCnt_Increment(uint32_t CounterIndex,
                                        uint32_t CounterNewValue)
{
    hseSrvResponse_t status = HSE_SRV_RSP_VERIFY_FAILED;
    uint8_t u8MuChannel;
    hseSrvDescriptor_t *pHseSrvDesc = NULL;

    /* Get a free channel on MU0 */
    u8MuChannel = HSE_MU_GetFreeChannel(MU0);
    if (HSE_INVALID_CHANNEL == u8MuChannel)
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    if ((CounterIndex > 16U))
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    pHseSrvDesc = (hseSrvDescriptor_t *)&gHseSrvDesc[MU0][u8MuChannel];

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_INCREMENT_COUNTER;

    pHseSrvDesc->hseSrv.incCounterReq.counterIndex = CounterIndex;
    pHseSrvDesc->hseSrv.incCounterReq.value = CounterNewValue;

    status = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);
EXIT:
    return status;
}

/* FUNCTION NAME: MonotonicCnt_Read
 *
 * DESCRIPTION:
 * This function read monotonic counter.
 */

hseSrvResponse_t MonotonicCnt_Read(uint32_t CounterIndex,
                                   HOST_ADDR CounterValue)
{
    hseSrvResponse_t status = HSE_SRV_RSP_VERIFY_FAILED;
    uint8_t u8MuChannel;
    hseSrvDescriptor_t *pHseSrvDesc = NULL;

    /* Get a free channel on MU0 */
    u8MuChannel = HSE_MU_GetFreeChannel(MU0);
    if (HSE_INVALID_CHANNEL == u8MuChannel)
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    if ((CounterIndex > 16U))
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    pHseSrvDesc = (hseSrvDescriptor_t *)&gHseSrvDesc[MU0][u8MuChannel];

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_READ_COUNTER;
    pHseSrvDesc->hseSrv.readCounterReq.counterIndex = CounterIndex;
    pHseSrvDesc->hseSrv.readCounterReq.pCounterVal = CounterValue;

    status = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);
EXIT:
    return status;
}

/* FUNCTION NAME: MonotonicCnt_Config
 *
 * DESCRIPTION:
 * This function configures monotonic counter.
 */

hseSrvResponse_t MonotonicCnt_Config(uint32_t CounterIndex,
                                     uint8_t RPBitSize)
{
    hseSrvResponse_t status = HSE_SRV_RSP_VERIFY_FAILED;
    uint8_t u8MuChannel;
    hseSrvDescriptor_t *pHseSrvDesc = NULL;

    /* Get a free channel on MU0 */
    u8MuChannel = HSE_MU_GetFreeChannel(MU0);
    if (HSE_INVALID_CHANNEL == u8MuChannel)
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    if ((CounterIndex > 16U))
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    if ((RPBitSize < 32U) || (RPBitSize > 64U) || (RPBitSize % 8U != 0U))
    {
        status = HSE_SRV_RSP_INVALID_PARAM;
        goto EXIT;
    }
    pHseSrvDesc = (hseSrvDescriptor_t *)&gHseSrvDesc[MU0][u8MuChannel];

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_CONFIG_COUNTER;
    pHseSrvDesc->hseSrv.configSecCounter.counterIndex = CounterIndex;
    pHseSrvDesc->hseSrv.configSecCounter.RPBitSize = RPBitSize;

    status = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);
EXIT:
    return status;
}

void monotonicCounterService(void)
{
    hseSrvResponse_t servResponse = HSE_SRV_RSP_GENERAL_ERROR;
    servResponse = HSE_SRV_RSP_GENERAL_ERROR;
    servResponse = monotonicCounterserviceSelect();
    if (HSE_SRV_RSP_OK == servResponse)
    {
        testStatus |= MONOTONIC_CNT_DONE;
    }
}

hseSrvResponse_t monotonicCounterserviceSelect()
{

    switch (monotonic_cnt_select)
    {
    case MONOTONIC_CNT_CONFIGURE:
        /* Configure MonoTonic Counter */
        MonotonicCntResponse = MonotonicCnt_Config(MonotonicCntIndex, MonotonicCntRPBitSize);
        break;
    case MONOTONIC_CNT_INCREMENT:
        MonotonicCntResponse = MonotonicCnt_Increment(MonotonicCntIndex, MonotonicCntIncrementValue);
        break;
    case MONOTONIC_CNT_READ:
        MonotonicCntResponse = MonotonicCnt_Read(MonotonicCntIndex, (uint32_t)&MonotonicCntReadValue);
        break;
    default:
        MonotonicCntResponse = HSE_SRV_RSP_INVALID_PARAM;
        break;
    }
    /* Clear Monotonic Variables */
    monotonic_cnt_select = MONOTONIC_CNT_NOT_SELECTED;
    MonotonicCntIndex = 0xFFU;
    MonotonicCntIncrementValue = 0x0U;
    MonotonicCntRPBitSize = 0xFFU;
    return MonotonicCntResponse;
}
#endif
