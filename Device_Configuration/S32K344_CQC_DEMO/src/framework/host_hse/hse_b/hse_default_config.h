/**
*   @file    hse_default_config.h
*

*   @brief   HSE internal default configuration.
*   @details This file contains the HSE default configuration.
*
*   @addtogroup hse_default_config HSE default config
*   @{
*/
/*==================================================================================================
*
*   (c) Copyright 2019 NXP.
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

#ifndef HSE_DEFAULT_CONFIG_H
#define HSE_DEFAULT_CONFIG_H


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           hse_default_config.h
*/
#include "hse_common_types.h"


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

/** @brief    HSE key catalog configuration.
 *            - Each catalog entry represent a key group of the same key type.
 *            - Each group is identified by its index within the catalog.
 *            Note that a key group can contain keys that have keybitLen <= maxKeyBitLen.
 *            For example, the group of key type "HSE_KEY_TYPE_AES" of 256bits can contain AES128, AES192 and AES256 keys.
 *            If there are not enough slots for an AES128 key in an AES128 group, the key can be store in an AES256 slot.
 *            The catalog is ending with a zero filled entry.
 *            */
/** @brief    Wrappers for ECC key definitions.
 *            If ECC is not enabled, transform the ECC key slots into AES key slots,
 *            so that the subsequent key slot indices are preserved
 *            */
#ifdef HSE_SPT_ECC
    #define WRP_KEY_TYPE_ECC_PAIR    HSE_KEY_TYPE_ECC_PAIR
    #define WRP_KEY_TYPE_ECC_PUB     HSE_KEY_TYPE_ECC_PUB
    #define WRP_KEY_TYPE_ECC_PUB_EXT HSE_KEY_TYPE_ECC_PUB_EXT
    #define WRP_ECC_KEY_SIZE         HSE_KEY521_BITS
#else
    #define WRP_KEY_TYPE_ECC_PAIR    HSE_KEY_TYPE_AES
    #define WRP_KEY_TYPE_ECC_PUB     HSE_KEY_TYPE_AES
    #define WRP_KEY_TYPE_ECC_PUB_EXT HSE_KEY_TYPE_AES
    #define WRP_ECC_KEY_SIZE         HSE_KEY128_BITS
#endif


/** @brief    HSE NVM key catalog configuration*/
#define  HSE_NVM_KEY_CATALOG_CFG  \
        /*  keyType                 numOfKeySlots   maxKeyBitLen  */  \
/* CUST keys */    \
		{ HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,          12U  ,     HSE_KEY128_BITS }, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,           4U,        HSE_KEY128_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,           7U,        HSE_KEY256_BITS }, \
        /* HMAC key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC,          1U,         HSE_KEY1024_BITS }, \
        /* ECC keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PAIR,      2U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB,       1U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB_EXT,   2U,         WRP_ECC_KEY_SIZE }, \
        /* RSA keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR,      2U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB,       2U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB_EXT,   3U,         HSE_KEY4096_BITS}, \
/* OEM keys */    \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES,            3U,        HSE_KEY128_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES,            3U,        HSE_KEY256_BITS }, \
        /* HMAC key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_HMAC,           1U,         HSE_KEY1024_BITS }, \
        /* ECC keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PAIR,       1U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB,        2U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB_EXT,    1U,         WRP_ECC_KEY_SIZE }, \
        /* RSA keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PAIR,       1U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB,        1U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB_EXT,    1U,         HSE_KEY4096_BITS}, \
        { HSE_MU0_MASK,    HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB,        1U,         WRP_ECC_KEY_SIZE }, \
        {0U,               0U,                0U,                          0U,         0U  }


/** @brief    HSE RAM key catalog configuration*/
#define  HSE_RAM_KEY_CATALOG_CFG  \
        /*  keyType                   numOfKeySlots maxKeyBitLen*/ \
        /* Symetric key */ \
		{ HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE,          1U   ,     HSE_KEY128_BITS }, /* KEY_RAM */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            10U,        HSE_KEY128_BITS }, \
        { HSE_MU0_MASK,    HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            10U,        HSE_KEY256_BITS }, \
        /* HMAC key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_HMAC,           6U,        HSE_KEY1024_BITS }, \
        /* RSA key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_RSA_PUB,        2U,        HSE_KEY2048_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_RSA_PUB_EXT,    1U,        HSE_KEY1024_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   WRP_KEY_TYPE_ECC_PAIR,       2U,        WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   WRP_KEY_TYPE_ECC_PUB,        1U,        WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  2U,        HSE_KEY638_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  1U,        HSE_KEY2048_BITS }, \
        {0U,               0U,                  0U,                          0U,         0U  }

#ifdef HSE_SPT_SMR_CR
/** @brief    HSE SB NVM key catalog configuration*/
#define  HSE_SB_NVM_KEY_CATALOG_CFG  \
            /*  keyType                 numOfKeySlots   maxKeyBitLen  */  \
            /* Symmetric key */ \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,            5U,        HSE_KEY128_BITS }, \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,            5U,        HSE_KEY256_BITS }, \
            /* HMAC key */ \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC,           1U,        HSE_KEY512_BITS }, \
            /* ECC keys */ \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PAIR,       2U,        WRP_ECC_KEY_SIZE }, \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB,        1U,        WRP_ECC_KEY_SIZE }, \
            /* RSA keys */ \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB,        1U,        HSE_KEY2048_BITS}, \
            { 0U,              0U,                 0U,                          0U,        0U  }

