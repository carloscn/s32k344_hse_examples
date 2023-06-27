/**
*   @file    hse_host_aead.c
*
*   @brief   This file contains tests of AEAD services: CCM, GCM.
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

#include "hse_host_aead.h"

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
#if defined(HSE_SPT_AEAD)
static uint8_t          muIf = 0U;
static uint8_t          muChannelIdx = 1U;

/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 ==================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/
static hseSrvResponse_t AeadReq(
        hseAccessMode_t accessMode,
        uint32_t streamId,
        hseAuthCipherMode_t authCipherMode,
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t* pIV,
        uint32_t aadLength,
        const uint8_t* pAAD,
        uint32_t inputLength,
        const uint8_t* pInput,
        uint32_t tagLength,
        uint8_t* pTag,
        uint8_t* pOutput,
        hseSGTOption_t inputSgtType
        );

#ifdef AEAD_STREAM_SUPPORTED
static hseSrvResponse_t AeadStartReq(
        uint32_t streamId,
        hseAuthCipherMode_t authCipherMode,
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t* pIV,
        uint32_t aadLength,
        const uint8_t* pAAD);

static hseSrvResponse_t AeadUpdateReq(
        uint32_t streamId,
        hseAuthCipherMode_t authCipherMode,
        hseCipherDir_t cipherDir,
        uint32_t inputLength,
        const uint8_t* pInput,
        uint8_t* pOutput);

static hseSrvResponse_t AeadFinishReq(
        uint32_t streamId,
        hseAuthCipherMode_t authCipherMode,
        hseCipherDir_t cipherDir,
        uint32_t inputLength,
        const uint8_t* pInput,
        uint32_t tagLength,
        uint8_t* pTag,
        uint8_t* pOutput);
#endif
/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/

static hseSrvResponse_t AeadReq(
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseAuthCipherMode_t authCipherMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t ivLength,
    const uint8_t* pIV,
    uint32_t aadLength,
    const uint8_t* pAAD,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint32_t tagLength,
    uint8_t* pTag,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseAeadSrv_t* pAeadSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_AEAD;
    pAeadSrv = &(pHseSrvDesc->hseSrv.aeadReq);

    pAeadSrv->accessMode = accessMode;
    pAeadSrv->streamId = streamId;
    pAeadSrv->authCipherMode = authCipherMode;
    pAeadSrv->cipherDir = cipherDir;
    pAeadSrv->keyHandle = keyHandle;
    pAeadSrv->ivLength = ivLength;
    pAeadSrv->pIV = (HOST_ADDR)pIV;
    pAeadSrv->aadLength = aadLength;
    pAeadSrv->pAAD = (HOST_ADDR)pAAD;
    pAeadSrv->inputLength = inputLength;
    pAeadSrv->pInput = (HOST_ADDR)pInput;
    pAeadSrv->tagLength = tagLength;
    pAeadSrv->pTag = (HOST_ADDR)pTag;
    pAeadSrv->pOutput = (HOST_ADDR)pOutput;
    pAeadSrv->sgtOption = inputSgtType;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

#ifdef AEAD_STREAM_SUPPORTED
static hseSrvResponse_t AeadStartReq(
    uint32_t streamId,
    hseAuthCipherMode_t authCipherMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t ivLength,
    const uint8_t* pIV,
    uint32_t aadLength,
    const uint8_t* pAAD)
{
    return AeadReq(HSE_ACCESS_MODE_START, streamId, authCipherMode, cipherDir, keyHandle, ivLength, pIV, aadLength, pAAD, 0, NULL, 0, NULL, NULL, 0U);
}

static hseSrvResponse_t AeadUpdateReq(
    uint32_t streamId,
    hseAuthCipherMode_t authCipherMode,
    hseCipherDir_t cipherDir,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput)
{
    return AeadReq(HSE_ACCESS_MODE_UPDATE, streamId, authCipherMode, cipherDir, 0, 0, NULL, 0, NULL, inputLength, pInput, 0, NULL, pOutput, 0U);
}

static hseSrvResponse_t AeadFinishReq(
    uint32_t streamId,
    hseAuthCipherMode_t authCipherMode,
    hseCipherDir_t cipherDir,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint32_t tagLength,
    uint8_t* pTag,
    uint8_t* pOutput)
{
    return AeadReq(HSE_ACCESS_MODE_FINISH, streamId, authCipherMode, cipherDir, 0, 0, NULL, 0, NULL, inputLength, pInput, tagLength, pTag, pOutput, 0U);
}
#endif


/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/

/*******************************************************************************
 *                                            GCM
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesGcm(
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pInput,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pOutput)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_GCM,
            cipherDir, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pInput, tagLength, pTag, pOutput, 0U);
}

hseSrvResponse_t AesGcmEncrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
                               const uint8_t *pIV, uint32_t aadLength,
                               const uint8_t *pAad, uint32_t inputLength,
                               const uint8_t *pPlainText, uint32_t tagLength,
                               uint8_t *pTag, uint8_t *pCipherText, hseSGTOption_t inputSgtType)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_GCM,
            HSE_CIPHER_DIR_ENCRYPT, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pPlainText, tagLength, pTag, pCipherText, inputSgtType);
}

hseSrvResponse_t AesGcmDecrypt(
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pCipherText,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pPlainText,
        hseSGTOption_t inputSgtType)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_GCM,
            HSE_CIPHER_DIR_DECRYPT, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pCipherText, tagLength, pTag, pPlainText, inputSgtType);
}

#ifdef AEAD_STREAM_SUPPORTED
/* Streaming for Gcm */
hseSrvResponse_t AesGcmStream(
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t ivLength,
    const uint8_t *pIV,
    uint32_t aadLength,
    const uint8_t *pAad,
    uint32_t inputLength,
    const uint8_t *pInput,
    uint32_t tagLength,
    uint8_t *pTag,
    uint8_t *pOutput)
{
    return AeadReq(accessMode, streamId, HSE_AUTH_CIPHER_MODE_GCM,
                   cipherDir, keyHandle, ivLength, pIV, aadLength, pAad,
                   inputLength, pInput, tagLength, pTag, pOutput, 0U);
}

