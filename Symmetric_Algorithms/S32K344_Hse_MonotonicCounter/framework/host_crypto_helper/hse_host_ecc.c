/**
*   @file    hse_host_ecc.c
*
*   @brief   This file contains tests of ECC services: generate key.
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
extern "C"
{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/

#include "hse_default_config.h"
#include "hse_host.h"
#include "hse_host_import_key.h"
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
#if (defined(HSE_SPT_KEY_GEN) && defined(HSE_SPT_ECC_KEY_PAIR_GEN)) || (defined(HSE_SPT_ECC_USER_CURVES))
static uint8_t          muIf = 0U;
static uint8_t          muChannelIdx = 1U;
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

static hseSrvResponse_t GenerateEccKeyReq
(
    hseKeyHandle_t targetKeyHandle,
    hseKeyType_t keyType,
    hseKeyFlags_t keyFlags,
    hseEccCurveId_t eccCurveId,
    uint32_t keyBitLength,
    uint8_t* pPubKey
);
/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/

static hseSrvResponse_t GenerateEccKeyReq
(
    hseKeyHandle_t targetKeyHandle,
    hseKeyType_t keyType,
    hseKeyFlags_t keyFlags,
    hseEccCurveId_t eccCurveId,
    uint32_t keyBitLength,
    uint8_t* pPubKey
)
{
#if defined(HSE_SPT_KEY_GEN) && defined(HSE_SPT_ECC_KEY_PAIR_GEN)
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc ->srvId = HSE_SRV_ID_KEY_GENERATE;
    hseKeyGenerateSrv_t*  pGenKeyReq = &pHseSrvDesc->hseSrv.keyGenReq;

    pGenKeyReq->keyInfo.keyType = keyType;
    pGenKeyReq->keyInfo.keyFlags = keyFlags;
    pGenKeyReq->keyInfo.specific.eccCurveId = eccCurveId;
    pGenKeyReq->keyInfo.keyBitLen = keyBitLength;
    pGenKeyReq->sch.eccKey.pPubKey = (HOST_ADDR)pPubKey;
    pGenKeyReq->keyGenScheme = HSE_KEY_GEN_ECC_KEY_PAIR;
    pGenKeyReq->targetKeyHandle = targetKeyHandle;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
#else
    (void)targetKeyHandle;
    (void)keyType;
    (void)keyFlags;
    (void)eccCurveId;
    (void)keyBitLength;
    (void)pPubKey;
    return HSE_SRV_RSP_NOT_SUPPORTED;
#endif
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/

/*****************************************************************************************
 *                                      Generic
 ****************************************************************************************/
uint32_t KeyBitLen(uint32_t eccCurveId)
{
    switch(eccCurveId)
    {
        #ifdef HSE_SPT_EC_SEC_SECP256R1
        case HSE_EC_SEC_SECP256R1:
            return 256UL;
        #endif

        #ifdef HSE_SPT_EC_SEC_SECP384R1
        case HSE_EC_SEC_SECP384R1:
            return 384UL;
        #endif

        #ifdef HSE_SPT_EC_SEC_SECP521R1
        case HSE_EC_SEC_SECP521R1:
            return 521UL;
        #endif

        #ifdef HSE_SPT_EC_BRAINPOOL_BRAINPOOLP256R1
        case HSE_EC_BRAINPOOL_BRAINPOOLP256R1:
            return 256UL;
        #endif

        #ifdef HSE_SPT_EC_BRAINPOOL_BRAINPOOLP320R1
        case HSE_EC_BRAINPOOL_BRAINPOOLP320R1:
            return 320UL;
        #endif

        #ifdef HSE_SPT_EC_BRAINPOOL_BRAINPOOLP384R1
        case HSE_EC_BRAINPOOL_BRAINPOOLP384R1:
            return 384UL;
        #endif

        #ifdef HSE_SPT_EC_BRAINPOOL_BRAINPOOLP512R1
        case HSE_EC_BRAINPOOL_BRAINPOOLP512R1:
            return 512UL;
        #endif

        #ifdef HSE_SPT_EC_25519_ED25519
        case HSE_EC_25519_ED25519:
            return 256UL;
        #endif

        #ifdef HSE_SPT_EC_25519_CURVE25519
        case HSE_EC_25519_CURVE25519:
            return 256UL;
        #endif

        #ifdef HSE_SPT_EC_448_ED448
        case HSE_EC_448_ED448:
            return 456UL;
        #endif

        #ifdef HSE_SPT_EC_448_CURVE448
        case HSE_EC_448_CURVE448:
            return 448UL;
        #endif

        default:
            return 0UL;
    }
}



