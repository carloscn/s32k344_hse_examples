
#ifndef _HSE_HOST_IMPORT_KEY_H_
#define _HSE_HOST_IMPORT_KEY_H_

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
#include "hse_host.h"
#include "hse_host_hash.h"
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

/** @brief HSE export key options*/
typedef uint8_t hseExportKeyOptions_t;
#define HSE_EXPORT_PUB_KEY                      ((hseExportKeyOptions_t)1U<<0U)   /**< @brief Export public key. */
#define HSE_EXPORT_SYM_PRIV_KEY                 ((hseExportKeyOptions_t)1U<<1U)   /**< @brief Export symmetric private key */
#define HSE_EXPORT_USE_AUTH_KEY_CONTAINER       ((hseExportKeyOptions_t)1U<<2U)   /**< @brief Export key service uses an authenticated container. */


/** @brief HSE import key options*/
typedef uint8_t hseImportKeyOptions_t;
#define HSE_IMPORT_USE_CIPHER                   ((hseImportKeyOptions_t)1U<<0U) /**< @brief Import key service uses a cipher scheme. */
#define HSE_IMPORT_USE_AUTH_KEY_CONTAINER       ((hseImportKeyOptions_t)1U<<1U) /**< @brief Import key service uses an authenticated key container. */
#define HSE_IMPORT_USE_NOT_AUTH_KEY_CONTAINER   ((hseImportKeyOptions_t)1U<<2U) /**< @brief Import key service uses a key container not authenticated (only for PUB_EXT keys). */
#define HSE_IMPORT_USE_AEAD                     ((hseImportKeyOptions_t)1U<<3U) /**< @brief Import key service uses an AEAD scheme(only for symmetric keys). */

#define MAX_KEY_CONTAINER_LENGTH            (1504UL)

#define HSE_RAM_KEY_COUNTER_VALUE           (HSE_KF_MAX_KEY_COUNTER_VALUE + 1UL)
/*==================================================================================================
 *                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

typedef struct {
    uint8_t *pKey0;
    uint16_t keyLen0;
    uint8_t *pKey1;
    uint16_t keyLen1;
    uint8_t *pKey2;
    uint16_t keyLen2;
} hseImportKeyValue_t;

typedef struct {
    hseKeyHandle_t keyHandle;
    hseKeyInfo_t *pKeyInfo;
    hseImportKeyValue_t keyValue;
} hseKey_t;

typedef struct {
    hseKeyHandle_t *pKeyHandle;
    hseCipherScheme_t *pCipherScheme;
} hseKeyImportCipherParams_t;

typedef struct {
    uint8_t *pKeyContainer;
    uint16_t keyContainerLength;
    hseKeyHandle_t *pKeyHandle;
    hseAuthScheme_t *pAuthScheme;
    uint8_t *pSign0;
    uint16_t signLen0;
    uint8_t *pSign1;
    uint16_t signLen1;
} hseKeyImportAuthParams_t;

typedef struct {
    uint8_t *pKeyContainer;
    uint32_t keyContainerLength;
} hseKeyFileImportParams_t;

typedef struct {
    hseImportKeyOptions_t options;
    hseKey_t *pKey;
    hseKeyImportCipherParams_t cipherParams;
    hseKeyImportAuthParams_t authParams;
    hseKeyFileImportParams_t keyFileParams;
} hseKeyImportParams_t;

typedef struct {
    hseExportKeyOptions_t options;
    hseKey_t *pKey;
    hseKeyImportCipherParams_t cipherParams;
    hseKeyImportAuthParams_t authParams;
} hseKeyExportParams_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
extern uint32_t         gKeySecCount;
/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

hseSrvResponse_t ImportKeyReq(hseKeyImportParams_t *pImportKeyParams);
hseSrvResponse_t ExportKeyReq(hseKeyExportParams_t *pExportKeyParams);

hseSrvResponse_t ImportKeyReqMuChannel(uint8_t muInstance, uint8_t muChannel, hseKeyImportParams_t *pImportKeyParams);
hseSrvResponse_t ImportKeyReqMuChannelWithoutErase(uint8_t muInstance, uint8_t muChannel, bool_t bEraseKeyBeforeImport, hseKeyImportParams_t *pImportKeyParams);
hseSrvResponse_t ExportKeyReqMuChannel(uint8_t muInstance, uint8_t muChannel, hseKeyExportParams_t *pExportKeyParams);

/*******************************************************************************
 *                      Symmetric keys Import/Export
 ******************************************************************************/
