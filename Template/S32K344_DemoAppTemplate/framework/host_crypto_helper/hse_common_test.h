/**
*   @file    hse_common_test.h
*
*   @brief   Function definitions to test the key loading
*   @details
*
*   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
*   @{
*/
/*==================================================================================================
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


#ifndef _HSE_COMMON_TEST_H_
#define _HSE_COMMON_TEST_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "hse_interface.h"
#include "hse_tracing.h"

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
extern const int testBufferSize;

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b))? (a):(b))
#endif
#if !defined(CHAR_ARRAY_SIZE_WITHOUT_TRAILING_ZERO)
#define CHAR_ARRAY_SIZE_WITHOUT_TRAILING_ZERO(x) (sizeof(x) / sizeof((x)[0]) - 1)
#endif

typedef uint32_t  testAccessMode_t;

#define   MODE_ONEPASS  ((testAccessMode_t)0U)
#define   MODE_START    ((testAccessMode_t)1U)
#define   MODE_UPDATE  ((testAccessMode_t)2U)
#define   MODE_FINISH  ((testAccessMode_t)3U)

#define DATALENGTH_AES 16U
#define DATALENGTH_TDES 8U

#define MU0         0
#define MU1         1

#if (HSE_NUM_OF_MU_INSTANCES > 2)
#define MU2         2
#define MU3         3
#endif

#if (HSE_NUM_OF_MU_INSTANCES > 4)
#define MU4         4
#define MU5         5
#define MU6         6
#define MU7         7
#endif

#ifdef HSE_SPT_TDES
    #define TDES_KEY_HANDLE    RAM_TDES192_KEY0
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

typedef enum eccKeyType_tag
{
    eEccKeyType_Pair,
    eEccKeyType_Public,
    eEccKeyType_PublicExternal
}eccKeyType_t;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


extern uint8_t testOutput[];
extern uint8_t tagOutput[];
extern uint8_t testOutput_Dec[];


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief         This function use to test the RSA key loading.
* @details
* \param[in]   key
*           Pointer to the key.
* \param[in]   keySize
*           Key size.
*
* \return  Error Status
*/

hseSrvResponse_t RSALoadKey(uint32_t keyHandle, const uint8_t* pmodules, const uint8_t* pubE,
                                 uint32_t pmodulessize, uint32_t pubESize,uint32_t keyBitLen, uint8_t keyType, uint16_t keyFlag);


/**
* @brief         This function use to test the key loading.
* @details
* \param[in]   key
* 			Pointer to the key.
* \param[in]   keySize
* 			Key size.
*
* \return  Error Status
*/
hseSrvResponse_t AesLoadKey(uint32_t keyHandle, const uint8_t* key, uint32_t keySize,uint8_t keyType);

/**
* @brief         This function formats the key catalogs.
* @details
*
*/
void TestFormatKeyCatalogs(void);
#if 0
void TestFormatKeyCatalogs2(void);
void TestFormatKeyCatalogs3(void);
#endif
void TestFormatKeyCatalogsNegative(void);

void TestSBFormatKeyCatalogs(void);
void TestImportExportSymKeys(void);
void TestImportExportSymKeysNegative(void);

void TestImportExportRSAKeys(void);
void TestImportRsa1024Cert(void);
void TestEraseKeys(void);

void TestEraseNVMData(void);

void TestImportInvalidPubKey(void);
void TestImportInvalidKeyPairs(void);

void TestDebugProtectedKey_CustDel(void);
void TestDebugProtectedKey_OemProd(void);
void TestDebugProtectedKey_InField(void);

#if defined(HSE_SPT_FORMAT_KEY_CATALOGS) && !defined (HSE_GM)
void Test_host_key_allocator(void);
#endif /* HSE_SPT_FORMAT_KEY_CATALOGS */

#if defined(HSE_H) && defined(HSE_S32S2XX)
void TestXRDCConfig(void);
#endif

/**
* @brief         Key Sanity checks

* @details      Sanity checks for key utilities:
                - Get Key info
                - import/export keys
                - erase  RAM key
*/
void TestKeySanityChecks(void);


hseSrvResponse_t EccLoadKey(uint32_t keyHandle, const uint8_t* publicKey, const uint8_t* privateKey, uint32_t keyBitLen, eccKeyType_t eccKeyType, uint32_t eccCurveId);

#ifdef HSE_TRACING
void T32_TracingStart(uint8_t mu, uint8_t ch);
#define TRACE_START(mu, ch)   T32_TracingStart(mu, ch)
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _HSE_COMMON_TEST_H_ */

/** @} */


