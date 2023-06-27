
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
#ifndef _HSE_HOST_MAC_H_
#define _HSE_HOST_MAC_H_

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

hseSrvResponse_t MacSignSrv(hseAccessMode_t accessMode, uint32_t streamId,
                            hseMacScheme_t macScheme, hseKeyHandle_t keyHandle, 
                            uint32_t inputLength, const uint8_t* pInput, 
                            uint32_t* pTagLength, uint8_t* pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t MacVerSrv(hseAccessMode_t accessMode, uint32_t streamId,
                           hseMacScheme_t macScheme, hseKeyHandle_t keyHandle, 
                           uint32_t inputLength, const uint8_t* pInput, 
                           const uint32_t* pTagLength, const uint8_t* pTag, hseSGTOption_t inputSgtType);

/*******************************************************************************
 *                                  XCBC_MAC
 ******************************************************************************/
hseSrvResponse_t AesXCbcmac(hseAuthDir_t authDir, uint32_t streamId,
                            hseKeyHandle_t keyHandle, uint32_t msgLength,
                            const uint8_t *pMsg, uint32_t* pTagLength,
                            uint8_t *pTag);

hseSrvResponse_t AesXCbcmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                    const uint8_t *pMsg, uint32_t* pTagLength,
                                    uint8_t *pTag);

hseSrvResponse_t AesXCbcmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                  const uint8_t *pMsg, const uint32_t* pTagLength,
                                  const uint8_t *pTag);

hseSrvResponse_t AesXCbcmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                               uint32_t msgLength, uint8_t *pMsg);

hseSrvResponse_t AesXCbcmacGenerateStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                                uint32_t msgLength, uint8_t *pMsg);
        
hseSrvResponse_t AesXCbcmacGenerateStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                                uint32_t msgLength, const uint8_t *pMsg,
                                                uint32_t* pTagLength, uint8_t *pTag);
      
hseSrvResponse_t AesXCbcmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                               uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t AesXCbcmacVerifyStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                                uint32_t msgLength, const uint8_t *pMsg);
        
hseSrvResponse_t AesXCbcmacVerifyStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                              uint32_t msgLength, const uint8_t *pMsg,
                                              const uint32_t* pTagLength, const uint8_t *pTag);

/*******************************************************************************
 *                                  CMAC
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesCmac(hseAuthDir_t authDir, uint32_t streamId,
                         hseKeyHandle_t keyHandle, uint32_t msgLength,
                         const uint8_t *pMsg, uint32_t* pTagLength,
                         uint8_t *pTag);

hseSrvResponse_t AesCmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                 const uint8_t *pMsg, uint32_t* pTagLength,
                                 uint8_t *pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesFastCmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                 const uint8_t *pMsg, uint8_t tagLength,
                                 uint8_t *pTag);
hseSrvResponse_t AesFastCmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                 const uint8_t *pMsg, uint8_t tagLength,
                                 uint8_t *pTag);

hseSrvResponse_t AesFastCmacGeneratewithCounter(hseKeyHandle_t keyHandle, uint32_t cntIndex, uint32_t msgLength,
                                         const uint8_t *pMsg, uint8_t tagLength, uint8_t *pTag, uint32_t *pVolatileCnt);

hseSrvResponse_t AesFastCmacVerifywithCounter(hseKeyHandle_t keyHandle, uint32_t cntIndex, uint8_t rpOffset,
                                       uint32_t msgLength, const uint8_t *pMsg, uint8_t tagLength, const uint8_t *pTag, 
                                       uint32_t *pVolatileCnt);

hseSrvResponse_t AesCmacVerify(hseKeyHandle_t keyHandle, uint32_t msgLength,
                               const uint8_t *pMsg, const uint32_t* tagLength,
                               const uint8_t *pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesCmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                            uint32_t msgLength, const uint8_t* pMsg, hseSGTOption_t inputSgtType);
hseSrvResponse_t AesCmacGenerateStreamUpdate(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg, hseSGTOption_t inputSgtType);
hseSrvResponse_t AesCmacGenerateStreamFinish(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg,
                                             uint32_t *pTagLength, uint8_t *pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesCmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId,
                                          uint32_t msgLength, const uint8_t* pMsg, hseSGTOption_t inputSgtType);
hseSrvResponse_t AesCmacVerifyStreamUpdate(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg, hseSGTOption_t inputSgtType);
hseSrvResponse_t AesCmacVerifyStreamFinish(uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg,
                                           const uint32_t *pTagLength, const uint8_t *pTag, hseSGTOption_t inputSgtType);

hseSrvResponse_t AesKmCmacGen(uint8_t u8MuInstance, hseKeyHandle_t keyHandle, uint32_t messageLength, const uint8_t *pMessage, uint8_t *tag,
                              uint32_t tagsize, uint32_t streamId, hseAccessMode_t accessMode);

/*******************************************************************************
 *                                  GMAC
 ******************************************************************************/

