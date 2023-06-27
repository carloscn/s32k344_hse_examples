
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/

#include "hse_host.h"
#include "string.h"

#include "hse_host_sign.h"
#include "hse_keys_allocator.h"
#include "hse_srv_sign.h"
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
#ifdef HSE_SPT_SIGN

static uint8_t localMuIf = 0U;
static uint8_t localMuChannelIdx = 1U;
/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 ==================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/
static hseSrvResponse_t SignReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                                hseKeyHandle_t keyHandle, const uint8_t muIf,
                                const uint8_t muChannelIdx, uint32_t inputLength,
                                const uint8_t* pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                uint32_t* pSignatureLength0, uint8_t* pSignature0,
                                uint32_t* pSignatureLength1, uint8_t* pSignature1,
                                hseTxOptions_t txOptions);

static hseSrvResponse_t VerReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                               hseKeyHandle_t keyHandle, const uint8_t muIf,
                               const uint8_t muChannelIdx, uint32_t inputLength,
                               const uint8_t* pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                               const uint32_t* pSignatureLength0, const uint8_t* pSignature0,
                               const uint32_t* pSignatureLength1, const uint8_t* pSignature1,
                               hseTxOptions_t txOptions);

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/

static hseSrvResponse_t SignReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                                hseKeyHandle_t keyHandle, const uint8_t muIf,
                                const uint8_t muChannelIdx, uint32_t inputLength,
                                const uint8_t* pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                uint32_t* pSignatureLength0, uint8_t* pSignature0,
                                uint32_t* pSignatureLength1, uint8_t* pSignature1,
                                hseTxOptions_t txOptions)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseSignSrv_t* pSignSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_SIGN;
    pSignSrv = &(pHseSrvDesc->hseSrv.signReq);

    pSignSrv->accessMode          = accessMode;
    pSignSrv->signScheme          = signScheme;
    pSignSrv->authDir             = HSE_AUTH_DIR_GENERATE;
    pSignSrv->keyHandle           = keyHandle;
    pSignSrv->inputLength         = inputLength;
    pSignSrv->pInput              = (HOST_ADDR)pInput;
    pSignSrv->bInputIsHashed      = bInputIsHashed;
    pSignSrv->sgtOption           = sgtOption;
    pSignSrv->pSignature[0]       = (HOST_ADDR)pSignature0;
    pSignSrv->pSignatureLength[0] = (HOST_ADDR)pSignatureLength0;
    pSignSrv->pSignatureLength[1] = (HOST_ADDR)pSignatureLength1;
    pSignSrv->pSignature[1]       = (HOST_ADDR)pSignature1;

    return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
}

static hseSrvResponse_t VerReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                               hseKeyHandle_t keyHandle, const uint8_t muIf,
                               const uint8_t muChannelIdx, uint32_t inputLength,
                               const uint8_t* pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                               const uint32_t* pSignatureLength0, const uint8_t* pSignature0,
                               const uint32_t* pSignatureLength1, const uint8_t* pSignature1,
                               hseTxOptions_t txOptions)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseSignSrv_t* pSignSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_SIGN;
    pSignSrv = &(pHseSrvDesc->hseSrv.signReq);

    pSignSrv->accessMode          = accessMode;
    pSignSrv->signScheme          = signScheme;
    pSignSrv->authDir             = HSE_AUTH_DIR_VERIFY;
    pSignSrv->keyHandle           = keyHandle;
    pSignSrv->inputLength         = inputLength;
    pSignSrv->pInput              = (HOST_ADDR)pInput;
    pSignSrv->bInputIsHashed      = bInputIsHashed;
    pSignSrv->sgtOption           = sgtOption;
    pSignSrv->pSignature[0]       = (HOST_ADDR)pSignature0;
    pSignSrv->pSignatureLength[0] = (HOST_ADDR)pSignatureLength0;
    pSignSrv->pSignatureLength[1] = (HOST_ADDR)pSignatureLength1;
    pSignSrv->pSignature[1]       = (HOST_ADDR)pSignature1;

    return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/

 /*************************************************************************************************
  *                                     Global Sign Services
  ************************************************************************************************/

hseSrvResponse_t SignSrvReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                            hseKeyHandle_t keyHandle, uint32_t inputLength,
                            const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                            uint32_t *pSignatureLength0, uint8_t *pSignature0,
                            uint32_t *pSignatureLength1, uint8_t *pSignature1)
{
    return SignReq(accessMode,signScheme, keyHandle,
                   localMuIf, localMuChannelIdx,
                   inputLength, pInput, bInputIsHashed, sgtOption,
                   pSignatureLength0, pSignature0,
                   pSignatureLength1, pSignature1, gSyncTxOption);
}

