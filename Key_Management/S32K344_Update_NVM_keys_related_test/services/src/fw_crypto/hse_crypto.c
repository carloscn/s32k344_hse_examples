/**
*   @file    hse_crypto.c
*
*   @brief   Example of HSE cryptographic services.
*   @details Example of sending crypto services requests to HSE over MU (sym/asym; sync/async).
*
*   @addtogroup hse_crypto
*   @{
*/
/*==================================================================================================
*
*   Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*=============================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=============================================================================*/
#include "hse_demo_app_services.h"
#include "hse_global_variables.h"
#include "hse_host.h"
#include "hse_host_aead.h"
#include "hse_host_cipher.h"
#include "hse_host_kdf.h"
#include "hse_host_sign.h"
#include "hse_host_import_key.h"
#include "hse_host_mac.h"
#include "hse_host_sys_authorization.h"
#include "hse_keymgmt_common_types.h"
#include "hse_host_ecc.h"
#include "host_stm.h"
#include "hse_monotonic_cnt.h"
#include "string.h"
#include "hse_b_catalog_formatting.h"
#include "global_defs.h"
#include "hse_host_cmac_with_counter.h"
#include "hse_host_sign.h"
#include "hse_keys_allocator.h"

/*=============================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

//Argument for the async hash callback function
typedef struct
{
    uint8_t u8MuInstance;
    uint8_t u8MuChannel;
} hashCallbackParams_t;

/*
 * ============================================================================
 *                                       LOCAL MACROS
 * ============================================================================
 */
#define CUST_SUPER_USER_MODE(hseStatus) \
    ( HSE_STATUS_CUST_SUPER_USER == \
(hseStatus & (HSE_STATUS_CUST_SUPER_USER|HSE_STATUS_OEM_SUPER_USER)))

#define OEM_SUPER_USER_MODE(hseStatus) \
    (HSE_STATUS_OEM_SUPER_USER == \
        (hseStatus & (HSE_STATUS_CUST_SUPER_USER|HSE_STATUS_OEM_SUPER_USER)))

#define IN_FIELD_USER_MODE(hseStatus) \
  (0UL == (hseStatus & (HSE_STATUS_CUST_SUPER_USER|HSE_STATUS_OEM_SUPER_USER)))
  
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif
#define CHALLENGE_LENGTH            (32UL)
#define SIGN_LENGTH_MAX             (512UL)
#define PSS_SALT_LENGTH             (20UL)
#define BUFFER_SIZE                 (512U)
#define NUMBER_OF_ASYNC_REQ         (3U)
#define MAX_REQS_FOR_FAST_CMAC		(50U)
#if !defined(CHAR_ARRAY_SIZE_WITHOUT_TRAILING_ZERO)
#define CHAR_ARRAY_SIZE_WITHOUT_TRAILING_ZERO(x) (sizeof(x) / sizeof((x)[0]) - 1)
#endif

/*
 * ============================================================================
 *                            LOCAL CONSTANTS
 * ============================================================================
*/
//HMAC key 1 - initial and second version - Update NVM key example
const uint8_t hmacKeyInitial[] =
{ 0x9a, 0x8c, 0xd4, 0x01, 0x8b, 0x1d, 0xe0, 0xaf, 0x06, 0xbb, 0xd7, 0x7a, 0xd3,
        0x28, 0x94, 0xb0, 0x36, 0xb2, 0x1e, 0xc7, 0x29, 0xbb, 0xd1, 0x09, 0x7b,
        0x34, 0xf2, 0x0e, 0x07, 0x0e, 0xbb, 0x29, 0xf9, 0x18, 0xda, 0xb1, 0x02,
        0xe0, 0x60, 0x4f, 0x19, 0x19, 0xc4, 0x58, 0x05, 0x80, 0xbf, 0x69, 0x2e,
        0xad
};
const uint32_t hmacKeyInitialLength = ARRAY_SIZE(hmacKeyInitial);
const uint8_t hmacKeyUpdated[] =
{ 0xf8, 0x69, 0x02, 0xe5, 0xe5, 0xdb, 0x47, 0x8e, 0xc6, 0xe2, 0x78, 0x69, 0x27,
        0x28, 0xa8, 0x12, 0xc4, 0xcd, 0x87, 0x45, 0xf9, 0x0a, 0x7d, 0x9f, 0x79,
        0x15, 0xf5, 0xa9, 0x43, 0x45, 0xfc, 0x12, 0xd2, 0x77, 0x0a, 0x3c, 0x94,
        0xb0, 0x1f, 0xfb, 0x9e, 0x04, 0x12, 0x99, 0x9e, 0xb6, 0x26, 0x1d, 0x11,
        0xa0
};

//CUST_SUPER_USER authorization key (RSA-2048 Key pair)
const uint8_t rsa2048CustAuthKeyModulus[] =
{ 0xcc, 0x83, 0x0b, 0x10, 0xc5, 0xf2, 0xa6, 0x2d, 0xd5, 0xd7, 0x07, 0x55, 0x4f,
        0x14, 0x9b, 0x6f, 0x52, 0x94, 0xe4, 0x82, 0x88, 0x9d, 0x8a, 0x48, 0xe7,
        0x5e, 0x25, 0x39, 0x08, 0xcf, 0xb6, 0x4e, 0x4d, 0xf4, 0xae, 0x22, 0x5e,
        0xee, 0x00, 0x31, 0x9e, 0xe7, 0x89, 0xc1, 0xba, 0x57, 0x21, 0xef, 0x0a,
        0x64, 0x9a, 0x8c, 0xd4, 0x01, 0x8b, 0x1d, 0xe0, 0xaf, 0x06, 0xbb, 0xd7,
        0x7a, 0xd3, 0x28, 0x94, 0xb0, 0x36, 0xb2, 0x1e, 0xc7, 0x29, 0xbb, 0xd1,
        0x09, 0x7b, 0x34, 0xf2, 0x0e, 0x07, 0x0e, 0xbb, 0x29, 0xf9, 0x18, 0xda,
        0xb1, 0x02, 0xe0, 0x60, 0x4f, 0x19, 0x19, 0xc4, 0x58, 0x05, 0x80, 0xbf,
        0x69, 0x2e, 0xad, 0x54, 0x14, 0x05, 0x39, 0x4d, 0xa0, 0xa9, 0xad, 0x79,
        0x1a, 0xe8, 0x39, 0xd0, 0xae, 0x60, 0x4b, 0x48, 0x0b, 0x5d, 0xe5, 0xe9,
        0x0f, 0x88, 0xa4, 0xdc, 0x14, 0x43, 0x4f, 0xb6, 0x9c, 0xa9, 0xb4, 0x05,
        0xc7, 0xe9, 0xc0, 0x4a, 0x70, 0x85, 0x51, 0x5c, 0x8a, 0x21, 0x85, 0x2a,
        0x61, 0xf6, 0xd3, 0x6e, 0xd7, 0x66, 0x23, 0x81, 0x4c, 0x42, 0x3b, 0xcc,
        0x4f, 0x22, 0xea, 0xfb, 0xa0, 0x95, 0x46, 0x14, 0x60, 0x2b, 0xa5, 0xe9,
        0x48, 0xaa, 0x75, 0x31, 0x07, 0xb3, 0x14, 0xad, 0x1c, 0xe6, 0x94, 0xea,
        0x99, 0xf0, 0x90, 0xbc, 0xb4, 0xe2, 0x00, 0x74, 0x1a, 0xf5, 0x44, 0x5f,
        0xfa, 0x55, 0xc9, 0x76, 0x34, 0x80, 0xea, 0x6c, 0xee, 0x5d, 0xac, 0x0b,
        0xe3, 0x0c, 0x31, 0xe7, 0xd1, 0xc5, 0xeb, 0xae, 0x20, 0x6a, 0x3c, 0x2d,
        0x59, 0x55, 0xca, 0x29, 0x17, 0xa7, 0x4b, 0xec, 0x76, 0xea, 0xe0, 0x29,
        0x37, 0x67, 0xf0, 0x09, 0x0f, 0x92, 0x93, 0x92, 0x46, 0x1a, 0x6d, 0x86,
        0x89, 0x6c, 0x9e, 0xce, 0x56, 0xad, 0xa9, 0x12, 0xe6, 0x79, 0x56, 0x6c,
        0x23, 0x67, 0x29
};
const uint8_t rsa2048CustAuthKeyPubExp[] = { 0x01, 0x00, 0x01 };
const uint8_t rsa2048CustAuthKeyPrivExp[] =
{ 0x4b, 0x60, 0x85, 0x44, 0x92, 0x60, 0xe3, 0xe5, 0x02, 0xea, 0xf5, 0x35, 0xf9,
        0x26, 0xb4, 0x3f, 0x6c, 0xa5, 0x9a, 0x2f, 0x8e, 0x60, 0xda, 0x66, 0x12,
        0x78, 0xbd, 0xa9, 0x6e, 0xd8, 0xf7, 0xed, 0x96, 0x87, 0xf7, 0x62, 0x8d,
        0xb0, 0x94, 0xfb, 0xb5, 0x00, 0xcb, 0xe2, 0x4e, 0x66, 0xed, 0x07, 0xe8,
        0xc1, 0xb9, 0xc0, 0xec, 0x27, 0x01, 0x7a, 0x6a, 0xa4, 0xb8, 0x0b, 0xa5,
        0xd9, 0x0c, 0x58, 0xe9, 0xac, 0xa5, 0x0c, 0x33, 0x91, 0xde, 0x8c, 0xed,
        0xf7, 0xdb, 0xa4, 0x61, 0x0e, 0xd0, 0x85, 0x1a, 0x70, 0xd6, 0xf1, 0xd5,
        0x30, 0xe6, 0xc9, 0x82, 0x55, 0xc4, 0xff, 0x9d, 0x41, 0x80, 0x0d, 0xba,
        0xfe, 0xee, 0x88, 0x4d, 0xf3, 0xef, 0x14, 0xf6, 0xca, 0x9f, 0x9f, 0x63,
        0x82, 0x8a, 0x53, 0x3c, 0xd9, 0xf8, 0x7d, 0xe6, 0xb8, 0xe1, 0xcb, 0xea,
        0x81, 0xa2, 0x30, 0x79, 0x39, 0x32, 0xb1, 0x56, 0xca, 0x0e, 0x9d, 0xbe,
        0xe5, 0x3d, 0x02, 0x09, 0x2f, 0x4c, 0xa0, 0x68, 0x43, 0x04, 0xd6, 0xad,
        0xe8, 0x26, 0xd8, 0x32, 0x7c, 0x8d, 0x68, 0x73, 0x7d, 0xdb, 0x00, 0xf0,
        0x63, 0x37, 0xc6, 0x1d, 0x63, 0xc1, 0x0e, 0x57, 0x4f, 0xeb, 0xcf, 0x22,
        0x96, 0xaf, 0x1f, 0xdc, 0xf4, 0x7a, 0x96, 0xc3, 0xfd, 0xb9, 0x18, 0xe7,
        0x5f, 0x2c, 0x43, 0x05, 0xad, 0xa4, 0x20, 0x84, 0x60, 0x04, 0x48, 0x54,
        0xd2, 0x0c, 0x45, 0x45, 0xb1, 0x5f, 0xac, 0x59, 0x0a, 0xff, 0xc7, 0x7d,
        0x9f, 0x47, 0xca, 0xa6, 0x04, 0xe5, 0xc7, 0xa4, 0x05, 0xd9, 0x07, 0x75,
        0xd0, 0x0f, 0xef, 0x70, 0x8b, 0x8c, 0xca, 0x73, 0x2b, 0x78, 0xc4, 0x9c,
        0x2d, 0xab, 0x84, 0xb7, 0x24, 0x05, 0x4a, 0x04, 0xce, 0x41, 0x7b, 0x32,
        0xcf, 0x9e, 0x5c, 0x1a, 0x4c, 0x1a, 0x27, 0x1d, 0x19, 0x96, 0x47, 0x5b,
        0x21, 0xd5, 0x81
};

