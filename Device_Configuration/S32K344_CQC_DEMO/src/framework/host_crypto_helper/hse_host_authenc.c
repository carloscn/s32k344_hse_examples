/**
 *   @file    hse_host_authenc.c
 *
 *   @brief   Function definitions to test the AuthEnc dual services
 *   @details This file will verify AES/null cipher-CMAC/GMAC/XCBC-MAC/HMAC functionality.
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

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/
#include"hse_platform.h"
#ifdef HSE_SPT_AUTHENC

#include "hse_host.h"
#include "string.h"
#include "hse_host_hash.h"
#include "hse_host_mac.h"
#include "hse_host_import_key.h"
#include "hse_common_test.h"
#include "hse_host_authenc.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/

#define HMAC_ALGORITHM_COUNT     (8)

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL VARIABLES
 ==================================================================================================*/
static uint8_t        muIf = 2U;
static uint8_t        muChannelIdx = 14U;

#if 0
static const uint32_t hashAlgoChunkSize[HMAC_ALGORITHM_COUNT + 1] =
{
        // NULL HASH
        0,
        //MD5
        64,
        //SHA1
        64,
        //SHA224
        64,
        //SHA256
        64,
        //SHA384
        128,
        //SHA512
        128,
        //SHA512_224
        128,
        //SHA512_256
        128
};
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
static hseSrvResponse_t AuthEncReq(hseAccessMode_t accessMode, hseStreamId_t streamId,
                                   hseCipherAlgo_t cipherAlgo, hseCipherBlockMode_t cipherBlockMode,
                                   hseCipherDir_t cipherDir, hseMacAlgo_t macAlgo, hseHashAlgo_t hashAlgo,
                                   hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                   uint32_t inputLength, const uint8_t* pInput,
                                   uint32_t aadLength, const uint8_t* pAAD,
                                   uint32_t ivLength, const uint8_t* pIV,
                                   uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType);

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/
static hseSrvResponse_t AuthEncReq(hseAccessMode_t accessMode, hseStreamId_t streamId,
                                   hseCipherAlgo_t cipherAlgo, hseCipherBlockMode_t cipherBlockMode,
                                   hseCipherDir_t cipherDir, hseMacAlgo_t macAlgo, hseHashAlgo_t hashAlgo,
                                   hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                   uint32_t inputLength, const uint8_t* pInput,
                                   uint32_t aadLength, const uint8_t* pAAD,
                                   uint32_t ivLength, const uint8_t* pIV,
                                   uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType)
{
    hseSrvResponse_t hseResponse = HSE_SRV_RSP_GENERAL_ERROR;

    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseAuthEncSrv_t* pAuthEncSrv;

    (void)accessMode;
    (void)streamId;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_AUTHENC;
    pAuthEncSrv = &(pHseSrvDesc->hseSrv.authEncReq);

    pAuthEncSrv->cipherAlgo = cipherAlgo;
    pAuthEncSrv->cipherBlockMode = cipherBlockMode;
    switch(macAlgo)
    {
         case HSE_MAC_ALGO_CMAC:
               pAuthEncSrv->macScheme.macAlgo = macAlgo;
               pAuthEncSrv->macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
               break;
         case HSE_MAC_ALGO_GMAC:
               pAuthEncSrv->macScheme.macAlgo = macAlgo;
         case HSE_MAC_ALGO_XCBC_MAC:
               pAuthEncSrv->macScheme.macAlgo = macAlgo;
               break;

         case HSE_MAC_ALGO_HMAC:
               pAuthEncSrv->macScheme.macAlgo = macAlgo;
               pAuthEncSrv->macScheme.sch.hmac.hashAlgo = hashAlgo;
               break;
    }
    pAuthEncSrv->cipherDir = cipherDir;
    pAuthEncSrv->cipherKeyHandle = cipherKeyHandle;
    pAuthEncSrv->authKeyHandle = authKeyHandle;
    pAuthEncSrv->inputLength = inputLength;
    pAuthEncSrv->pInput = (HOST_ADDR)pInput;
    pAuthEncSrv->ivLength = ivLength;
    pAuthEncSrv->pIV = (HOST_ADDR)pIV;
    pAuthEncSrv->aadLength = aadLength;
    pAuthEncSrv->pAAD = (HOST_ADDR)pAAD;
    pAuthEncSrv->pOutput = (HOST_ADDR)pOutput;
    pAuthEncSrv->pTagLength = (HOST_ADDR)pTagLength;
    pAuthEncSrv->pTag = (HOST_ADDR)pTag;
    pAuthEncSrv->sgtOption = inputSgtType;
    hseResponse = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);

    return hseResponse;
}
/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/
hseSrvResponse_t AuthEncSignAesEnc(hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                   hseCipherBlockMode_t block, hseMacAlgo_t macAlgo,
                                   hseHashAlgo_t hashAlgo,
                                   uint32_t inputLength,const uint8_t* pInput,
                                   uint32_t aadLength, const uint8_t* pAAD,
                                   uint32_t ivLength, const uint8_t* pIV, uint8_t* pOutput,
                                   uint32_t* pTagLength, uint8_t* pTag)
{

        return AuthEncReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_CIPHER_ALGO_AES, block, HSE_CIPHER_DIR_ENCRYPT, macAlgo, hashAlgo,
                          cipherKeyHandle, authKeyHandle, inputLength, pInput, aadLength, pAAD, ivLength, pIV, pOutput, pTagLength, pTag, 0U);
}

