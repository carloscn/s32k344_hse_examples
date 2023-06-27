
#ifndef _HSE_HOST_RSA_CIPHER_H_
#define _HSE_HOST_RSA_CIPHER_H_


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

hseSrvResponse_t GenerateRsaKeyPair(hseKeyHandle_t* pTargetKeyHandle, uint8_t isNvmKey,
                                    uint32_t keyBitLength, uint32_t pubExpLen, 
                                    const uint8_t* pPubExp, uint8_t* pModulus);

hseSrvResponse_t GenerateRsaPreMasterTLS(hseKeyHandle_t* targetKeyHandle);
/* General */
hseSrvResponse_t RsaEncrypt(hseRsaCipherScheme_t rsaScheme, hseKeyHandle_t keyHandle,
                            uint32_t plaintextLength, uint8_t *pPlaintext,
                            uint32_t *pCiphertextLength, uint8_t *pCiphertext);

/* Specific */
hseSrvResponse_t RsaNoPaddEncrypt(hseKeyHandle_t keyHandle, uint32_t plaintextLength,
                                  const uint8_t *pPlaintext, uint32_t *pCiphertextLength,
                                  uint8_t *pCiphertext);

hseSrvResponse_t RsaOaepEncrypt(hseHashAlgo_t hashAlgo, uint32_t labelLength,
                                uint8_t *pLabel, hseKeyHandle_t keyHandle,
                                uint32_t plaintextLength, const uint8_t *pPlaintext,
                                uint32_t *pCiphertextLength, uint8_t *pCiphertext);

hseSrvResponse_t RsaPkcs1V15Encrypt(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t labelLength, uint8_t *pLabel,
                                    uint32_t plaintextLength, const uint8_t *pPlaintext, 
                                    uint32_t *pCiphertextLength, uint8_t *pCiphertext);

hseSrvResponse_t RsaPkcs1v15DecryptAsyncSrv(hseKeyHandle_t keyHandle,
                                            uint32_t ciphertextLength, const uint8_t *pCiphertext,
                                            uint32_t *pPlaintextLength, uint8_t *pPlaintext,
                                            const uint8_t u8MuIf, const uint8_t u8MuChannelIdx,
                                            hseTxOptions_t asyncTxOptions);

/* General */
hseSrvResponse_t RsaDecrypt(hseRsaCipherScheme_t rsaScheme, hseKeyHandle_t keyHandle,
                            uint32_t ciphertextLength, uint8_t *pCiphertext,
                            uint32_t *pPlaintextLength, uint8_t *pPlaintext);

/* Specific */
hseSrvResponse_t RsaNoPaddDecrypt(hseKeyHandle_t keyHandle, uint32_t ciphertextLength,
                                  const uint8_t *pCiphertext, uint32_t *pPlaintextLength,
                                  uint8_t *pPlaintext);

hseSrvResponse_t RsaOaepDecrypt(hseHashAlgo_t hashAlgo, uint32_t labelLength,
                                uint8_t *pLabel, hseKeyHandle_t keyHandle,
                                uint32_t ciphertextLength, const uint8_t *pCiphertext,
                                uint32_t *pPlaintextLength, uint8_t *pPlaintext);

hseSrvResponse_t RsaPkcs1V15Decrypt(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t labelLength, uint8_t *pLabel, 
                                    uint32_t ciphertextLength, uint8_t *pCiphertext, 
                                    uint32_t *pPlaintextLength, uint8_t *pPlaintext);

/* ======================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_RSA_CIPHER_H_ */

/** @} */

