
#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "hse_host.h"
#include "hse_keys_allocator.h"
#include "string.h"

#include "hse_host_hash.h"
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static uint8_t          localMuIf = 0U;
static uint8_t          localMuChannelIdx = 1U;

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef HASH_STREAM_SUPPORTED
static hseSrvResponse_t HashDataStreamStart(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                           const uint8_t muChannelIdx, uint32_t streamId);

static hseSrvResponse_t HashDataStreamUpdate(hseHashAlgo_t hashAlgo, const uint8_t muIf,
                                             const uint8_t muChannelIdx, uint32_t streamId,
                                             uint32_t inputLength, const uint8_t *pInput);

static hseSrvResponse_t HashDataStreamFinish(hseHashAlgo_t hashAlgo, const uint8_t muIf,
                                             const uint8_t muChannelIdx, uint32_t streamId,
                                             uint32_t inputLength, const uint8_t *pInput, 
                                             uint32_t *pHashLength, uint8_t *pHash);
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

hseSrvResponse_t HashReq(hseAccessMode_t accessMode, const uint8_t muIf,
                                const uint8_t muChannelIdx, hseHashAlgo_t hashAlgo,
                                uint32_t streamId, uint32_t inputLength,
                                const uint8_t* pInput, uint32_t* pHashLength,
                                uint8_t* pHash, hseTxOptions_t txOptions, hseSGTOption_t inputSgtType)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseHashSrv_t* pHashSrv;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_HASH;
    pHashSrv = &(pHseSrvDesc->hseSrv.hashReq);

    pHashSrv->accessMode    = accessMode;
    pHashSrv->hashAlgo      = hashAlgo;
    pHashSrv->streamId      = streamId;
    pHashSrv->inputLength   = inputLength;
    pHashSrv->pInput        = (HOST_ADDR)pInput;
    pHashSrv->pHashLength   = (HOST_ADDR)pHashLength;
    pHashSrv->pHash         = (HOST_ADDR)pHash;
    pHashSrv->sgtOption     = inputSgtType;

    return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
}

#ifdef HASH_STREAM_SUPPORTED
static hseSrvResponse_t HashDataStreamStart(hseHashAlgo_t hashAlgo, const uint8_t muIf,
                                            const uint8_t muChannelIdx, uint32_t streamId)
{
    return HashReq(HSE_ACCESS_MODE_START, muIf, muChannelIdx, hashAlgo, streamId, 0, NULL, 0, NULL, gSyncTxOption, 0U);
}

static hseSrvResponse_t HashDataStreamUpdate(hseHashAlgo_t hashAlgo, const uint8_t muIf,
                                             const uint8_t muChannelIdx, uint32_t streamId,
                                             uint32_t inputLength, const uint8_t* pInput)
{
    return HashReq(HSE_ACCESS_MODE_UPDATE, muIf, muChannelIdx, hashAlgo, streamId, inputLength, pInput, 0, NULL, gSyncTxOption, 0U);
}

static hseSrvResponse_t HashDataStreamFinish(hseHashAlgo_t hashAlgo, const uint8_t muIf,
                                             const uint8_t muChannelIdx, uint32_t streamId,
                                             uint32_t inputLength, const uint8_t* pInput,
                                             uint32_t* pHashLength, uint8_t* pHash)
{
    return HashReq(HSE_ACCESS_MODE_FINISH, muIf, muChannelIdx, hashAlgo, streamId, inputLength, pInput, pHashLength, pHash, gSyncTxOption, 0U);
}
#endif

/* TODO: SHAKE */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
hseSrvResponse_t HashDataSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                             const uint8_t muChannelIdx, uint32_t inputLength, 
                             const uint8_t * pInput, uint32_t* pHashLength, 
                             uint8_t * pHash, hseTxOptions_t txOptions, hseSGTOption_t inputSgtType)
{
    return HashReq(HSE_ACCESS_MODE_ONE_PASS, muIf, muChannelIdx, hashAlgo, 0,
                   inputLength, pInput, pHashLength, pHash, txOptions, inputSgtType);
}

