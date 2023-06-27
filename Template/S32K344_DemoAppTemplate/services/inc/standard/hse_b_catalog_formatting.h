/**
 *   @file    hse_b_catalog_formatting.h
 *
 *   @brief   Contains the configuration file for catalog formatting
 *   @details This file contains the configuration for key catalog formatting.
 *
 *   @addtogroup
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

#ifndef HSE_B_CATALOG_FORMATTING_H
#define HSE_B_CATALOG_FORMATTING_H

#include "hse_interface.h"
#include "hse_keys_allocator.h"

#ifdef HSE_SPT_ECC
#define WRP_KEY_TYPE_ECC_PAIR HSE_KEY_TYPE_ECC_PAIR
#define WRP_KEY_TYPE_ECC_PUB HSE_KEY_TYPE_ECC_PUB
#define WRP_KEY_TYPE_ECC_PUB_EXT HSE_KEY_TYPE_ECC_PUB_EXT
#define WRP_ECC_KEY_SIZE HSE_KEY521_BITS
#else
#define WRP_KEY_TYPE_ECC_PAIR HSE_KEY_TYPE_AES
#define WRP_KEY_TYPE_ECC_PUB HSE_KEY_TYPE_AES
#define WRP_KEY_TYPE_ECC_PUB_EXT HSE_KEY_TYPE_AES
#define WRP_ECC_KEY_SIZE HSE_KEY128_BITS
#endif

/** @brief    HSE NVM key catalog configuration*/
#define HSE_DEMO_NVM_KEY_CATALOG_CFG                                                                                                      \
        /*  keyType                 numOfKeySlots   maxKeyBitLen  */                                                                      \
        /* CUST keys */                                                                                                                   \
        {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 12U, HSE_KEY128_BITS}, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */ \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 4U, HSE_KEY128_BITS},                                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 7U, HSE_KEY256_BITS},  /* HMAC key */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC, 2U, HSE_KEY512_BITS}, /* ECC keys */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PAIR, 3U, WRP_ECC_KEY_SIZE},                                           \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB_EXT, 1U, WRP_ECC_KEY_SIZE}, /* RSA keys */                         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR, 2U, HSE_KEY4096_BITS},                                           \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB, 1U, HSE_KEY4096_BITS},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS}, /* OEM keys */                         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES, 3U, HSE_KEY128_BITS},                                                  \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES, 3U, HSE_KEY256_BITS},   /* HMAC key */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_HMAC, 1U, HSE_KEY1024_BITS}, /* ECC keys */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PAIR, 1U, WRP_ECC_KEY_SIZE},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB_EXT, 1U, WRP_ECC_KEY_SIZE}, /* RSA keys */                          \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PAIR, 1U, HSE_KEY4096_BITS},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB, 1U, HSE_KEY4096_BITS},                                             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS},                                         \
            {HSE_MU0_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                                \
        {                                                                                                                                 \
                0U, 0U, 0U, 0U, 0U                                                                                                        \
        }

/** @brief    HSE RAM key catalog configuration*/
#define HSE_DEMO_RAM_KEY_CATALOG_CFG                                                                      \
        /*  keyType                   numOfKeySlots maxKeyBitLen*/                                        \
        /* Symetric key */                                                                                \
        {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 1U, HSE_KEY128_BITS}, /* KEY_RAM */        \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10U, HSE_KEY128_BITS},                 \
            {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10U, HSE_KEY256_BITS},     /* HMAC key */ \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_HMAC, 6U, HSE_KEY1024_BITS}, /* RSA key */  \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB, 2U, HSE_KEY2048_BITS},             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY1024_BITS},         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, WRP_KEY_TYPE_ECC_PAIR, 2U, WRP_ECC_KEY_SIZE},            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, WRP_KEY_TYPE_ECC_PUB, 5U, WRP_ECC_KEY_SIZE},             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 2U, HSE_KEY638_BITS},        \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 1U, HSE_KEY2048_BITS},       \
        {                                                                                                 \
                0U, 0U, 0U, 0U, 0U                                                                        \
        }

#define HSE_DEMO_NVM_SHE_AES128_BOOT_KEY GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 1)

#define HSE_DEMO_NVM_AES128_PROVISION_KEY GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 0)
#define HSE_DEMO_NVM_AES128_BOOT_KEY GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 1)
#define HSE_DEMO_NVM_AES128_AUTHORIZATION_KEY GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 2)

#define HSE_DEMO_NVM_AES256_PROVISION_KEY0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 0)
#define HSE_DEMO_NVM_AES256_PROVISION_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 1)
#define HSE_DEMO_NVM_AES256_KEY2 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 2)
#define HSE_DEMO_NVM_AES256_KEY3 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 3)

#define HSE_DEMO_NVM_HMAC_KEY0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 3, 0)
#define HSE_DEMO_NVM_HMAC_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 3, 1)

#define HSE_DEMO_NVM_ECC_BOOT_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 4, 0)
#define HSE_DEMO_NVM_ECC_BOOT_KEY_HANDLE_1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 4, 1)

/* Copy of authorization keys to generate the signature over the challenge */
#define HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 7, 0)
#define HSE_DEMO_NVM_RSA2048_PAIR_CUSTAUTH_HANDLE1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 7, 1)

/* Must be in NVM */
#define HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 8, 0)
#define HSE_DEMO_NVM_RSA2048_PUB_CUSTAUTH_HANDLE1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 8, 1)

/* Points to a ECC key pair NVM slot */
#define HSE_DEMO_SHE_RAM_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 0)

#define HSE_DEMO_RAM_AES128_KEY0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 0)
#define HSE_DEMO_RAM_AES128_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 1)

#define HSE_DEMO_RAM_AES256_KEY0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 0)
#define HSE_DEMO_RAM_AES256_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 1)
#define HSE_DEMO_RAM_AES256_KEY2 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 2)
#define HSE_DEMO_RAM_AES128_ADKP_KEY GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 3)

#define HSE_DEMO_RAM_HMAC_KEY0 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 0)
#define HSE_DEMO_RAM_HMAC_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 1)

#define HSE_DEMO_RAM_ECC_PAIR_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 6, 0)
#define HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 7, 0)

#define HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 7, 1)
#define HSE_DEMO_RAM_ECC_PUB_KEY_HANDLE_SLOT3 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 7, 3)

#define HSE_DEMO_DERIVED_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 8, 0)
#define HSE_DEMO_BD_SHARED_SECRET_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 8, 1)

#define HSE_DEMO_DH_SHARED_SECRET_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 9, 0)
#define HSE_DEMO_RAM_SHARED_SECRET4096_KEY1 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 9, 1)

#define HSE_DEMO_DH_SHARED_SECRET_HANDLE_0 RAM_AES256_KEY0
#define HSE_DEMO_DH_SHARED_SECRET_HANDLE_1 RAM_SHARED_SECRET4096_KEY1

#define HSE_DEMO_SECRET_SRC_KEY_HANDLE RAM_AES256_KEY0

#define HSE_DEMO_NVM_ECC_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 4, 2)
#define HSE_DEMO_NVM_ECC_KEY_HANDLE_PUBLIC GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 5, 0)

hseSrvResponse_t FormatKeyCatalogs_(void);
hseSrvResponse_t ParseKeyCatalogs(void);
bool_t IsKeyCatalogFormatted(void);

#ifdef __cplusplus
extern "C"
{
#endif

#endif