hseSrvResponse_t AuthEncVerAesDec(hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                  hseCipherBlockMode_t block, hseMacAlgo_t macAlgo,
                                  hseHashAlgo_t hashAlgo,
                                  uint32_t inputLength, const uint8_t* pInput,
                                  uint32_t aadLength, const uint8_t* pAAD,
                                  uint32_t ivLength, const uint8_t* pIV, uint8_t* pOutput,
                                  uint32_t* pTagLength, uint8_t* pTag)
{
        return AuthEncReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_CIPHER_ALGO_AES, block, HSE_CIPHER_DIR_DECRYPT, macAlgo, hashAlgo,
                          cipherKeyHandle, authKeyHandle, inputLength, pInput, aadLength, pAAD, ivLength, pIV, pOutput, pTagLength, pTag, 0U);
}

hseSrvResponse_t AuthEncSign(hseKeyHandle_t authKeyHandle, hseMacAlgo_t macAlgo,
                             hseHashAlgo_t hashAlgo,
                             uint32_t inputLength, const uint8_t* pInput,
                             uint32_t aadLength, const uint8_t* pAAD,
                             uint32_t ivLength, const uint8_t* pIV,
                             uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType)
{

        return AuthEncReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_CIPHER_ALGO_NULL, HSE_CIPHER_BLOCK_MODE_NULL, HSE_CIPHER_DIR_ENCRYPT,
                          macAlgo, hashAlgo, 0, authKeyHandle, inputLength, pInput, aadLength, pAAD, ivLength, pIV, pOutput, pTagLength, pTag, inputSgtType);
}

hseSrvResponse_t AuthEncVerify(hseKeyHandle_t authKeyHandle, hseMacAlgo_t macAlgo,
                               hseHashAlgo_t hashAlgo,
                               uint32_t inputLength, const uint8_t* pInput,
                               uint32_t aadLength, const uint8_t* pAAD,
                               uint32_t ivLength, const uint8_t* pIV,
                               uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType)
{
        return AuthEncReq(HSE_ACCESS_MODE_ONE_PASS, 0, HSE_CIPHER_ALGO_NULL, HSE_CIPHER_BLOCK_MODE_NULL, HSE_CIPHER_DIR_DECRYPT,
                          macAlgo, hashAlgo, 0, authKeyHandle, inputLength, pInput, aadLength, pAAD, ivLength, pIV, pOutput, pTagLength, pTag, inputSgtType);
}

#else
void AuthEnc_NotSupported(void)
{
        ; /* Avoid warning */
}
#endif /* HSE_SPT_AUTHENC */

#ifdef __cplusplus
}
#endif
