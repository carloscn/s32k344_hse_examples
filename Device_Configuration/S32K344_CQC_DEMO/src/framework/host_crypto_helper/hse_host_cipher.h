
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
#ifndef _HSE_HOST_CIPHER_H_
#define _HSE_HOST_CIPHER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 * ==================================================================================================*/

#include "hse_interface.h"
#include "hse_host_utils.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 * ==================================================================================================*/

/*==================================================================================================
 *                                     FILE VERSION CHECKS
 * ==================================================================================================*/

/*==================================================================================================
 *                                          CONSTANTS
 * ==================================================================================================*/

/*==================================================================================================
 *                                      DEFINES AND MACROS
 * ==================================================================================================*/

/*==================================================================================================
 *                                             ENUMS
 * ==================================================================================================*/

/*==================================================================================================
 *                               STRUCTURES AND OTHER TYPEDEFS
 * ==================================================================================================*/

/*==================================================================================================
 *                               GLOBAL VARIABLE DECLARATIONS
 * ==================================================================================================*/

/*==================================================================================================
 *                                   FUNCTION PROTOTYPES
 * ==================================================================================================*/


/* ==== AES ====*/
/* General */
hseSrvResponse_t AesCrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                          hseCipherDir_t cipherDir, const uint8_t *pIV, uint32_t inputLength,
                          const uint8_t *pInput, uint8_t *pOutput);
hseSrvResponse_t AesCryptMu(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                            hseCipherDir_t cipherDir, const uint8_t *pIV, uint32_t inputLength,
                            const uint8_t *pInput, uint8_t *pOutput, uint8_t mu);

hseSrvResponse_t AesEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                            const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                            uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                            const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                            uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesStartStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                       const uint8_t *pIV,
                                       uint32_t inputLength, const uint8_t *pInput,
                                       uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesUpdateStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput, uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesFinishStreamEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput,
                                        uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesStartStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                       const uint8_t *pIV,
                                       uint32_t inputLength, const uint8_t *pInput,
                                       uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesUpdateStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput, uint8_t *pOutput, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesFinishStreamDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                                        uint32_t inputLength, const uint8_t *pInput,
                                        uint8_t *pOutput, hseSGTOption_t inputSgtType);
#ifdef HSE_SPT_XTS_AES
hseSrvResponse_t AesXtsEncrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                               const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                               uint8_t *pOutput);

hseSrvResponse_t AesXtsDecrypt(hseKeyHandle_t keyHandle, hseCipherBlockMode_t cipherBlockMode,
                               const uint8_t *pIV, uint32_t inputLength, const uint8_t *pInput,
                               uint8_t *pOutput);
#endif /*HSE_SPT_XTS_AES */
#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_CIPHER_H_ */

/** @} */
