
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
#ifndef _HSE_HOST_AEAD_H_
#define _HSE_HOST_AEAD_H_

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
#include "hse_host_utils.h"
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

#define AEAD_STREAM_SUPPROTED
//#define AEAD_TDES_SUPPORTED

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


/*******************************************************************************
 *                                          GCM
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesGcm(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
                        uint32_t ivLength, const uint8_t *pIV,
                        uint32_t aadLength, const uint8_t *pAad,
                        uint32_t inputLength, const uint8_t *pInput,
                        uint32_t tagLength, uint8_t *pTag,
                        uint8_t *pOutput);

hseSrvResponse_t AesGcmEncrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
                               const uint8_t *pIV, uint32_t aadLength,
                               const uint8_t *pAad, uint32_t inputLength,
                               const uint8_t *pPlainText, uint32_t tagLength,
                               uint8_t *pTag, uint8_t *pCipherText, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesGcmDecrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
                               const uint8_t *pIV, uint32_t aadLength,
                               const uint8_t *pAad, uint32_t inputLength,
                               const uint8_t *pCipherText, uint32_t tagLength,
                               uint8_t *pTag, uint8_t *pPlainText, hseSGTOption_t inputSgtType);

#ifdef AEAD_STREAM_SUPPROTED
/* Streaming for Gcm */
hseSrvResponse_t AesGcmStream(hseAccessMode_t accessMode, uint32_t streamId,
                              hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
                              uint32_t ivLength, const uint8_t *pIV,
                              uint32_t aadLength, const uint8_t *pAad,
                              uint32_t inputLength, const uint8_t *pInput,
                              uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);

/* || */

hseSrvResponse_t AesGcmStartStreamEncrypt(uint32_t streamId, hseKeyHandle_t keyHandle,
                                          uint32_t ivLength, const uint8_t *pIV,
                                          uint32_t aadLength, const uint8_t *pAad);

hseSrvResponse_t AesGcmUpdateStreamEncrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput, uint8_t *pOutput);

hseSrvResponse_t AesGcmFinishStreamEncrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput,
                                           uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);

hseSrvResponse_t AesGcmStartStreamDecrypt(uint32_t streamId, hseKeyHandle_t keyHandle,
                                          uint32_t ivLength, const uint8_t *pIV,
                                          uint32_t aadLength, const uint8_t *pAad);

hseSrvResponse_t AesGcmUpdateStreamDecrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput, uint8_t *pOutput);

hseSrvResponse_t AesGcmFinishStreamDecrypt(uint32_t streamId, uint32_t inputLength, uint8_t *pInput,
                                           uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);
#endif

#ifdef AEAD_TDES_SUPPORTED
/* === 3DES === */
hseSrvResponse_t TDesGcm(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                 uint32_t ivLength, uint8_t *pIV, uint32_t aadLength,
		                 uint8_t *pAad, uint32_t inputLength,
		                 uint8_t *pInput, uint32_t tagLength,
		                 uint8_t *pTag, uint8_t *pOutput);

hseSrvResponse_t TDesGcmEncrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                        uint8_t *pIV, uint32_t aadLength,
		                        uint8_t *pAad, uint32_t inputLength,
		                        const uint8_t *pPlainText, uint32_t tagLength,
		                        uint8_t *pTag, uint8_t *pCipherText);

hseSrvResponse_t TDesGcmDecrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                        uint8_t *pIV, uint32_t aadLength,
		                        uint8_t *pAad, uint32_t inputLength,
		                        const uint8_t *pCipherText, uint32_t tagLength,
		                        uint8_t *pTag, uint8_t *pPlainText);

/* Streaming for Gcm */
hseSrvResponse_t TDesGcmStream(hseAccessMode_t accessMode, hseCipherDir_t cipherDir,
		                       hseKeyHandle_t keyHandle, uint32_t ivLength,
		                       uint8_t *pIV, uint32_t aadLength,
		                       uint8_t *pAad, uint32_t inputLength,
		                       uint8_t *pInput, uint32_t tagLength,
		                       uint8_t *pTag, uint8_t *pOutput);

/* || */

hseSrvResponse_t TDesGcmStreamStart(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                            uint32_t ivLength, uint8_t *pIV,
		                            uint32_t aadLength, uint8_t *pAad);

hseSrvResponse_t TDesGcmStreamUpdate(hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput);

