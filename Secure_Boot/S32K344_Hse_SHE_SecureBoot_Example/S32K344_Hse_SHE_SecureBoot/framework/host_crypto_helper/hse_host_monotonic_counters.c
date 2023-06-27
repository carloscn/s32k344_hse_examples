/**
*   @file    hse_host_monotonic_counters.c
*
*   @brief   This file contains tests of monotonic counters services: IncrementCnt, ReadCnt, Publish/LoadCntTbl.
*
*   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
*   @{
*/
/*==================================================================================================
*   Project              : HSE 16FFC
*   Platform             : Arm Architecture
*   Peripheral           : CortexM7
*   Dependencies         : none
*
*   (c) Copyright 2018 NXP.
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


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#ifndef HSE_SPT_MONOTONIC_COUNTERS
#define HSE_SPT_MONOTONIC_COUNTERS
#endif

#include "hse_host.h"
#include "hse_interface.h"
#include "string.h"



/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

static const uint8_t u8MuInstance = 0U;
static const uint8_t u8MuChInd = 1U;

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/**
 *  @brief  Config counters
 */
hseSrvResponse_t ConfigCounterReq(uint32_t ind, uint32_t rpBitSize)
{    
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChInd];
    hseConfigSecCounterSrv_t *pConfigSecCounter = &(pHseSrvDesc->hseSrv.configSecCounter);

    /* Try to configure the Monotonic Counter in Infield User Mode */
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_CONFIG_COUNTER;
    pConfigSecCounter->counterIndex = ind;
    pConfigSecCounter->RPBitSize = rpBitSize;

    return HSE_Send(u8MuInstance, u8MuChInd, gSyncTxOption, pHseSrvDesc);
}

/**
 *  @brief  Increment counters
 */
hseSrvResponse_t IncCounterReq(uint32_t ind, uint32_t value)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChInd];
    hseIncrementCounterSrv_t *pIncCntSrv = &pHseSrvDesc->hseSrv.incCounterReq;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_INCREMENT_COUNTER;
    pIncCntSrv->counterIndex = ind;
    pIncCntSrv->value = value;

    return HSE_Send(u8MuInstance, u8MuChInd, gSyncTxOption, pHseSrvDesc);
}

/**
 *  @brief Read counters
 */
hseSrvResponse_t ReadCounterReq(uint32_t ind, uint64_t *pValue)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChInd];
    hseReadCounterSrv_t *pReadCntSrv = &pHseSrvDesc->hseSrv.readCounterReq;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_READ_COUNTER;
    pReadCntSrv->counterIndex = ind;
    pReadCntSrv->pCounterVal = (HOST_ADDR)pValue;

    return HSE_Send(u8MuInstance, u8MuChInd, gSyncTxOption, pHseSrvDesc);
}
#if defined(HSE_SPT_FLASHLESS_DEV)
/**
 *  @brief Publish/Load counters table
 */
hseSrvResponse_t PublishLoadCntTblReq(hseNvmCntTblAction_t action, uint8_t *pCntTblContainer)
{
    hseSrvResponse_t hseResponse = HSE_SRV_RSP_NOT_SUPPORTED;

    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChInd];
    hsePublishLoadCntTblSrv_t *pPubLoadCntTblSrv = &pHseSrvDesc->hseSrv.publishLoadCntTblReq;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_PUBLISH_LOAD_CNT_TBL;
    pPubLoadCntTblSrv->action = action;
    pPubLoadCntTblSrv->pNvmContainerCntTbl = (HOST_ADDR)pCntTblContainer;

    hseResponse = HSE_Send(u8MuInstance, u8MuChInd, gSyncTxOption, pHseSrvDesc);

    return hseResponse;
}
#endif

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
