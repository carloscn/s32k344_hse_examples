/**
 *   @file    hse_host_mac.c
 *
 *   @brief   This file use verify MAC operation
 *   @details This file will generate & verify CMAC & GMAC.
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
 *   (c) Copyright 2018-2021 NXP.
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

#include "hse_host.h"
#include "string.h"

#include "hse_host_mac.h"

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
static const uint8_t muIf = 0U;
static const uint8_t muChannelIdx = 1U;

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

hseSrvResponse_t MacSignSrv(hseAccessMode_t accessMode, uint32_t streamId,
                            hseMacScheme_t macScheme, hseKeyHandle_t keyHandle,
                            uint32_t inputLength, const uint8_t* pInput,
                            uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseMacSrv_t* pMacSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_MAC;
    pMacSrv = &(pHseSrvDesc->hseSrv.macReq);

    pMacSrv->accessMode = accessMode;
    pMacSrv->streamId = streamId;
    pMacSrv->macScheme = macScheme;
    pMacSrv->authDir = HSE_AUTH_DIR_GENERATE;
    pMacSrv->keyHandle = keyHandle;
    pMacSrv->inputLength = inputLength;
    pMacSrv->pInput = (HOST_ADDR)pInput;
    pMacSrv->pTagLength = (HOST_ADDR)pTagLength;
    pMacSrv->pTag = (HOST_ADDR)pTag;
    pMacSrv->sgtOption = inputSgtType;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

hseSrvResponse_t MacVerSrv(hseAccessMode_t accessMode, uint32_t streamId,
                           hseMacScheme_t macScheme, hseKeyHandle_t keyHandle,
                           uint32_t inputLength, const uint8_t* pInput,
                           const uint32_t* pTagLength, const uint8_t* pTag, hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseMacSrv_t* pMacSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_MAC;
    pMacSrv = &(pHseSrvDesc->hseSrv.macReq);

    pMacSrv->accessMode     = accessMode;
    pMacSrv->streamId       = streamId;
    pMacSrv->macScheme      = macScheme;
    pMacSrv->authDir        = HSE_AUTH_DIR_VERIFY;
    pMacSrv->keyHandle      = keyHandle;
    pMacSrv->inputLength    = inputLength;
    pMacSrv->pInput         = (HOST_ADDR)pInput;
    pMacSrv->pTagLength     = (HOST_ADDR)pTagLength;
    pMacSrv->pTag           = (HOST_ADDR)pTag;
    pMacSrv->sgtOption      = inputSgtType;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

hseSrvResponse_t AesKmCmacGen(uint8_t u8MuInstance, hseKeyHandle_t keyHandle, uint32_t messageLength, const uint8_t * pMessage, uint8_t* tag,
        uint32_t tagsize, uint32_t streamId, hseAccessMode_t accessMode)
{

    uint8_t u8MuChannel;
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc;
    hseMacSrv_t* pMacSrv;

    u8MuChannel = HSE_MU_GetFreeChannel(u8MuInstance);
    if (HSE_INVALID_CHANNEL == u8MuChannel)
    {
        goto exit;
    }

    pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChannel];
    pMacSrv = &(pHseSrvDesc->hseSrv.macReq);


    pHseSrvDesc->srvId = HSE_SRV_ID_MAC;

    pMacSrv->accessMode = accessMode;
    pMacSrv->streamId = streamId;
    pMacSrv->macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    pMacSrv->macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    pMacSrv->authDir = HSE_AUTH_DIR_GENERATE;
    pMacSrv->keyHandle = keyHandle;
    pMacSrv->pInput = (HOST_ADDR) pMessage;
    pMacSrv->inputLength = messageLength;
    pMacSrv->pTag = (HOST_ADDR) tag;
    pMacSrv->pTagLength = (HOST_ADDR) &tagsize;
    pMacSrv->sgtOption = 0U;

    hseSrvResponse = HSE_Send(u8MuInstance, u8MuChannel, gSyncTxOption, pHseSrvDesc);
exit:
    return hseSrvResponse;
}

/*******************************************************************************
 *                                  XCBC_MAC
 ******************************************************************************/