hseSrvResponse_t ImportPlainSymKeyReq(hseKeyHandle_t targetKeyHandle,
                                      hseKeyType_t keyType, hseKeyFlags_t keyFlags,
                                      uint16_t keyByteLength, const uint8_t* pKey,
                                      hseAesBlockModeMask_t cipherModeMask);

hseSrvResponse_t ImportPlainSymKeyReqMuChannel(uint8_t u8MuInstance, uint8_t u8MuChannel, hseKeyHandle_t targetKeyHandle,
                                      hseKeyType_t keyType, hseKeyFlags_t keyFlags, hseSmrFlags_t smrFlags,
                                      uint16_t keyByteLength, const uint8_t* pKey, bool_t bEraseKeyBeforeImport,
                                      hseAesBlockModeMask_t cipherModeMask);

hseSrvResponse_t ImportEncryptedSymKeyReq(hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t cipherScheme,
                                          hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                          hseKeyFlags_t keyFlags, uint16_t keyByteLength,
                                          uint8_t *pKey, uint16_t encryptedKeyLength);

hseSrvResponse_t ImportAuthSymKeyReq(hseKeyHandle_t authKeyHandle, hseAuthScheme_t authScheme,
                                     hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                     hseKeyFlags_t keyFlags, uint16_t keyByteLength,
                                     uint8_t* pKey, uint16_t keyLength, uint8_t* pSign0,
                                     uint16_t sign0Length, uint8_t* pSign1, uint16_t sign1Length);

hseSrvResponse_t ImportAuthEncSymKeyReq(hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t cipherScheme,
                                        hseKeyHandle_t authKeyHandle, hseAuthScheme_t authScheme,
                                        hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                        hseKeyFlags_t keyFlags, uint16_t keyByteLength,
                                        uint8_t* pEncKey, uint16_t encKeyLength,
                                        uint8_t* pSign0, uint16_t sign0Length,
                                        uint8_t* pSign1, uint16_t sign1Length,
                                        uint8_t* pAuthContainer, uint16_t authContainerLen);

hseSrvResponse_t ExportPlainSymKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyInfo_t *pKeyInfo,
                                      uint8_t *pOutBuffer, uint16_t *pOutBufferLength);

hseSrvResponse_t ExportPlainSymKeyReqMuChannel(uint8_t muInstance, uint8_t muChannel,
    hseKeyHandle_t targetKeyHandle, hseKeyInfo_t *pKeyInfo, uint8_t *pOutBuffer, uint16_t *pOutBufferLength);

hseSrvResponse_t ExportSymKeyReqMuChannel(uint8_t muInstance, uint8_t muChannel,
    hseKeyHandle_t targetKeyHandle, hseKeyInfo_t *pKeyInfo, uint8_t *pOutBuffer, uint16_t *pOutBufferLength,
    hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t *pCipherScheme);

hseSrvResponse_t ExportEncryptedSymKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyInfo_t *pKeyInfo,
                                          uint8_t *pOutBuffer, uint16_t *pOutBufferLength,
                                          hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t cipherScheme);

hseSrvResponse_t ExportAuthSymKeyReq(hseKeyHandle_t authKeyHandle, hseAuthScheme_t authScheme,
                                     hseKeyHandle_t targetKeyHandle, hseKeyInfo_t *pKeyInfo,
                                     uint8_t *pOutBuffer, uint16_t *pOutBufferLength,
                                     uint8_t* pSign0, uint16_t *pSign0Length,
                                     uint8_t* pSign1, uint16_t *pSign1Length);

/*******************************************************************************
 * Function:    GenerateAesKey
 *
 * Description: This function generate a random AES key and it writes into desired location.
 *
 * Returns:
 HSE_SRV_RSP_OK                                HSE service successfully executed with no error
 HSE_SRV_RSP_INVALID_PARAM             The HSE request parameters are invalid (e.g misaligned, invalid range)
 HSE_SRV_RSP_SMALL_BUFFER                    The provided buffer is too small
 HSE_SRV_RSP_NOT_ENOUGH_SPACE              There is no enough space to perform operation (e.g. load a key)
 HSE_SRV_RSP_READ_FAILURE              The service request failed because read access was denied
 HSE_SRV_RSP_WRITE_FAILURE                 The service request failed because write access was denied
 HSE_SRV_RSP_STREAMING_MODE_FAILURE    The service request that uses streaming mode failed (e.g. UPDATES and FINISH steps do not use the same HSE interface ID and channel ID as START step)
 HSE_SRV_RSP_VERIFY_FAILED             HSE signals that a verification request fails (e.g. MAC and Signature verification)
 HSE_SRV_RSP_KEY_NOT_AVAILABLE     This error code is returned if a key is locked due to failed boot measurement or an active debugger
 HSE_SRV_RSP_KEY_INVALID               Specified key slot is either not valid or not available due to a key usage flags restrictions
 HSE_SRV_RSP_KEY_EMPTY                 Specified key slot is empty
 HSE_SRV_RSP_BUSY                      HSE request issued when the HSE is in busy state (on that HSE channel)
 HSE_SRV_RSP_MEMORY_FAILURE            Detect physical errors, flipped bits etc., during memory read or write operations
 HSE_SRV_RSP_GENERAL_ERROR         This error code is returned if an error not covered by the error codes above is detected inside HSE
 ******************************************************************************/