hseSrvResponse_t VerSrvReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                           hseKeyHandle_t keyHandle, uint32_t inputLength,
                           const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                           const uint32_t* pSignatureLength0, const uint8_t *pSignature0,
                           const uint32_t* pSignatureLength1, const uint8_t *pSignature1)
{
    return VerReq(accessMode,signScheme, keyHandle,
                  localMuIf, localMuChannelIdx,
                  inputLength, pInput, bInputIsHashed, sgtOption,
                  pSignatureLength0, pSignature0,
                  pSignatureLength1, pSignature1, gSyncTxOption);
}

/********************************************************************************
 *                           ECDSA(generate/verify)
 *******************************************************************************/
hseSrvResponse_t EcdsaSign(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                              uint32_t inputLength, const uint8_t* pInput,
                              bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                              uint32_t* pRLen, uint8_t* pR,
                              uint32_t* pSLen, uint8_t* pS)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_ECDSA;
    signScheme.sch.ecdsa.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_ONE_PASS, signScheme,
                   keyHandle, localMuIf, localMuChannelIdx,
                   inputLength, pInput, bInputIsHashed, sgtOption,
                   pRLen, pR,
                   pSLen, pS, gSyncTxOption);
}

hseSrvResponse_t EcdsaVerify(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                             uint32_t inputLength, const uint8_t* pInput,
                             bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                             const uint32_t* pRLen, const uint8_t* pR,
                             const uint32_t* pSLen, const uint8_t* pS)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_ECDSA;
    signScheme.sch.ecdsa.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_ONE_PASS, signScheme,
                  keyHandle, localMuIf, localMuChannelIdx,
                  inputLength, pInput, bInputIsHashed, sgtOption,
                  pRLen, pR,
                  pSLen, pS, gSyncTxOption);
}

/******************************************************************************
 *                              EdDSA(generate/verify)
 *****************************************************************************/
hseSrvResponse_t EddsaSign(hseKeyHandle_t keyHandle, bool_t bHashEddsa,
                              uint32_t inputLength, const uint8_t* pInput, bool_t bInputIsHashed,
                              uint8_t userContextLength, const uint8_t* pUserContext,
                              uint32_t* pRLen, uint8_t* pR,
                              uint32_t* pSLen, uint8_t* pS)
{
    hseSignScheme_t signScheme;

    signScheme.signSch                 = HSE_SIGN_EDDSA;
    signScheme.sch.eddsa.bHashEddsa    = bHashEddsa;
    signScheme.sch.eddsa.contextLength = userContextLength;
    signScheme.sch.eddsa.pContext      = (HOST_ADDR)pUserContext;

    return SignReq(HSE_ACCESS_MODE_ONE_PASS, signScheme,
                   keyHandle, localMuIf, localMuChannelIdx,
                   inputLength, pInput, bInputIsHashed, 0,
                   pRLen, pR,
                   pSLen, pS, gSyncTxOption);
}

hseSrvResponse_t EddsaVerify(hseKeyHandle_t keyHandle, bool_t bHashEddsa,
                             uint32_t inputLength, const uint8_t* pInput, bool_t bInputIsHashed,
                             uint8_t userContextLength, const uint8_t* pUserContext,
                             const uint32_t* pRLen, const uint8_t* pR,
                             const uint32_t* pSLen, const uint8_t* pS)
{
    hseSignScheme_t signScheme;

    signScheme.signSch                 = HSE_SIGN_EDDSA;
    signScheme.sch.eddsa.bHashEddsa    = bHashEddsa;
    signScheme.sch.eddsa.contextLength = userContextLength;
    signScheme.sch.eddsa.pContext      = (HOST_ADDR)pUserContext;

    return VerReq(HSE_ACCESS_MODE_ONE_PASS, signScheme,
                  keyHandle, localMuIf, localMuChannelIdx,
                  inputLength, pInput, bInputIsHashed, 0,
                  pRLen, pR,
                  pSLen, pS, gSyncTxOption);
}

/**********************************************************************************
 *                         RSA SA PSS(generate/verify)
 *********************************************************************************/