hseSrvResponse_t TDesGcmStreamFinish(hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput,
		                             uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);
#endif

/*******************************************************************************
 *                                    CCM
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesCcm(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                uint32_t ivLength, const uint8_t *pIV,
		                uint32_t aadLength, const uint8_t *pAad,
		                uint32_t inputLength, const uint8_t *pInput,
		                uint32_t tagLength, uint8_t *pTag,
		                uint8_t *pOutput);

hseSrvResponse_t AesCcmEncrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                       const uint8_t *pIV, uint32_t aadLength,
		                       const uint8_t *pAad, uint32_t inputLength,
		                       const uint8_t *pPlainText, uint32_t tagLength,
		                       uint8_t *pTag, uint8_t *pCipherText);

hseSrvResponse_t AesCcmDecrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                       const uint8_t *pIV, uint32_t aadLength,
		                       const uint8_t *pAad, uint32_t inputLength,
		                       const uint8_t *pCipherText, uint32_t tagLength,
		                       uint8_t *pTag, uint8_t *pPlainText);

#ifdef AEAD_STREAM_SUPPROTED
/* Streaming for Ccm */
hseSrvResponse_t AesCcmStream(hseAccessMode_t accessMode, uint32_t streamId,
		                      hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                      uint32_t ivLength, const uint8_t *pIV,
		                      uint32_t aadLength, const uint8_t *pAad,
		                      uint32_t inputLength, const uint8_t *pInput,
		                      uint32_t tagLength, uint8_t *pTag,
		                      uint8_t *pOutput);

/* || */

hseSrvResponse_t AesCcmStreamStart(uint32_t streamId, hseCipherDir_t cipherDir,
                                   hseKeyHandle_t keyHandle, uint32_t ivLength,
                                   const uint8_t *pIV, uint32_t aadLength,
                                   const uint8_t *pAad);

hseSrvResponse_t AesCcmStreamUpdate(uint32_t streamId, hseCipherDir_t cipherDir, uint32_t inputLength,
		                            uint8_t *pInput, uint8_t *pOutput);

hseSrvResponse_t AesCcmStreamFinish(uint32_t streamId, hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput,
		                            uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);
#endif

#ifdef AEAD_TDES_SUPPORTED
/* === 3DES === */
hseSrvResponse_t TDesCcm(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                 uint32_t ivLength, uint8_t *pIV,
		                 uint32_t aadLength, uint8_t *pAad,
		                 uint32_t inputLength, uint8_t *pInput,
		                 uint32_t tagLength, uint8_t *pTag,
		                 uint8_t *pOutput);

hseSrvResponse_t TDesCcmEncrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                        uint8_t *pIV, uint32_t aadLength,
		                        uint8_t *pAad, uint32_t inputLength,
		                        const uint8_t *pPlainText, uint32_t tagLength,
		                        uint8_t *pTag, uint8_t *pCipherText);

hseSrvResponse_t TDesCcmDecrypt(hseKeyHandle_t keyHandle, uint32_t ivLength,
		                        uint8_t *pIV, uint32_t aadLength,
		                        uint8_t *pAad, uint32_t inputLength,
		                        const uint8_t *pCipherText, uint32_t tagLength,
		                        uint8_t *pTag, uint8_t *pPlainText);

/* Streaming for Ccm */
hseSrvResponse_t TDesCcmStream(hseAccessMode_t accessMode, hseCipherDir_t cipherDir,
		                       hseKeyHandle_t keyHandle, uint32_t ivLength,
		                       uint8_t *pIV, uint32_t aadLength,
		                       uint8_t *pAad, uint32_t inputLength,
		                       uint8_t *pInput, uint32_t tagLength,
		                       uint8_t *pTag, uint8_t *pOutput);

/* || */

hseSrvResponse_t TDesCcmStreamStart(hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle,
		                            uint32_t ivLength, uint8_t *pIV,
		                            uint32_t aadLength, uint8_t *pAad);

hseSrvResponse_t TDesCcmStreamUpdate(hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput);

hseSrvResponse_t TDesCcmStreamFinish(hseCipherDir_t cipherDir, uint32_t inputLength, uint8_t *pInput,
		                             uint32_t tagLength, uint8_t *pTag, uint8_t *pOutput);
#endif

/* ======================================================================================== */


#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_AEAD_H_ */

/** @} */