hseSrvResponse_t AesXCbcmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                    const uint8_t *pMsg, uint32_t* pTagLength,
                                    uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacSignSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}

hseSrvResponse_t AesXCbcmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                  const uint8_t *pMsg, const uint32_t* pTagLength,
                                  const uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacVerSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                     msgLength, pMsg, pTagLength, pTag, 0U);
}

hseSrvResponse_t AesXCbcmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                               uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacSignSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesXCbcmacGenerateStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId,
                                                uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacSignSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesXCbcmacGenerateStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId,
                                                uint32_t msgLength, const uint8_t *pMsg,
                                                uint32_t* pTagLength, uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacSignSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}

hseSrvResponse_t AesXCbcmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                               uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacVerSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesXCbcmacVerifyStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId,
                                                uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacVerSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesXCbcmacVerifyStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId,
                                              uint32_t msgLength, const uint8_t *pMsg,
                                              const uint32_t* pTagLength, const uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_XCBC_MAC;
    return MacVerSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}


/*******************************************************************************
 *                                  FAST CMAC
 ******************************************************************************/
#ifdef HSE_SPT_FAST_CMAC

hseSrvResponse_t AesFastCmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                     const uint8_t *pMsg, uint8_t tagLength, uint8_t *pTag)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseFastCMACSrv_t *pFastCMacSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_FAST_CMAC;
    pFastCMacSrv       = &(pHseSrvDesc->hseSrv.fastCmacReq);

    pFastCMacSrv->authDir        = HSE_AUTH_DIR_GENERATE;
    pFastCMacSrv->keyHandle      = keyHandle;
    pFastCMacSrv->inputBitLength = msgLength;
    pFastCMacSrv->pInput         = (HOST_ADDR)pMsg;
    pFastCMacSrv->tagBitLength   = tagLength;
    pFastCMacSrv->pTag           = (HOST_ADDR)pTag;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

hseSrvResponse_t AesFastCmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                   const uint8_t *pMsg, uint8_t tagLength, const uint8_t *pTag)
{
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseFastCMACSrv_t *pFastCMacSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_FAST_CMAC;
    pFastCMacSrv       = &(pHseSrvDesc->hseSrv.fastCmacReq);

    pFastCMacSrv->authDir        = HSE_AUTH_DIR_VERIFY;
    pFastCMacSrv->keyHandle      = keyHandle;
    pFastCMacSrv->inputBitLength = msgLength;
    pFastCMacSrv->pInput         = (HOST_ADDR)pMsg;
    pFastCMacSrv->tagBitLength   = tagLength;
    pFastCMacSrv->pTag           = (HOST_ADDR)pTag;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

#endif

/*******************************************************************************
 *                                  CMAC
 ******************************************************************************/
hseSrvResponse_t AesCmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                 const uint8_t *pMsg, uint32_t* pTagLength,
                                 uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacSignSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t AesCmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                               const uint8_t *pMsg, const uint32_t* pTagLength,
                               const uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacVerSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                     msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t AesCmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                            uint32_t msgLength, const uint8_t* pMsg, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacSignSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, inputSgtType);
}

hseSrvResponse_t AesCmacGenerateStreamUpdate(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacSignSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, 0,
                      msgLength, pMsg, 0, 0, inputSgtType);
}

hseSrvResponse_t AesCmacGenerateStreamFinish(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg,
                                             uint32_t *pTagLength, uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacSignSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, 0,
                      msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t AesCmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                          uint32_t msgLength, const uint8_t* pMsg, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacVerSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, inputSgtType);
}

hseSrvResponse_t AesCmacVerifyStreamUpdate(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacVerSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, 0,
                      msgLength, pMsg, 0, 0, inputSgtType);
}