hseSrvResponse_t HashDataDefSrv(hseHashAlgo_t hashAlgo, uint32_t inputLength, 
                             const uint8_t *pInput, uint32_t *pHashLength, 
                             uint8_t *pHash, hseSGTOption_t inputSgtType)
{
    return HashDataSrv(hashAlgo, localMuIf, localMuChannelIdx, inputLength, pInput, pHashLength, pHash, gSyncTxOption, inputSgtType);
}

hseSrvResponse_t HashDataAsyncSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                  const uint8_t muChannelIdx, uint32_t inputLength, 
                                  const uint8_t * pInput, uint32_t* pHashLength, 
                                  uint8_t * pHash, hseTxOptions_t txOptions)
{
    return HashDataSrv(hashAlgo, muIf, muChannelIdx, inputLength, pInput, pHashLength, pHash, txOptions, 0U);
}

hseSrvResponse_t HashDataStartStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                        const uint8_t muChannelIdx, uint32_t streamId)
{
    return HashDataStreamStart(hashAlgo, muIf, muChannelIdx, streamId);
}

hseSrvResponse_t HashDataStartStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId)
{
    return HashDataStartStreamSrv(hashAlgo, localMuIf, localMuChannelIdx, streamId);
}

hseSrvResponse_t HashDataUpdateStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                         const uint8_t muChannelIdx, uint32_t streamId, 
                                         uint32_t inputLength, const uint8_t* pInput)
{
    return  HashDataStreamUpdate(hashAlgo, muIf, muChannelIdx, streamId, inputLength, pInput);
}

hseSrvResponse_t HashDataUpdateStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                            uint32_t inputLength, const uint8_t* pInput)
{
    return HashDataUpdateStreamSrv(hashAlgo, localMuIf, localMuChannelIdx, streamId, inputLength, pInput);
}

hseSrvResponse_t HashDataFinishStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                         const uint8_t muChannelIdx, uint32_t streamId, 
                                         uint32_t inputLength, const uint8_t* pInput, 
                                         uint32_t* pHashLength, uint8_t* tagOutput)
{
    return HashDataStreamFinish(hashAlgo, muIf, 
                                muChannelIdx, streamId,
                                inputLength, pInput,
                                pHashLength, tagOutput);
}

hseSrvResponse_t HashDataFinishStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                            uint32_t inputLength, const uint8_t* pInput, 
                                            uint32_t* pHashLength, uint8_t* tagOutput)
{
    return HashDataFinishStreamSrv(hashAlgo, localMuIf, localMuChannelIdx, streamId, inputLength, pInput, 
                                   pHashLength, tagOutput);
}
#ifdef HSE_SPT_HMAC
hseSrvResponse_t GenerateHmacKey(hseKeyHandle_t *pTargetKeyHandle, uint8_t isNvmKey, uint16_t keyBitLen,
                                 hseKeyFlags_t keyFlags)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseKeyGenerateSrv_t* pKeyGenSrv;

    hseStatus = HKF_AllocKeySlot(isNvmKey, HSE_KEY_TYPE_HMAC, keyBitLen, pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != hseStatus)
    {
        goto exit;
    }

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_GENERATE;

    pKeyGenSrv = &(pHseSrvDesc->hseSrv.keyGenReq);
    pKeyGenSrv->targetKeyHandle = *pTargetKeyHandle; /*TODO :  Need to verify how can pass key handle*/
    pKeyGenSrv->keyInfo.keyType = HSE_KEY_TYPE_HMAC;
    pKeyGenSrv->keyInfo.keyBitLen = keyBitLen; /*TODO :  Need to verify for otherkey size and define the design*/
    pKeyGenSrv->keyInfo.keyFlags = keyFlags;
    pKeyGenSrv->keyGenScheme = HSE_KEY_GEN_SYM_RANDOM_KEY;

    hseStatus = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != hseStatus)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
    }
exit:
    return hseStatus;
}
#endif /*HSE_SPT_HMAC*/
#ifdef __cplusplus
}
#endif

/** @} */

