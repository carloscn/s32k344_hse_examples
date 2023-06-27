/**
 *   @file    memory_update_protocol.c
 *
 *   @brief   This file contains teh memory update protocol implementation
 *   @details
 *
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

#include "hse_interface.h"
#include <string.h>
#include "hse_host_wrappers.h"
#include "hse_she_api.h"
#include "hse_she_commands.h"
#include "hse_memory_update_protocol.h"
/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/
#define RAM_AES128_KEY0                 GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 0)
#define SHE_RAM_KEY_HANDLE              RAM_AES128_KEY0
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

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/

/********************************************************************************
 * Function:    MemoryUpdateProtocol
 * @brief       This function is used to prepare Load Key Parameters based on SHE Memory Update Protocol.
 * @details     The new key value is loaded/updated as per the SHE Menory Update Protocol.
 *              The Updated is verified by checking the authentication values we receive from HSE
 *              against the values we calculate locally. If these values are equal HSE_SRV_RSP_OK is sent
 *              to the calling test case.
 ******************************************************************************/

hseSrvResponse_t MemoryUpdateProtocol(MemoryUpdate_t *pMemUpdate)
{
    hseSrvResponse_t status;
    
    const uint8_t KEY_UPDATE_ENC_C[AES_BLOCK_SIZE] =
    { 0x01, 0x01, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0 };
    const uint8_t KEY_UPDATE_MAC_C[AES_BLOCK_SIZE] =
    { 0x01, 0x02, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0 };

    /* Initialization Vector */
    uint8_t IV[AES_BLOCK_SIZE] =
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t K1[AES_BLOCK_SIZE];
    uint8_t K2[AES_BLOCK_SIZE];
    uint8_t K3[AES_BLOCK_SIZE];
    uint8_t K4[AES_BLOCK_SIZE];

    uint8_t M1[AES_BLOCK_SIZE];
    uint8_t M2_t[AES_BLOCK_SIZE * 2];
    uint8_t M2[AES_BLOCK_SIZE * 2];
    uint8_t M3_t[AES_BLOCK_SIZE * 3];
    uint8_t M3[AES_BLOCK_SIZE];
    uint8_t M4_t[AES_BLOCK_SIZE];
    uint8_t M4_te[AES_BLOCK_SIZE];
    uint8_t M4[AES_BLOCK_SIZE * 2];
    uint8_t M4_o[AES_BLOCK_SIZE * 2];
    uint8_t M5_o[AES_BLOCK_SIZE];
    uint8_t M5[AES_BLOCK_SIZE];
    uint8_t plaintext[AES_BLOCK_SIZE * 2];
    int i = 0;
    uint32_t outLen;
/* Generate K1 */
    /* K1 = KDF(KAuthID, KEY_UPDATE_ENC_C) */
    for(i = 0; i < AES_BLOCK_SIZE; i++)
    {
        plaintext[i] = pMemUpdate->AuthKey[i];
    }
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
    {
        plaintext[i] = KEY_UPDATE_ENC_C[i - AES_BLOCK_SIZE];
    }
    /* running KDF function to get K1 */
    outLen = ARRAY_SIZE(K1);
    status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K1, HSE_SGT_OPTION_NONE);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }

/*Generate K2*/
    /* K2 = KDF(KAuthID,KEY_UPDATE_MAC_C) */
    for(i = 0; i < AES_BLOCK_SIZE; i++)
    {
        plaintext[i] = pMemUpdate->AuthKey[i];
    }
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
    {
        plaintext[i] = KEY_UPDATE_MAC_C[i - AES_BLOCK_SIZE];
    }
    /* running KDF function to get K2 */
    outLen = ARRAY_SIZE(K2);
    status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K2, HSE_SGT_OPTION_NONE);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }
/* generate M1 */
    /* M1 = UIDâ€™|ID|AuthID */
    for(i = 0; i < 15; i++)
    {
        M1[i] = pMemUpdate->uid[i];
    }
    /* key to be updated and authorizing key ID */
    M1[15] = (pMemUpdate->KeyId << 4 & 0xF0) | (pMemUpdate->AuthId & 0x0F);
/* generate M2 */
    /* M2 = ENCCBC,K1,IV=0(CIDâ€™|FIDâ€™|â€œ0...0"95|KIDâ€™)*/
    M2_t[0] = ((pMemUpdate->count_val >> 20) & 0xFF);
    M2_t[1] = ((pMemUpdate->count_val >> 12) & 0xFF);
    M2_t[2] = ((pMemUpdate->count_val >> 4) & 0xFF);
    M2_t[3] = ((pMemUpdate->count_val << 4) & 0xF0) | ((pMemUpdate->flag_val >> 2) & 0x0F);
    M2_t[4] = ((pMemUpdate->flag_val << 6) & 0xC0);
    for(i = 5; i < 16; i++)
    {
        M2_t[i] = 0x00;
    }
    for(i = 16; i < AES_BLOCK_SIZE * 2; i++)
    {
        M2_t[i] = pMemUpdate->KeyNew[i - AES_BLOCK_SIZE];
    }
/* Load K1 in RAM key */
    status = SheLoadPlainKey(K1);
    ASSERT(HSE_SRV_RSP_OK == status);
    /*ASSERT(HSE_SRV_RSP_OK == LoadAesKey(SHE_RAM_KEY_HANDLE, ARRAY_SIZE(K1), K1));*/
    memset(M2, 0, AES_BLOCK_SIZE * 2);
