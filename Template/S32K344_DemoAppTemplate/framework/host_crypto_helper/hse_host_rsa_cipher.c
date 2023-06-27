/**
*   @file    hse_host_rsa_cipher.c
*
*   @brief   This file contains tests of RSA cipher services: encrypt(oaep, pkcs1v15), decrypt(oaep, pkcs1v15).
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

#include "hse_host.h"
#include "string.h"

#include "hse_host_hash.h"
#include "hse_host_import_key.h"
#include "hse_keys_allocator.h"


#ifdef HSE_SPT_RSA

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
static uint8_t muIf = 0U;
static uint8_t muChannelIdx = 1U;
/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 ==================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/
static hseSrvResponse_t RsaCipherReq(hseCipherDir_t cipherDir, hseRsaCipherScheme_t rsaScheme,
                                     hseKeyHandle_t keyHandle, uint32_t inLength,
                                     HOST_ADDR pInput, HOST_ADDR pOutLength,
                                     HOST_ADDR pOutput);

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/

static hseSrvResponse_t RsaCipherReq(hseCipherDir_t cipherDir, hseRsaCipherScheme_t rsaScheme,
                                     hseKeyHandle_t keyHandle, uint32_t inLength,
                                     HOST_ADDR pInput, HOST_ADDR pOutLength,
                                     HOST_ADDR pOutput)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];

    pHseSrvDesc->srvId = HSE_SRV_ID_RSA_CIPHER;
    hseRsaCipherSrv_t *pRsaCipherSrv = &(pHseSrvDesc->hseSrv.rsaCipherReq);
    memset(pRsaCipherSrv, 0, sizeof(hseRsaCipherSrv_t));

    pRsaCipherSrv->cipherDir = cipherDir;
    pRsaCipherSrv->rsaScheme = rsaScheme;
    pRsaCipherSrv->keyHandle = keyHandle;

    pRsaCipherSrv->pInput = pInput;
    pRsaCipherSrv->inputLength = inLength;
    pRsaCipherSrv->pOutput = pOutput;
    pRsaCipherSrv->pOutputLength = pOutLength;

    return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
}

static hseSrvResponse_t RsaCipherReqAsync(
    hseCipherDir_t cipherDir, hseRsaCipherScheme_t rsaScheme,
    hseKeyHandle_t keyHandle, uint32_t inLength,
    HOST_ADDR pInput, HOST_ADDR pOutLength, HOST_ADDR pOutput,
    const uint8_t u8MuIf, const uint8_t u8MuChannelIdx,
    hseTxOptions_t asyncTxOptions)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[u8MuIf][u8MuChannelIdx];

    pHseSrvDesc->srvId = HSE_SRV_ID_RSA_CIPHER;
    hseRsaCipherSrv_t *pRsaCipherSrv = &(pHseSrvDesc->hseSrv.rsaCipherReq);
    memset(pRsaCipherSrv, 0, sizeof(hseRsaCipherSrv_t));

    pRsaCipherSrv->cipherDir = cipherDir;
    pRsaCipherSrv->rsaScheme = rsaScheme;
    pRsaCipherSrv->keyHandle = keyHandle;

    pRsaCipherSrv->pInput = pInput;
    pRsaCipherSrv->inputLength = inLength;
    pRsaCipherSrv->pOutput = pOutput;
    pRsaCipherSrv->pOutputLength = pOutLength;

    return HSE_Send(u8MuIf, u8MuChannelIdx, asyncTxOptions, pHseSrvDesc);
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/
#ifdef HSE_SPT_KEY_GEN
hseSrvResponse_t GenerateRsaKeyPair(hseKeyHandle_t* pTargetKeyHandle, uint8_t isNvmKey,
                                    uint32_t keyBitLength, uint32_t pubExpLen, 
                                    const uint8_t* pPubExp, uint8_t* pModulus)
{
    hseSrvResponse_t status = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseKeyGenerateSrv_t* pKeyGenSrv = &(pHseSrvDesc->hseSrv.keyGenReq);
    hseKeyInfo_t lKeyInfo = {0};

    status = HKF_AllocKeySlot(NVM_KEY, HSE_KEY_TYPE_RSA_PAIR, keyBitLength, pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != status)
    {
        goto exit;
    }

    if((NVM_KEY == isNvmKey) &&
       (HSE_SRV_RSP_KEY_EMPTY != GetKeyInfo(*pTargetKeyHandle, &lKeyInfo)))
    {
        if(HSE_SRV_RSP_OK !=  EraseKeyReq(*pTargetKeyHandle, HSE_ERASE_NOT_USED))
        {
            HKF_FreeKeySlot(pTargetKeyHandle);
            status = HSE_SRV_RSP_INVALID_PARAM;
            goto exit;
        }
    }

    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_GENERATE;
    memset(pKeyGenSrv, 0, sizeof(hseKeyGenerateSrv_t));
    pKeyGenSrv->targetKeyHandle         = *pTargetKeyHandle;
    pKeyGenSrv->keyInfo.keyType         = HSE_KEY_TYPE_RSA_PAIR;
    pKeyGenSrv->keyInfo.keyBitLen       = keyBitLength;
    pKeyGenSrv->keyInfo.keyFlags        = (HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_EXCHANGE | HSE_KF_USAGE_DECRYPT | HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE);
    pKeyGenSrv->keyGenScheme            = HSE_KEY_GEN_RSA_KEY_PAIR;
    pKeyGenSrv->sch.rsaKey.pubExpLength = pubExpLen;
    pKeyGenSrv->sch.rsaKey.pPubExp      = (HOST_ADDR)pPubExp;
    pKeyGenSrv->sch.rsaKey.pModulus     = (HOST_ADDR)pModulus;

    status = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != status)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
    }
exit:
    return status;
}
#endif

#ifdef HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN
hseSrvResponse_t GenerateRsaPreMasterTLS(hseKeyHandle_t *pTargetKeyHandle)
{
    hseSrvResponse_t status         = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];

    pHseSrvDesc->srvId = HSE_SRV_ID_KEY_GENERATE;
    hseKeyGenerateSrv_t *pKeyGenSrv = &(pHseSrvDesc->hseSrv.keyGenReq);

    status = HKF_AllocKeySlot(RAM_KEY, HSE_KEY_TYPE_SHARED_SECRET, 384 /*48byte for version||46-byte random*/,
                              pTargetKeyHandle);
    if(HSE_SRV_RSP_OK != status)
    {
        goto exit;
    }

    memset(pKeyGenSrv, 0U, sizeof(hseKeyGenerateSrv_t));
    pKeyGenSrv->targetKeyHandle   = *pTargetKeyHandle;
    pKeyGenSrv->keyInfo.keyType   = HSE_KEY_TYPE_SHARED_SECRET;
    pKeyGenSrv->keyInfo.keyBitLen = 384;
    pKeyGenSrv->keyInfo.keyFlags  = (HSE_KF_USAGE_DERIVE | HSE_KF_ACCESS_EXPORTABLE);
    pKeyGenSrv->keyGenScheme      = HSE_TLS12_RSA_PRE_MASTER_SECRET_GEN;
    pKeyGenSrv->sch.rsaPreMaster.protocolVersion[0]      = 3;
    pKeyGenSrv->sch.rsaPreMaster.protocolVersion[1]      = 3;

    status = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    if(HSE_SRV_RSP_OK != status)
    {
        HKF_FreeKeySlot(pTargetKeyHandle);
    }