const uint8_t KdfSP800_108_FixedInfo_1[] = { 0x5a, 0xc3, 0x73, 0xd4, 0x2e, 0xd9, 0x24, 0x27, 0xd8, 
0xff, 0x6c, 0xff, 0xf7, 0xea, 0xe1, 0x3d, 0x66, 0xd3, 0xc7, 0xe5, 0x36, 0xcc, 0x74, 0x98, 0x59, 
0xe2, 0xa4, 0x9e, 0x3e, 0xea, 0x2a, 0xd8, 0x46, 0xc9, 0xfb, 0xb7, 0xdd, 0xd9, 0x9a, 0x1e, 0x6a,
0x54, 0xa8, 0x9a, 0x87, 0xdb, 0x98, 0xdb, 0x6b, 0x82, 0x29, 0xf5, 0x77, 0xb5, 0x52, 0xe0, 0x9a, 0xee, 
0xd5, 0xe6 };

//Fixed Info for KDF example
uint8_t KdfSP800_108_FixedInfo_2[] =
{ 0x5a, 0xc3, 0x73, 0xd4, 0x2e, 0xd9, 0x24, 0x27, 0xd8, 0xff, 0x6c, 0xff, 0xf7,
        0xea, 0xe1, 0x3d, 0x66, 0xd3, 0xc7, 0xe5, 0x36, 0xcc, 0x74, 0x98, 0x59,
        0xe2, 0xa4, 0x9e, 0x3e, 0xea, 0x2a, 0xd8, 0x46, 0xc9, 0xfb, 0xb7, 0xdd,
        0xd9, 0x9a, 0x1e, 0x6a, 0x54, 0xa8, 0x9a, 0x87, 0xdb, 0x98, 0xdb, 0x6b,
        0x82, 0x29, 0xf5, 0x77, 0xb5, 0x52, 0xe0, 0x9a, 0xee, 0xd5, 0xe6 };

const uint8_t eccP256PubKey[] =
{ 0xd6, 0x60, 0x62, 0x71, 0x13, 0x1e, 0x7e, 0x7e, 0x61, 0x7a, 0x81, 0xaa, 0x11,
        0xf0, 0x9e, 0x7e, 0xd5, 0x63, 0x11, 0x82, 0x88, 0x23, 0x36, 0x7a, 0x86,
        0x9b, 0x45, 0x40, 0x40, 0xb3, 0xf9, 0x05, 0xcf, 0x48, 0x97, 0x76, 0x61,
        0x31, 0xaa, 0x8b, 0x7f, 0x80, 0x45, 0x3a, 0x15, 0xbf, 0x90, 0xf7, 0x51,
        0x78, 0x78, 0x57, 0x9d, 0x5a, 0x4f, 0x97, 0x3a, 0xea, 0x5b, 0xb1, 0x15,
        0x42, 0xe0, 0x7f
};
const uint8_t secp256v1PubKey_2[]  = {0xF5, 0xCF, 0xC6, 0x06, 0xEF, 0x6E, 0x52, 0x0F, 0xA9, 0xBA,
 0xDA, 0x8F, 0x03,0x39, 0x71, 0x17, 0x5C, 0xF2, 0xCB, 0xD5, 0x16, 0x31, 0xE0, 0x30, 0x03, 0xE4, 0xE7, 
 0x00, 0x30, 0x79, 0xC1, 0xB2, 0x7B, 0xE8, 0xF8, 0x4C, 0xE4, 0xA0, 0xEA, 0x71, 0x0B, 0x60, 0x37, 0xD9,
 0xF6, 0x23, 0x47, 0xFF, 0x99, 0x7D, 0x36,0xAC, 0xD6, 0x51, 0x87, 0x67, 0x03, 0xFD, 0x06, 0x74, 0xF2, 
 0xE3, 0xAC, 0xF0};

const uint8_t secp256v1Key[] = {0x48, 0x26, 0xD8, 0x96, 0xB2, 0x17, 0x4E, 0x9F, 0x82, 0x21, 0x95, 0x11, 0x67, 0xE5, 0x64, 0xE8, 0xE7, 0x9A, 0x17, 0x55, 0x71, 0xE0, 0x2B, 0xD5, 0x7F, 0xDC, 0x4E, 0x0C, 0x4D, 0xD6, 0x31, 0xA4, 0x09, 0x2E, 0xC5, 0x52, 0x6E, 0xD0, 0x2B, 0xEF, 0xFD, 0xDD, 0x6D, 0x76, 0xA9, 0x60, 0x1D, 0xB5, 0xAE, 0x8B, 0x5B, 0x9F, 0x38, 0xC5, 0xA0, 0x2D, 0x6E, 0x73, 0x86, 0xA7, 0xBD, 0xAF, 0xF0, 0xA3};

const uint8_t eccP256PrivKey[] =
{ 0x00, 0xd0, 0x07, 0xe1, 0xb9, 0xaf, 0xcc, 0x31, 0x2e, 0xec, 0x9c, 0xec, 0xff,
        0xa0, 0x28, 0x07, 0x52, 0xbb, 0xd1, 0x95, 0x31, 0x82, 0xed, 0xef, 0x12,
        0xf3, 0xfc, 0x36, 0x6e, 0x8f, 0x43, 0x56
};

#ifdef HSE_SPT_SHA2_256
const uint8_t testMsgSha256Secp256v1_r[] = {0x4C, 0x82, 0x16, 0xA9, 0xEB, 0xEE, 0xFB, 0xAC, 0xD3, 0x68, 0x34, 0x73, 0x43, 0x00, 0x2D, 0xC5, 0xEE, 0x78, 0x15, 0x96, 0xC5, 0x71, 0xBD, 0xD7, 0x41, 0x3B, 0x4B, 0x45, 0x5C, 0x77, 0xDD, 0x90};
const uint8_t testMsgSha256Secp256v1_s[] = {0x42, 0x32, 0x76, 0xB4, 0xA5, 0x04, 0x15, 0x3F, 0xB1, 0x80, 0x67, 0xFC, 0x54, 0xEE, 0x6E, 0xFE, 0x88, 0x86, 0xC9, 0x56, 0xB2, 0x33, 0x70, 0x01, 0xF2, 0xBD, 0xBE, 0xC6, 0x57, 0x22, 0x93, 0x66};
#endif
const uint8_t testMsg[] = "The quick brown fox jumps over the lazy dog.";
const uint8_t message[] =
        "The surest way to corrupt a youth is to instruct him to hold in higher esteem those who think alike than those who think differently - Friedrich Nietzsche 2020";

//IV example (used for AES CBC and AEAD example)
#ifdef HSE_SPT_GMAC  
static const uint8_t iv[] =
{ 0xff, 0xbc, 0x51, 0x6a, 0x8f, 0xbe, 0x61, 0x52, 0xaa, 0x42, 0x8c, 0xdd, 0x80,
        0x0c, 0x06, 0x2d
};
#endif

const uint8_t aesEcbPlaintext[] =
{ 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
        0x93, 0x17, 0x2a
};

const uint8_t aesEcbCiphertext[] =
{ 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24,
        0x66, 0xef, 0x97
};

const uint32_t aesEcbPlaintextLength = ARRAY_SIZE(aesEcbPlaintext);
const uint32_t aesEcbCiphertextLength = ARRAY_SIZE(aesEcbCiphertext);

const uint8_t KdfSP800_108_SrcKey_1[] = { 0x00, 0x93, 0x00, 0xd2, 0x65, 0xd1, 0xf1, 0xb2, 0x8b, 0x50, 0x5d, 0xcc, 0xc1, 0x62, 0xf4, 0xf8 };
//Hash Data
static const uint8_t sha1Message[] =
{ 0x97, 0x77, 0xcf, 0x90, 0xdd, 0x7c, 0x7e, 0x86, 0x35, 0x06 };
static const uint8_t sha1Hash[] =
{ 0x05, 0xc9, 0x15, 0xb5, 0xed, 0x4e, 0x4c, 0x4a, 0xff, 0xfc, 0x20, 0x29, 0x61,
        0xf3, 0x17, 0x43,0x71, 0xe9, 0x0b, 0x5c
};
static const uint8_t sha256Message[] =
{ 0x59, 0xeb, 0x45, 0xbb, 0xbe, 0xb0, 0x54, 0xb0, 0xb9, 0x73, 0x34, 0xd5, 0x35,
        0x80, 0xce, 0x03, 0xf6, 0x99
};
static const uint8_t sha256Hash[] =
{ 0x32, 0xc3, 0x8c, 0x54, 0x18, 0x9f, 0x23, 0x57, 0xe9, 0x6b, 0xd7, 0x7e, 0xb0,
        0x0c, 0x2b, 0x9c, 0x34, 0x1e, 0xbe, 0xba, 0xcc, 0x29, 0x45, 0xf9, 0x78,
        0x04, 0xf5, 0x9a, 0x93, 0x23, 0x82, 0x88
};

static const uint8_t sha512Message[] =
{ 0x16, 0xb1, 0x70, 0x74, 0xd3, 0xe3, 0xd9, 0x75, 0x57, 0xf9, 0xed, 0x77, 0xd9,
        0x20, 0xb4, 0xb1, 0xbf, 0xf4, 0xe8, 0x45, 0xb3, 0x45, 0xa9, 0x22
};
static const uint8_t sha512Hash[] =
{ 0x68, 0x84, 0x13, 0x45, 0x82, 0xa7, 0x60, 0x04, 0x64, 0x33, 0xab, 0xcb, 0xd5,
        0x3d, 0xb8, 0xff, 0x1a, 0x89, 0x99, 0x58, 0x62, 0xf3, 0x05, 0xb8, 0x87,
        0x02, 0x0f, 0x6d, 0xa6, 0xc7, 0xb9, 0x03, 0xa3, 0x14, 0x72, 0x1e, 0x97,
        0x2b, 0xf4, 0x38, 0x48, 0x3f, 0x45, 0x2a, 0x8b, 0x09, 0x59, 0x62, 0x98,
        0xa5, 0x76, 0xc9, 0x03, 0xc9, 0x1d, 0xf4, 0xa4, 0x14, 0xc7, 0xbd, 0x20,
        0xfd, 0x1d, 0x07
};

#ifdef HSE_SPT_BURMESTER_DESMEDT 
static const uint8_t ECC_SECP224R1_PRIME_P[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
};

//Elliptic curve coefficient a 
static const uint8_t ECC_SECP224R1_CURVEPARAM_A[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE 
};