/*CBC ENCRYPT M2_t using K1 to get M2*/
    status = she_cmd_enc_cbc(RAM_KEY_ID, IV, 2U, M2_t, M2);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }
/* generate M3 */
    /* M3 = CMACK2(M1|M2) */
    /*Load K2 in RAM key*/

    status = SheLoadPlainKey(K2);
    ASSERT(HSE_SRV_RSP_OK == status);

/*Generate (M1|M2)*/
    for(i = 0; i < AES_BLOCK_SIZE; i++)
    {
        M3_t[i] = M1[i];
    }
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 3; i++)
    {
        M3_t[i] = M2[i - AES_BLOCK_SIZE];
    }

    /*generate MAC over (M1|M2) to get M3*/
    status = cmd_generate_mac(RAM_KEY_ID, (ARRAY_SIZE(M3_t)*8), M3_t, M3 );
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }

/* key to be updated and authorizing key ID */
    M1[15] = (pMemUpdate->KeyId << 4 & 0xF0) | (pMemUpdate->AuthId & 0x0F);
/* load key to the Key Storage Area */
    status = SheLoadKey(pMemUpdate->sheGroupId, M1, M2, M3, M4_o, M5_o);
    /*ASSERT(HSE_SRV_RSP_OK == status);*/
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }

/*Get K3*/
    /* K3 = KDF(KEYID,KEY_UPDATE_ENC_C) */
    for(i = 0; i < AES_BLOCK_SIZE; i++)
    {
        plaintext[i] = pMemUpdate->KeyNew[i];
    }
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
    {
        plaintext[i] = KEY_UPDATE_ENC_C [i - AES_BLOCK_SIZE];
    }
    outLen  = ARRAY_SIZE(K3);
    status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K3, HSE_SGT_OPTION_NONE);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }

/*Get K4*/
    /* K4 = KDF (KEYID,KEY_UPDATE_MAC_C) */
    /*for(i=0;i<KEY_SIZE_IN_WORD;i++)*/
    for(i = 0; i < AES_BLOCK_SIZE; i++)
    {
        plaintext[i] = pMemUpdate->KeyNew[i];
    }
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
    {
        plaintext[i] = KEY_UPDATE_MAC_C [i - AES_BLOCK_SIZE];
    }
    outLen  = ARRAY_SIZE(K4);
    status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K4, HSE_SGT_OPTION_NONE);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }

/* Generate M4 */

    /* M4 = UID|ID|AuthID|M4*
     * M4* - the encrypted counter value; prior to encryption the counter
     * value (28 bits) is padded with a 1 and 99 0â€™s.
     * The key for the ECB encryption is K3
     */
    M4_t[0] = ((pMemUpdate->count_val >> 20) & 0xFF);
    M4_t[1] = ((pMemUpdate->count_val >> 12) & 0xFF);
    M4_t[2] = ((pMemUpdate->count_val >> 4) & 0xFF);
    // M4_t[3] = ((pMemUpdate->count_val<<4) & 0xF0)|0x08;
    M4_t[3] = ((pMemUpdate->count_val << 4) & 0xF0);
    /*Single "1"-bit Padding followed by "0"-bits on the LSB side*/
    M4_t[3] |= (uint8_t)(1UL << 3U);
    for(i = 4; i < AES_BLOCK_SIZE; i++)
    {
        M4_t[i] = 0x00;
    }
/* Load K3 in RAM key */
    status = SheLoadPlainKey(K3);
    ASSERT(HSE_SRV_RSP_OK == status);
    memset(M4_te, 0, sizeof(M4_te));
/*ECB ENCRYPT */
    status = she_cmd_enc_ecb(RAM_KEY_ID, 1U, M4_t, M4_te);
    ASSERT(HSE_SRV_RSP_OK == status);
    if(HSE_SRV_RSP_OK != status)
    {
        return status;
    }
    
    for(i = 0; i < (AES_BLOCK_SIZE - 1); i++)
    {
        M4[i] = pMemUpdate->uid[i];
    }
    M4[15] = ((((uint8_t)pMemUpdate->KeyId) << 4U) & 0xF0U) | (((uint8_t)pMemUpdate->AuthId) & 0x0FU);
    for(i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
    {
        M4[i] = M4_te[i - AES_BLOCK_SIZE];
    }

/* Generate M5 */
    /* M5 = CMACK4(M4) */
    status = SheLoadPlainKey(K4);
    ASSERT(HSE_SRV_RSP_OK == status);
/* Generate MAC to get M5 */
    ASSERT(HSE_SRV_RSP_OK == cmd_generate_mac(RAM_KEY_ID, (ARRAY_SIZE(M4)*8), M4, M5 ));
                                            
/* check if M4 and M5 are equal */
    /*ASSERT(0 == memcmp(M4, M4_o, ARRAY_SIZE(M4)));*/
    /*ASSERT(0 == memcmp(M5, M5_o,ARRAY_SIZE(M5)));*/
    if(((0 == memcmp(M4, M4_o, ARRAY_SIZE(M4)))) && (0 == memcmp(M5, M5_o, ARRAY_SIZE(M5))))
    {
        return HSE_SRV_RSP_OK;
    }
    else
    {
        return HSE_SRV_RSP_GENERAL_ERROR;
    }

}

#ifdef __cplusplus
}
#endif

/** @} */