hseSrvResponse_t GenerateAesKey(hseKeyHandle_t *pTargetKeyHandle, uint8_t isNvm, uint16_t keyBitLen,
                                hseKeyFlags_t keyFlags,  hseAesBlockModeMask_t cipherBlockMode);

/*******************************************************************************
 * Function:    GenerateHmacKey
 *
 * Description: This function generate a random AES key and it writes into desired location.
 *
 * Returns:
 HSE_SRV_RSP_OK                                HSE service successfully executed with no error
 HSE_SRV_RSP_INVALID_PARAM             The HSE request parameters are invalid (e.g misaligned, invalid range)
 HSE_SRV_RSP_SMALL_BUFFER                    The provided buffer is too small
 HSE_SRV_RSP_NOT_ENOUGH_SPACE              There is no enough space to perform operation (e.g. load a key)
 HSE_SRV_RSP_READ_FAILURE              The service request failed because read access was denied
 HSE_SRV_RSP_WRITE_FAILURE                 The service request failed because write access was denied
 HSE_SRV_RSP_STREAMING_MODE_FAILURE    The service request that uses streaming mode failed (e.g. UPDATES and FINISH steps do not use the same HSE interface ID and channel ID as START step)
 HSE_SRV_RSP_VERIFY_FAILED             HSE signals that a verification request fails (e.g. MAC and Signature verification)
 HSE_SRV_RSP_KEY_NOT_AVAILABLE     This error code is returned if a key is locked due to failed boot measurement or an active debugger
 HSE_SRV_RSP_KEY_INVALID               Specified key slot is either not valid or not available due to a key usage flags restrictions
 HSE_SRV_RSP_KEY_EMPTY                 Specified key slot is empty
 HSE_SRV_RSP_BUSY                      HSE request issued when the HSE is in busy state (on that HSE channel)
 HSE_SRV_RSP_MEMORY_FAILURE            Detect physical errors, flipped bits etc., during memory read or write operations
 HSE_SRV_RSP_GENERAL_ERROR         This error code is returned if an error not covered by the error codes above is detected inside HSE
 ******************************************************************************/
hseSrvResponse_t LoadShePlainKey(const uint8_t *pKey);
hseSrvResponse_t GenerateHmacKey(hseKeyHandle_t *pTargetKeyHandle, uint8_t isNvmKey, uint16_t keyBitLen,
                                 hseKeyFlags_t keyFlags);

hseSrvResponse_t LoadSymKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseKeyType_t keyType,
                            uint16_t keyByteLength, const uint8_t* pKey);

hseSrvResponse_t LoadSymKeyWithCipherMode(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseKeyType_t keyType,
                                          uint16_t keyByteLength, const uint8_t* pKey, hseAesBlockModeMask_t cipherModeMask);

hseSrvResponse_t LoadAesKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyByteLength,
                            const uint8_t* pKey);

hseSrvResponse_t LoadAesKeyWithCipherMode(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyByteLength,
                                          const uint8_t* pKey, hseAesBlockModeMask_t cipherModeMask);

hseSrvResponse_t LoadTweakKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyByteLength,
                            const uint8_t* pKey, hseKeyFlags_t keyFlags,  hseAesBlockModeMask_t cipherModeMask);

hseSrvResponse_t LoadHmacKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyByteLength,
                             const uint8_t* pKey);

hseSrvResponse_t LoadSipHashKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyByteLength,
                                const uint8_t* pKey);
hseSrvResponse_t LoadPSK(hseKeyHandle_t *pTargetKeyHandle, uint16_t keyByteLength, const uint8_t *pKey);

hseSrvResponse_t LoadSmrAuthSymKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseKeyType_t keyType,
                                   uint16_t keyByteLength, const uint8_t *pKey);

