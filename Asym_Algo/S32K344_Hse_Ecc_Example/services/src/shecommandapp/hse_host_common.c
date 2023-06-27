/**
    @file        host_common.c
    @version     1.0.0

    @brief       HSE - Host SHE command application
    @details     Sample application demonstrating host request SHE commands using MU driver.
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

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "hse_she_api.h"
#include "hse_interface.h"
#include "hse_host.h"
#include "hse_host_wrappers.h"
#include "hse_she_commands.h"
#include "hse_memory_update_protocol.h"
#include "hse_host_import_key.h"
#include "hse_host_rng.h"
#include "hse_host_mac.h"
#include <string.h>

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define BUFFER_SIZE (512U)
    /*==================================================================================================
                                          FILE VERSION CHECKS
    ==================================================================================================*/

    /*==================================================================================================
                              LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL CONSTANTS
    ==================================================================================================*/

    /*==================================================================================================
                                           LOCAL VARIABLES
    ==================================================================================================*/
    static uint8_t muIf = 0U;         /* MU0 */
    static uint8_t muChannelIdx = 1U; /* channel 1 */
    static hseTxOptions_t txOptions = {HSE_TX_SYNCHRONOUS, NULL, NULL};

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
     * Function:    SheGetId
     *
     * Description: This function is used to issue SheGetId service.
     *
     ******************************************************************************/
    hseSrvResponse_t SheGetId(uint8_t *pChallenge, uint8_t *pId, uint8_t *pSreg, uint8_t *pMac)
    {

        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSheGetIdSrv_t *pSheGetIdReq = &pHseSrvDesc->hseSrv.sheGetIdReq;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_SHE_GET_ID;
        pSheGetIdReq->pChallenge = (HOST_ADDR)pChallenge;
        pSheGetIdReq->pId = (HOST_ADDR)pId;
        pSheGetIdReq->pSreg = (HOST_ADDR)pSreg;
        pSheGetIdReq->pMac = (HOST_ADDR)pMac;

        return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    SheLoadKey
     *
     * Description: This function is used to test She Load Key Command.
     *
     ******************************************************************************/
    hseSrvResponse_t SheLoadKey(uint8_t sheGroupId, uint8_t *M1, uint8_t *M2,
                                uint8_t *M3, uint8_t *M4, uint8_t *M5)
    {

        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSheLoadKeySrv_t *pSheLoadKeyReq = &pHseSrvDesc->hseSrv.sheLoadKeyReq;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_SHE_LOAD_KEY;
        pSheLoadKeyReq->sheGroupIndex = (hseKeyGroupIdx_t)sheGroupId;
        pSheLoadKeyReq->pM1 = (HOST_ADDR)M1;
        pSheLoadKeyReq->pM2 = (HOST_ADDR)M2;
        pSheLoadKeyReq->pM3 = (HOST_ADDR)M3;
        pSheLoadKeyReq->pM4 = (HOST_ADDR)M4;
        pSheLoadKeyReq->pM5 = (HOST_ADDR)M5;

        return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    SheExportRamKey
     *
     * Description: This function is used to send She Export Ram Key Command.
     *
     ******************************************************************************/
    hseSrvResponse_t SheExportRamKey(uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5)
    {

        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSheExportRamKeySrv_t *pSheExportRamKeyReq = &pHseSrvDesc->hseSrv.sheExportRamKeyReq;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_SHE_EXPORT_RAM_KEY;
        pSheExportRamKeyReq->pM1 = (HOST_ADDR)M1;
        pSheExportRamKeyReq->pM2 = (HOST_ADDR)M2;
        pSheExportRamKeyReq->pM3 = (HOST_ADDR)M3;
        pSheExportRamKeyReq->pM4 = (HOST_ADDR)M4;
        pSheExportRamKeyReq->pM5 = (HOST_ADDR)M5;

        return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    getRandomNumReq
     *
     * Description: This function is used to get random number.
     *
     ******************************************************************************/
    hseSrvResponse_t getRandomNumReq(hseRngClass_t rngClass, uint32_t rngNumSize, uint8_t *rngNum)
    {
        hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseGetRandomNumSrv_t *pGetRndSrv;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_GET_RANDOM_NUM;
        pGetRndSrv = &(pHseSrvDesc->hseSrv.getRandomNumReq);
        pGetRndSrv->rngClass = rngClass;
        pGetRndSrv->pRandomNum = (HOST_ADDR)rngNum;
        pGetRndSrv->randomNumLength = rngNumSize;

        hseStatus = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
        return hseStatus;
    }

    /*******************************************************************************
     * Function:    SymCipherReq
     *
     * Description: This function is used to send symmetric cipher request.
     *
     ******************************************************************************/
    hseSrvResponse_t SymCipherReq(
        hseAccessMode_t accessMode,
        hseCipherAlgo_t cipherAlgo,
        hseCipherBlockMode_t cipherBlockMode,
        hseCipherDir_t cipherDir,
        hseKeyHandle_t keyHandle,
        const uint8_t *pIV,
        uint32_t inputLength,
        const uint8_t *pInput,
        uint8_t *pOutput,
        hseSGTOption_t inputSgtType)
    {
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSymCipherSrv_t *pSymCipherReq;
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        pHseSrvDesc->srvId = HSE_SRV_ID_SYM_CIPHER;
        pSymCipherReq = &pHseSrvDesc->hseSrv.symCipherReq;

        pSymCipherReq->accessMode = accessMode;
        pSymCipherReq->cipherAlgo = cipherAlgo;
        pSymCipherReq->cipherBlockMode = cipherBlockMode;
        pSymCipherReq->cipherDir = cipherDir;
        pSymCipherReq->keyHandle = keyHandle;

        pSymCipherReq->pIV = (HOST_ADDR)pIV;
        pSymCipherReq->inputLength = inputLength;
        pSymCipherReq->pInput = (HOST_ADDR)pInput;
        pSymCipherReq->pOutput = (HOST_ADDR)pOutput;
        pSymCipherReq->sgtOption = inputSgtType;

        return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    SysAuthorizationReq
     *
     * Description: Performs a system authorization request
     *
     ******************************************************************************/
    hseSrvResponse_t SysAuthorizationReq(
        hseSysAuthOption_t sysAuthOption,
        hseSysRights_t sysAccess,
        hseKeyHandle_t authorizationKeyHandle,
        hseAuthScheme_t *pSignScheme,
        uint8_t *pChallenge)
    {
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSysAuthorizationReqSrv_t *pSysAuthReqSrv = &(pHseSrvDesc->hseSrv.sysAuthorizationReq);

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        pHseSrvDesc->srvId = HSE_SRV_ID_SYS_AUTH_REQ;
        pSysAuthReqSrv->sysAuthOption = sysAuthOption;
        pSysAuthReqSrv->sysRights = sysAccess;
        pSysAuthReqSrv->ownerKeyHandle = authorizationKeyHandle;
        pSysAuthReqSrv->pChallenge = (HOST_ADDR)pChallenge;

        if (NULL != pSignScheme)
        {
            memcpy(&pSysAuthReqSrv->authScheme, pSignScheme, sizeof(hseAuthScheme_t));
        }

        return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    SysAuthorizationResp
     *
     * Description: Performs a system authorization response
     *
     ******************************************************************************/
    hseSrvResponse_t SysAuthorizationResp(
        uint8_t *pSign0,
        uint32_t sign0Length,
        uint8_t *pSign1,
        uint32_t sign1Length)
    {
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSysAuthorizationRespSrv_t *pSysAuthRespSrv = &(pHseSrvDesc->hseSrv.sysAuthorizationResp);

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_SYS_AUTH_RESP;
        pSysAuthRespSrv->pAuth[0] = (HOST_ADDR)pSign0;
        pSysAuthRespSrv->pAuth[1] = (HOST_ADDR)pSign1;
        pSysAuthRespSrv->authLen[0] = sign0Length;
        pSysAuthRespSrv->authLen[1] = sign1Length;

        return HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    HashReq
     *
     * Description: This function is used to send Hash request.
     *
     ******************************************************************************/
    hseSrvResponse_t Hash_Req(hseAccessMode_t accessMode, hseHashAlgo_t hashAlgo,
                              uint32_t streamId, uint32_t inputLength,
                              const uint8_t *pInput, uint32_t *pHashLength,
                              uint8_t *pHash, hseSGTOption_t inputSgtType)
    {
        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseHashSrv_t *pHashSrv;
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        pHseSrvDesc->srvId = HSE_SRV_ID_HASH;
        pHashSrv = &(pHseSrvDesc->hseSrv.hashReq);

        pHashSrv->accessMode = accessMode;
        pHashSrv->hashAlgo = hashAlgo;
        pHashSrv->streamId = streamId;
        pHashSrv->inputLength = inputLength;
        pHashSrv->pInput = (HOST_ADDR)pInput;
        pHashSrv->pHashLength = (HOST_ADDR)pHashLength;
        pHashSrv->pHash = (HOST_ADDR)pHash;
        pHashSrv->sgtOption = inputSgtType;

        return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
    }

    /*******************************************************************************
     * Function:    Get_M1_M2_M3
     * Description: This function computes the parameters M1, M2 and M3 used to Load SHE Keys
     ******************************************************************************/
    hseSrvResponse_t Get_M1_M2_M3(const uint8_t *pAuthKey, uint8_t *pKeyNew, uint8_t KeyId, uint8_t AuthId, uint32_t count_val,
                                  uint8_t flag_val, uint8_t *pM1, uint8_t *pM2, uint8_t *pM3)
    {
        hseSrvResponse_t status;
        uint8_t tempM1[AES_BLOCK_SIZE];
        uint8_t tempM2[AES_BLOCK_SIZE * 2];
        uint8_t tempM3[AES_BLOCK_SIZE];
        uint8_t M2_t[AES_BLOCK_SIZE * 2];
        uint8_t M3_t[AES_BLOCK_SIZE * 3];
        const uint8_t KEY_UPDATE_ENC_C[AES_BLOCK_SIZE] =
            {0x01, 0x01, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0};
        const uint8_t KEY_UPDATE_MAC_C[AES_BLOCK_SIZE] =
            {0x01, 0x02, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0};
        uint8_t uid[] =
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        /* Initialization Vector */
        uint8_t IV[AES_BLOCK_SIZE] =
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        uint8_t K1[AES_BLOCK_SIZE];
        uint8_t K2[AES_BLOCK_SIZE];
        uint32_t outLen;
        uint8_t plaintext[AES_BLOCK_SIZE * 2];
        int i = 0;

        /* Generate K1 */
        /* K1 = KDF(KAuthID, KEY_UPDATE_ENC_C) */
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            plaintext[i] = pAuthKey[i];
        }
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
        {
            plaintext[i] = KEY_UPDATE_ENC_C[i - AES_BLOCK_SIZE];
        }
        outLen = ARRAY_SIZE(K1);
        /* running KDF function to get K1 */
        status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K1, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }

        /*Generate K2*/
        /* K2 = KDF(KAuthID,KEY_UPDATE_MAC_C) */
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            plaintext[i] = pAuthKey[i];
        }
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
        {
            plaintext[i] = KEY_UPDATE_MAC_C[i - AES_BLOCK_SIZE];
        }
        outLen = ARRAY_SIZE(K2);
        /* running KDF function to get K2 */
        status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K2, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }
        /* generate M1 */
        /* M1 = UIDâ€™|ID|AuthID */
        for (i = 0; i < 15; i++)
        {
            tempM1[i] = uid[i];
        }
        /* key to be updated and authorizing key ID */
        tempM1[15] = (KeyId << 4 & 0xF0) | (AuthId & 0x0F);
        /* generate M2 */
        /* M2 = ENCCBC,K1,IV=0(CIDâ€™|FIDâ€™|â€œ0...0"95|KIDâ€™)*/
        M2_t[0] = ((count_val >> 20) & 0xFF);
        M2_t[1] = ((count_val >> 12) & 0xFF);
        M2_t[2] = ((count_val >> 4) & 0xFF);
        M2_t[3] = ((count_val << 4) & 0xF0) | ((flag_val >> 2) & 0x0F);
        M2_t[4] = ((flag_val << 6) & 0xC0);
        for (i = 5; i < 16; i++)
        {
            M2_t[i] = 0x00;
        }
        for (i = 16; i < AES_BLOCK_SIZE * 2; i++)
        {
            M2_t[i] = pKeyNew[i - AES_BLOCK_SIZE];
        }
        /* Load K1 in RAM key */
        status = SheLoadPlainKey(K1);
        ASSERT(HSE_SRV_RSP_OK == status);
        /*ASSERT(HSE_SRV_RSP_OK == LoadAesKey(SHE_RAM_KEY_HANDLE, ARRAY_SIZE(K1), K1));*/
        memset(tempM2, 0, AES_BLOCK_SIZE * 2);
        /*CBC ENCRYPT M2_t using K1 to get M2*/
        status = she_cmd_enc_cbc(0x0E, IV, 2U, M2_t, tempM2);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }
        /* generate M3 */
        /* M3 = CMACK2(M1|M2) */
        /*Load K2 in RAM key*/

        status = SheLoadPlainKey(K2);
        ASSERT(HSE_SRV_RSP_OK == status);

        /*Generate (M1|M2)*/
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            M3_t[i] = tempM1[i];
        }
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 3; i++)
        {
            M3_t[i] = tempM2[i - AES_BLOCK_SIZE];
        }

        /*generate MAC over (M1|M2) to get M3*/
        status = cmd_generate_mac(0x0E, (ARRAY_SIZE(M3_t) * 8), M3_t, tempM3);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }
        memcpy(pM1, tempM1, sizeof(tempM1));
        memcpy(pM2, tempM2, sizeof(tempM2));
        memcpy(pM3, tempM3, sizeof(tempM3));
        return status;
    }

    /*******************************************************************************
     * Function:    Get_M4_M5
     * Description: This function computes the verification parameters M4 and M5 used to verify Load SHE Keys
     ******************************************************************************/
    hseSrvResponse_t Get_M4_M5(const uint8_t *pAuthKey, uint8_t *pKeyNew, uint8_t KeyId, uint8_t AuthId, uint32_t count_val,
                               uint8_t flag_val, uint8_t *pM4, uint8_t *pM5)
    {
        hseSrvResponse_t status;
        uint8_t K3[AES_BLOCK_SIZE];
        uint8_t K4[AES_BLOCK_SIZE];

        uint8_t M4_t[AES_BLOCK_SIZE];
        uint8_t M4_te[AES_BLOCK_SIZE];
        uint8_t tempM4[AES_BLOCK_SIZE * 2];
        uint8_t tempM5[AES_BLOCK_SIZE];
        uint8_t plaintext[AES_BLOCK_SIZE * 2];
        uint32_t outLen;
        uint32_t i;
        const uint8_t KEY_UPDATE_ENC_C[AES_BLOCK_SIZE] =
            {0x01, 0x01, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0};
        const uint8_t KEY_UPDATE_MAC_C[AES_BLOCK_SIZE] =
            {0x01, 0x02, 0x53, 0x48, 0x45, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0};
        uint8_t uid[] =
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        /*Get K3*/
        /* K3 = KDF(KEYID,KEY_UPDATE_ENC_C) */
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            plaintext[i] = pKeyNew[i];
        }
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
        {
            plaintext[i] = KEY_UPDATE_ENC_C[i - AES_BLOCK_SIZE];
        }
        outLen = ARRAY_SIZE(K3);
        status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K3, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }

        /*Get K4*/
        /* K4 = KDF (KEYID,KEY_UPDATE_MAC_C) */
        /*for(i=0;i<KEY_SIZE_IN_WORD;i++)*/
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            plaintext[i] = pKeyNew[i];
        }
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
        {
            plaintext[i] = KEY_UPDATE_MAC_C[i - AES_BLOCK_SIZE];
        }
        outLen = ARRAY_SIZE(K4);
        status = HostKdf(AES_BLOCK_SIZE * 2, plaintext, &outLen, K4, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == status);
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }

        /* Generate M4 */

        /* M4 = UID|ID|AuthID|M4*
         * M4* - the encrypted counter value; prior to encryption the counter
         * value (28 bits) is padded with a 1 and 99 0â€™s.
         * The key for the ECB encryption is K3
         */
        M4_t[0] = ((count_val >> 20) & 0xFF);
        M4_t[1] = ((count_val >> 12) & 0xFF);
        M4_t[2] = ((count_val >> 4) & 0xFF);
        // M4_t[3] = ((pMemUpdate->count_val<<4) & 0xF0)|0x08;
        M4_t[3] = ((count_val << 4) & 0xF0);
        /*Single "1"-bit Padding followed by "0"-bits on the LSB side*/
        M4_t[3] |= (uint8_t)(1UL << 3U);
        for (i = 4; i < AES_BLOCK_SIZE; i++)
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
        if (HSE_SRV_RSP_OK != status)
        {
            return status;
        }

        for (i = 0; i < (AES_BLOCK_SIZE - 1); i++)
        {
            tempM4[i] = uid[i];
        }
        tempM4[15] = ((((uint8_t)KeyId) << 4U) & 0xF0U) | (((uint8_t)AuthId) & 0x0FU);
        for (i = AES_BLOCK_SIZE; i < AES_BLOCK_SIZE * 2; i++)
        {
            tempM4[i] = M4_te[i - AES_BLOCK_SIZE];
        }

        /* Generate M5 */
        /* M5 = CMACK4(M4) */
        status = SheLoadPlainKey(K4);
        ASSERT(HSE_SRV_RSP_OK == status);
        /* Generate MAC to get M5 */
        ASSERT(HSE_SRV_RSP_OK == cmd_generate_mac(RAM_KEY_ID, (ARRAY_SIZE(tempM4) * 8), tempM4, tempM5));
        memcpy(pM4, tempM4, sizeof(tempM4));
        memcpy(pM5, tempM5, sizeof(tempM5));
        return status;
    }

    /*******************************************************************************
     * Function:    SheLoadPlainKey
     *
     * Description: This function is used to test She Load Plain Key Command.
     *
     * Returns:
     HSE_SRV_RSP_OK                               HSE command successfully executed with no error
     HSE_SRV_RSP_INVALID_PARAM                    The HSE request parameters are invalid (e.g misaligned, invalid range)
     HSE_SRV_RSP_SMALL_BUFFER                     The provided buffer is too small
     HSE_SRV_RSP_NOT_ENOUGH_SPACE                 There is no enough space to perform operation (e.g. load a key)
     HSE_SRV_RSP_READ_FAILURE                     The service request failed because read access was denied
     HSE_SRV_RSP_WRITE_FAILURE                    The service request failed because write access was denied
     HSE_SRV_RSP_STREAMING_MODE_FAILURE           The service request that uses streaming mode failed (e.g. UPDATES and FINISH steps do not use the same HSE interface ID and channel ID as START step)
     HSE_SRV_RSP_VERIFY_FAILED                    HSE signals that a verification request fails (e.g. MAC and Signature verification)
     HSE_SRV_RSP_KEY_NOT_AVAILABLE                This error code is returned if a key is locked due to failed boot measurement or an active debugger
     HSE_SRV_RSP_KEY_INVALID                      Specified key slot is either not valid or not available due to a key usage flags restrictions
     HSE_SRV_RSP_KEY_EMPTY                        Specified key slot is empty
     HSE_SRV_RSP_BUSY                             HSE request issued when the HSE is in busy state (on that HSE channel)
     HSE_SRV_RSP_MEMORY_FAILURE                   Detect physical errors, flipped bits etc., during memory read or write operations
     HSE_SRV_RSP_GENERAL_ERROR                    This error code is returned if an error not covered by the error codes above is detected inside HSE
     ******************************************************************************/
    hseSrvResponse_t SheLoadPlainKey(const uint8_t *pKey)
    {

        hseSrvDescriptor_t *pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
        hseSheLoadPlainKeySrv_t *pSheLoadPlainKeyReq = &pHseSrvDesc->hseSrv.sheLoadPlainKeyReq;

        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
        pHseSrvDesc->srvId = HSE_SRV_ID_SHE_LOAD_PLAIN_KEY;
        pSheLoadPlainKeyReq->pKey = (HOST_ADDR)pKey;

        return HSE_Send(muIf, muChannelIdx, txOptions, pHseSrvDesc);
    }