//Elliptic curve coefficient b 
static const uint8_t ECC_SECP224R1_CURVEPARAM_B[] =
{
    0xB4, 0x05, 0x0A, 0x85, 0x0C, 0x04, 0xB3, 0xAB, 0xF5, 0x41, 0x32, 0x56, 0x50, 0x44, 0xB0, 0xB7, 
    0xD7, 0xBF, 0xD8, 0xBA, 0x27, 0x0B, 0x39, 0x43, 0x23, 0x55, 0xFF, 0xB4 
};
//Elliptic curve base point G(x,y) 
static const uint8_t ECC_SECP224R1_BASEPOINT[] =
{
    0xB7, 0x0E, 0x0C, 0xBD, 0x6B, 0xB4, 0xBF, 0x7F, 0x32, 0x13, 0x90, 0xB9, 0x4A, 0x03, 0xC1, 0xD3, 
    0x56, 0xC2, 0x11, 0x22, 0x34, 0x32, 0x80, 0xD6, 0x11, 0x5C, 0x1D, 0x21, 0xBD, 0x37, 0x63, 0x88, 
    0xB5, 0xF7, 0x23, 0xFB, 0x4C, 0x22, 0xDF, 0xE6, 0xCD, 0x43, 0x75, 0xA0, 0x5A, 0x07, 0x47, 0x64, 
    0x44, 0xD5, 0x81, 0x99, 0x85, 0x00, 0x7E, 0x34 
};

//Elliptic curve order n 
static const uint8_t ECC_SECP224R1_ORDER_N[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0xA2, 
    0xE0, 0xB8, 0xF0, 0x3E, 0x13, 0xDD, 0x29, 0x45, 0x5C, 0x5C, 0x2A, 0x3D 
};

static const uint8_t fcaA1[] = 
{
    0x33, 0xb5, 0x8b, 0xf6, 0xc8, 0x4a, 0xb9, 0x7e, 0xa4, 0xd6, 0xde, 0x9a, 0x59, 0x25, 0x25, 0xdf, 
    0xa2, 0xf7, 0x24, 0x50, 0x23, 0x64, 0x2c, 0xe6, 0xf4, 0xd4, 0x90, 0xbb
};

static const uint8_t fcaA2[] =
{
    0x0c, 0x24, 0xfe, 0xa3, 0xe5, 0x04, 0x95, 0xd2, 0xb4, 0x13, 0xdb, 0xac, 0xfe, 0x88, 0xd2, 0x13, 
    0x89, 0x4f, 0x9e, 0x70, 0x98, 0xca, 0x17, 0x91, 0xad, 0xde, 0xca, 0xc7
};

static const uint8_t fcaA3[] =
{
    0x33, 0xb5, 0xbc, 0x34, 0x6f, 0x4a, 0xa4, 0x51, 0x33, 0x7a, 0x6e, 0x34, 0xed, 0x5a, 0xd0, 0x32, 
    0x96, 0xd4, 0xda, 0xb1, 0xbe, 0x44, 0x93, 0x65, 0xac, 0xfe, 0xab, 0x58
};

static const uint8_t fcaZ1[] =
{
    0x1E, 0xC5, 0x91, 0xD3, 0x19, 0xD9, 0x87, 0x2E, 0x2F, 0x62, 0xC6, 0x9D, 0xC1, 0xC4, 0xCA, 0xE6, 
    0x7D, 0x3E, 0xBD, 0x03, 0x19, 0x20, 0xB9, 0xBB, 0x7D, 0x06, 0xE9, 0x94, 0x51, 0xEC, 0x05, 0xC4, 
    0x1E, 0x12, 0x53, 0xB4, 0x28, 0x29, 0xA5, 0x13, 0xA8, 0x30, 0x17, 0x45, 0x2A, 0x96, 0x91, 0xBB, 
    0xE2, 0x3C, 0xB3, 0x97, 0x0D, 0x71, 0xD9, 0xC3
};

static const uint8_t fcaZ2[] =
{
    0x0E, 0x82, 0x0B, 0x7F, 0x49, 0x2E, 0x06, 0x41, 0x4A, 0x66, 0xED, 0xB8, 0x2B, 0x7C, 0x1B, 0xAB, 
    0xB5, 0xEC, 0xB3, 0x67, 0x30, 0xCC, 0xBD, 0x69, 0x29, 0x99, 0xD5, 0x33, 0x82, 0xE8, 0x95, 0x98, 
    0x01, 0x69, 0x27, 0x30, 0xB2, 0x5C, 0xD3, 0x5F, 0x71, 0xC8, 0x94, 0x2E, 0x5C, 0x4D, 0x5A, 0xCA, 
    0x80, 0x2B, 0x3A, 0x13, 0xEC, 0x92, 0x84, 0x6C
};

static const uint8_t fcaZ3[] =
{
    0xC0, 0x83, 0x55, 0x21, 0x78, 0xB0, 0xAC, 0x17, 0x3E, 0xF5, 0xCB, 0xF9, 0xF5, 0xB6, 0x16, 0xD7, 
    0x70, 0x64, 0x49, 0x28, 0xC2, 0x01, 0xF1, 0xBB, 0x7A, 0xA3, 0xDA, 0x1C, 0x89, 0x6C, 0x52, 0x0F, 
    0x3C, 0x4D, 0x94, 0xEB, 0xA4, 0xC8, 0xAD, 0xCB, 0x35, 0x33, 0x6E, 0x55, 0x58, 0x25, 0xCD, 0x8A, 
    0xB3, 0x10, 0xF1, 0x6A, 0x7A, 0xC7, 0xDB, 0xAC
};

static const uint8_t fcaX1[] =
{
    0x85, 0xF2, 0x74, 0x78, 0xDF, 0x00, 0x7E, 0x15, 0xD1, 0x01, 0xDB, 0x07, 0xE3, 0x59, 0x2E, 0x0A, 
    0xEC, 0x73, 0xCF, 0xEC, 0x96, 0x0C, 0x16, 0x70, 0xD0, 0xA3, 0xDE, 0xF2, 0xBB, 0xC2, 0xE9, 0x14, 
    0x5F, 0xB3, 0x46, 0xDC, 0xA9, 0xDB, 0xBB, 0xE0, 0x4A, 0x22, 0x9C, 0x9E, 0x12, 0x84, 0xBB, 0x67, 
    0x0C, 0x3F, 0x5D, 0x5B, 0xA9, 0x64, 0x73, 0xE8
};

static const uint8_t fcaX2[] =
{
    0x8E, 0xCC, 0xBB, 0x99, 0x0D, 0xF9, 0x42, 0x99, 0x09, 0x2A, 0xD4, 0xF9, 0x96, 0x4F, 0x17, 0x0E, 
    0xE3, 0xBE, 0x6A, 0x79, 0xA8, 0xEA, 0xA2, 0xCC, 0x5B, 0xD0, 0x1D, 0x06, 0xAE, 0x98, 0xC1, 0xDB, 
    0xF4, 0x85, 0x17, 0xA8, 0x1B, 0xF9, 0xB0, 0x44, 0x31, 0x2A, 0x42, 0x1B, 0x2B, 0x5C, 0x1A, 0x2B, 
    0xE6, 0xD4, 0xA1, 0x23, 0x0A, 0x9C, 0xB8, 0x77
};


static const uint8_t fcaX3[] =
{
    0x65, 0x8F, 0x92, 0xEB, 0xBD, 0x00, 0x3F, 0x33, 0x02, 0x76, 0xB3, 0x6D, 0xA5, 0x26, 0xF8, 0x29, 
    0x07, 0x17, 0x0B, 0xEF, 0x76, 0x64, 0xF0, 0xD9, 0xF3, 0xD6, 0x20, 0x24, 0xC4, 0x82, 0x0C, 0xAB, 
    0x8B, 0x3C, 0xBF, 0x84, 0xFF, 0xFF, 0xC8, 0x3A, 0x21, 0x57, 0xFD, 0xE4, 0x49, 0x21, 0x47, 0x85, 
    0xFF, 0xBB, 0x24, 0x85, 0x72, 0x26, 0x19, 0x76
};

static const uint8_t fcaK[] =
{
    0xA4, 0xF7, 0xCE, 0x86, 0xB4, 0x8B, 0xB1, 0xBF, 0x59, 0xC3, 0xE0, 0x69, 0xE6, 0x89, 0x9B, 0x5C, 
    0xD0, 0x1B, 0xF9, 0xF7, 0xE7, 0xBC, 0xCC, 0x0A, 0x3C, 0xB3, 0x37, 0x17, 0x3E, 0xAC, 0x91, 0x38, 
    0x2D, 0xCC, 0xA4, 0xCE, 0xF6, 0x4F, 0x2B, 0x2E, 0x92, 0xDD, 0x44, 0x6E, 0x50, 0x50, 0x52, 0xBF, 
    0x44, 0x33, 0x0F, 0xE8, 0x0F, 0x78, 0x91, 0x2F
};
#endif

#ifdef HSE_SPT_ECC_COMPRESSED_KEYS
typedef struct ecdsaVerifTestCase_tag
{
    uint32_t       curveId;
    uint32_t       hashAlgo;
    const uint8_t *pMsg;
    uint8_t        msgLen;
    const uint8_t *pPubKey;
    const uint8_t *r;
    uint16_t       rLen;
    const uint8_t *s;
    uint16_t       sLen;
}ecdsaVerifTestCase_t;
#endif

static const hseHashAlgo_t hashAlgos[] =
{
    HSE_HASH_ALGO_SHA_1,
    HSE_HASH_ALGO_SHA2_256,
    HSE_HASH_ALGO_SHA2_512
};

static const uint8_t *hashMessages[] =
{
    sha1Message,
    sha256Message,
    sha512Message
};

static const uint32_t hashMessagesLengths[] =
{
    ARRAY_SIZE(sha1Message),
    ARRAY_SIZE(sha256Message),
    ARRAY_SIZE(sha512Message)
};

static const uint8_t *hashExpectedOutput[] =
{
    sha1Hash,
    sha256Hash,
    sha512Hash
};

static const uint32_t hashLength[] =
{
    ARRAY_SIZE(sha1Hash),
    ARRAY_SIZE(sha256Hash),
    ARRAY_SIZE(sha512Hash),
};
/*
 * ============================================================================
 *                            LOCAL VARIABLES
 * ============================================================================
*/
extern hseKeyHandle_t aesCmacKeyHandle;
extern hseKeyHandle_t AesNVMKeyHandle;
uint8_t testoutput[BUFFER_SIZE] = {0};
uint8_t hashTestOutput[NUMBER_OF_ASYNC_REQ][BUFFER_SIZE] = {0};
uint32_t hashTestOutputLength[NUMBER_OF_ASYNC_REQ] = {BUFFER_SIZE,
        BUFFER_SIZE, BUFFER_SIZE};
hashCallbackParams_t callbackParams[HSE_NUM_OF_MU_INSTANCES]
                                    [HSE_NUM_OF_CHANNELS_PER_MU];
uint8_t KdfNXP_KDF_Output[8] = {0U};
#ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static uint8_t signR[256] = {0};
static uint8_t signS[256] = {0};
static uint32_t signRLen = ARRAY_SIZE(signR);
static uint32_t signSLen = ARRAY_SIZE(signS);
#endif
/*
 * ============================================================================
 *                               GLOBAL CONSTANTS
 * ============================================================================
*/
/*
 * ============================================================================
 *                               GLOBAL VARIABLES
 * ============================================================================
*/

volatile CryptoServicesTestStatus_t gCryptoServicesExecuted = CRYPTO_SERVICE_SUCCESS_NONE;
volatile CryptoServicesTestStartedStatus_t  gCryptoServicesStarted =  CRYPTO_SERVICE_NONE;
static uint32_t numberOfResponses = 0;
volatile hseSrvResponse_t asyncResponses[HSE_NUM_OF_MU_INSTANCES]
                                         [HSE_NUM_OF_CHANNELS_PER_MU] = {0};
