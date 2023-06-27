
#ifndef _HSE_HOST_SIGN_H_
#define _HSE_HOST_SIGN_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "hse_interface.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
hseSrvResponse_t SignSrvReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                            hseKeyHandle_t keyHandle, uint32_t inputLength,
                            const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                            uint32_t *pSignatureLength0, uint8_t *pSignature0,  
                            uint32_t *pSignatureLength1, uint8_t *pSignature1);

hseSrvResponse_t VerSrvReq(hseAccessMode_t accessMode, hseSignScheme_t signScheme,
                           hseKeyHandle_t keyHandle, uint32_t inputLength,
                           const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                           const uint32_t* pSignatureLength0, const uint8_t *pSignature0, 
                           const uint32_t* pSignatureLength1, const uint8_t *pSignature1);
 /*************************************************************************************
  *                                         ECDSA
  ************************************************************************************/                          

hseSrvResponse_t EcdsaSign(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                              uint32_t inputLength, const uint8_t* pInput, 
                              bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                              uint32_t* pRLen, uint8_t* pR, 
                              uint32_t* pSLen, uint8_t* pS);

hseSrvResponse_t EcdsaVerify(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                             uint32_t inputLength, const uint8_t* pInput,
                             bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                             const uint32_t* pRLen, const uint8_t* pR,
                             const uint32_t* pSLen, const uint8_t* pS);

/*******************************************************************************************
 *                                          EdDSA
 ******************************************************************************************/
hseSrvResponse_t EddsaSign(hseKeyHandle_t keyHandle, bool_t bHashEddsa,
                              uint32_t inputLength, const uint8_t* pInput, bool_t bInputIsHashed,
                              uint8_t userContextLength, const uint8_t* pUserContext,
                              uint32_t* pRLen, uint8_t* pR,
                              uint32_t* pSLen, uint8_t* pS);

hseSrvResponse_t EddsaVerify(hseKeyHandle_t keyHandle, bool_t bHashEddsa,
                             uint32_t inputLength, const uint8_t* pInput, bool_t bInputIsHashed,
                             uint8_t userContextLength, const uint8_t* pUserContext,
                             const uint32_t* pRLen, const uint8_t* pR,
                             const uint32_t* pSLen, const uint8_t* pS);

/******************************************************************************************* 
 *                                        RSA SA PSS
 ******************************************************************************************/
hseSrvResponse_t RsaPssSignSrv(hseKeyHandle_t keyHandle, uint32_t saltLength, 
                               hseHashAlgo_t hashAlgo, uint32_t inputLength,
                               const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                               uint32_t *pSignatureLength, uint8_t *pSignature);

hseSrvResponse_t RsaPssVerSrv(hseKeyHandle_t keyHandle, uint32_t saltLength, 
                              hseHashAlgo_t hashAlgo, uint32_t inputLength,
                              const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                              const uint32_t* pSignatureLength, const uint8_t *pSignature);

hseSrvResponse_t RsaPssSignStreamStartSrv(hseKeyHandle_t keyHandle, 
                                          hseHashAlgo_t hashAlgo, 
                                          uint32_t saltLength);

hseSrvResponse_t RsaPssSignStreamUpdateSrv(uint32_t inputLength, const uint8_t *pInput);

hseSrvResponse_t RsaPssSignStreamFinishSrv(uint32_t inputLength, 
                                           const uint8_t *pInput, 
                                           uint32_t *pSignatureLength, 
                                           uint8_t *pSignature);

hseSrvResponse_t RsaPssVerStreamStartSrv(hseKeyHandle_t keyHandle, 
                                         hseHashAlgo_t hashAlgo, 
                                         uint32_t saltLength);

hseSrvResponse_t RsaPssVerStreamUpdateSrv(uint32_t inputLength, const uint8_t *pInput);

hseSrvResponse_t RsaPssVerStreamFinishSrv(uint32_t inputLength, 
                                          const uint8_t *pInput, 
                                          const uint32_t* pSignatureLength, 
                                          const uint8_t *pSignature);

/******************************************************************************************
 *                              RSA SA PKCS1 V15(generate/verify)
 *****************************************************************************************/
hseSrvResponse_t RsaPkcs1v15SignSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo, 
                                    uint32_t inputLength, uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                    uint32_t *pSignatureLength, uint8_t *pSignature);

hseSrvResponse_t RsaPkcs1v15SignAsyncSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo, 
                                         const uint8_t muIf,  const uint8_t muChannelIdx,
                                         uint32_t inputLength, uint8_t *pInput, 
                                         uint32_t *pSignatureLength, uint8_t *pSignature,
                                         hseTxOptions_t asyncTxOptions);

hseSrvResponse_t RsaPkcs1v15VerSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                   uint32_t inputLength, const uint8_t *pInput, bool_t bInputIsHashed, hseSGTOption_t sgtOption,
                                   const uint32_t* pSignatureLength, const uint8_t *pSignature);

hseSrvResponse_t RsaPkcs1v15VerAsyncSrv(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                        const uint8_t muIf, const uint8_t muChannelIdx,
                                        uint32_t inputLength, const uint8_t *pInput, 
                                        const uint32_t* pSignatureLength, const uint8_t *pSignature,
                                        hseTxOptions_t asyncTxOptions);

hseSrvResponse_t RsaPkcs1v15SignStreamStart(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo);

hseSrvResponse_t RsaPkcs1v15SignUpdate(uint32_t inputLength, uint8_t *pInput);

hseSrvResponse_t RsaPkcs1v15SignFinish(uint32_t inputLength, uint8_t *pInput, 
                                       uint32_t *pSignatureLength, uint8_t *pSignature);

hseSrvResponse_t RsaPkcs1v15VerSha1StreamStart(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo);

hseSrvResponse_t RsaPkcs1v15VerUpdate(uint32_t inputLength, uint8_t *pInput);

hseSrvResponse_t RsaPkcs1v15VerFinish(uint32_t inputLength, uint8_t *pInput, 
                                      uint32_t *pSignatureLength, uint8_t *pSignature);

hseSrvResponse_t DHSharedSecretCompute(hseKeyHandle_t pubKeyHandle, hseKeyHandle_t privKeyHandle,
                                       hseKeyHandle_t *pTargetKeyHandle, uint8_t isNvmKey, uint16_t maxBitLength);

#ifdef HSE_SPT_BURMESTER_DESMEDT
hseSrvResponse_t BDComputeSecondPubKey(hseKeyHandle_t deviceKeyHandle, hseKeyHandle_t pubKeyHandle);

hseSrvResponse_t BDComputeSharedSecret(hseKeyHandle_t deviceKeyHandle, hseKeyHandle_t pubKeyHandle,
                                       uint8_t numParticipants, hseKeyHandle_t *pSharedSecretKeyHandle, uint8_t isNvmKey, uint16_t sharedSecretLength);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_SIGN_H_ */

/** @} */