exit:
    return status;
}
#endif

hseSrvResponse_t RsaEncrypt(hseRsaCipherScheme_t rsaScheme, hseKeyHandle_t keyHandle, uint32_t plaintextLength,
                            uint8_t *pPlaintext, uint32_t *pCiphertextLength, uint8_t *pCiphertext)
{
    return RsaCipherReq(HSE_CIPHER_DIR_ENCRYPT, rsaScheme, keyHandle, plaintextLength, (HOST_ADDR)pPlaintext,
                        (HOST_ADDR)pCiphertextLength, (HOST_ADDR)pCiphertext);
}

hseSrvResponse_t RsaDecrypt
(
    hseRsaCipherScheme_t rsaScheme,
    hseKeyHandle_t keyHandle,
    uint32_t ciphertextLength,
    uint8_t *pCiphertext,
    uint32_t *pPlaintextLength,
    uint8_t *pPlaintext
)
{
    return RsaCipherReq(HSE_CIPHER_DIR_DECRYPT, rsaScheme, keyHandle, ciphertextLength, (HOST_ADDR)pCiphertext,
                        (HOST_ADDR)pPlaintextLength, (HOST_ADDR)pPlaintext);
}

/* HSE_RSA_ALGO_NO_PADDING */
hseSrvResponse_t RsaNoPaddEncrypt
(
    hseKeyHandle_t keyHandle,
    uint32_t plaintextLength,
    const uint8_t *pPlaintext,
    uint32_t *pCiphertextLength,
    uint8_t *pCiphertext
)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_NO_PADDING;

    return RsaCipherReq(HSE_CIPHER_DIR_ENCRYPT, rsaScheme, keyHandle, plaintextLength, (HOST_ADDR)pPlaintext,
                        (HOST_ADDR)pCiphertextLength, (HOST_ADDR)pCiphertext);
}

/* HSE_RSA_ALGO_RSAES_OAEP */
hseSrvResponse_t RsaOaepEncrypt
(
    hseHashAlgo_t hashAlgo,
    uint32_t labelLength,
    uint8_t *pLabel,
    hseKeyHandle_t keyHandle,
    uint32_t plaintextLength,
    const uint8_t *pPlaintext,
    uint32_t *pCiphertextLength,
    uint8_t *pCiphertext
)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_RSAES_OAEP;
    rsaScheme.sch.rsaOAEP.hashAlgo = hashAlgo;
    rsaScheme.sch.rsaOAEP.labelLength = labelLength;
    rsaScheme.sch.rsaOAEP.pLabel = (HOST_ADDR)pLabel;

    return RsaCipherReq(HSE_CIPHER_DIR_ENCRYPT, rsaScheme, keyHandle, plaintextLength, (HOST_ADDR)pPlaintext,
                        (HOST_ADDR)pCiphertextLength, (HOST_ADDR)pCiphertext);
}