//variable for time calculation for Fast CMAC generate and verify keys
volatile uint32_t FastCmacGenerateTime = 0U;
volatile uint32_t FastCmacVerifyTime = 0U;
volatile uint32_t TotalFastCmacGenerateTime = 0U;
volatile uint32_t TotalFastCmacVerifyTime = 0U;
hseKeyHandle_t srcKey = HSE_INVALID_KEY_HANDLE;
hseKeyHandle_t targetSharedSecretKey = HSE_INVALID_KEY_HANDLE;

#if defined(HSE_SPT_EC_SEC_SECP256R1)&&defined(HSE_SPT_ECC_COMPRESSED_KEYS)
ecdsaVerifTestCase_t ecdsaVerifTestCases[] =
{
    #if defined(HSE_SPT_SHA2_256) && defined(HSE_SPT_EC_SEC_SECP256R1)
    {
        .curveId  = HSE_EC_SEC_SECP256R1,
        .hashAlgo = HSE_HASH_ALGO_SHA2_256,
        .pMsg     = testMsg,
        .msgLen   = CHAR_ARRAY_SIZE_WITHOUT_TRAILING_ZERO(testMsg),
        .pPubKey  = secp256v1Key,
        .r        = testMsgSha256Secp256v1_r,
        .rLen     = ARRAY_SIZE(testMsgSha256Secp256v1_r),
        .s        = testMsgSha256Secp256v1_s,
        .sLen     = ARRAY_SIZE(testMsgSha256Secp256v1_s)
    },
#endif
};
#endif



/* kdf */
#ifdef HSE_SPT_KDF_SP800_108
  hseKeyInfo_t KdfSP800_108_SECRET_KEY_INFO_1 =
{
    .keyType = HSE_KEY_TYPE_AES,
    .keyBitLen = 128UL,
    .keyFlags = (HSE_KF_USAGE_DERIVE | HSE_KF_ACCESS_EXPORTABLE)
};

hseKey_t KdfSP800_108_SECRET_KEY_1 = {
    .keyHandle = HSE_INVALID_KEY_HANDLE,
    .pKeyInfo = &KdfSP800_108_SECRET_KEY_INFO_1,
    .keyValue = {
        .pKey2 = (uint8_t *)KdfSP800_108_SrcKey_1,
        .keyLen2 = ARRAY_SIZE(KdfSP800_108_SrcKey_1),
    },
};

hseKeyImportParams_t KdfSP800_108_ImportSecret_1 =
{
    .pKey = &KdfSP800_108_SECRET_KEY_1
};

/* kdf */
hseKdfSP800_108Scheme_t KdfSP800_108_Scheme_1 =
{
    .mode = HSE_KDF_SP800_108_COUNTER,
    .counterByteLength = HSE_KDF_SP800_108_COUNTER_LEN_DEFAULT,
    .kdfCommon = {
        .srcKeyHandle = HSE_INVALID_KEY_HANDLE,
        .targetKeyHandle = HSE_INVALID_KEY_HANDLE,
        .keyMatLen = BITS_TO_BYTES(512UL),
        .kdfPrf = HSE_KDF_PRF_CMAC,
        .pInfo = (HOST_ADDR)KdfSP800_108_FixedInfo_1,
        .infoLength = ARRAY_SIZE(KdfSP800_108_FixedInfo_1)
    }
};

#endif
  
/*
 * ============================================================================
 *                        LOCAL FUNCTION PROTOTYPES
 * ============================================================================
*/
static void HSE_HashRequestCallback(hseSrvResponse_t srvResponse, void *pArg);
static void VerifyOutput( void );
/* ============================================================================
 *                              LOCAL FUNCTIONS
 * ============================================================================
*/
/******************************************************************************
 * Function:    HSE_HashRequestCallback
 * Description: Callback of Hash Request. Logs and checks the HSE response.
 ******************************************************************************/
static void HSE_HashRequestCallback(hseSrvResponse_t srvResponse,void* pArg)
{
   /*  Argument is a callbackInfo_t pointer which contains the MU interface
     * and the channel on which the request was sent*/
    hashCallbackParams_t *pCallbackParams = (hashCallbackParams_t *) pArg;
    uint8_t u8MuInstance = pCallbackParams->u8MuInstance;
    uint8_t u8MuChannel = pCallbackParams->u8MuChannel;

     /*Log the response*/
    asyncResponses[u8MuInstance][u8MuChannel] = srvResponse;
    numberOfResponses += 1;

     /*Check the HSE response*/
    if (HSE_SRV_RSP_OK != srvResponse)
    {

    }
}

/******************************************************************************
 * Function:    HSE_HashDataNonBlocking
 * Description: Non-blocking hash request.
 *****************************************************************************/
hseSrvResponse_t HSE_HashDataNonBlocking
(
    uint8_t u8MuInstance,
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseHashAlgo_t hashAlgo,
    const uint8_t *pInput,
    uint32_t inputLength,
    uint8_t *pHash,
    uint32_t *pHashLength
)
{
    uint8_t u8MuChannel = 1U;
    hseTxOptions_t asyncTxOptions;
    hseSrvDescriptor_t *pHseSrvDesc;
    hseHashSrv_t *pHashSrv;
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    //Complete the service descriptor placed in shared memory
    pHseSrvDesc = &gHseSrvDesc[0U][u8MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHashSrv = &(pHseSrvDesc->hseSrv.hashReq);

    pHseSrvDesc->srvId      = HSE_SRV_ID_HASH;
    pHashSrv->accessMode    = accessMode;
    pHashSrv->streamId      = streamId;
    pHashSrv->hashAlgo      = hashAlgo;
    pHashSrv->inputLength   = inputLength;
    pHashSrv->pInput        = PTR_TO_HOST_ADDR(pInput);
    pHashSrv->pHash         = PTR_TO_HOST_ADDR(pHash);
    pHashSrv->pHashLength   = PTR_TO_HOST_ADDR(pHashLength);

    //Complete callback info and async txOptions*/
    callbackParams[u8MuInstance][u8MuChannel].u8MuInstance  = u8MuInstance;
    callbackParams[u8MuInstance][u8MuChannel].u8MuChannel   = u8MuChannel;
    asyncTxOptions.txOp              = HSE_TX_ASYNCHRONOUS;
    asyncTxOptions.pfAsyncCallback   = &(HSE_HashRequestCallback);
    asyncTxOptions.pCallbackpArg     =
            (void *)(&(callbackParams[u8MuInstance][u8MuChannel]));

    //Send the request asynchronously
    srvResponse = HSE_Send(u8MuInstance,u8MuChannel,asyncTxOptions,pHseSrvDesc);
    return srvResponse;
}

/******************************************************************************
 * Function:    VerifyOutput
 * Description: Check hash requests outputs match the expected.
 *****************************************************************************/
static void VerifyOutput(void)
{
     /*Check output length and data are matching expected hash*/
    for (uint8_t i = 0U; i < NUMBER_OF_ASYNC_REQ; i++)
    {
        if( (hashLength[i] != hashTestOutputLength[i]) ||
            (0 != memcmp(hashTestOutput[i], hashExpectedOutput[i], hashLength[i])) )
        {
            goto exit;
        }
    }
 exit:
    return;
}

/******************************************************************************
 * Function:    SetCustAuthorizationKey
 * Description: Sets the authorization key for CUST_SUPER_USER.
 *****************************************************************************/
#ifdef HSE_SPT_RSA
hseSrvResponse_t SetCustAuthorizationKey( void )
{
    hseSrvResponse_t hseResponse;

    /* Set the CUST_SUPER_USER authorization key
     * This is an example as NVM keys CANNOT be imported
     * in plain unless the slot is empty (see `HSE_UpdateNvmKey_Example`)
     */
    hseResponse = ImportPlainRsaKeyReq(
            HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE0,
            HSE_KEY_TYPE_RSA_PUB,
            (HSE_KF_USAGE_VERIFY | HSE_KF_USAGE_AUTHORIZATION),
            (HOST_ADDR)rsa2048CustAuthKeyModulus,
           (ARRAY_SIZE(rsa2048CustAuthKeyModulus)*8),
            (HOST_ADDR)rsa2048CustAuthKeyPubExp,
            ARRAY_SIZE(rsa2048CustAuthKeyPubExp),
            (HOST_ADDR) NULL
            );
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    /* Set a copy of authorization key for signature generation using HSE
     * (over challenge) Intended use case - Sign challenge via external means
     */
    hseResponse = ImportPlainRsaKeyReq(
            HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0,
            HSE_KEY_TYPE_RSA_PAIR,
            HSE_KF_USAGE_SIGN,
            (HOST_ADDR)rsa2048CustAuthKeyModulus,
            (ARRAY_SIZE(rsa2048CustAuthKeyModulus)*8),
            (HOST_ADDR)rsa2048CustAuthKeyPubExp,
            ARRAY_SIZE(rsa2048CustAuthKeyPubExp),
            (HOST_ADDR)rsa2048CustAuthKeyPrivExp
            );

    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

exit:
    return hseResponse;
}
#endif



/******************************************************************************
 * Function:    AuthorizeCust
 * Description: Authorization Request/Response sequence for CUST SU
 *****************************************************************************/
#ifdef HSE_SPT_RSA
static hseSrvResponse_t AuthorizeCust( void )
{
    hseSrvResponse_t hseResponse;

    uint8_t challenge[CHALLENGE_LENGTH] = {0U};
    uint8_t sign0[SIGN_LENGTH_MAX] = {0U};
    uint32_t signLen0;
   /*  Auth scheme used for CUST SU authorization */
    hseAuthScheme_t rsaPssSignScheme = {
        .sigScheme.signSch = HSE_SIGN_RSASSA_PSS,
        .sigScheme.sch.rsaPss.hashAlgo = HSE_HASH_ALGO_SHA2_512,
        .sigScheme.sch.rsaPss.saltLength = PSS_SALT_LENGTH
    };

    /* Send the authorization request */
    memset(challenge, 0x00U, CHALLENGE_LENGTH);
    hseResponse = HSE_SysAuthorizationReq(HSE_SYS_AUTH_ALL, HSE_RIGHTS_SUPER_USER,
        HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE0, &rsaPssSignScheme, challenge);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    /* Sign the challenge using the pair private key of the authorization key
     * Intended use case - Sign challenge via external means
     */
    signLen0 = SIGN_LENGTH_MAX;
    memset(sign0, 0x00U, SIGN_LENGTH_MAX);
    hseResponse = RsaPssSignSrv(HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0, PSS_SALT_LENGTH,
            HSE_HASH_ALGO_SHA2_512, CHALLENGE_LENGTH,
            challenge, FALSE, 0U, &signLen0, sign0);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    /* Send the authorization response */
    hseResponse = HSE_SysAuthorizationResp(sign0, NULL, signLen0, 0UL);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }
exit:
    return hseResponse;
}
#endif

/******************************************************************************
 * Function:    BDComputeSecondPublicKey
 * Description: Burmester Desmudt Protocol compute Public Key
 *****************************************************************************/

#ifdef HSE_SPT_BURMESTER_DESMEDT   
static hseSrvResponse_t BDComputeSecondPublicKey( hseKeyHandle_t deviceKeyHandle, hseKeyHandle_t pubKeyHandle )
{
    hseSrvResponse_t hseResponse;
    uint8_t localMuIf = 0U;
    uint8_t localMuChannelIdx = 1U;

    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseBurmesterDesmedtSrv_t *pBdReq;
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_BURMESTER_DESMEDT;
    pBdReq = &(pHseSrvDesc->hseSrv.burmesterDesmedtReq);

    pBdReq->bdStep                = HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY;
    pBdReq->deviceKeyHandle       = deviceKeyHandle;
    pBdReq->pubKeyHandle          = pubKeyHandle;

    hseResponse = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);

    return hseResponse;
}