hseSrvResponse_t RsaPssSignSrv(hseKeyHandle_t keyHandle, uint32_t saltLength,
                               hseHashAlgo_t hashAlgo, uint32_t inputLength,
                               const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                               uint32_t *pSignatureLength, uint8_t *pSignature)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PSS;
    signScheme.sch.rsaPss.saltLength = saltLength;
    signScheme.sch.rsaPss.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                   localMuIf, localMuChannelIdx, inputLength, pInput, bInputIsHashed, sgtOption,
                   pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssVerSrv(hseKeyHandle_t keyHandle, uint32_t saltLength,
                              hseHashAlgo_t hashAlgo, uint32_t inputLength,
                              const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                              const uint32_t* pSignatureLength, const uint8_t *pSignature)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PSS;
    signScheme.sch.rsaPss.saltLength = saltLength;
    signScheme.sch.rsaPss.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                  localMuIf, localMuChannelIdx, inputLength, pInput, bInputIsHashed, sgtOption,
                  pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssSignStreamStartSrv(hseKeyHandle_t keyHandle,
                                          hseHashAlgo_t hashAlgo,
                                          uint32_t saltLength)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PSS;
    signScheme.sch.rsaPss.saltLength = saltLength;
    signScheme.sch.rsaPss.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_START, signScheme, keyHandle,
                   localMuIf, localMuChannelIdx, 0, NULL, FALSE, 0,
                   0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssSignStreamUpdateSrv(uint32_t inputLength, const uint8_t *pInput)
{
    hseSignScheme_t signScheme = {0};
    return SignReq(HSE_ACCESS_MODE_UPDATE, signScheme, 0,
                   localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                   0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssSignStreamFinishSrv(uint32_t inputLength,
                                           const uint8_t *pInput,
                                           uint32_t *pSignatureLength,
                                           uint8_t *pSignature)
{
    hseSignScheme_t signScheme = {0};
    return SignReq(HSE_ACCESS_MODE_FINISH, signScheme, 0,
                   localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                   pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssVerStreamStartSrv(hseKeyHandle_t keyHandle,
                                         hseHashAlgo_t hashAlgo,
                                         uint32_t saltLength)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PSS;
    signScheme.sch.rsaPss.saltLength = saltLength;
    signScheme.sch.rsaPss.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_START, signScheme, keyHandle,
                  localMuIf, localMuChannelIdx, 0, NULL, FALSE, 0,
                  0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssVerStreamUpdateSrv(uint32_t inputLength, const uint8_t *pInput)
{
    hseSignScheme_t signScheme = {0};
    return VerReq(HSE_ACCESS_MODE_UPDATE, signScheme, 0,
                  localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                  0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPssVerStreamFinishSrv(uint32_t inputLength,
                                          const uint8_t *pInput,
                                          const uint32_t* pSignatureLength,
                                          const uint8_t *pSignature)
{
    hseSignScheme_t signScheme = {0};
    return VerReq(HSE_ACCESS_MODE_FINISH, signScheme, 0,
                   localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                   pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

/******************************************************************************************
 *                              RSA SA PKCS1 V15(generate/verify)
 *****************************************************************************************/
hseSrvResponse_t RsaPkcs1v15SignSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t inputLength, uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                    uint32_t *pSignatureLength, uint8_t *pSignature)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                   localMuIf, localMuChannelIdx, inputLength, pInput, bInputIsHashed, sgtOption,
                   pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15SignAsyncSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                         const uint8_t muIf, const uint8_t muChannelIdx,
                                         uint32_t inputLength, uint8_t *pInput,
                                         uint32_t *pSignatureLength, uint8_t *pSignature,
                                         hseTxOptions_t asyncTxOptions)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                   muIf, muChannelIdx, inputLength, pInput, FALSE, 0, pSignatureLength, pSignature, 0, NULL, asyncTxOptions);
}

hseSrvResponse_t RsaPkcs1v15VerSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                   uint32_t inputLength, const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                   const uint32_t* pSignatureLength, const uint8_t *pSignature)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                  localMuIf, localMuChannelIdx, inputLength, pInput, bInputIsHashed, sgtOption,
                  pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15VerAsyncSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                        const uint8_t muIf, const uint8_t muChannelIdx,
                                        uint32_t inputLength, const uint8_t *pInput,
                                        const uint32_t* pSignatureLength, const uint8_t *pSignature,
                                        hseTxOptions_t asyncTxOptions)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_ONE_PASS, signScheme, keyHandle,
                  muIf, muChannelIdx, inputLength, pInput, FALSE, 0, pSignatureLength, pSignature, 0, NULL, asyncTxOptions);
}

