
#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "string.h"
#include "hse_host.h"

#include "hse_host_cipher.h"


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
static hseSrvResponse_t SymCipherReq(
    hseAccessMode_t accessMode,
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    const uint8_t* pIV,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType);

static hseSrvResponse_t SymCipherStartReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    const uint8_t* pIV,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType);

static hseSrvResponse_t SymCipherUpdateReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType);

static hseSrvResponse_t SymCipherFinishReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

static hseSrvResponse_t SymCipherReq(
    hseAccessMode_t accessMode,
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    const uint8_t* pIV,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseSymCipherSrv_t* pSymCipherReq;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId              = HSE_SRV_ID_SYM_CIPHER;
    pSymCipherReq                   = &pHseSrvDesc->hseSrv.symCipherReq;

    pSymCipherReq->accessMode       = accessMode;
    pSymCipherReq->cipherAlgo       = cipherAlgo;
    pSymCipherReq->cipherBlockMode  = cipherBlockMode;
    pSymCipherReq->cipherDir        = cipherDir;
    pSymCipherReq->keyHandle        = keyHandle;

    pSymCipherReq->pIV              = (HOST_ADDR)pIV;
    pSymCipherReq->inputLength      = inputLength;
    pSymCipherReq->pInput           = (HOST_ADDR)pInput;
    pSymCipherReq->pOutput          = (HOST_ADDR)pOutput;
    pSymCipherReq->sgtOption        = inputSgtType;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

static hseSrvResponse_t SymCipherMuReq(
    hseAccessMode_t accessMode,
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    const uint8_t* pIV,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType,
    uint8_t mu)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[mu][muChannelIdx];
    hseSymCipherSrv_t* pSymCipherReq;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId              = HSE_SRV_ID_SYM_CIPHER;
    pSymCipherReq                   = &pHseSrvDesc->hseSrv.symCipherReq;

    pSymCipherReq->accessMode       = accessMode;
    pSymCipherReq->cipherAlgo       = cipherAlgo;
    pSymCipherReq->cipherBlockMode  = cipherBlockMode;
    pSymCipherReq->cipherDir        = cipherDir;
    pSymCipherReq->keyHandle        = keyHandle;

    pSymCipherReq->pIV              = (HOST_ADDR)pIV;
    pSymCipherReq->inputLength      = inputLength;
    pSymCipherReq->pInput           = (HOST_ADDR)pInput;
    pSymCipherReq->pOutput          = (HOST_ADDR)pOutput;
    pSymCipherReq->sgtOption        = inputSgtType;

    return HSE_Send(mu, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

static hseSrvResponse_t SymCipherStartReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    const uint8_t *pIV,
    uint32_t inputLength,
    const uint8_t *pInput,
    uint8_t *pOutput,
    hseSGTOption_t inputSgtType)
{
    return SymCipherReq(HSE_ACCESS_MODE_START, cipherAlgo,
                        cipherBlockMode, cipherDir, keyHandle,
                        pIV, inputLength, pInput, pOutput, inputSgtType);
}

static hseSrvResponse_t SymCipherUpdateReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType)
{
    return SymCipherReq(HSE_ACCESS_MODE_UPDATE, cipherAlgo,
                        cipherBlockMode, cipherDir, keyHandle,
                        0, inputLength, pInput, pOutput, inputSgtType);
}

static hseSrvResponse_t SymCipherFinishReq(
    hseCipherAlgo_t cipherAlgo,
    hseCipherBlockMode_t cipherBlockMode,
    hseCipherDir_t cipherDir,
    hseKeyHandle_t keyHandle,
    uint32_t inputLength,
    const uint8_t* pInput,
    uint8_t* pOutput,
    hseSGTOption_t inputSgtType)
{
    return SymCipherReq(HSE_ACCESS_MODE_FINISH, cipherAlgo,
                        cipherBlockMode, cipherDir, keyHandle,
                        0, inputLength, pInput, pOutput, inputSgtType);
}