#endif


/******************************************************************************
 * Function:    HSE_Aes_Example
 * Description:  Example of AES requests sent synchronously.
 *****************************************************************************/
static hseSrvResponse_t HSE_Aes_Example(void)
{
    hseKeyHandle_t aesEcbKeyHandle = HSE_DEMO_RAM_AES128_KEY0;    
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    /* import keys for AES operation before calling HSE_Aes_Example fn*/
    srvResponse = ImportPlainSymKeyReq(
            aesEcbKeyHandle ,
            HSE_KEY_TYPE_AES,
            (HSE_KF_USAGE_ENCRYPT|HSE_KF_USAGE_DECRYPT),
            aesEcbKeyLength,
            aesEcbKey,
            0U);

    ASSERT(HSE_SRV_RSP_OK == srvResponse);

    /* --------- AES ECB Encrypt Request --------- */

    memset(testoutput, 0, BUFFER_SIZE);

    /* Send the request */
    srvResponse = AesEncrypt( aesEcbKeyHandle, HSE_CIPHER_BLOCK_MODE_ECB,
        0UL, aesEcbPlaintextLength, aesEcbPlaintext, testoutput, HSE_SGT_OPTION_NONE);

    /* Check response and output */
    if( (HSE_SRV_RSP_OK != srvResponse) ||
        (0 != memcmp(testoutput, aesEcbCiphertext, aesEcbCiphertextLength)) )
    {
        goto exit;
    }

    /* --------- AES ECB Decrypt Request --------- */

    memset(testoutput, 0, BUFFER_SIZE);

    /* Send the request */
    srvResponse = AesDecrypt(aesEcbKeyHandle, HSE_CIPHER_BLOCK_MODE_ECB,
             0UL, aesEcbCiphertextLength, aesEcbCiphertext, testoutput, HSE_SGT_OPTION_NONE);

     /*Check response and output*/
    if( (HSE_SRV_RSP_OK != srvResponse) ||
        (0 != memcmp(testoutput, aesEcbPlaintext, aesEcbPlaintextLength)))
    {
        goto exit;
    }
   
    /* --------- AES Fast CMAC Generate/Verify Requests with STM measuring (50 reqs) --------- */
    for (uint32_t i = 0; i < MAX_REQS_FOR_FAST_CMAC; i++)
    {
		memset(testoutput, 0, BUFFER_SIZE);

		/* enable timer before starting Fast CMAC key generate operation */
		EnableStm();
		/* Generate */
		srvResponse = AesFastCmacGenerate(AesNVMKeyHandle,
		 NUM_OF_ELEMS(aesEcbPlaintext)*8U, aesEcbPlaintext, (16U*8U), testoutput);

		/* get counter value and then disable timer */
		FastCmacGenerateTime = MeasureStm();
		DisbleStm();
        
		/* calculate time when STM is derived from PLL of frequency 48MHz */
		TotalFastCmacGenerateTime += (FastCmacGenerateTime/48);
		if(HSE_SRV_RSP_OK != srvResponse)
			goto exit;

		/* enable timer before starting Fast CMAC key verify operation */
		EnableStm();
		/* Verify */
		srvResponse = AesFastCmacVerify(AesNVMKeyHandle,
			NUM_OF_ELEMS(aesEcbPlaintext)*8U, aesEcbPlaintext, (16U*8U), testoutput);
		/*get time and then disable timer*/
		FastCmacVerifyTime = MeasureStm();
		DisbleStm();
		TotalFastCmacVerifyTime += (FastCmacVerifyTime/48);
		if(HSE_SRV_RSP_OK != srvResponse)
			goto exit;
    }

    FastCmacGenerateTime = TotalFastCmacGenerateTime/MAX_REQS_FOR_FAST_CMAC;

    FastCmacVerifyTime = TotalFastCmacVerifyTime/MAX_REQS_FOR_FAST_CMAC;
    
exit:
   return srvResponse;
}

/******************************************************************************
 * Function:    HSE_HashAsync_Example
 * Description: Example of Hash requests sent asynchronously,
 *              Hashes - SHA-1, SHA2-256, SHA2-512.
 *****************************************************************************/
static hseSrvResponse_t HSE_HashAsync_Example(void)
{
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    /* Enable Receive Interrupt on all channels */
    for(uint8_t mu = 0U; mu < HSE_NUM_OF_MU_INSTANCES; ++mu)
        HSE_MU_EnableInterrupts(mu, HSE_INT_RESPONSE, 0xFFFFUL);

    /* -------- Hash Requests --------- */

    /* Send requests asynchronously */
    for (uint8_t i = 0U; i < NUMBER_OF_ASYNC_REQ; i++)
    {
        srvResponse = HSE_HashDataNonBlocking(MU0, HSE_ACCESS_MODE_ONE_PASS,
            0, hashAlgos[i], hashMessages[i], hashMessagesLengths[i],
            hashTestOutput[i], &(hashTestOutputLength[i]));
        //Verify that transmission was successful
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            break;
        }

        /* Adding some delay in between */
        DelayStm(0x2000U);
    }
    /* Wait all responses */
    while (numberOfResponses < NUMBER_OF_ASYNC_REQ) {};

    /* Responses are checked in callback - Check outputs */
    VerifyOutput();
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_FastCmacwithCounter_Example
 * Description: Example of Fast CMAC with  sent Synchronously
 * 
 *****************************************************************************/
#ifdef HSE_SPT_MONOTONIC_COUNTERS
static hseSrvResponse_t HSE_FastCmacwithCounter_Example(void)
{
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    uint32_t rpBitSize          = 40UL;
    uint32_t TxnodecntIdx       = HSE_NUM_OF_MONOTONIC_COUNTERS - 3UL;
    uint32_t RxnodecntIdx       = HSE_NUM_OF_MONOTONIC_COUNTERS - 2UL;
    uint32_t volatileCnt       = 0xFFFFFFFFUL;
    uint32_t hseCounter        = 0UL;

    /* Configure Node A */
    srvResponse = MonotonicCnt_Config(TxnodecntIdx, rpBitSize);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Configure Node B */
    srvResponse = MonotonicCnt_Config(RxnodecntIdx, rpBitSize);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Configure Node A Counter as a default value */
    srvResponse = MonotonicCnt_Increment(TxnodecntIdx, 0x800000UL);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Configure Node B Counter as a default value */
    srvResponse = MonotonicCnt_Increment(RxnodecntIdx, 0x800000UL);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Generate CMAC with Counter on Node A */
    srvResponse = CmacWithCounter(AesNVMKeyHandle, HSE_AUTH_DIR_GENERATE,TxnodecntIdx,0,
    NUM_OF_ELEMS(aesEcbPlaintext)*8U, aesEcbPlaintext, (16U*8U), testoutput, &volatileCnt,HSE_SGT_OPTION_NONE);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    ASSERT(0x800001UL == (volatileCnt &0x00FFFFFF) );

    /* Read Counter & check for the expected value */
    srvResponse = MonotonicCnt_Read(TxnodecntIdx, (uint32_t)&hseCounter);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    ASSERT(0x800001UL == hseCounter);

    /* Verify CMAC with Counter on Node B */
    srvResponse = CmacWithCounter(AesNVMKeyHandle, HSE_AUTH_DIR_VERIFY,RxnodecntIdx, 0x0U,
    NUM_OF_ELEMS(aesEcbPlaintext)*8U, aesEcbPlaintext, (16U*8U), testoutput, &hseCounter,HSE_SGT_OPTION_NONE);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

exit:
    return srvResponse;
}
#endif
/******************************************************************************
 * Function:    HSE_BurmesterDesmedt_Example
 * Description: Example of Burmester Desmedt sent Synchronously
 * 
 *****************************************************************************/
