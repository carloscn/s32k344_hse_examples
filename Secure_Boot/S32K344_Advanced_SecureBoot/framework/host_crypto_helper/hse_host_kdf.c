/**
 *   @file    hse_host_kdf.c
 *
 *   @brief   This file containts wrappers for KDF services
 *   @details
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
 *
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

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/

#include "hse_host.h"
#include "hse_host_kdf.h"
#include "hse_keys_allocator.h"

#include "string.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL VARIABLES
 ==================================================================================================*/
#ifdef HSE_SPT_KEY_DERIVE
static uint8_t muIf = 0U;
static uint8_t muChannelIdx = 1U;
#endif
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
#ifdef HSE_SPT_KDF_IKEV2
hseSrvResponse_t HSEKeyDeriveIKEv2Req
(
    hseKdfIKEV2Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t* pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_IKEV2;
    memcpy(&pDeriveKeySrv->sch.IKEv2, pKdfScheme, sizeof(hseKdfIKEV2Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KEY_DERIVE
hseSrvResponse_t HSEKeyDeriveExtractKeyReq
(
    hseKeyHandle_t      keyHandle,
    uint16_t            startOffset,
    hseKeyHandle_t      *pTargetKeyHandle,
    uint8_t             isNvmKey,
    hseKeyInfo_t        keyInfo
)
{
    hseSrvResponse_t hseResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveCopyKeySrv_t *pExtractKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveCopyKeyReq);

    hseResponse = HKF_AllocKeySlot(isNvmKey, keyInfo.keyType, keyInfo.keyBitLen, pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE_COPY;

    pExtractKeySrv->keyHandle = keyHandle;
    pExtractKeySrv->startOffset = startOffset;
    pExtractKeySrv->targetKeyHandle = *pTargetKeyHandle;
    pExtractKeySrv->keyInfo = keyInfo;

    hseResponse = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
    }
exit:
    return hseResponse;
}
#endif
#ifdef HSE_SPT_KDF_ISO18033_KDF1
hseSrvResponse_t HSEKdfISO_KDF1Req
(
    hseKdfISO18033_KDF1Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t* pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_ISO18033_KDF1;
    memcpy(&pDeriveKeySrv->sch.ISO18033_KDF1, pKdfScheme, sizeof(hseKdfISO18033_KDF1Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_ISO18033_KDF2
hseSrvResponse_t HSEKdfISO_KDF2Req
(
    hseKdfISO18033_KDF2Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t* pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_ISO18033_KDF2;
    memcpy(&pDeriveKeySrv->sch.ISO18033_KDF2, pKdfScheme, sizeof(hseKdfISO18033_KDF2Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_NXP_GENERIC
hseSrvResponse_t HSEKdfNXP_KDFReq
(
    hseKdfNxpGenericScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t* pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_NXP_GENERIC;
    memcpy(&pDeriveKeySrv->sch.nxpGeneric, pKdfScheme, sizeof(hseKdfNxpGenericScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_SP800_56C_ONESTEP
hseSrvResponse_t HSEKdfSP800_56COneStepReq
(
    hseKdfSP800_56COneStepScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t* pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_SP800_56C_ONE_STEP;
    memcpy(&pDeriveKeySrv->sch.SP800_56COneStep, pKdfScheme, sizeof(hseKdfSP800_56COneStepScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_ANS_X963
hseSrvResponse_t HSEKdfANS_X963Req
(
    hseKdfANSX963Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_ANS_X963;
    memcpy(&pDeriveKeySrv->sch.ANS_X963, pKdfScheme, sizeof(hseKdfANSX963Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_SP800_56C_TWOSTEP
hseSrvResponse_t HSEKdfSP800_56C_TwoStepReq
(
    hseKdfSP800_56CTwoStepScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_SP800_56C_TWO_STEP;
    memcpy(&pDeriveKeySrv->sch.SP800_56CTwoStep, pKdfScheme, sizeof(hseKdfSP800_56CTwoStepScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_SP800_108
hseSrvResponse_t HSEKdfSP800_108Req
(
    hseKdfSP800_108Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_SP800_108;
    memcpy(&pDeriveKeySrv->sch.SP800_108, pKdfScheme, sizeof(hseKdfSP800_108Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
 #ifdef HSE_SPT_KEY_DERIVE
hseSrvResponse_t HSEKdfExtract_StepReq
(
    hseKdfExtractStepScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_EXTRACT_STEP;
    memcpy(&pDeriveKeySrv->sch.extractStep, pKdfScheme, sizeof(hseKdfExtractStepScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_PBKDF2
hseSrvResponse_t HSE_PBKDF2Req
(
    hsePBKDF2Scheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_PBKDF2HMAC;
    memcpy(&pDeriveKeySrv->sch.PBKDF2, pKdfScheme, sizeof(hsePBKDF2Scheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_KDF_TLS12_PRF
hseSrvResponse_t HSE_TLS12_PRFReq
(
    hseKdfTLS12PrfScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_TLS12PRF;
    memcpy(&pDeriveKeySrv->sch.TLS12Prf, pKdfScheme, sizeof(hseKdfTLS12PrfScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef HSE_SPT_HKDF
hseSrvResponse_t HSE_HKDFReq
(
    hseHKDF_ExpandScheme_t *pKdfScheme
)
{
    hseSrvDescriptor_t *pHseSrvDesc  = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyDeriveSrv_t *pDeriveKeySrv = &(pHseSrvDesc->hseSrv.keyDeriveReq);

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_DERIVE;

    pDeriveKeySrv->kdfAlgo = HSE_KDF_ALGO_HKDF_EXPAND;
    memcpy(&pDeriveKeySrv->sch.HKDF_Expand, pKdfScheme, sizeof(hseHKDF_ExpandScheme_t));

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}
#endif
#ifdef __cplusplus
}
#endif

/** @} */