hseSrvResponse_t LoadSmrAuthAesKey(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey,
                            uint16_t keyByteLength, const uint8_t* pKey);

hseSrvResponse_t LoadSmrHmacKey(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey,
                             uint16_t keyByteLength, const uint8_t* pKey);

hseSrvResponse_t LoadSmrDecKey(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey,
                            uint16_t keyByteLength, const uint8_t* pKey);

/*******************************************************************************
 *                                    RSA
 ******************************************************************************/

hseSrvResponse_t ImportPlainRsaKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                      hseKeyFlags_t keyFlags, HOST_ADDR pModulus,
                                      uint16_t modulusBitLength, HOST_ADDR pPublicExponent,
                                      uint16_t publicExponentLength, HOST_ADDR pPrivateExponent);

hseSrvResponse_t ExportPlainRsaPubKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyInfo_t* keyInfo,
                                         uint16_t* pModulusLength, const uint8_t* pModulus,
                                         uint16_t* pPublicExponentLength, const uint8_t* pPublicExponent,
                                         uint16_t* pPrivateExponentLength, const uint8_t* pPrivateExponent);

hseSrvResponse_t ImportEncryptedRsaKeyReq(hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t cipherScheme,
                                          hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                          hseKeyFlags_t keyFlags, HOST_ADDR pModulus,
                                          uint16_t modulusLength, HOST_ADDR pPublicExponent,
                                          uint16_t publicExponentLength, HOST_ADDR pPrivateExponent,
                                          uint16_t privateExponentLength);

hseSrvResponse_t LoadRsaPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyBitLen,
                                  const uint8_t *pModulus, uint16_t publicExponentLength,
                                  const uint8_t *pPublicExponent);

hseSrvResponse_t LoadSmrRsaPublicKey(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey, uint16_t keyBitLen,
                                  const uint8_t *pModulus, uint16_t publicExponentLength,
                                  const uint8_t *pPublicExponent);

hseSrvResponse_t LoadRsaPrivateKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, uint16_t keyBitLen,
                                   const uint8_t *pModulus, uint16_t publicExponentLength,
                                   const uint8_t *pPublicExponent, const uint8_t *pPrivateExponent);

hseSrvResponse_t LoadRsaPair(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey, uint16_t keyBitLen,
                                   const uint8_t *pModulus, uint16_t publicExponentLength,
                                   const uint8_t *pPublicExponent, const uint8_t *pPrivateExponent);

hseSrvResponse_t LoadRsaCertKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseKeyInfo_t* pKeyInfo,
                                uint16_t modulusLength, const uint8_t *pModulus,
                                uint16_t publicExpLength, const uint8_t *pPublicExponent,
                                uint16_t containerLength, const uint8_t *pContainer);

/*******************************************************************************
 *                                  Classic DH
 ******************************************************************************/
#ifdef HSE_SPT_CLASSIC_DH
hseSrvResponse_t ImportClassicDhKeyReq
(
    hseKeyHandle_t targetKeyHandle,
    bool_t bIsKeyPair,
    hseKeyFlags_t keyFlags,
    uint16_t keyBitLength,
    const uint8_t* pPrimeModulus,
    const uint8_t* pPubKey,
    uint16_t privKeyBitLength,
    const uint8_t* pPrivKey
);

hseSrvResponse_t LoadClassicDhPublicKey(hseKeyHandle_t *pTargetKeyHandle,
                                        uint16_t keyBitLength,
                                        const uint8_t* pPrimeModulus,
                                        const uint8_t* pPublicKey);

hseSrvResponse_t LoadClassicDhKeyPair(hseKeyHandle_t *pTargetKeyHandle,
                                      uint16_t keyBitLength,
                                      const uint8_t* pPrimeModulus,
                                      const uint8_t* pPublicKey,
                                      uint16_t privKeyBitLength,
                                      const uint8_t* pPrivateKey);

hseSrvResponse_t ExportPlainClassicDhPubKeyReq(hseKeyHandle_t targetKeyHandle,
                                               hseKeyInfo_t* pKeyInfo,
                                               uint16_t* pPrimeModulusLength,
                                               uint8_t* pPrimeModulus,
                                               uint16_t* pPubKeyLength,
                                               uint8_t* pPubKey);
#endif

#ifdef HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN
hseSrvResponse_t GenerateClassicDhKey(uint32_t *pTargetKeyHandle,
                                      uint16_t keyBitLen,
                                      const uint8_t* pPrimeModulus,
                                      uint16_t baseGByteLen,
                                      const uint8_t* pBaseG);
