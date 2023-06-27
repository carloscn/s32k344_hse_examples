/**
    @file        she_commands.c
    @version     1.0.0

    @brief       Implementation of SHE commands.
    @details     Contains function implementation for SHE commands

    This file contains sample code only. It is not part of the production code deliverables.
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
/*==================================================================================================
 ==================================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*==================================================================================================
     *                                        INCLUDE FILES
     ==================================================================================================*/

#include "hse_memory_update_protocol.h"
#include "hse_host_wrappers.h"
#include "hse_interface.h"
#include "hse_she_commands.h"
#include "hse_she_api.h"
#include "string.h"
#include "hse_host_test.h"
#include "hse_host_mac.h"
    /*==================================================================================================
     *                                      LOCAL VARIABLES
     ==================================================================================================*/
    /*==================================================================================================
     *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
     ==================================================================================================*/
    /*==================================================================================================
     *                                       LOCAL MACROS
     ==================================================================================================*/

#define SHE_GROUP_0 (hseKeyGroupIdx_t)0U
#define SHE_SECRET_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_ROM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U))
#define SHE_MASTER_ECU_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U))
#define SHE_BOOT_MAC_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)1U))
#define SHE_RAM_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U))
#define AES_RAM_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, (hseKeyGroupIdx_t)1U, (hseKeySlotIdx_t)0U))
#define SHE_KEY_SIZE (16U)
#define GEN_BUFFER_SIZE (256U)
    // #define RAM_KEY_ID                      (0x0E)

    /*==================================================================================================
     *                                      LOCAL CONSTANTS
     ==================================================================================================*/
    /* Array to get the Key Handle Value for Key IDs */
    uint32_t key_id_to_key_handle_table[15] = {
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_ROM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)1U),
        HSE_INVALID_KEY_HANDLE,
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)2U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)3U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)4U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)5U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)6U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)7U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)8U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)9U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)10U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)11U),
        GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0)};
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

    /*==================================================================================================
     *                                       GLOBAL FUNCTIONS
     ==================================================================================================*/

    /*******************************************************************************
     * Function:    she_cmd_enc_ecb
     * Description: Wrapper function for sending AES-ECB encryption request
     ******************************************************************************/
    hseSrvResponse_t she_cmd_enc_ecb(
        uint32_t keyId,
        uint32_t num_of_blocks,
        const uint8_t *pInput,
        uint8_t *pOutput)
    {
        uint8_t iv[16] = {0U};
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];
        return SymCipherReq(
            HSE_ACCESS_MODE_ONE_PASS,
            HSE_CIPHER_ALGO_AES,
            HSE_CIPHER_BLOCK_MODE_ECB,
            HSE_CIPHER_DIR_ENCRYPT,
            KeyHandle,
            iv,
            (num_of_blocks * 16), // 1 block=16 bytes
            pInput,
            pOutput,
            HSE_SGT_OPTION_NONE);
    }

    /*******************************************************************************
     * Function:    she_cmd_dec_ecb
     * Description: Wrapper function for sending AES-ECB decryption request
     ******************************************************************************/
    hseSrvResponse_t she_cmd_dec_ecb(
        uint32_t keyId,
        uint32_t num_of_blocks,
        const uint8_t *pInput,
        uint8_t *pOutput)
    {
        uint8_t iv[16] = {0U};
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];
        return SymCipherReq(
            HSE_ACCESS_MODE_ONE_PASS,
            HSE_CIPHER_ALGO_AES,
            HSE_CIPHER_BLOCK_MODE_ECB,
            HSE_CIPHER_DIR_DECRYPT,
            KeyHandle,
            iv,
            (num_of_blocks * 16), // 1 block=16 bytes
            pInput,
            pOutput,
            HSE_SGT_OPTION_NONE);
    }

    /*******************************************************************************
     * Function:    she_cmd_enc_cbc
     * Description: Wrapper function for sending CBC encryption request
     ******************************************************************************/
    hseSrvResponse_t she_cmd_enc_cbc(
        uint32_t keyId,
        const uint8_t *pIV,
        uint32_t num_of_blocks,
        const uint8_t *pInput,
        uint8_t *pOutput)
    {
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];

        return SymCipherReq(
            HSE_ACCESS_MODE_ONE_PASS,
            HSE_CIPHER_ALGO_AES,
            HSE_CIPHER_BLOCK_MODE_CBC,
            HSE_CIPHER_DIR_ENCRYPT,
            KeyHandle,
            pIV,
            (num_of_blocks * 16), // 1 block=16 bytes
            pInput,
            pOutput,
            HSE_SGT_OPTION_NONE);
    }

    /*******************************************************************************
     * Function:    she_cmd_dec_cbc
     * Description: Wrapper function for sending CBC decryption request
     ******************************************************************************/
    hseSrvResponse_t she_cmd_dec_cbc(
        uint32_t keyId,
        const uint8_t *pIV,
        uint32_t num_of_blocks,
        const uint8_t *pInput,
        uint8_t *pOutput)
    {
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];
        return SymCipherReq(
            HSE_ACCESS_MODE_ONE_PASS,
            HSE_CIPHER_ALGO_AES,
            HSE_CIPHER_BLOCK_MODE_CBC,
            HSE_CIPHER_DIR_DECRYPT,
            KeyHandle,
            pIV,
            (num_of_blocks * 16), // 1 block=16 bytes
            pInput,
            pOutput,
            HSE_SGT_OPTION_NONE);
    }

    /*******************************************************************************
     * Function:    cmd_generate_mac
     * Description: Wrapper function for requesting to generate CMAC
     ******************************************************************************/
    hseSrvResponse_t cmd_generate_mac(
        uint32_t keyId,
        uint32_t message_length_in_bits,
        const uint8_t *pInput,
        uint8_t *pTag)
    {
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];
        uint32_t TagLength_in_bits = 128UL;
        return AesFastCmacGenerate(
            KeyHandle,
            message_length_in_bits,
            pInput,
            TagLength_in_bits,
            pTag);
    }

    /*******************************************************************************
     * Function:    cmd_verify_mac
     * Description: Wrapper function for requesting for verifying CMAC
     ******************************************************************************/
    hseSrvResponse_t cmd_verify_mac(
        uint32_t keyId,
        uint32_t message_length_in_bits,
        const uint8_t *pInput,
        uint8_t *pTag)
    {
        uint32_t KeyHandle = key_id_to_key_handle_table[keyId];
        uint32_t TagLength_in_bits = 128UL;
        return AesFastCmacVerify(
            KeyHandle,
            message_length_in_bits,
            pInput,
            TagLength_in_bits,
            pTag);
    }

    /*******************************************************************************
     * Function:    cmd_load_key
     * Description: Wrapper function for loading SHE keys
     ******************************************************************************/
    hseSrvResponse_t cmd_load_key(uint8_t sheGroupId, uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5)
    {
        return SheLoadKey(sheGroupId, M1, M2, M3, M4, M5);
    }

    /*******************************************************************************
     * Function:    cmd_load_plain_key
     * Description: Wrapper function for loading RAM Key in plain format
     ******************************************************************************/
    hseSrvResponse_t cmd_load_plain_key(const uint8_t *pKey)
    {
        return SheLoadPlainKey(pKey);
    }

    /*******************************************************************************
     * Function:    cmd_export_ram_key
     * Description: Wrapper function for exporting SHE keys
     ******************************************************************************/
    hseSrvResponse_t cmd_export_ram_key(uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5)
    {
        return SheExportRamKey(M1, M2, M3, M4, M5);
    }

    /*******************************************************************************
     * Function:    cmd_extend_seed
     * Description: Wrapper function for generating random number seed
     ******************************************************************************/
    hseSrvResponse_t cmd_extend_seed(uint8_t *rngNum)
    {
        return getRandomNumReq(HSE_RNG_CLASS_DRG4, 16U, rngNum);
    }
    /*******************************************************************************
     * Function:    cmd_rnd
     * Description: Wrapper function for generating random number
     ******************************************************************************/
    hseSrvResponse_t cmd_rnd(uint8_t *rngNum)
    {
        return getRandomNumReq(HSE_RNG_CLASS_DRG3, 16U, rngNum);
    }

    /*******************************************************************************
     * Function:    cmd_trng_rnd
     * Description: Wrapper function for generating random number
     ******************************************************************************/
    hseSrvResponse_t cmd_trng_rnd(uint8_t *rngNum)
    {
        return getRandomNumReq(HSE_RNG_CLASS_DRG4, 16U, rngNum);
    }
    /*******************************************************************************
     * Function:    cmd_get_id
     * Description: Wrapper function for requesting ID
     ******************************************************************************/
    hseSrvResponse_t cmd_get_id(uint8_t *pChallenge, uint8_t *pId, uint8_t *pSreg, uint8_t *pMac)
    {
        return SheGetId(pChallenge, pId, pSreg, pMac);
    }

    /*******************************************************************************
     * Function:    cmd_debug_chal
     * Description: Wrapper function for debug challenge for sys auth
     ******************************************************************************/
    hseSrvResponse_t cmd_debug_chal(uint8_t *pChallenge)
    {
        hseAuthScheme_t cmacAuthScheme = {
            .macScheme.macAlgo = HSE_MAC_ALGO_CMAC,
            .macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES};
        return SysAuthorizationReq(HSE_SYS_AUTH_ALL, HSE_RIGHTS_SUPER_USER, MASTER_ECU_KEY_HANDLE, &cmacAuthScheme, pChallenge);
    }
    /*******************************************************************************
     * Function:    cmd_debug_auth
     * Description: Wrapper function for debug authorization for sys auth
     ******************************************************************************/
    hseSrvResponse_t cmd_debug_auth(uint8_t *pAuthVal)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        srvResponse = SysAuthorizationResp(pAuthVal, 16UL, NULL, 0U);
        return srvResponse;
    }

    hseSrvResponse_t cmd_debug_chal_auth(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t input[4U * SHE_KEY_SIZE] = {0};
        uint8_t output[SHE_KEY_SIZE] = {0};
        uint8_t K_auth[SHE_KEY_SIZE] = {0};
        uint8_t challenge[2U * SHE_KEY_SIZE] = {0};
        uint32_t outLen = SHE_KEY_SIZE;
        /* Downgrade to User rights */
        srvResponse = SysAuth_User();
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
            return srvResponse;

        /* Get the Challenge value */
        srvResponse = cmd_debug_chal(challenge);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
            return srvResponse;

        /* Derive key from MASTER_ECU_KEY with DEBUG_KEY_C for challenge response
         * K = KDF(KEYMASTER_ECU_KEY, DEBUG_KEY_C)
         */
        memcpy(input, MASTER_ECU_KEY, SHE_KEY_SIZE);
        memcpy(&input[SHE_KEY_SIZE], DEBUG_KEY_C, SHE_KEY_SIZE);
        srvResponse = HostKdf(2U * SHE_KEY_SIZE, input, &outLen, K_auth, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
            return srvResponse;
        memset(output, 0, sizeof(output));

        /* Load derievd key in RAM */
        srvResponse = SheLoadPlainKey(K_auth);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
            return srvResponse;

        /* Gen CMAC with the derived Key */
        srvResponse = cmd_generate_mac(RAM_KEY_ID, ((2 * SHE_KEY_SIZE - 1) * 8), challenge, output);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
            return srvResponse;
        /* Send Debug AUth Command */
        srvResponse = cmd_debug_auth(output);
        return srvResponse;
    }

#ifdef __cplusplus
}
#endif

/** @} */