/* TODO: AES XTS */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/* ==== AES ====*/
hseSrvResponse_t AesCrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                            hseCipherDir_t cipherDir, const uint8_t *pIV, uint32_t inputLength,
                            const uint8_t* pInput, uint8_t* pOutput)
{
    return SymCipherReq(HSE_ACCESS_MODE_ONE_PASS, HSE_CIPHER_ALGO_AES,
                        cipherBlockMode, cipherDir,
                        keyHandle, pIV, inputLength, pInput, pOutput, 0U);
}
hseSrvResponse_t AesCryptMu(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                            hseCipherDir_t cipherDir, const uint8_t *pIV, uint32_t inputLength,
                            const uint8_t* pInput, uint8_t* pOutput, uint8_t mu)
{
    return SymCipherMuReq(HSE_ACCESS_MODE_ONE_PASS, HSE_CIPHER_ALGO_AES,
                          cipherBlockMode, cipherDir,
                          keyHandle,pIV, inputLength, pInput, pOutput, 0U, mu);
}
hseSrvResponse_t AesEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode, 
                            const uint8_t *pIV, uint32_t inputLength, const uint8_t* pInput, 
                            uint8_t* pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherReq(HSE_ACCESS_MODE_ONE_PASS, HSE_CIPHER_ALGO_AES,
                        cipherBlockMode, HSE_CIPHER_DIR_ENCRYPT,
                        keyHandle, pIV, inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode, 
                            const uint8_t *pIV, uint32_t inputLength, const uint8_t* pInput, 
                            uint8_t* pOutput,  hseSGTOption_t inputSgtType)
{
    return SymCipherReq(HSE_ACCESS_MODE_ONE_PASS, HSE_CIPHER_ALGO_AES,
                        cipherBlockMode, HSE_CIPHER_DIR_DECRYPT,
                        keyHandle, pIV, inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesStartStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                       const uint8_t *pIV, uint32_t inputLength, const uint8_t* pInput,
                                       uint8_t* pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherStartReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_ENCRYPT, keyHandle,
                             pIV, inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesUpdateStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                      uint32_t inputLength, const uint8_t *pInput,
                                      uint8_t *pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherUpdateReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_ENCRYPT, keyHandle,
                             inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesFinishStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput, uint8_t *pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherFinishReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_ENCRYPT, keyHandle,
                             inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesStartStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                       const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                                       uint8_t *pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherStartReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_DECRYPT, keyHandle,
                             pIV, inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesUpdateStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                      uint32_t inputLength, const uint8_t *pInput,
                                      uint8_t *pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherUpdateReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_DECRYPT, keyHandle,
                             inputLength, pInput, pOutput, inputSgtType);
}

hseSrvResponse_t AesFinishStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput, uint8_t *pOutput, hseSGTOption_t inputSgtType)
{
    return SymCipherFinishReq(HSE_CIPHER_ALGO_AES, cipherBlockMode, HSE_CIPHER_DIR_DECRYPT, keyHandle,
                             inputLength, pInput, pOutput, inputSgtType);
}

#ifdef HSE_SPT_XTS_AES
hseSrvResponse_t AesXtsEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                               const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                               uint8_t *pOutput)
{
    hseSrvResponse_t hseResponse;
    (void)keyHandle;
    (void)cipherBlockMode;
    (void)pIV;
    (void)inputLength;
    (void)pInput;
    (void)pOutput;

    memset(&gHseSrvDesc[muIf][muChannelIdx], 0, sizeof(hseSrvDescriptor_t));
    gHseSrvDesc[muIf][muChannelIdx].srvId = HSE_SRV_ID_XTS_AES_CIPHER;
    hseResponse = HSE_Send(muIf, muChannelIdx, gSyncTxOption, &gHseSrvDesc[muIf][muChannelIdx]);

    return hseResponse;
}

hseSrvResponse_t AesXtsDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode, 
                             const uint8_t *pIV, uint32_t inputLength, const uint8_t* pInput, 
                            uint8_t* pOutput)
{
    hseSrvResponse_t hseResponse;
    (void)keyHandle;
    (void)cipherBlockMode;
    (void)pIV;
    (void)inputLength;
    (void)pInput;
    (void)pOutput;

    memset(&gHseSrvDesc[muIf][muChannelIdx], 0, sizeof(hseSrvDescriptor_t));
    gHseSrvDesc[muIf][muChannelIdx].srvId = HSE_SRV_ID_XTS_AES_CIPHER;
    hseResponse = HSE_Send(muIf, muChannelIdx, gSyncTxOption, &gHseSrvDesc[muIf][muChannelIdx]);

    return hseResponse;
}
#endif /* HSE_SPT_XTS_AES*/

#ifdef __cplusplus
}
#endif