#endif
/*******************************************************************************
 *                                  ECC
 ******************************************************************************/
hseSrvResponse_t ImportFormattedEccKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                          hseKeyFlags_t keyFlags, hseEccCurveId_t eccCurveId,
                                          uint16_t keyBitLength, hseEccKeyFormat_t keyFormat,
                                          const uint8_t* pPubKey, const uint8_t* pPrivKey);

hseSrvResponse_t ImportFormattedCertEccKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                              hseKeyFlags_t keyFlags, hseEccCurveId_t eccCurveId,
                                              uint16_t keyBitLength, hseEccKeyFormat_t keyFormat,
                                              const uint8_t* pPubKey, uint16_t containerLen,
                                              const uint8_t* pContainer);

hseSrvResponse_t ImportEccKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                 hseKeyFlags_t keyFlags, hseEccCurveId_t eccCurveId,
                                 uint16_t keyBitLength, const uint8_t* pPubKey,
                                 const uint8_t* pPrivKey);

hseSrvResponse_t ExportPlainFormattedEccPubKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyInfo_t* pKeyInfo,
                                         uint16_t* pPubKeyLength, uint8_t* pPubKey, hseEccKeyFormat_t eccKeyFormat);

inline hseSrvResponse_t ExportPlainEccPubKeyReq(hseKeyHandle_t targetKeyHandle, hseKeyInfo_t* pKeyInfo,
                                         uint16_t* pPubKeyLength, uint8_t* pPubKey)
{
    return ExportPlainFormattedEccPubKeyReq(targetKeyHandle, pKeyInfo, pPubKeyLength, pPubKey, HSE_KEY_FORMAT_ECC_PUB_RAW);
}


hseSrvResponse_t ImportEncryptedEccKeyReq(hseKeyHandle_t cipherKeyHandle, hseCipherScheme_t cipherScheme,
                                          hseKeyHandle_t targetKeyHandle, hseKeyType_t keyType,
                                          hseKeyFlags_t keyFlags, hseEccCurveId_t eccCurveId,
                                          uint16_t keyBitLength, const uint8_t* pPubKey,
                                          const uint8_t* pPrivKey, uint16_t encryptedPrivKeyLength);

hseSrvResponse_t LoadEccKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                            uint16_t keyBitLength);

hseSrvResponse_t LoadEccPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccCompressedPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccUncompressedPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccCompressedExternalPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccUncompressedExternalPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccPublicKeyForKeyExchange(hseKeyHandle_t targetKeyHandle, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadSmrEccPublicKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey);

hseSrvResponse_t LoadEccPrivateKey(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                   uint16_t keyBitLength, const uint8_t* pPrivKey);

hseSrvResponse_t LoadEccKeyPair(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                uint16_t keyBitLength, const uint8_t* pPubKey,
                                const uint8_t* pPrivKey);

hseSrvResponse_t LoadSmrEccKeyPair(hseKeyHandle_t* pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                uint16_t keyBitLength, const uint8_t* pPubKey,
                                const uint8_t* pPrivKey);

hseSrvResponse_t LoadEccKeyPairForKeyExchange(hseKeyHandle_t *pTargetKeyHandle, bool_t isNvmKey, hseEccCurveId_t eccCurveId,
                                  uint16_t keyBitLength, const uint8_t* pPubKey,
                                  const uint8_t* pPrivKey);

/*******************************************************************************
 *                              Other KM Services
 ******************************************************************************/
hseSrvResponse_t EraseKeyReq
(
    hseKeyHandle_t        keyHandle, //HSE_INVALID_KEY_HANDLE to delete more then one key
    hseEraseKeyOptions_t  eraseKeyOptions
);

#ifdef HSE_B
hseSrvResponse_t EraseNVMDataReq(void);
#endif

hseSrvResponse_t GetKeyInfo(hseKeyHandle_t keyHandle, hseKeyInfo_t* reqKeyInfo);
hseSrvResponse_t GetKeyInfoMuChannel(uint8_t u8MuInstance, uint8_t u8MuChannel,
     hseKeyHandle_t keyHandle, hseKeyInfo_t* reqKeyInfo);

#ifdef HSE_SPT_KEY_VERIFY
hseSrvResponse_t VerifySHA
(
    const uint8_t   *pKey,      /* IN*/
    hseKeyHandle_t* pKeyHandle/* IN*/
);
#endif
/* ======================================================================================== */


#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_IMPORT_KEY_H_ */

/** @} */
