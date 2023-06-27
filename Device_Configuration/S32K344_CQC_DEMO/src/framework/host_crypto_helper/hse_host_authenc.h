/**
 *   @file    hse_host_authenc.h
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


#ifndef HSE_HOST_AUTHENC_H
#define HSE_HOST_AUTHENC_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
==================================================================================================*/

#include "hse_interface.h"
#include "hse_host_utils.h"


/*==================================================================================================
 *                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                      DEFINES AND MACROS
==================================================================================================*/

#define AUTHENC_STREAM_SUPPORTED

/*==================================================================================================
 *                                             ENUMS
==================================================================================================*/

/*==================================================================================================
 *                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
 *                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
 *                                    FUNCTION PROTOTYPES
==================================================================================================*/
hseSrvResponse_t AuthEncSignAesEnc(hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                   hseCipherBlockMode_t block, hseMacAlgo_t macAlgo,
                                   hseHashAlgo_t hashAlgo,
                                   uint32_t inputLength, const uint8_t* pInput,
                                   uint32_t aadLength, const uint8_t* pAAD,
                                   uint32_t ivLength, const uint8_t* pIV, uint8_t* pOutput,
                                   uint32_t* pTagLength, uint8_t* pTag);

hseSrvResponse_t AuthEncVerAesDec(hseKeyHandle_t cipherKeyHandle, hseKeyHandle_t authKeyHandle,
                                  hseCipherBlockMode_t block, hseMacAlgo_t macAlgo,
                                  hseHashAlgo_t hashAlgo,
                                  uint32_t inputLength, const uint8_t* pInput,
                                  uint32_t aadLength, const uint8_t* pAAD,
                                  uint32_t ivLength, const uint8_t* pIV, uint8_t* pOutput,
                                  uint32_t* pTagLength, uint8_t* pTag);

hseSrvResponse_t AuthEncSign(hseKeyHandle_t authKeyHandle, hseMacAlgo_t macAlgo,
                             hseHashAlgo_t hashAlgo,
                             uint32_t inputLength, const uint8_t* pInput,
                             uint32_t aadLength, const uint8_t* pAAD,
                             uint32_t ivLength, const uint8_t* pIV,
                             uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t AuthEncVerify(hseKeyHandle_t authKeyHandle, hseMacAlgo_t macAlgo,
                               hseHashAlgo_t hashAlgo,
                               uint32_t inputLength, const uint8_t* pInput,
                               uint32_t aadLength, const uint8_t* pAAD,
                               uint32_t ivLength, const uint8_t* pIV,
                               uint8_t* pOutput, uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType);

#ifdef __cplusplus
}
#endif

#endif /* HSE_HOST_AUTHENC_H */

/** @} */