hseSrvResponse_t AesCmacVerifyStreamFinish(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg,
                                           const uint32_t *pTagLength, const uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
    macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
    return MacVerSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, 0,
                     msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

/*******************************************************************************
 *                                  GMAC
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesGmacGenerate(hseKeyHandle_t keyHandle, uint32_t ivLength,
                                 const uint8_t *pIV, uint32_t msgLength,
                                 const uint8_t *pMsg, uint32_t* pTagLength,
                                 uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    macScheme.sch.gmac.ivLength = ivLength;
    macScheme.sch.gmac.pIV = (HOST_ADDR)pIV;
    return MacSignSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                     msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t AesGmacVerify(hseKeyHandle_t keyHandle, uint32_t ivLength,
                               const uint8_t *pIV, uint32_t msgLength,
                               const uint8_t *pMsg, const uint32_t* pTagLength,
                               const uint8_t *pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    macScheme.sch.gmac.ivLength = ivLength;
    macScheme.sch.gmac.pIV = (HOST_ADDR)pIV;
    return MacVerSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, keyHandle,
                     msgLength, pMsg, pTagLength, pTag, inputSgtType);
}

/* Streaming for Gmac ? */
hseSrvResponse_t AesGmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                            uint32_t ivLength, const uint8_t* pIV,
                                            uint32_t msgLength, const uint8_t* pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    macScheme.sch.gmac.ivLength = ivLength;
    macScheme.sch.gmac.pIV = (HOST_ADDR)pIV;
    return MacSignSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesGmacGenerateStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId,
                                             uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    return MacSignSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesGmacGenerateStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId,
                                             uint32_t msgLength, const uint8_t *pMsg,
                                             uint32_t *pTagLength, uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    return MacSignSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}

hseSrvResponse_t AesGmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                          uint32_t ivLength, const uint8_t* pIV,
                                          uint32_t msgLength, const uint8_t* pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    macScheme.sch.gmac.ivLength = ivLength;
    macScheme.sch.gmac.pIV = (HOST_ADDR)pIV;
    return MacVerSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesGmacVerifyStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId,
                                           uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    return MacVerSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t AesGmacVerifyStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId,
                                           uint32_t msgLength, const uint8_t *pMsg,
                                           const uint32_t *pTagLength, const uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_GMAC;
    return MacVerSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, keyHandle,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}


/*******************************************************************************
 *                                  HMAC
 ******************************************************************************/
hseSrvResponse_t HmacGenerate(hseKeyHandle_t authKeyHandle, hseHashAlgo_t hashAlgo,
                              uint32_t inputLength, const uint8_t* pInput,
                              uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacSignSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, authKeyHandle,
                      inputLength, pInput, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t HmacVerify(hseKeyHandle_t authKeyHandle, hseHashAlgo_t hashAlgo,
                            uint32_t inputLength, const uint8_t* pInput,
                            const uint32_t* pTagLength, const uint8_t* pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacVerSrv(HSE_ACCESS_MODE_ONE_PASS, 0, macScheme, authKeyHandle,
                      inputLength, pInput, pTagLength, pTag, 0U);
}

hseSrvResponse_t HmacGenerateStartStream(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                         uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacSignSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t HmacGenerateUpdateStream(hseHashAlgo_t hashAlgo, uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacSignSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, 0,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t HmacGenerateFinishStream(hseHashAlgo_t hashAlgo, uint32_t streamId,
                                          uint32_t msgLength, const uint8_t *pMsg,
                                          uint32_t *pTagLength, uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacSignSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, 0,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}

hseSrvResponse_t HmacVerifyStartStream(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                       uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacVerSrv(HSE_ACCESS_MODE_START, streamId, macScheme, keyHandle,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t HmacVerifyUpdateStream(hseHashAlgo_t hashAlgo, uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacVerSrv(HSE_ACCESS_MODE_UPDATE, streamId, macScheme, 0,
                      msgLength, pMsg, 0, 0, 0U);
}

hseSrvResponse_t HmacVerifyFinishStream(hseHashAlgo_t hashAlgo, uint32_t streamId,
                                        uint32_t msgLength, const uint8_t *pMsg,
                                        const uint32_t *pTagLength, const uint8_t *pTag)
{
    hseMacScheme_t macScheme;
    macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
    macScheme.sch.hmac.hashAlgo = hashAlgo;
    return MacVerSrv(HSE_ACCESS_MODE_FINISH, streamId, macScheme, 0,
                      msgLength, pMsg, pTagLength, pTag, 0U);
}

/* ======================================================================================== */

#ifdef __cplusplus
}
#endif

/** @} */
