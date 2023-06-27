/**
    @file        host_test.c
    @version     1.0.0

    @brief       Test functions in host application.
    @details     Test functions called in main function and requested to HSE via MU driver

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

#ifdef __cplusplus
extern "C"
{
#endif

#include "hse_she_api.h"
#include "hse_interface.h"
#include "hse_host_wrappers.h"
#include "hse_host_test.h"
#include "hse_she_commands.h"
#include "hse_memory_update_protocol.h"
#include "string.h"
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SHE_RAM_KEY_HANDLE (GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, (hseKeyGroupIdx_t)0U, (hseKeySlotIdx_t)0U))
#define BUFFER_SIZE (512U)
#define SHE_KEY_SIZE (16U)
#define MASTER_ECU_KEY_ID 0x01
#define NVM_KEY1_ID 0x04
#define NVM_KEY2_ID 0x05
#define NVM_KEY3_ID 0x06
#define NVM_KEY4_ID 0x07

    /*==================================================================================================
                                          FILE VERSION CHECKS
    ==================================================================================================*/

    /*==================================================================================================
                              LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL CONSTANTS
    ==================================================================================================*/
    /* Master ECU Key value */
    // static const uint8_t MASTER_ECU_KEY[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    /* Test vectors for AES ECB Encryption/Decryption */
    static const uint8_t aesEcbPlaintext[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    static const uint8_t aesEcbCiphertext[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

    /* Test vectors for AES CBC Encryption/Decryption */
    static uint8_t aes_cbc_test01_plaintext[] =
        {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
         0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e,
         0x51, 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a,
         0x52, 0xef, 0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6,
         0x6c, 0x37, 0x10};
    static uint8_t aes_cbc_test01_ciphertext[] =
        {0x76, 0x49, 0xAB, 0xAC, 0x81, 0x19, 0xB2, 0x46, 0xCE, 0xE9, 0x8E, 0x9B, 0x12, 0xE9, 0x19, 0x7D,
         0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78,
         0xb2, 0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22,
         0x95, 0x16, 0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75,
         0x86, 0xe1, 0xa7};
    static uint8_t cbc_test_case01_iv[] =
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    /* Test vectors for MAC Generation/Verification */
    static uint8_t aes_cmac_test01_message[] =
        {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
    static uint8_t aes_cmac_test01_tag_expected[] =
        {0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44, 0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c};

    /* constant value used to derive key used in debugging protocol */
    uint8_t DEBUG_KEY_C[] = {0x01, 0x03, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0};
    /*==================================================================================================
                                           LOCAL VARIABLES
    ==================================================================================================*/
    uint8_t testOutput[BUFFER_SIZE] = {0U};
    uint8_t testOutput1[256];

    /*==================================================================================================
                                           GLOBAL CONSTANTS
    ==================================================================================================*/

    /*==================================================================================================
                                           GLOBAL VARIABLES
    ==================================================================================================*/

    /*==================================================================================================

                                       LOCAL FUNCTION PROTOTYPES
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL FUNCTIONS
    ==================================================================================================*/

    /*==================================================================================================
                                           GLOBAL FUNCTIONS
    ==================================================================================================*/

    /*******************************************************************************
     * Function:    Test_ECB_ENC_DEC
     * Description: Test function for AES-ECB encryption and decryption
     ******************************************************************************/
    hseSrvResponse_t Test_ECB_ENC_DEC(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint32_t num_of_blocks = 1UL;

        srvResponse = she_cmd_enc_ecb(NVM_KEY1_ID, num_of_blocks, aesEcbPlaintext, testOutput);
        /* Check response and output */
        ASSERT((HSE_SRV_RSP_OK == srvResponse) && (0 == memcmp(testOutput, aesEcbCiphertext, sizeof(aesEcbCiphertext))));
        if ((HSE_SRV_RSP_OK != srvResponse) || (0 != memcmp(testOutput, aesEcbCiphertext, sizeof(aesEcbCiphertext))))
        {
            goto exit;
        }

        memset(testOutput, 0, BUFFER_SIZE);
        srvResponse = she_cmd_dec_ecb(NVM_KEY1_ID, num_of_blocks, aesEcbCiphertext, testOutput);
        /*Check response and output*/
        ASSERT((HSE_SRV_RSP_OK == srvResponse) && (0 == memcmp(testOutput, aesEcbPlaintext, sizeof(aesEcbPlaintext))));
        if ((HSE_SRV_RSP_OK != srvResponse) || (0 != memcmp(testOutput, aesEcbPlaintext, sizeof(aesEcbPlaintext))))
            goto exit;
    exit:
        return srvResponse;
    }
    /*******************************************************************************
     * Function:    Test_CBC_ENC_DEC
     * Description: Test function for CBC-AES encryption and decryption
     ******************************************************************************/
    hseSrvResponse_t Test_CBC_ENC_DEC(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint32_t num_of_blocks = 0U;

        if (sizeof(aes_cbc_test01_plaintext) % 16 != 0U)
            num_of_blocks = ((sizeof(aes_cbc_test01_plaintext) / 16) + 1);
        else
            num_of_blocks = (sizeof(aes_cbc_test01_plaintext) / 16);

        memset(testOutput, 0, BUFFER_SIZE);
        /*encrypted CBC*/
        srvResponse = she_cmd_enc_cbc(NVM_KEY2_ID, cbc_test_case01_iv, num_of_blocks, aes_cbc_test01_plaintext, testOutput);
        ASSERT((HSE_SRV_RSP_OK == srvResponse) || (0 == memcmp(testOutput, aes_cbc_test01_ciphertext, ARRAY_SIZE(aes_cbc_test01_ciphertext))));
        if ((HSE_SRV_RSP_OK != srvResponse) || (0 != memcmp(testOutput, aes_cbc_test01_ciphertext, ARRAY_SIZE(aes_cbc_test01_ciphertext))))
        {
            goto exit;
        }
        memset(testOutput, 0, BUFFER_SIZE);
        /*decrypted CBC*/
        srvResponse = she_cmd_dec_cbc(NVM_KEY2_ID, cbc_test_case01_iv, num_of_blocks, aes_cbc_test01_ciphertext, testOutput);
        ASSERT((HSE_SRV_RSP_OK == srvResponse) || (0 == memcmp(testOutput, aes_cbc_test01_plaintext, NUM_OF_ELEMS(aes_cbc_test01_plaintext))));
        if ((HSE_SRV_RSP_OK != srvResponse) || (0 != memcmp(testOutput, aes_cbc_test01_plaintext, NUM_OF_ELEMS(aes_cbc_test01_plaintext))))
        {
            goto exit;
        }
    exit:
        return srvResponse;
    }
    /*******************************************************************************
     * Function:    Test_CMAC_GENERATE_VERIFY
     * Description: Test function for CMAC generation and verification
     ******************************************************************************/
    hseSrvResponse_t Test_CMAC_GENERATE_VERIFY(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        /*generate cmac*/
        srvResponse = cmd_generate_mac(NVM_KEY3_ID, (ARRAY_SIZE(aes_cmac_test01_message) * 8), aes_cmac_test01_message, testOutput1);
        ASSERT((HSE_SRV_RSP_OK == srvResponse) || (0 == memcmp(testOutput1, aes_cmac_test01_tag_expected, ARRAY_SIZE(aes_cmac_test01_tag_expected))));
        if ((HSE_SRV_RSP_OK != srvResponse) || (0 != memcmp(testOutput1, aes_cmac_test01_tag_expected, ARRAY_SIZE(aes_cmac_test01_tag_expected))))
        {
            goto exit;
        }
        /*verify cmac*/
        srvResponse = cmd_verify_mac(NVM_KEY3_ID, (ARRAY_SIZE(aes_cmac_test01_message) * 8), aes_cmac_test01_message, aes_cmac_test01_tag_expected);
        if (HSE_SRV_RSP_OK == srvResponse)
        {
            goto exit;
        }
    exit:
        return srvResponse;
    }

    /*******************************************************************************
     * Function:    Test_SHE_LOAD_KEYS
     * Description: Test function for loading SHE keys
     ******************************************************************************/
    hseSrvResponse_t Test_SHE_LOAD_KEYS(void)
    {
        uint8_t M1[AES_BLOCK_SIZE];
        uint8_t M2[AES_BLOCK_SIZE * 2];
        uint8_t M3[AES_BLOCK_SIZE];
        uint8_t M4[AES_BLOCK_SIZE * 2];
        uint8_t M5[AES_BLOCK_SIZE];
        uint8_t M4_o[AES_BLOCK_SIZE * 2];
        uint8_t M5_o[AES_BLOCK_SIZE];
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t t_KeyNew[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
        uint8_t KeyId = NVM_KEY4_ID;
        uint8_t AuthId = MASTER_ECU_KEY_ID;
        uint32_t count_val = 0x01;
        uint8_t flag_val = 0x00;
        uint8_t groupId = 0x00;
        /* Calculate parameters M1, M2, M3 used for SHE Load Key*/
        srvResponse = Get_M1_M2_M3(MASTER_ECU_KEY, t_KeyNew, KeyId, AuthId, count_val, flag_val, M1, M2, M3);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            return srvResponse;
        }
        /* Calcualtion of Verification parameters M4, M5*/
        srvResponse = Get_M4_M5(MASTER_ECU_KEY, t_KeyNew, KeyId, AuthId, count_val, flag_val, M4_o, M5_o);
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            return srvResponse;
        }
        /* Issue Load Key Command */
        srvResponse = cmd_load_key(groupId, M1, M2, M3, M4, M5);
        if (HSE_SRV_RSP_OK != srvResponse)
        {
            return srvResponse;
        }
        /* Verify the verification prameters are equal */
        if (((0 == memcmp(M4, M4_o, ARRAY_SIZE(M4)))) && (0 == memcmp(M5, M5_o, ARRAY_SIZE(M5))))
        {
            return HSE_SRV_RSP_OK;
        }
        else
        {
            return HSE_SRV_RSP_GENERAL_ERROR;
        }
    }

    hseSrvResponse_t Test_SHE_LOAD_PLAIN_KEY(void)
    {
        // uint32_t sheLoadPlainKeyResult = 0UL;
        hseSrvResponse_t status;
        hseSrvResponse_t hseResponse;
        uint32_t resp = 0;
        uint8_t ramKey[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x00C, 0x0D, 0x0E, 0x0F};
        /*
         * the test vectors used for verifying the successful update of the keys
         */
        uint8_t plaintext[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa,
                               0xbb, 0xcc, 0xdd, 0xee, 0xff};
        uint8_t cipher[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80,
                            0x70, 0xb4, 0xc5, 0x5a};
        /*
         * Arrays to store the encrypted and decrypted values
         */
        uint8_t Output_Enc[AES_BLOCK_SIZE];
        uint8_t Output_Dec[AES_BLOCK_SIZE];
        /*
         *First we upload the RAM Key in plain format
         */
        status = cmd_load_plain_key(ramKey);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            goto exit;
        }

        /*
         * verify the successful encryption and decryption against the given test vectors
         */
        memset(Output_Enc, 0, sizeof(Output_Enc));
        memset(Output_Dec, 0, sizeof(Output_Dec));

        /* Encrypt the given plaintext with the key pointed by the SHE_RAM_KEY_HANDLE*/
        hseResponse = she_cmd_enc_ecb(0x0E, 1U, plaintext, Output_Enc);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
        {
            goto exit;
        }
        /* verify if the encrypted value matches the given cipher vector*/
        resp = memcmp(Output_Enc, cipher, ARRAY_SIZE(cipher));
        ASSERT(0 == resp);
        if (0 != resp)
        {
            goto exit;
        }
        /* Decrypt the given plaintext with the key pointed by the SHE_RAM_KEY_HANDLE*/
        hseResponse = she_cmd_dec_ecb(0x0E, 1U, Output_Enc, Output_Dec);
        ASSERT(HSE_SRV_RSP_OK == hseResponse);
        if (HSE_SRV_RSP_OK != hseResponse)
        {
            goto exit;
        }
        /* verify if the decrypted value matches the given plaintext vector*/
        resp = memcmp(Output_Dec, plaintext, ARRAY_SIZE(plaintext));
        ASSERT(0 == resp);
        if (0 != resp)
        {
            goto exit;
        }
    exit:
        return hseResponse;
    }
    /*******************************************************************************
     * Function:    Test_CMD_EXTEND_SEED
     * Description: Test function for generating Random Number Seed
     ******************************************************************************/
    hseSrvResponse_t Test_CMD_EXTEND_SEED(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t RandomNumber[16] = {0};
        srvResponse = cmd_extend_seed(RandomNumber);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        return srvResponse;
    }

    /*******************************************************************************
     * Function:    Test_RANDOM_NUM_REQ
     * Description: Test function for generating Random Number
     ******************************************************************************/
    hseSrvResponse_t Test_RANDOM_NUM_REQ(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t RandomNumber[16] = {0};
        srvResponse = cmd_rnd(RandomNumber);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        return srvResponse;
    }
    /*******************************************************************************
     * Function:    Test_SHE_GET_ID
     * Description: Test function for She Get ID
     ******************************************************************************/
    hseSrvResponse_t Test_SHE_GET_ID(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t ramKey[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x00C, 0x0D, 0x0E, 0x0F};
        uint8_t randomChallenge[16] =
            {0U};
        uint8_t uid[15] =
            {0U};
        uint8_t sReg = 0U;
        uint8_t hseMac[16] =
            {0U};
        uint8_t inputForCmac[32] =
            {0U};
        uint8_t hostMac[16] =
            {0U};
        srvResponse = cmd_rnd(randomChallenge);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        srvResponse = cmd_get_id(randomChallenge, uid, &sReg, hseMac);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        memcpy(&inputForCmac[0], randomChallenge, sizeof(randomChallenge));
        memcpy(&inputForCmac[16], uid, sizeof(uid));
        memcpy(&inputForCmac[31], &sReg, 1UL);

        /* Loading RAM key using SHE Load Plain key service. Use same key value which was
         * loaded in SHE_MASTER_ECU_KEY_HANDLE in SHE Load key service */
        srvResponse = SheLoadPlainKey(ramKey);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* Generating CMAC over (randomChallenge | uid | sReg) on host side using key which
         * was loaded in SHE_MASTER_ECU_KEY_HANDLE */
        srvResponse = cmd_generate_mac(RAM_KEY_ID, (sizeof(inputForCmac) * 8), inputForCmac, hostMac);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        ASSERT(0 == memcmp(hseMac, hostMac, 16UL));
        return srvResponse;
    }

    /*******************************************************************************
     * Function:    Test_EXPORT_RAM_KEY
     * Description: Test function for exporting RAM key, Verifies that the RAM Key can be exported when updated in plain format
     ******************************************************************************/
    hseSrvResponse_t Test_EXPORT_RAM_KEY(void)
    {
        hseSrvResponse_t status;
        uint8_t M1[AES_BLOCK_SIZE];
        uint8_t M2[AES_BLOCK_SIZE * 2];
        uint8_t M3[AES_BLOCK_SIZE];
        uint8_t M4[AES_BLOCK_SIZE * 2];
        uint8_t M5[AES_BLOCK_SIZE];
        uint8_t tempM4_MUP[32] = {0U};
        uint8_t tempM5_MUP[16] = {0U};
        uint8_t tempM4_LPK[32] = {0U};
        uint8_t tempM5_LPK[16] = {0U};
        uint8_t AuthKey[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
        uint8_t ramKey[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x00C, 0x0D, 0x0E, 0x0F};
        /* Key to be updated */
        uint8_t KeyId = RAM_KEY_ID;
        /* Auth Key */
        uint8_t AuthId = NVM_KEY4_ID;
        uint32_t count_val = 0x00UL;
        uint8_t flag_val = 0x00U;
        uint8_t groupId = 0x00U;
        status = Get_M1_M2_M3(AuthKey, ramKey, KeyId, AuthId, count_val, flag_val, M1, M2, M3);
        /* Send Load Key Command */
        status = cmd_load_key(groupId, M1, M2, M3, M4, M5);
        /*
         * Verify that the Export RAM Key will not be successful after we update RAM
         * Key with SHE MemoryUpdate Protocol
         */
        status = cmd_export_ram_key(M1, M2, M3, tempM4_MUP, tempM5_MUP);
        ASSERT(HSE_SRV_RSP_KEY_INVALID == status);
        /*
         * Verify that the Export RAM Key will be successful after we update RAM
         * Key with LoadPlainKey command
         */
        status = cmd_load_plain_key(ramKey);
        ASSERT(HSE_SRV_RSP_OK == status);
        status = cmd_export_ram_key(M1, M2, M3, tempM4_LPK, tempM5_LPK);
        ASSERT(HSE_SRV_RSP_OK == status);
        return status;
    }

    /*******************************************************************************
     * Function:    Test_GET_RAND_NUM_REQ
     * Description:Test function for generating random number
     ******************************************************************************/
    hseSrvResponse_t Test_CMD_TRNG_RND(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        uint8_t RandomNumber[16] = {0};
        srvResponse = cmd_trng_rnd(RandomNumber);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
        return srvResponse;
    }
    /*******************************************************************************
     * Function:    Test_CMD_DEBUG_CHAL_AUTH
     * Description:Test function for getting debug challenge
     ******************************************************************************/
    hseSrvResponse_t Test_CMD_DEBUG_CHAL_AUTH(void)
    {
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
        srvResponse = cmd_debug_chal_auth();
        return srvResponse;
    }