hseSrvResponse_t GenerateEccKey(
    hseKeyHandle_t *pTargetKeyHandle,
    bool_t isNvmKey,
    hseEccCurveId_t eccCurveId,
    uint32_t usageFlags
)
{
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseKeyInfo_t lKeyInfo = {0};
    bool_t bEraseKeyBeforeGen = FALSE;

    hseSrvResponse = HKF_AllocKeySlot(isNvmKey, WRP_KEY_TYPE_ECC_PAIR, WRP_ECC_KEY_SIZE, pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != hseSrvResponse)
    {
        goto exit;
    }
    bEraseKeyBeforeGen = ((NVM_KEY == isNvmKey) && (HSE_SRV_RSP_KEY_EMPTY != GetKeyInfo(*pTargetKeyHandle, &lKeyInfo)));
    if(bEraseKeyBeforeGen)
    {
        /* Erase NVM key before import (ensure the key slot is empty) */
        if(HSE_SRV_RSP_OK != (hseSrvResponse = EraseKeyReq(*pTargetKeyHandle, HSE_ERASE_NOT_USED)))
        {
            goto exit;
        }
    }
    hseSrvResponse = GenerateEccKeyReq(*pTargetKeyHandle, HSE_KEY_TYPE_ECC_PAIR, usageFlags, eccCurveId, KeyBitLen(eccCurveId), NULL);
    if(HSE_SRV_RSP_OK != hseSrvResponse)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
        goto exit;
    }
exit:
    return hseSrvResponse;
}

hseSrvResponse_t GenerateEccKeyAndExportPublic(
    hseKeyHandle_t targetKeyHandle,
    hseEccCurveId_t eccCurveId,
    uint32_t usageFlags,
    uint8_t* pPubKey
)
{
    return GenerateEccKeyReq(targetKeyHandle, HSE_KEY_TYPE_ECC_PAIR, usageFlags, eccCurveId, KeyBitLen(eccCurveId), pPubKey);
}

hseSrvResponse_t LoadEccUserCurve(
    hseEccCurveId_t eccCurveId,
    hseKeyBits_t nBitLength,
    hseKeyBits_t pBitLength,
    const uint8_t* pA,
    const uint8_t* pB,
    const uint8_t* pG,
    const uint8_t* pN,
    const uint8_t* pP
)
{
#ifdef HSE_SPT_ECC_USER_CURVES
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_LOAD_ECC_CURVE;
    hseLoadEccCurveSrv_t* pLoadCurveSrv = &pHseSrvDesc->hseSrv.loadEccCurveReq;
    pLoadCurveSrv->eccCurveId = eccCurveId;
    pLoadCurveSrv->nBitLen = nBitLength;
    pLoadCurveSrv->pBitLen = pBitLength;
    pLoadCurveSrv->pA = (HOST_ADDR)pA;
    pLoadCurveSrv->pB = (HOST_ADDR)pB;
    pLoadCurveSrv->pG = (HOST_ADDR)pG;
    pLoadCurveSrv->pN = (HOST_ADDR)pN;
    pLoadCurveSrv->pP = (HOST_ADDR)pP;
    hseStatus = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);

    return hseStatus;
#else
    (void)eccCurveId;
    (void)nBitLength;
    (void)pBitLength;
    (void)pA;
    (void)pB;
    (void)pG;
    (void)pN;
    (void)pP;
    return HSE_SRV_RSP_NOT_SUPPORTED;
#endif
}

#ifdef __cplusplus
}
#endif

/** @} */