/* || */

hseSrvResponse_t AesGcmStartStreamEncrypt(
    uint32_t streamId,
    hseKeyHandle_t keyHandle,
    uint32_t ivLength,
    const uint8_t *pIV,
    uint32_t aadLength,
    const uint8_t *pAad)
{
    return AeadStartReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_ENCRYPT,
                        keyHandle, ivLength, pIV, aadLength, pAad);
}

hseSrvResponse_t AesGcmUpdateStreamEncrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput, uint8_t *pOutput)
{
    return AeadUpdateReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_ENCRYPT,
                         inputLength, pInput, pOutput);
}

hseSrvResponse_t AesGcmFinishStreamEncrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput,
        uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput)
{
    return AeadFinishReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_ENCRYPT,
                         inputLength, pInput, tagLength, pTag, pOutput);
}

/* || */

hseSrvResponse_t AesGcmStartStreamDecrypt(
    uint32_t streamId,
    hseKeyHandle_t keyHandle,
    uint32_t ivLength,
    const uint8_t *pIV,
    uint32_t aadLength,
    const uint8_t *pAad)
{
    return AeadStartReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_DECRYPT,
            keyHandle, ivLength, pIV, aadLength, pAad);
}

hseSrvResponse_t AesGcmUpdateStreamDecrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput, uint8_t *pOutput)
{
    return AeadUpdateReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_DECRYPT,
                         inputLength, pInput, pOutput);
}

hseSrvResponse_t AesGcmFinishStreamDecrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput,
        uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput)
{
    return AeadFinishReq(streamId, HSE_AUTH_CIPHER_MODE_GCM, HSE_CIPHER_DIR_DECRYPT,
                         inputLength, pInput, tagLength, pTag, pOutput);
}
#endif

/*******************************************************************************
*                                         CCM
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesCcm(
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pInput,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pOutput)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_CCM,
            cipherDir, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pInput, tagLength, pTag, pOutput, 0U);
}

hseSrvResponse_t AesCcmEncrypt(
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pPlainText,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pCipherText)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_CCM,
            HSE_CIPHER_DIR_ENCRYPT, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pPlainText, tagLength, pTag, pCipherText, 0U);
}

hseSrvResponse_t AesCcmDecrypt(
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pCipherText,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pPlainText)
{
    return AeadReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_AUTH_CIPHER_MODE_CCM,
            HSE_CIPHER_DIR_DECRYPT, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pCipherText, tagLength, pTag, pPlainText, 0U);
}

#ifdef AEAD_STREAM_SUPPORTED
/* Streaming for Ccm */
hseSrvResponse_t AesCcmStream(
        hseAccessMode_t accessMode,
        uint32_t streamId,
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad,
        uint32_t inputLength,
        const uint8_t *pInput,
        uint32_t tagLength,
        uint8_t *pTag,
        uint8_t *pOutput)
{
    return AeadReq(accessMode, streamId, HSE_AUTH_CIPHER_MODE_CCM,
            cipherDir, keyHandle, ivLength, pIV, aadLength, pAad,
            inputLength, pInput, tagLength, pTag, pOutput, 0U);
}

/* || */

hseSrvResponse_t AesCcmStreamStart(
        uint32_t streamId,
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        uint32_t ivLength,
        const uint8_t *pIV,
        uint32_t aadLength,
        const uint8_t *pAad)
{
    return AeadStartReq(streamId, HSE_AUTH_CIPHER_MODE_CCM, cipherDir,
            keyHandle, ivLength, pIV, aadLength, pAad);
}

hseSrvResponse_t AesCcmStreamUpdate(uint32_t streamId, hseCipherDir_t cipherDir, uint32_t inputLength,
        uint8_t *pInput, uint8_t *pOutput)
{
    return AeadUpdateReq(streamId, HSE_AUTH_CIPHER_MODE_CCM,
            cipherDir, inputLength, pInput, pOutput);
}

hseSrvResponse_t AesCcmStreamFinish(uint32_t streamId, hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput,
        uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput)
{
    return AeadFinishReq(streamId, HSE_AUTH_CIPHER_MODE_CCM, cipherDir,
            inputLength, pInput, tagLength, pTag, pOutput);
}
#endif
#endif
#ifdef __cplusplus
}
#endif

/** @} */

