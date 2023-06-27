
#ifndef _HSE_HOST_HASH_H_
#define _HSE_HOST_HASH_H_

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

#define HASH_STREAM_SUPPORTED

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

typedef enum
{
   /* chunk size */
   CHUNK_SIZE_NIL,
   CHUNK_SIZE_MD5_OBSOLETE,
   CHUNK_SIZE_SHA1,
   CHUNK_SIZE_SHA224,
   CHUNK_SIZE_SHA256,
   CHUNK_SIZE_SHA384,
   CHUNK_SIZE_SHA512,
   CHUNK_SIZE_SHA512_224,
   CHUNK_SIZE_SHA512_256,
   CHUNK_SIZE_SHA3224,
   CHUNK_SIZE_SHA3256,
   CHUNK_SIZE_SHA3384,
   CHUNK_SIZE_SHA3512,
}hseChunkSize_t;

typedef enum
{
   /* hash size */
   HASH_SIZE_NIL,
   HASH_SIZE_MD5_OBSOLETE,
   HASH_SIZE_SHA1,
   HASH_SIZE_SHA224,
   HASH_SIZE_SHA256,
   HASH_SIZE_SHA384,
   HASH_SIZE_SHA512,
   HASH_SIZE_SHA512_224,
   HASH_SIZE_SHA512_256,
   HASH_SIZE_SHA3224,
   HASH_SIZE_SHA3256,
   HASH_SIZE_SHA3384,
   HASH_SIZE_SHA3512,
}hseHashMaxSize_t;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

hseSrvResponse_t HashReq(hseAccessMode_t accessMode, const uint8_t muIf,
                                const uint8_t muChannelIdx, hseHashAlgo_t hashAlgo,
                                uint32_t streamId, uint32_t inputLength, 
                                const uint8_t* pInput, uint32_t* pHashLength, 
                                uint8_t* pHash, hseTxOptions_t txOptions, hseSGTOption_t inputSgtType);

hseSrvResponse_t HashDataSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                             const uint8_t muChannelIdx, uint32_t inputLength, 
                             const uint8_t *pInput, uint32_t *pHashLength, 
                             uint8_t *pHash, hseTxOptions_t txOptions, hseSGTOption_t inputSgtType);

hseSrvResponse_t HashDataDefSrv(hseHashAlgo_t hashAlgo, uint32_t inputLength, 
                             const uint8_t *pInput, uint32_t *pHashLength, 
                             uint8_t *pHash, hseSGTOption_t inputSgtType);

hseSrvResponse_t HashDataAsyncSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                  const uint8_t muChannelIdx, uint32_t inputLength, 
                                  const uint8_t * pInput, uint32_t* pHashLength, 
                                  uint8_t * pHash, hseTxOptions_t txOptions);

hseSrvResponse_t HashDataStartStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                        const uint8_t muChannelIdx, uint32_t streamId);

hseSrvResponse_t HashDataStartStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId);

hseSrvResponse_t HashDataUpdateStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                         const uint8_t muChannelIdx, uint32_t streamId, 
                                         uint32_t inputLength, const uint8_t* pInput);
                            
hseSrvResponse_t HashDataUpdateStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                            uint32_t inputLength, const uint8_t* pInput);

hseSrvResponse_t HashDataFinishStreamSrv(hseHashAlgo_t hashAlgo, const uint8_t muIf, 
                                         const uint8_t muChannelIdx, uint32_t streamId, 
                                         uint32_t inputLength, const uint8_t* pInput, 
                                         uint32_t* pHashLength, uint8_t* tagOutput);

hseSrvResponse_t HashDataFinishStreamDefSrv(hseHashAlgo_t hashAlgo, uint32_t streamId, 
                                            uint32_t inputLength, const uint8_t* pInput, 
                                            uint32_t* pHashLength, uint8_t* tagOutput);

hseSrvResponse_t GenerateHmacKey(uint32_t *pTargetKeyHandle, uint8_t isNvmKey, uint16_t keyBitLen,
                                 hseKeyFlags_t opType);

#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_HASH_H_ */

/** @} */
