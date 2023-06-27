
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

hseSrvResponse_t GenerateRsaKeyPair(hseKeyHandle_t targetKeyHandle,
                                    uint32_t keyBitLength, uint32_t pubExpLen, 
                                    uint8_t* pPubExp, uint8_t* pModulus);

/* General */
hseSrvResponse_t RsaEncrypt(hseRsaCipherScheme_t rsaScheme, hseKeyHandle_t keyHandle,
                            uint32_t plaintextLength, uint8_t *pPlaintext,
                            uint32_t *pCiphertextLength, uint8_t *pCiphertext);

/* Specific */
hseSrvResponse_t RsaNoPaddEncrypt(hseKeyHandle_t keyHandle, uint32_t plaintextLength,
                                  uint8_t *pPlaintext, uint32_t *pCiphertextLength,
                                  uint8_t *pCiphertext);

hseSrvResponse_t RsaOaepEncrypt(hseHashAlgo_t hashAlgo, uint32_t labelLength,
                                uint8_t *pLabel, hseKeyHandle_t keyHandle,
                                uint32_t plaintextLength, uint8_t *pPlaintext,
                                uint32_t *pCiphertextLength, uint8_t *pCiphertext);

hseSrvResponse_t RsaPkcs1V15Encrypt(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo,
                                    uint32_t labelLength, uint8_t *pLabel,
                                    uint32_t plaintextLength, uint8_t *pPlaintext, 
                                    uint32_t *pCiphertextLength, uint8_t *pCiphertext);

hseSrvResponse_t RsaPkcs1v15DecryptAsyncSrv(hseKeyHandle_t keyHandle,
                                            uint32_t ciphertextLength, uint8_t *pCiphertext,
                                            uint32_t *pPlaintextLength, uint8_t *pPlaintext,
                                            const uint8_t u8MuIf, const uint8_t u8MuChannelIdx,
                                            hseTxOptions_t asyncTxOptions);

/* General */
hseSrvResponse_t RsaDecrypt(hseRsaCipherScheme_t rsaScheme, hseKeyHandle_t keyHandle,
                            uint32_t ciphertextLength, uint8_t *pCiphertext,
                            uint32_t *pPlaintextLength, uint8_t *pPlaintext);

/* Specific */
hseSrvResponse_t RsaNoPaddDecrypt(hseKeyHandle_t keyHandle, uint32_t ciphertextLength,
                                  uint8_t *pCiphertext, uint32_t *pPlaintextLength,
                                  uint8_t *pPlaintext);

hseSrvResponse_t RsaOaepDecrypt(hseHashAlgo_t hashAlgo, uint32_t labelLength,
                                uint8_t *pLabel, hseKeyHandle_t keyHandle,
                                uint32_t ciphertextLength, uint8_t *pCiphertext,
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