/* HSE_RSA_ALGO_RSAES_PKCS1_V15 */
hseSrvResponse_t RsaPkcs1V15Encrypt(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t labelLength, uint8_t *pLabel,
                                    uint32_t plaintextLength, const uint8_t *pPlaintext, 
                                    uint32_t *pCiphertextLength, uint8_t *pCiphertext)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_RSAES_PKCS1_V15;
    if(HSE_CIPHER_ALGO_NULL != hashAlgo)
    {
       rsaScheme.sch.rsaOAEP.hashAlgo = hashAlgo;
       rsaScheme.sch.rsaOAEP.labelLength = labelLength;
       rsaScheme.sch.rsaOAEP.pLabel = (HOST_ADDR)pLabel; 
    }

    return RsaCipherReq(HSE_CIPHER_DIR_ENCRYPT, rsaScheme, keyHandle, plaintextLength, (HOST_ADDR)pPlaintext,
                        (HOST_ADDR)pCiphertextLength, (HOST_ADDR)pCiphertext);
}

hseSrvResponse_t RsaPkcs1V15Decrypt(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t labelLength, uint8_t *pLabel,
                                    uint32_t ciphertextLength, uint8_t *pCiphertext, 
                                    uint32_t *pPlaintextLength, uint8_t *pPlaintext)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_RSAES_PKCS1_V15;
    if(HSE_CIPHER_ALGO_NULL != hashAlgo)
    {
       rsaScheme.sch.rsaOAEP.hashAlgo = hashAlgo;
       rsaScheme.sch.rsaOAEP.labelLength = labelLength;
       rsaScheme.sch.rsaOAEP.pLabel = (HOST_ADDR)pLabel; 
    }

    return RsaCipherReq(HSE_CIPHER_DIR_DECRYPT, rsaScheme, keyHandle, ciphertextLength, (HOST_ADDR)pCiphertext,
                        (HOST_ADDR)pPlaintextLength, (HOST_ADDR)pPlaintext);
}

hseSrvResponse_t RsaPkcs1v15DecryptAsyncSrv(hseKeyHandle_t keyHandle,
                                            uint32_t ciphertextLength, const uint8_t *pCiphertext,
                                            uint32_t *pPlaintextLength, uint8_t *pPlaintext,
                                            const uint8_t u8MuIf, const uint8_t u8MuChannelIdx,
                                            hseTxOptions_t asyncTxOptions)
{
    hseRsaCipherScheme_t rsaScheme = {0U};
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_RSAES_PKCS1_V15;
    return RsaCipherReqAsync(HSE_CIPHER_DIR_DECRYPT, rsaScheme, keyHandle,
                             ciphertextLength, (HOST_ADDR)pCiphertext,
                             (HOST_ADDR)pPlaintextLength, (HOST_ADDR)pPlaintext,
                             u8MuIf, u8MuChannelIdx, asyncTxOptions);
}

/* HSE_RSA_ALGO_NO_PADDING */
hseSrvResponse_t RsaNoPaddDecrypt
(
    hseKeyHandle_t keyHandle,
    uint32_t ciphertextLength,
    const uint8_t *pCiphertext,
    uint32_t *pPlaintextLength,
    uint8_t *pPlaintext
)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_NO_PADDING;

    return RsaCipherReq(HSE_CIPHER_DIR_DECRYPT, rsaScheme, keyHandle, ciphertextLength, (HOST_ADDR)pCiphertext,
                        (HOST_ADDR)pPlaintextLength, (HOST_ADDR)pPlaintext);
}

/* HSE_RSA_ALGO_RSAES_OAEP */
hseSrvResponse_t RsaOaepDecrypt
(
    hseHashAlgo_t hashAlgo,
    uint32_t labelLength,
    uint8_t *pLabel,
    hseKeyHandle_t keyHandle,
    uint32_t ciphertextLength,
    uint8_t *pCiphertext,
    uint32_t *pPlaintextLength,
    uint8_t *pPlaintext
)
{
    hseRsaCipherScheme_t rsaScheme;
    rsaScheme.rsaAlgo = HSE_RSA_ALGO_RSAES_OAEP;
    rsaScheme.sch.rsaOAEP.hashAlgo = hashAlgo;
    rsaScheme.sch.rsaOAEP.labelLength = labelLength;
    rsaScheme.sch.rsaOAEP.pLabel = (HOST_ADDR)pLabel;

    return RsaCipherReq(HSE_CIPHER_DIR_DECRYPT, rsaScheme, keyHandle, ciphertextLength, (HOST_ADDR)pCiphertext,
                        (HOST_ADDR)pPlaintextLength, (HOST_ADDR)pPlaintext);
}

#endif /* HSE_SPT_RSA */

#ifdef __cplusplus
}
#endif

/** @} */