#ifdef HSE_SPT_BURMESTER_DESMEDT 
static hseSrvResponse_t HSE_BurmesterDesmedt_Example(void)
{
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseKeyInfo_t keyInfo = {0};
    uint8_t sharedSecret[448];
    uint16_t sharedSecretLen = 56;
    hseKeyHandle_t hmacKeyHandle = HSE_DEMO_RAM_HMAC_KEY0;
    hseKeyHandle_t BDSharedSecretKeyHandle = HSE_INVALID_KEY_HANDLE;
    srvResponse = ParseKeyCatalogs();
    if(HSE_SRV_RSP_OK !=srvResponse)
    goto exit;
    /* load P224 curve into HSE */
    srvResponse = LoadEccUserCurve(HSE_EC_USER_CURVE1,
                                 224, 224,
                                 ECC_SECP224R1_CURVEPARAM_A, ECC_SECP224R1_CURVEPARAM_B,
                                 ECC_SECP224R1_BASEPOINT, ECC_SECP224R1_ORDER_N,
                                 ECC_SECP224R1_PRIME_P);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /**************************** Node 1 Test ********************************************/

    /* Load Node 1's Device Key */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PAIR,
                (HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE),
                HSE_EC_USER_CURVE1,
                224,
                fcaZ1,
                fcaA1
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z3 in Slot 0 (Node 2 Predecessor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ3,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z2 in Slot 1 (Node 2 Successor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT1,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ2,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 1 */
    srvResponse = BDComputeSecondPublicKey(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load X2 in Slot 3 */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT3,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaX2,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 2 */
    srvResponse = BDComputeSharedSecret(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, 3U, &BDSharedSecretKeyHandle ,RAM_KEY,224);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = GetKeyInfo(BDSharedSecretKeyHandle, &keyInfo);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(448 == keyInfo.keyBitLen);   

    /* Copy the shared secret to an exportable HMAC slot */
    keyInfo.keyType = HSE_KEY_TYPE_HMAC;
    keyInfo.keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE);
    keyInfo.keyBitLen = 448;
    srvResponse = HSEKeyDeriveExtractKeyReq(BDSharedSecretKeyHandle, 0U,&hmacKeyHandle, RAM_KEY, keyInfo );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = ExportPlainSymKeyReq(HSE_DEMO_RAM_HMAC_KEY0, &keyInfo, sharedSecret, &sharedSecretLen);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(56U == sharedSecretLen);
    ASSERT(0U == memcmp(sharedSecret, fcaK, 56U));

    /**************************** Node 2 Test ********************************************/

    /* Load Node 1's Device Key */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PAIR,
                (HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE),
                HSE_EC_USER_CURVE1,
                224,
                fcaZ2,
                fcaA2
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z3 in Slot 0 (Node 2 Predecessor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ1,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z2 in Slot 1 (Node 2 Successor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT1,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ3,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 1 */
    srvResponse = BDComputeSecondPublicKey(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load X2 in Slot 3 */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT3,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaX3,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 2 */
    srvResponse = BDComputeSharedSecret(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, 3U, &BDSharedSecretKeyHandle,RAM_KEY,224);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = GetKeyInfo(BDSharedSecretKeyHandle, &keyInfo);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(448 == keyInfo.keyBitLen);   

    /* Copy the shared secret to an exportable HMAC slot */
    keyInfo.keyType = HSE_KEY_TYPE_HMAC;
    keyInfo.keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE);
    keyInfo.keyBitLen = 448;
    srvResponse = HSEKeyDeriveExtractKeyReq(BDSharedSecretKeyHandle, 0U, &hmacKeyHandle, RAM_KEY,keyInfo );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = ExportPlainSymKeyReq(HSE_DEMO_RAM_HMAC_KEY0, &keyInfo, sharedSecret, &sharedSecretLen);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(56U == sharedSecretLen);
    ASSERT(0U == memcmp(sharedSecret, fcaK, 56U));

    /**************************** Node 3 Test ********************************************/

    /* Load Node 1's Device Key */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PAIR,
                (HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE),
                HSE_EC_USER_CURVE1,
                224,
                fcaZ3,
                fcaA3
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z3 in Slot 0 (Node 2 Predecessor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ2,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load Z2 in Slot 1 (Node 2 Successor) */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT1,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaZ1,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 1 */
    srvResponse = BDComputeSecondPublicKey(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    /* Load X2 in Slot 3 */
    srvResponse = ImportEccKeyReq(
                HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT3,
                HSE_KEY_TYPE_ECC_PUB,
                HSE_KF_USAGE_EXCHANGE | HSE_KF_ACCESS_EXPORTABLE,
                HSE_EC_USER_CURVE1,
                224,
                fcaX1,
                NULL
            );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }
    
    /* Perform BD Step 2 */
    srvResponse = BDComputeSharedSecret(HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, 3U, &BDSharedSecretKeyHandle,RAM_KEY,224);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = GetKeyInfo(BDSharedSecretKeyHandle, &keyInfo);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(448 == keyInfo.keyBitLen);   

    /* Copy the shared secret to an exportable HMAC slot */
    keyInfo.keyType = HSE_KEY_TYPE_HMAC;
    keyInfo.keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE);
    keyInfo.keyBitLen = 448;
    srvResponse = HSEKeyDeriveExtractKeyReq( BDSharedSecretKeyHandle, 0U, &hmacKeyHandle,RAM_KEY,keyInfo );
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    srvResponse = ExportPlainSymKeyReq(HSE_DEMO_RAM_HMAC_KEY0, &keyInfo, sharedSecret, &sharedSecretLen);
    if(HSE_SRV_RSP_OK != srvResponse)
    {
        goto exit;
    }

    ASSERT(56U == sharedSecretLen);
    ASSERT(0U == memcmp(sharedSecret, fcaK, 56U));

exit:
    return srvResponse;
}
#endif
/******************************************************************************
* Function:    HSE_Ecdsa_Example
* Description: Example of ECC key pair generation and ECDSA Sign/Verify operations
*       Send a request to generate ECC exportable key pair, usable for signing and verification.
*      - Send request to HSE & Verify the response is OK
*      - Initialize a request to ECDSA sign with the
*        generated key a test vector
*      - Send request to HSE & Verify the response is OK
*      - Initialize a request to ECDSA verify with the
*        generated key the signed test vector
 *****************************************************************************/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static hseSrvResponse_t HSE_Ecdsa_Example(void)
{
    hseSrvResponse_t hseResponse;
    hseKeyHandle_t eccKeyPairRAMKeyHandle = HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE;
    
    //Generate an exportable ECC key pair in RAM (ephemeral ECDH)
    hseResponse = GenerateEccKey(
            &eccKeyPairRAMKeyHandle,
            RAM_KEY,
            HSE_EC_SEC_SECP256R1,
            HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;

    /* ECDSA Sign request */
     hseResponse = EcdsaSign(
             HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
             HSE_HASH_ALGO_SHA2_256,
             ARRAY_SIZE(message), message,FALSE, 0U,
             &signRLen, signR, &signSLen, signS);
     if(HSE_SRV_RSP_OK != hseResponse)
         goto exit;

     /* ECDSA Verify request */
     hseResponse = EcdsaVerify(
              HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE, HSE_HASH_ALGO_SHA2_256,
             ARRAY_SIZE(message), message, FALSE, 0U,
             &signRLen, signR, &signSLen, signS);
     if(HSE_SRV_RSP_OK != hseResponse)
         goto exit;

exit:
    return hseResponse;
}
#endif
/*******************************************************************************
 * Function:    TestCompressedEccKeyExport
 *
 * Description: Test that a given key can be exported in compressed format
 *
 * Returns:     nothing
 ********************************************************************************/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
 static hseSrvResponse_t TestCompressedEccKeyExport(uint8_t curveId, const uint8_t* pKey)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    uint8_t keyBuf[BITS_TO_BYTES(HSE_MAX_ECC_KEY_BITS_LEN) + 1];//67
    uint16_t keyBufLen = sizeof(keyBuf);//67 bytes
    hseKeyInfo_t keyInfo;
    uint8_t signByte;
    uint8_t keyByteLen = BITS_TO_BYTES(KeyBitLen(curveId));//32 bytes
    hseKeyHandle_t eccPublicRAMKeyHandle = HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE;
    hseStatus = LoadEccPublicKey(&eccPublicRAMKeyHandle  , 
                                 RAM_KEY,
                                 curveId,
                                 KeyBitLen(curveId), 
                                 pKey);
     if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;
    hseStatus = ExportPlainFormattedEccPubKeyReq(HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE  , 
                                                 &keyInfo, 
                                                 &keyBufLen, 
                                                 keyBuf, 
                                                 HSE_KEY_FORMAT_ECC_PUB_COMPRESSED);
    if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;

    //key length must be curve byte length + 1
    if((1 + keyByteLen) != keyBufLen)
    {  //33                //33
    hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
    goto exit;
    }

    // check that x coordinate matches
    if(0 != (memcmp(keyBuf + 1, pKey, keyByteLen)))
    {
    hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
    goto exit;
    }

    // check that the sign of the y coordinate matches
    if(0x01 == (pKey[2 * keyByteLen - 1] & 0x01))
    {
        signByte = 0x03;
    }
    else
    {
        signByte = 0x02;
    }
    if(signByte!= keyBuf[0])
    {
    hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
    goto exit;
    }
    exit:
    return hseStatus;
}
#endif

/*******************************************************************************
 * Function:    TestUncompressedEccKeyExport
 *
 * Description: Test that a given key can be exported in uncompressed format
 *
 * Returns:     nothing
 ********************************************************************************/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static hseSrvResponse_t TestUncompressedEccKeyExport(uint8_t curveId, const uint8_t* pKey)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    uint8_t keyBuf[2 * BITS_TO_BYTES(HSE_MAX_ECC_KEY_BITS_LEN) + 1];//133
    uint16_t keyBufLen = sizeof(keyBuf);//133
    hseKeyInfo_t keyInfo;
    uint8_t keyByteLen = BITS_TO_BYTES(KeyBitLen(curveId));//32 bytes
    hseKeyHandle_t eccPublicRAMKeyHandle = HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE;
    hseStatus = LoadEccPublicKey(&eccPublicRAMKeyHandle  , 
                                 RAM_KEY,
                                 curveId,
                                 KeyBitLen(curveId), //256 bits
                                 pKey);
     if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;

    hseStatus = ExportPlainFormattedEccPubKeyReq(HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE  , 
                                                 &keyInfo, 
                                                 &keyBufLen, 
                                                 keyBuf, 
                                                 HSE_KEY_FORMAT_ECC_PUB_UNCOMPRESSED);
     if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;

    // key length must be 2 * curve byte length + 1
    if((1 + 2 * keyByteLen)!= keyBufLen)//65
    {
        hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
        goto exit;
    }

    // check that the key matches
    if(0 != memcmp(keyBuf + 1, pKey, 2 * keyByteLen))
    {
        hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
        goto exit;
    }

    // check that the first byte is 0x04 (which marks an uncompressed key)
   if(0x04!= keyBuf[0])
    {
        hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
        goto exit;
    }
   exit:
   return hseStatus;
}
#endif
/*******************************************************************************
 * Function:    TestRawEccKeyExport
 *
 * Description: Test that a given key can be exported in raw format
 *
 * Returns:     nothing
 ********************************************************************************/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static hseSrvResponse_t TestRawEccKeyExport(uint8_t curveId, const uint8_t* pKey)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    uint8_t keyBuf[2 * BITS_TO_BYTES(HSE_MAX_ECC_KEY_BITS_LEN)];//132
    uint16_t keyBufLen = sizeof(keyBuf);//132
    hseKeyInfo_t keyInfo;
    uint8_t keyByteLen = BITS_TO_BYTES(KeyBitLen(curveId));//32
    hseKeyHandle_t eccPublicRAMKeyHandle = HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE;

    hseStatus = LoadEccPublicKey(&eccPublicRAMKeyHandle   , 
                                 RAM_KEY,
                                 curveId,
                                 KeyBitLen(curveId), 
                                 pKey);
     if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;

    hseStatus = ExportPlainFormattedEccPubKeyReq(HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE  , 
                                                 &keyInfo, 
                                                 &keyBufLen, 
                                                 keyBuf, 
                                                 HSE_KEY_FORMAT_ECC_PUB_RAW);
     if(HSE_SRV_RSP_OK != hseStatus)
     goto exit;

    // key length must be 2 * curve byte length
    if((2 * keyByteLen)!= keyBufLen)//64
    {
        hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
        goto exit;
    }

    // check that the key matches
    if(0 != memcmp(keyBuf, pKey, 2 * keyByteLen))//64
    {
        hseStatus=HSE_SRV_RSP_VERIFY_FAILED;
        goto exit;
    }
   exit:
   return hseStatus;
}
#endif

/**
* @test_id TestCompressedEcccPublicKeyExportSuite
* @brief Test compressed key export
* @details Test that HSE can export keys in compressed uncompressed and raw format
* @test_type      Functional
* @test_procedure Steps:
*   For each key:
*   - Load key into HSE
*   - Export key in compressed,uncompressed and raw format
*   - Check that HSE returns HSE_SRV_RSP_OK
*   - Check that exported key is correct
* @pass_criteria Verification Points are successful
*/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static hseSrvResponse_t TestEccPublicKeyExportSuite(void)
{
      hseSrvResponse_t hseResponse;
      hseResponse = TestCompressedEccKeyExport(HSE_EC_SEC_SECP256R1, secp256v1PubKey_2);
      if(HSE_SRV_RSP_OK != hseResponse)
      goto exit;
      hseResponse = TestUncompressedEccKeyExport(HSE_EC_SEC_SECP256R1, secp256v1PubKey_2);
      if(HSE_SRV_RSP_OK != hseResponse)
      goto exit;
      hseResponse = TestRawEccKeyExport(HSE_EC_SEC_SECP256R1, secp256v1PubKey_2);
      if(HSE_SRV_RSP_OK != hseResponse)
      goto exit;
exit:
    return hseResponse;
}
#endif


/*******************************************************************************
 * Function:    TestEcdsaVerifTestCase
 *
 * Description: Run through a single ECDSA verification test case.
 *              Import the public key, then try to verify the signature
 *
 * Returns:     whether the test passes or not
 ********************************************************************************/
 #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
static hseSrvResponse_t TestEcdsaVerifTestCase(ecdsaVerifTestCase_t* pTestCase)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    uint32_t rLen = 0U;
    uint32_t sLen = 0U;
    hseKeyHandle_t eccRAMKeyHandle = HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE;

    hseStatus = ParseKeyCatalogs();
    if(HSE_SRV_RSP_OK !=hseStatus)
    goto exit;

    hseStatus = LoadEccPublicKey(&eccRAMKeyHandle,RAM_KEY,pTestCase->curveId,
                                 KeyBitLen(pTestCase->curveId), pTestCase->pPubKey);
    if (HSE_SRV_RSP_OK != hseStatus)
    {
        goto exit;
    }
    rLen = pTestCase->rLen;
    sLen = pTestCase->sLen;

    hseStatus = EcdsaVerify(HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, pTestCase->hashAlgo, pTestCase->msgLen, pTestCase->pMsg, FALSE, 0,
                            &rLen, pTestCase->r, &sLen, pTestCase->s);
    if (HSE_SRV_RSP_OK != hseStatus)
    {
        goto exit;
    }

exit:
    return hseStatus;
}
#endif

#ifdef HSE_SPT_KDF_SP800_108
static hseSrvResponse_t KdfSP800_108Test
(
    hseKeyImportParams_t *pImportSecretParams,
    hseKdfSP800_108Scheme_t *pKdfScheme
)
{
    hseSrvResponse_t hseResponse;

    pImportSecretParams->authParams.pKeyHandle = NULL;
    pImportSecretParams->cipherParams.pKeyHandle = NULL;
    hseResponse = ImportKeyReq(pImportSecretParams);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    hseResponse = HSEKdfSP800_108Req(pKdfScheme);
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }
    exit:
    return hseResponse;
}