/** @brief    HSE SB RAM key catalog configuration*/
#define  HSE_SB_RAM_KEY_CATALOG_CFG  \
            /*  keyType                 numOfKeySlots   maxKeyBitLen  */  \
            { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_AES,            5U,        HSE_KEY128_BITS }, \
            { 0U,              0U,                 0U,                          0U,        0U  }
#endif/*#ifdef HSE_SPT_SMR_CR*/

#if 0

/** @brief    HSE NVM key catalog2 configuration*/
#define  HSE_NVM_KEY_CATALOG_CFG2  \
        /*  keyType                 numOfKeySlots   maxKeyBitLen  */  \
        /* Symetric key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST,   HSE_KEY_TYPE_AES,            1U,        HSE_KEY128_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST,   HSE_KEY_TYPE_AES,            1U,        HSE_KEY256_BITS }, \
        /* RSA keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST,   HSE_KEY_TYPE_RSA_PUB,        2U,        HSE_KEY2048_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST,   HSE_KEY_TYPE_RSA_PAIR,       2U,        HSE_KEY2048_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST,   HSE_KEY_TYPE_RSA_PUB_EXT,    1U,        HSE_KEY1024_BITS }, \
        {0U,               0U,                  0U,                          0U,         0U  }

/** @brief    HSE RAM key catalog2 configuration*/
#define  HSE_RAM_KEY_CATALOG_CFG2  \
        /*  keyType                   numOfKeySlots maxKeyBitLen*/ \
        /* Symetric key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            1U,        HSE_KEY128_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            1U,        HSE_KEY256_BITS }, \
        /* RSA key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_RSA_PUB,        2U,        HSE_KEY2048_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_RSA_PUB_EXT,    1U,        HSE_KEY1024_BITS }, \
        {0U,               0U,                  0U,                          0U,         0U  }

/** @brief    HSE NVM key catalog3 configuration*/
#define  HSE_NVM_KEY_CATALOG_CFG3  HSE_NVM_KEY_CATALOG_CFG2

/** @brief    HSE RAM key catalog3 configuration*/
#define  HSE_RAM_KEY_CATALOG_CFG3  \
        /*  keyType                   numOfKeySlots maxKeyBitLen*/ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            1U,        HSE_KEY256_BITS }, \
        /* HMAC key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_HMAC,           2U,        HSE_KEY1024_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  1U,        HSE_KEY638_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  1U,        HSE_KEY2048_BITS }, \
        {0U,               0U,                  0U,                          0U,         0U  }
#endif

/** @brief    HSE NVM key catalog configuration*/
#define  HSE_NVM_KEY_CATALOG_CFG4  \
        /*  keyType                 numOfKeySlots   maxKeyBitLen  */  \
/* CUST keys */    \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,           4U,        HSE_KEY128_BITS }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,           7U,        HSE_KEY256_BITS }, \
        /* HMAC key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC,          1U,         HSE_KEY1024_BITS }, \
        /* ECC keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PAIR,      2U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB,       1U,         WRP_ECC_KEY_SIZE }, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB_EXT,   2U,         WRP_ECC_KEY_SIZE }, \
        /* RSA keys */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR,      3U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB,       2U,         HSE_KEY4096_BITS}, \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB_EXT,   2U,         HSE_KEY4096_BITS}, \
        {0U,               0U,                0U,                          0U,         0U  }

/** @brief    HSE NVM key catalog configuration*/
#define  HSE_SHE_NVM_KEY_CATALOG_CFG  \
        /*  keyType                    numOfKeySlots         maxKeyBitLen  */  \
        /* Symmetric key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,          12U  ,     HSE_KEY128_BITS }, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,          10U  ,     HSE_KEY128_BITS }, /* KEY_11 to KEY_20 */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,          10U  ,     HSE_KEY128_BITS }, /* KEY_21 to KEY_30 */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_SHE,          10U  ,     HSE_KEY128_BITS }, /* KEY_31 to KEY_40 */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_SHE,          10U  ,     HSE_KEY128_BITS }, /* KEY_41 to KEY_50 */ \
        { 0U,              0U,                            0U   ,          0U   ,     0U  }

/** @brief    HSE RAM key catalog configuration*/
#define  HSE_SHE_RAM_KEY_CATALOG_CFG  \
/*  keyType                    numOfKeySlots         maxKeyBitLen  */  \
        /* Symmetric key */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE,          1U   ,     HSE_KEY128_BITS }, /* KEY_RAM */ \
        { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES,          1U   ,     HSE_KEY128_BITS }, /* AES RAM key */ \
        {0U,               0U,                0U              ,          0U   ,     0U  }


