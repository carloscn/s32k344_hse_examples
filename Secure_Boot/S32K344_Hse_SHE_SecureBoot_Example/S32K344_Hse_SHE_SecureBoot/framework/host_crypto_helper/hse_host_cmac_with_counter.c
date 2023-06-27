/**
*   @file    hse_host_cmac_with_counter.c
*
*   @brief   This file contains tests for CMAC with counter generate/verify.
*
*   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
*   @{
*/
/*==================================================================================================*
*   (c) Copyright 2021-2022 NXP.
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
#include "string.h"
#include "hse_host.h"
#include "hse_host_cmac_with_counter.h"

#ifdef HSE_SPT_CMAC_WITH_COUNTER

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

static const uint8_t muInstance = 0U;
static const uint8_t muChIdx = 1U;

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

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

hseSrvResponse_t CmacWithCounter(hseKeyHandle_t keyHandle, hseAuthDir_t authDir, uint32_t cntIndex, uint8_t rpOffset,
                                 uint32_t msgLength, const uint8_t *pMsg, uint8_t tagLength, const uint8_t *pTag, 
                                 uint32_t *pVolatileCnt, hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muInstance][muChIdx];
    hseCmacWithCounterSrv_t *pCMacWithCounterSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId                    = HSE_SRV_ID_CMAC_WITH_COUNTER;
    pCMacWithCounterSrv                   = &(pHseSrvDesc->hseSrv.cmacWithCounterReq);

    pCMacWithCounterSrv->authDir          = authDir;
    pCMacWithCounterSrv->keyHandle        = keyHandle;
    pCMacWithCounterSrv->counterIdx       = cntIndex;
    pCMacWithCounterSrv->RPOffset         = rpOffset;
    pCMacWithCounterSrv->inputBitLength   = msgLength;
    pCMacWithCounterSrv->pInput           = (HOST_ADDR)pMsg;
    pCMacWithCounterSrv->tagBitLength     = tagLength;
    pCMacWithCounterSrv->pTag             = (HOST_ADDR)pTag;
    pCMacWithCounterSrv->pVolatileCounter = (HOST_ADDR)pVolatileCnt;
    pCMacWithCounterSrv->sgtOption        = inputSgtType;

    return HSE_Send(muInstance, muChIdx, gSyncTxOption, pHseSrvDesc);
}

#endif /* HSE_SPT_CMAC_WITH_COUNTER */

#ifdef __cplusplus
}
#endif

/** @} */