#endif

#ifdef HSE_SPT_KDF_SP800_108
hseSrvResponse_t KdfSP800_108ReqTest()
{
    hseSrvResponse_t hseResponse;
    HKF_AllocKeySlot(RAM_KEY, KdfSP800_108_ImportSecret_1.pKey->pKeyInfo->keyType,
                     KdfSP800_108_ImportSecret_1.pKey->pKeyInfo->keyBitLen, &srcKey);
    HKF_AllocKeySlot(RAM_KEY, HSE_KEY_TYPE_SHARED_SECRET, KdfSP800_108_Scheme_1.kdfCommon.keyMatLen * 8U, &targetSharedSecretKey);
    KdfSP800_108_ImportSecret_1.pKey->keyHandle = srcKey;
    KdfSP800_108_Scheme_1.kdfCommon.srcKeyHandle = srcKey;
    KdfSP800_108_Scheme_1.kdfCommon.targetKeyHandle = targetSharedSecretKey;
    hseResponse = KdfSP800_108Test(&KdfSP800_108_ImportSecret_1, &KdfSP800_108_Scheme_1);
    goto exit;
    exit:
    return hseResponse;
}
#endif

/******************************************************************************
 * Function:    HSE_SessionKeys_Example
 * Description: Key Exchange example using HSE
 *              ECC key generation, ECC key import, ephemeral ECDH,
 *              Key derivation (KDF SP800_108),
 *              Key extraction - AES, HMAC keys from derived key material
 *****************************************************************************/
#ifdef HSE_SPT_KEY_DERIVE
static hseSrvResponse_t HSE_SessionKeys_Example(void)
{
    hseSrvResponse_t hseResponse;
    hseKeyHandle_t eccRAMKeyHandle = HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE;
    hseKeyHandle_t DHSharedSecretRAMKeyHandle = HSE_DEMO_DH_SHARED_SECRET_HANDLE;
    hseKeyHandle_t AESDerivedKeyInfoHandle1 = HSE_DEMO_RAM_AES256_KEY1;
    hseKeyHandle_t AESDerivedKeyInfoHandle0 = HSE_DEMO_RAM_AES256_KEY0;
    
    hseResponse= ParseKeyCatalogs();
    if(HSE_SRV_RSP_OK !=hseResponse)
    goto exit;
    //Generate an ECC key pair in RAM (ephemeral ECDH)
    hseResponse = GenerateEccKey(
            &eccRAMKeyHandle,
            RAM_KEY,
            HSE_EC_SEC_SECP256R1,
            HSE_KF_USAGE_EXCHANGE);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;

    //Import the peer public key
    hseResponse = ImportEccKeyReq(
            HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE, HSE_KEY_TYPE_ECC_PUB,
            HSE_KF_USAGE_EXCHANGE, HSE_EC_SEC_SECP256R1,
            KeyBitLen(HSE_EC_SEC_SECP256R1), eccP256PubKey, NULL);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;

    //Compute DH Shared Secret (ECDH)
    hseResponse = DHSharedSecretCompute(
            HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE,
            HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE,
            &DHSharedSecretRAMKeyHandle,
            RAM_KEY,
            KeyBitLen(HSE_EC_SEC_SECP256R1));

       if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;

    #ifdef HSE_SPT_KDF_SP800_108 
    hseResponse = KdfSP800_108ReqTest();
    if(HSE_SRV_RSP_OK != hseResponse)
    goto exit;

    //Extract from the derived key material 3 keys: 192-bits AES, 256-bits AES, HMAC
    {
        //Declare the information about the 192 bits AES key to be extracted
        hseKeyInfo_t aes192KeyInfo = {
            .keyType = HSE_KEY_TYPE_AES,      //Will generate an AES key
            .keyFlags = (HSE_KF_USAGE_ENCRYPT|HSE_KF_USAGE_DECRYPT),//Usage flags for this key - Encrypt/Decrypt
            .keyBitLen = 192U,                //192 bits key
        };
        //Declare the information about the HMAC key to be extracted
        hseKeyInfo_t hmacKeyInfo = {
            .keyType = HSE_KEY_TYPE_HMAC,                        //Will generate a HMAC key
            .keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY), //Usage flags for this key - Sign/Verify
            .keyBitLen = 512U,                                   //512 bits key
        };
        //Declare the information about the 256 bits AES key to be extracted
        hseKeyInfo_t aes256KeyInfo = {
            .keyType = HSE_KEY_TYPE_AES,                             //Will generate an AES key
            .keyFlags = (HSE_KF_USAGE_ENCRYPT |HSE_KF_USAGE_DECRYPT| //Usage flags for this key - Encrypt/Decrypt/Sign/Verify - AEAD
                HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY),
            .keyBitLen = 256U,                                       //256 bits key
        };

        //Extract the 192 bits AES key from the beginning of the derived key
        hseResponse = HSEKeyDeriveExtractKeyReq
                (
                KdfSP800_108_Scheme_1.kdfCommon.targetKeyHandle,
                0U,
                &AESDerivedKeyInfoHandle1,
                RAM_KEY,
                aes192KeyInfo
                );
        if(HSE_SRV_RSP_OK != hseResponse)
            goto exit;
        //Extract the HMAC key from the remaining derived key material
        hseResponse = HSEKeyDeriveExtractKeyReq
                (
                        KdfSP800_108_Scheme_1.kdfCommon.targetKeyHandle,
                        0U,
                        &AESDerivedKeyInfoHandle0,
                        RAM_KEY,
                        hmacKeyInfo
                );
        if(HSE_SRV_RSP_OK != hseResponse)
            goto exit;

        //Extract the 256 bits AES key from the remaining derived key material
        hseResponse = HSEKeyDeriveExtractKeyReq
                (
                        KdfSP800_108_Scheme_1.kdfCommon.targetKeyHandle,
                        BITS_TO_BYTES(aes192KeyInfo.keyBitLen),
                        &AESDerivedKeyInfoHandle1,
                        RAM_KEY,
                        aes256KeyInfo
                );
        if(HSE_SRV_RSP_OK != hseResponse)
            goto exit;
    #endif
        
    }

    //Keys sanity checks: AES encrypt/decrypt, HMAC sign/verify
    {
        uint8_t tag[64] = {0U};
        uint32_t tagLen = 64UL;
        uint8_t cipherText[NUM_OF_ELEMS(message)] = {0U};
        uint8_t plainText[NUM_OF_ELEMS(message)] = {0U};

        //AES key sanity check - Encrypt/Decrypt
        hseResponse = AesEncrypt(
                HSE_DEMO_RAM_AES256_KEY1,
                HSE_CIPHER_BLOCK_MODE_CBC,
                iv,
                NUM_OF_ELEMS(message),
                message,
                cipherText,
                0U );
        if(HSE_SRV_RSP_OK != hseResponse)
            goto exit;

        hseResponse = AesDecrypt(
                HSE_DEMO_RAM_AES256_KEY1,
                HSE_CIPHER_BLOCK_MODE_CBC,
                iv,
                NUM_OF_ELEMS(cipherText),
                cipherText,
                plainText,
                0U );
        if( (HSE_SRV_RSP_OK != hseResponse) ||
            (0 != memcmp(message, plainText, NUM_OF_ELEMS(message))) )
            goto exit;

        //Alternatively using only 2 calls - AEAD GCM Encrypt/Decrypt
        tagLen = 16UL;
        memset(tag, 0, 64);
        memset(cipherText, 0, NUM_OF_ELEMS(message));
        memset(plainText, 0, NUM_OF_ELEMS(message));

        hseResponse = AesGcmEncrypt(
                HSE_DEMO_RAM_AES256_KEY1,
                NUM_OF_ELEMS(iv),
                iv,
                0UL,
                NULL,
                NUM_OF_ELEMS(message),
                message,
                tagLen,
                tag,
                cipherText,
                0U );
        if(HSE_SRV_RSP_OK != hseResponse)
            goto exit;

        hseResponse = AesGcmDecrypt(
                HSE_DEMO_RAM_AES256_KEY1,
                NUM_OF_ELEMS(iv),
                iv,
                0UL,
                NULL,
                NUM_OF_ELEMS(cipherText),
                cipherText,
                tagLen,
                tag,
                plainText,
                0U );
        if( (HSE_SRV_RSP_OK != hseResponse) ||
            (0 != memcmp(message, plainText, NUM_OF_ELEMS(message))) )
            goto exit;
    }

exit:
    return hseResponse;
}
#endif

/******************************************************************************
 * Function:    HSE_SysAuthorization_Example
 * Description: SYS Authorization Example
 *              Import RSA keys, Authorization Request/Response,
 *              RSA Sign generation, Erase Key
******************************************************************************/
#ifdef HSE_SPT_RSA
static hseSrvResponse_t HSE_SysAuthorization_Example(void)
{
    uint16_t hseStatus = 0U;
    hseSrvResponse_t hseResponse;

    //Set the CUST_SUPER_USER authorization key
    /*hseResponse = SetCustAuthorizationKey();
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }*/

    //Switch to IN_FIELD User
    hseResponse = HSE_SysAuthorizationReq
            (
                    HSE_SYS_AUTH_ALL,
                    HSE_RIGHTS_USER,
                    0UL,
                    NULL,
                    NULL
            );
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }
    //Check user: IN_FIELD User mode
    hseStatus = HSE_MU_GetHseStatus(MU0);
    if(!IN_FIELD_USER_MODE(hseStatus))
    {
        goto exit;
    }

    //Operations with USER rights

    //Try erase operation - NOT_ALLOWED
    hseResponse = EraseKeyReq
            (
                HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0,
                HSE_ERASE_NOT_USED
            );
    if(HSE_SRV_RSP_NOT_ALLOWED != hseResponse)
    {
        goto exit;
    }

    //Authorize as CUST_SUPER_USER using CUST authorization key
    hseResponse = AuthorizeCust();
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    //Check user: CUST_SUPER_USER mode
    hseStatus = HSE_MU_GetHseStatus(MU0);
    if(!CUST_SUPER_USER_MODE(hseStatus))
    {
        goto exit;
    }

    //Operations with SU rights
    //Try erase operation - should work now - HSE_SRV_RSP_OK
    hseResponse = EraseKeyReq
            (
                    HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0,
                    HSE_ERASE_NOT_USED
            );
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

exit:
    return hseResponse;
}
#endif
/******************************************************************************
 * Function:    HSE_UpdateNvmKey_Example
 * Description: Example of how to update a NVM key with SU rights
 *              (must be imported in an authenticated key container)
 *              Import RSA keys, Authorization Request/Response,
 *              RSA Sign generation, Erase Key
 *****************************************************************************/