/** @brief    HSE stream count per interface */
#define HSE_MU0_STREAM_COUNT 2

#define HSE_MU1_STREAM_COUNT 2

#define HSE_MU2_STREAM_COUNT 2

#define HSE_MU3_STREAM_COUNT 2

/** @brief AES 128 RAM KEYS */
/** @brief AES 128 RAM KEYS */
#define RAM_AES128_KEY0         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 0)
#define RAM_AES128_KEY1         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 1)
#define RAM_AES128_KEY2         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 2)
#define RAM_AES128_KEY3         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 3)
#define RAM_AES128_KEY4         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 4)
#define RAM_AES128_KEY5         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 5)
#define RAM_AES128_KEY6         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 6)

/** @brief AES 256 RAM KEYS */
#define RAM_AES256_KEY0         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 0)
#define RAM_AES256_KEY1         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 1)
#define RAM_AES256_KEY2         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 2)
#define RAM_AES256_KEY3         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 3)
#define RAM_AES256_KEY4         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 4)
#define RAM_AES256_KEY5         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 5)
#define RAM_AES256_KEY6         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 6)
#define RAM_AES256_KEY7         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 1, 7)

/** @brief HMAC RAM KEYS */
#define RAM_HMAC_KEY0           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 0)
#define RAM_HMAC_KEY1           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 1)
#define RAM_HMAC_KEY2           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 2)
#define RAM_HMAC_KEY3           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 3)
#define RAM_HMAC_KEY4           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 4)
#define RAM_HMAC_KEY5           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 5)
#define RAM_HMAC_KEY6           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 2, 6)

/** @brief RSA_PUB RAM KEYS */
#define RAM_RSA_PUB_KEY0        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 0)
#define RAM_RSA_PUB_KEY1        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 3, 1)

/** @brief RSA_EXT RAM KEYS */
#define RAM_RSA_PUB_EXT_KEY0    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 4, 0)

#define RAM_ECC_PAIR_KEY0               GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 5, 0)
#define RAM_ECC_PAIR_KEY1               GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 5, 1)
#define RAM_ECC_PUB_KEY0                GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 6, 0)
#define RAM_SHARED_SECRET638_KEY0       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 7, 0)
#define RAM_SHARED_SECRET638_KEY1       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 7, 1)
#define RAM_SHARED_SECRET2048_KEY0      GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 8, 0)
#if 0
#define RAM_SHARED_SECRET1024_KEY1      GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 8, 1)
#endif



/** @brief AES 128 NVM KEYS */
#define NVM_AES128_KEY0         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 0)
#define NVM_AES128_KEY1         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 1)
#define NVM_AES128_KEY2         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 2)
#define NVM_AES128_KEY3         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 3)

/** @brief AES 256 NVM KEYS */
#define NVM_AES256_KEY0         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 0)
#define NVM_AES256_KEY1         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 1)
#define NVM_AES256_KEY2         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 2)
#define NVM_AES256_KEY3         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 3)
#define NVM_AES256_KEY4         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 4)
#define NVM_AES256_KEY5         GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 5)
#define NVM_OEM_AES256_KEY0     GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 10, 0)
#define NVM_OEM_AES256_KEY1     GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 10, 1)
#define NVM_OEM_AES256_KEY2     GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 10, 2)

/** @brief HMAC NVM KEYS */
#define NVM_HMAC_KEY0           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 0)

/** @brief ECC_PAIR NVM KEYS */
#define NVM_ECC_PAIR_KEY0       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 3, 0)
#define NVM_ECC_PAIR_KEY1       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 3, 1)

/** @brief ECC_PUB NVM KEYS */
#define NVM_ECC_PUB_KEY0        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 4, 0)
#define NVM_OEM_ECC_PUB_KEY0    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 13, 0)
#define NVM_OEM_ECC_PUB_KEY1    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 18, 0)

/** @brief ECC_PUB_EXT NVM KEYS */
#define NVM_ECC_PUB_EXT_KEY0    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 5, 0)
#define NVM_ECC_PUB_EXT_KEY1    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 5, 1)

/** @brief RSA_PAIR NVM KEYS */
#define NVM_RSA_PAIR_KEY0       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 6, 0)
#define NVM_RSA_PAIR_KEY1       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 6, 1)
#define NVM_RSA_PAIR_KEY2       GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 6, 2)

/** @brief RSA_PUB NVM KEYS */
#define NVM_RSA_PUB_KEY0        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 7, 0)
#define NVM_RSA_PUB_KEY1        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 7, 1)
#define NVM_OEM_RSA_PUB_KEY0    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 16, 0)

/** @brief RSA_EXT NVM KEYS */
#define NVM_RSA_PUB_EXT_KEY0    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 8, 0)
#define NVM_RSA_PUB_EXT_KEY1    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 8, 1)
#define NVM_RSA_PUB_EXT_KEY2    GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 8, 2)


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


#ifdef __cplusplus
}
#endif

#endif /* HSE_DEFAULT_CONFIG_H */

/** @} */
