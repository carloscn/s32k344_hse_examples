/**
 *   @file    hse_memory_update_protocol.c
 *
 *   @brief   This file is used to test SHE Key Memory Update commands
 *   @details
 *
 *   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
 *   @{
 */
/*==================================================================================================
 *   Copyright 2022 NXP. .
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

#ifdef __cplusplus
extern "C"
{
#endif

    /*==================================================================================================
     *                                        INCLUDE FILES
     ==================================================================================================*/

#include "hse_host.h"
#include "hse_interface.h"
#include "string.h"
#include "hse_default_config.h"
#include "global_defs.h"
#include "hse_b_catalog_formatting.h"
#include "hse_host_rng.h"
#include "hse_host_mac.h"
#include "hse_host_format_key_catalogs.h"
#include "hse_host_cipher.h"
#include "hse_host_import_key.h"
#include "hse_she_api.h"
#include "hse_memory_update_protocol.h"

#ifdef HSE_SPT_SHE
/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/
#define RAM_KEY_ID 0x0E
#define KEY_SIZE_IN_WORD 4
#define AES_BLOCK_SIZE 16

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

    /*==================================================================================================
     *                                      LOCAL CONSTANTS
     ==================================================================================================*/

    /*==================================================================================================
     *                                      LOCAL VARIABLES
     ==================================================================================================*/

    /*==================================================================================================
     *                                      GLOBAL CONSTANTS
     ==================================================================================================*/

    /*==================================================================================================
     *                                      GLOBAL VARIABLES
     ==================================================================================================*/

    /*==================================================================================================
     *                                   LOCAL FUNCTION PROTOTYPES
     ==================================================================================================*/

    /*==================================================================================================
     *                                       LOCAL FUNCTIONS
     ==================================================================================================*/
    hseSrvResponse_t hse_kdf(uint8_t *plaintext, uint8_t *dst, uint32_t numblocks);

    /*==================================================================================================
     *                                       GLOBAL FUNCTIONS
     ==================================================================================================*/

    /********************************************************************************
     * Function:    hse_kdf
     *
     * Description: This function is used to  derive the key values e.g. K1, K2, K3 , K4.
     ********************************************************************************/

    hseSrvResponse_t hse_kdf(uint8_t *plaintext, uint8_t *dst, uint32_t numblocks)
    {
        hseSrvResponse_t hseResponse;
        /*Load IV as RAM key*/
        /* IV is loaded to RAM KEY */
        uint8_t *temp;
        uint8_t cipher[16] = {0U};
        uint8_t iv[16] = {0U};

        temp = dst;
        uint8_t ptr_plaintext = 0U;
        uint8_t t_plaintext[AES_BLOCK_SIZE];
        while (numblocks)
        {
            /*Load IV as RAM key*/
            /* IV is loaded to RAM KEY */
            for (uint32_t i = 0U; i < AES_BLOCK_SIZE; i++)
            {
                t_plaintext[i] = plaintext[i + (AES_BLOCK_SIZE * ptr_plaintext)];
            }
            SheLoadPlainKey(iv);
            /*Calculate ECB ENC over 128 bit chunk of Plaintext*/
            /* prepares data structure for encrypt ECB command */
            hseResponse = AesEncrypt(HSE_DEMO_SHE_RAM_KEY_HANDLE, HSE_CIPHER_BLOCK_MODE_ECB, iv, ARRAY_SIZE(t_plaintext),
                                     t_plaintext, cipher, HSE_SGT_OPTION_NONE);
            if (HSE_SRV_RSP_OK != hseResponse)
            {
                return hseResponse;
            }
            numblocks--;
            for (uint32_t i = 0U; i < AES_BLOCK_SIZE; i++)
            {
                iv[i] = iv[i] ^ cipher[i] ^ plaintext[i + (AES_BLOCK_SIZE * ptr_plaintext)];
            }
            ptr_plaintext++;
        }
        memcpy(temp, iv, ARRAY_SIZE(iv));
        return hseResponse;
    }

#endif

#ifdef __cplusplus
}
#endif

/** @} */