hseSrvResponse_t RsaPkcs1v15SignStreamStart(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return SignReq(HSE_ACCESS_MODE_START, signScheme, keyHandle,
                   localMuIf, localMuChannelIdx, 0, NULL, FALSE, 0,
                   0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15SignStreamUpdate(uint32_t inputLength, const uint8_t *pInput)
{
    hseSignScheme_t signScheme = {0};
    return SignReq(HSE_ACCESS_MODE_UPDATE, signScheme, 0,
                   localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                   0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15SignStreamFinish(uint32_t inputLength, const uint8_t *pInput,
                                             uint32_t *pSignatureLength, uint8_t *pSignature)
{
    hseSignScheme_t signScheme = {0};
    return SignReq(HSE_ACCESS_MODE_FINISH, signScheme, 0,
                   localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                   pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15VerSha1StreamStart(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo)
{
    hseSignScheme_t signScheme;
    signScheme.signSch = HSE_SIGN_RSASSA_PKCS1_V15;
    signScheme.sch.rsaPkcs1v15.hashAlgo = hashAlgo;
    return VerReq(HSE_ACCESS_MODE_START, signScheme, keyHandle,
                  localMuIf, localMuChannelIdx, 0, NULL, FALSE, 0,
                  0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15VerSha1StreamUpdate(uint32_t inputLength, const uint8_t *pInput)
{
    hseSignScheme_t signScheme = {0};
    return VerReq(HSE_ACCESS_MODE_UPDATE, signScheme, 0,
                  localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                  0, NULL, 0, NULL, gSyncTxOption);
}

hseSrvResponse_t RsaPkcs1v15VerSha1StreamFinish(uint32_t inputLength, const uint8_t *pInput,
                                                uint32_t *pSignatureLength, const uint8_t *pSignature)
{
    hseSignScheme_t signScheme = {0};
    return VerReq(HSE_ACCESS_MODE_FINISH, signScheme, 0,
                  localMuIf, localMuChannelIdx, inputLength, pInput, FALSE, 0,
                  pSignatureLength, pSignature, 0, NULL, gSyncTxOption);
}

#endif /*HSE_SPT_SIGN*/

/*****************************************************************************
 *                                     DH
 ****************************************************************************/

hseSrvResponse_t DHSharedSecretCompute(hseKeyHandle_t pubKeyHandle, hseKeyHandle_t privKeyHandle,
                                       hseKeyHandle_t *pTargetKeyHandle, uint8_t isNvmKey, uint16_t maxBitLength)
{
#ifdef HSE_SPT_COMPUTE_DH
    hseSrvResponse_t hseResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseDHComputeSharedSecretSrv_t *pDhSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    hseResponse = HKF_AllocKeySlot(isNvmKey, HSE_KEY_TYPE_SHARED_SECRET, maxBitLength, pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    pHseSrvDesc->srvId = HSE_SRV_ID_DH_COMPUTE_SHARED_SECRET;
    pDhSrv = &(pHseSrvDesc->hseSrv.dhComputeSecretReq);
    pDhSrv->privKeyHandle    = privKeyHandle;
    pDhSrv->peerPubKeyHandle = pubKeyHandle;
    pDhSrv->targetKeyHandle  = *pTargetKeyHandle;

    hseResponse = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
    }
exit:
    return hseResponse;
#else
    (void)pubKeyHandle;
    (void)privKeyHandle;
    (void)pTargetKeyHandle;
    (void)isNvmKey;
    (void)maxBitLength;
    return HSE_SRV_RSP_NOT_SUPPORTED;
#endif
}


/*****************************************************************************
 *                                     Burmester-Desmedt
 ****************************************************************************/
#ifdef HSE_SPT_BURMESTER_DESMEDT
hseSrvResponse_t BDComputeSecondPubKey(hseKeyHandle_t deviceKeyHandle, hseKeyHandle_t pubKeyHandle)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseBurmesterDesmedtSrv_t *pBdReq;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_BURMESTER_DESMEDT;
    pBdReq = &(pHseSrvDesc->hseSrv.burmesterDesmedtReq);

    pBdReq->bdStep                = HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY;
    pBdReq->deviceKeyHandle       = deviceKeyHandle;
    pBdReq->pubKeyHandle          = pubKeyHandle;

    return HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
}

hseSrvResponse_t BDComputeSharedSecret(hseKeyHandle_t deviceKeyHandle, hseKeyHandle_t pubKeyHandle,
                                       uint8_t numParticipants, hseKeyHandle_t *pSharedSecretKeyHandle, uint8_t isNvmKey, uint16_t sharedSecretLength)
{
    hseSrvResponse_t hseResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseBurmesterDesmedtSrv_t *pBdReq;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    hseResponse = HKF_AllocKeySlot(isNvmKey, HSE_KEY_TYPE_SHARED_SECRET, sharedSecretLength, pSharedSecretKeyHandle);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    pHseSrvDesc->srvId = HSE_SRV_ID_BURMESTER_DESMEDT;
    pBdReq = &(pHseSrvDesc->hseSrv.burmesterDesmedtReq);

    pBdReq->bdStep                = HSE_BD_STEP_COMPUTE_SHARED_SECRET;
    pBdReq->deviceKeyHandle       = deviceKeyHandle;
    pBdReq->pubKeyHandle          = pubKeyHandle;
    pBdReq->sharedSecretKeyHandle = *pSharedSecretKeyHandle;
    pBdReq->numParticipants       = numParticipants;

    hseResponse = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        HKF_FreeKeySlot(pSharedSecretKeyHandle);
    }
exit:
    return hseResponse;
}
#endif //HSE_SPT_BURMESTER_DESMEDT

#ifdef __cplusplus
}
#endif

/** @} */