/* === AES === */
hseSrvResponse_t AesGmacGenerate(hseKeyHandle_t keyHandle, uint32_t ivLength,
                                 const uint8_t *pIV, uint32_t msgLength,
                                 const uint8_t *pMsg, uint32_t* pTagLength,
                                 uint8_t *pTag);

hseSrvResponse_t AesGmacVerify(hseKeyHandle_t keyHandle, const uint32_t ivLength,
                               const uint8_t* pIV, uint32_t msgLength,
                               const uint8_t *pMsg, const uint32_t* pTagLength,
                               const uint8_t *pTag);

/* Streaming for Gmac ? */
hseSrvResponse_t AesGmacGenerateStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                            uint32_t ivLength, const uint8_t* pIV,
                                            uint32_t msgLength, const uint8_t* pMsg);

hseSrvResponse_t AesGmacGenerateStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                             uint32_t msgLength, const uint8_t *pMsg);


hseSrvResponse_t AesGmacGenerateStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                             uint32_t msgLength, const uint8_t *pMsg,
                                             uint32_t *pTagLength, uint8_t *pTag);

hseSrvResponse_t AesGmacVerifyStreamStart(hseKeyHandle_t keyHandle, uint32_t streamId, 
                                          uint32_t ivLength, const uint8_t* pIV,
                                          uint32_t msgLength, const uint8_t* pMsg);

hseSrvResponse_t AesGmacVerifyStreamUpdate(hseKeyHandle_t keyHandle, uint32_t streamId,
                                           uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t AesGmacVerifyStreamFinish(hseKeyHandle_t keyHandle, uint32_t streamId,
                                           uint32_t msgLength, const uint8_t *pMsg,
                                           const uint32_t *pTagLength, const uint8_t *pTag);

/*******************************************************************************
 *                                  HMAC
 ******************************************************************************/

hseSrvResponse_t HmacGenerate(hseKeyHandle_t authKeyHandle, hseHashAlgo_t hashAlgo,
                              uint32_t inputLength, const uint8_t* pInput, 
                              uint32_t* pTagLength, uint8_t* pTag);

hseSrvResponse_t HmacVerify(hseKeyHandle_t authKeyHandle, hseHashAlgo_t hashAlgo, 
                            uint32_t inputLength, const uint8_t* pInput, 
                            const uint32_t* tagLength, const uint8_t* pTag);

/* Streaming */
hseSrvResponse_t HmacStream(
        hseAccessMode_t accessMode,
        hseHashAlgo_t hashAlgo,
        hseAuthDir_t authDir,
        hseKeyHandle_t keyHandle,
        uint32_t msgLength,
        uint8_t *pMsg,
        uint32_t *pTagLength,
        uint8_t *pTag);

/* || */

hseSrvResponse_t HmacGenerateStartStream(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo, 
                                         uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t HmacGenerateUpdateStream(hseHashAlgo_t hashAlgo, uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t HmacGenerateFinishStream(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                          uint32_t msgLength, const uint8_t *pMsg,
                                          uint32_t *pTagLength, uint8_t *pTag);

hseSrvResponse_t HmacVerifyStartStream(hseKeyHandle_t keyHandle, hseHashAlgo_t hashAlgo, 
                                       uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t HmacVerifyUpdateStream(hseHashAlgo_t hashAlgo, uint32_t streamId, uint32_t msgLength, const uint8_t *pMsg);

hseSrvResponse_t HmacVerifyFinishStream(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                        uint32_t msgLength, const uint8_t *pMsg,
                                        const uint32_t *pTagLength, const uint8_t *pTag);

/* ======================================================================================== */


#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_MAC_H_ */

/** @} */