#ifdef HSE_SPT_GMAC    
static hseSrvResponse_t HSE_UpdateNvmKey_Example(void)
{
    hseSrvResponse_t hseResponse;
     /*Declare the HMAC key info that will update initial version*/
    hseKeyInfo_t keyInfo = {
        .keyType = HSE_KEY_TYPE_HMAC,                        //Will generate a HMAC key
        .keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY), //Usage flags for this key - Sign/Verify
        .keyBitLen = BYTES_TO_BITS(NUM_OF_ELEMS(hmacKeyUpdated)), //Key size in bits
        .keyCounter = 1U                                     //The key counter must be incremented(greater than current counter of the key in NVM slot)*/
    };

    /*
     * Declare the authentication scheme that HSE will use
     * (along with the provision key) to verify the authenticity
     */
/*    hseAuthScheme_t authScheme = {
 -         .macScheme.macAlgo = HSE_MAC_ALGO_GMAC,
 -         .macScheme.sch.gmac.pIV = PTR_TO_HOST_ADDR(iv),
 -         .macScheme.sch.gmac.ivLength = NUM_OF_ELEMS(iv),
 -     };*/
    uint8_t tag[16U] = {0U};
    uint32_t tagLen = 16UL;

    /*
     * Declare a key container:
     * Authenticated buffer that MUST contain:
     *          - key data (i.e. pKey[0], pKey[1], pKey[2], depending on key type)
     *          - key info (which should have a higher key counter)
     *              - optional for public keys (RSA/ECC_PUB)
     * Optional, may contain any other information
     * For more details checkout `hse_srv_key_import_export.h` or dedicated chapter in HSE RM
     */
    uint8_t keyContainer[1056] = {0U};
/*    uint16_t keyInfoOffset, keyDataOffset;*/
    uint16_t offset = 0U;

    /*
     * Populate the NVM HMAC key slot with initial key -
     * first import can be done in plain (SU rights)
     */
    /*hseResponse = ImportPlainSymKeyReq(NVM_HMAC_KEY0, HSE_KEY_TYPE_HMAC,
        HSE_KF_USAGE_SIGN, NUM_OF_ELEMS(hmacKeyInitial), hmacKeyInitial);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;*/


    /*
     * Fill the container with the necessary data
     * (Optional) - leave some space for any specific data
     */
    offset += 50U;

    //HMAC - Symmetric key - Must copy the key info
    //keyInfoOffset = offset;
    (void)memcpy(&keyContainer[offset], &keyInfo, sizeof(keyInfo));
    offset += sizeof(keyInfo);

    //(Optional) - leave some space for any specific data
    offset += 100U;

    //HMAC - Symmetric key - Must copy the key data in the container
    //keyDataOffset = offset;
    (void)memcpy(&keyContainer[offset], hmacKeyUpdated, NUM_OF_ELEMS(hmacKeyUpdated));

    /*
     * (Optional) - add any other data
     * Key container is ready - it must be authenticated
     * Import in RAM a copy of the AES provision key to sign the
     * container using HSE
     * NOTE: Intended use case: The container comes already signed
     * (/ is signed externally)
     */
    hseResponse = ImportPlainSymKeyReq(HSE_DEMO_RAM_AES128_KEY1, HSE_KEY_TYPE_AES,
        HSE_KF_USAGE_SIGN, gAESProvisionKeyLength, gAES128ProvisionKey,0U);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;

    //Sign the container - generate GMAC
    hseResponse = AesGmacGenerate(HSE_DEMO_RAM_AES128_KEY1, NUM_OF_ELEMS(iv), iv,
            NUM_OF_ELEMS(keyContainer), keyContainer, &tagLen, tag,HSE_SGT_OPTION_NONE);
    if(HSE_SRV_RSP_OK != hseResponse)
        goto exit;
exit:
    return hseResponse;
}
#endif
/* ============================================================================
 *                              GLOBAL FUNCTIONS
 * ============================================================================
*/

/******************************************************************************
 * Function:    HSE_Crypto
 * Description: HSE crypto services examples
 *              Examples of symmetric/asymmetric, sync/async HSE crypto
 *              operations and SYS authorization
 *****************************************************************************/
hseSrvResponse_t HSE_Crypto(void)
{
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    /* Key Catalogs must be configured */
    ASSERT(CHECK_HSE_STATUS(HSE_STATUS_INSTALL_OK));
 
    /*Note: Keys for all below cryptographic operations have already
     * been imported in Generic_ImportKey() called in main() function*/
    /*run AES related tests*/
    gCryptoServicesStarted|=AES_EXAMPLE_STARTED;
    srvResponse = HSE_Aes_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= AES_EXAMPLES_SUCCESS;
    }
    #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
    /*run ECC related tests*/
    gCryptoServicesStarted|= ECC_KEYS_EXAMPLE_STARTED;
    srvResponse = HSE_Ecdsa_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= ECC_KEYS_EXAMPLES_SUCCESS;
    }
    #endif
    /*run ECC Key Export related tests*/
    #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
    gCryptoServicesStarted|= ECC_EXPORT_PUBLIC_KEY_STARTED;
    srvResponse = TestEccPublicKeyExportSuite();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= ECC_EXPORT_PUBLIC_KEY_SUCCESS;
    }
    #endif
    #ifdef HSE_SPT_ECC_COMPRESSED_KEYS
    /*Importing of ECC public key using import key
    ECC signature verification using the public key imported*/
    gCryptoServicesStarted|= ECC_IMPORT_PUBLIC_KEY_SIGNATURE_VERIFICATION_STARTED;
    srvResponse = TestEcdsaVerifTestCase(ecdsaVerifTestCases+0);
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= ECC_IMPORT_PUBLIC_KEY_SIGNATURE_VERIFICATION_SUCCESS;
    }
    #endif
    /*run session key related tests*/
    #ifdef HSE_SPT_KEY_DERIVE
    gCryptoServicesStarted|= SESSION_KEY_EXAMPLE_STARTED;
    srvResponse = HSE_SessionKeys_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= SESSION_KEY_EXAMPLES_SUCCESS;
    }
    #endif
    /*run Fast Cmac with Counter Protocol */
    #ifdef HSE_SPT_MONOTONIC_COUNTERS
    gCryptoServicesStarted|= FAST_CMAC_WITH_COUNTER_EXAMPLE_STARTED;
    srvResponse = HSE_FastCmacwithCounter_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= FAST_CMAC_WITH_COUNTER_EXAMPLES_SUCCESS;
    }
    #endif

    /*run Burmester Desmedt Protocol */
    #ifdef HSE_SPT_BURMESTER_DESMEDT 
    gCryptoServicesStarted|= BURMESTER_DESMEDT_EXAMPLE_STARTED;
    srvResponse = HSE_BurmesterDesmedt_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= BURMESTER_DESMEDT_EXAMPLES_SUCCESS;
    }
    #endif
    /*run sys authorization related tests*/ 
    #ifdef HSE_SPT_RSA
    gCryptoServicesStarted|=SYS_AUTHORIZATION_EXAMPLE_STARTED;
    srvResponse = HSE_SysAuthorization_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= SYS_AUTHORIZATION_EXAMPLE_SUCCESS;
    }
    #endif
    /*run update NVM keys related tests*/
    #ifdef HSE_SPT_GMAC    
    gCryptoServicesStarted|=UPDATE_NVM_KEY_EXAMPLE_STARTED;
    srvResponse = HSE_UpdateNvmKey_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= UPDATE_NVM_KEY_EXAMPLE_SUCCESS;
    }
    #endif
    /*run HASH related tests*/
    gCryptoServicesStarted|=HASH_EXAMPLE_STARTED;
    srvResponse = HSE_HashAsync_Example();
    if( HSE_SRV_RSP_OK == srvResponse)
    {
        gCryptoServicesExecuted |= HASH_EXAMPLES_SUCCESS;
    }
    ASSERT( gCryptoServicesStarted == gCryptoServicesExecuted );
    testStatus |= CRYPTOGRAPHIC_SERVICES_SUCCESS;
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_HashDataBlocking
 * Description: Blocking hash request.
 *****************************************************************************/
hseSrvResponse_t HSE_HashDataBlocking
(
    uint8_t u8MuInstance,
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseHashAlgo_t hashAlgo,
    const uint8_t *pInput,
    uint32_t inputLength,
    uint8_t *pHash,
    uint32_t *pHashLength
)
{
    uint8_t u8MuChannel = 1U;
    hseTxOptions_t asyncTxOptions;
    hseSrvDescriptor_t *pHseSrvDesc;
    hseHashSrv_t *pHashSrv;
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    /*Complete the service descriptor placed in shared memory*/
    pHseSrvDesc = &gHseSrvDesc[0U][u8MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHashSrv = &(pHseSrvDesc->hseSrv.hashReq);

    pHseSrvDesc->srvId      = HSE_SRV_ID_HASH;
    pHashSrv->accessMode    = accessMode;
    pHashSrv->streamId      = streamId;
    pHashSrv->hashAlgo      = hashAlgo;
    pHashSrv->inputLength   = inputLength;
    pHashSrv->pInput        = PTR_TO_HOST_ADDR(pInput);
    pHashSrv->pHash         = PTR_TO_HOST_ADDR(pHash);
    pHashSrv->pHashLength   = PTR_TO_HOST_ADDR(pHashLength);

    /*Complete callback info and async txOptions*/
    callbackParams[u8MuInstance][u8MuChannel].u8MuInstance  = u8MuInstance;
    callbackParams[u8MuInstance][u8MuChannel].u8MuChannel   = u8MuChannel;
    asyncTxOptions.txOp              = HSE_TX_SYNCHRONOUS;
    asyncTxOptions.pfAsyncCallback   = &(HSE_HashRequestCallback);
    asyncTxOptions.pCallbackpArg     =
            (void *)(&(callbackParams[u8MuInstance][u8MuChannel]));

    /*Send the request asynchronously*/
    srvResponse = HSE_Send(u8MuInstance,u8MuChannel,asyncTxOptions,pHseSrvDesc);
    return srvResponse;
}

/******************************************************************************
 * Function:    Grant_SuperUser_Rights
 * Description: main function for granting super user rights.
 *****************************************************************************/
#ifdef HSE_SPT_RSA

hseSrvResponse_t Grant_SuperUser_Rights(void)
{
    uint16_t hseStatus = 0U;
    hseSrvResponse_t hseResponse;
    /*Set the CUST_SUPER_USER authorization key*/
    hseResponse = SetCustAuthorizationKey();
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }
    /*Switch to IN_FIELD User*/
    hseResponse = HSE_SysAuthorizationReq
            (
                    HSE_SYS_AUTH_ALL,
                    HSE_RIGHTS_USER,
                    0UL,
                    NULL,
                    NULL
                    );
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }
    /*Check user: IN_FIELD User mode*/
    hseStatus = HSE_MU_GetHseStatus(MU0);
    if(!IN_FIELD_USER_MODE(hseStatus))
    {
        goto exit;
    }

    /*Authorize as CUST_SUPER_USER using CUST authorization key*/
    hseResponse = AuthorizeCust();
    if(HSE_SRV_RSP_OK != hseResponse)
    {
        goto exit;
    }

    /*Check user: CUST_SUPER_USER mode*/
    hseStatus = HSE_MU_GetHseStatus(MU0);
    if(!CUST_SUPER_USER_MODE(hseStatus))
    {
        goto exit;
    }
exit:
    return hseResponse;
}

#endif

#ifdef __cplusplus
}
#endif

/** @} */
