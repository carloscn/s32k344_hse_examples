/**
*   @file    hse_she_api.h
*

*   @brief   Installer services.
*   @details This file contains declaration of functions or variables used throughout the project and eclaration of functions used to send request to HSE.
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

#ifndef HSE_SHE_API_H
#define HSE_SHE_API_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "hse_host.h"
#include "std_typedefs.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
#define ASSERT(condition) \
    do                    \
    {                     \
        if (!(condition)) \
            while (1)     \
                ;         \
    } while (0)

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**< @brief HSE FW pink image is in primary location (specified in IVT, currently running) */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MASTER_ECU_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 0)
#define COPY_MASTER_ECU_KEY_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM, 0, 0)
#define SHE_KEY_11_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 0)
#define SHE_KEY_21_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 0)
#define SHE_KEY_32_HANDLE GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 3, 0)

    /*==================================================================================================
    *                                             ENUMS
    ==================================================================================================*/

    /*==================================================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/

    /*==================================================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/
    extern uint32_t HSE_HOST_RAM_DST_START_ADDR[];
    extern uint32_t HSE_HOST_FLASH_SRC_START_ADDR[];
    extern uint32_t HSE_HOST_FLASH_SRC_END_ADDR[];
    /*==================================================================================================
                                         FUNCTION PROTOTYPES
    ==================================================================================================*/
    hseSrvResponse_t GetRngDRG3Num(uint8_t *rngNum, uint32_t rngNumSize);
    hseSrvResponse_t SheGetId(uint8_t *pChallenge, uint8_t *pId, uint8_t *pSreg, uint8_t *pMac);
    hseSrvResponse_t SheLoadPlainKey(const uint8_t *pKey);
    hseSrvResponse_t SheLoadKey(uint8_t sheGroupId, uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5);
    hseSrvResponse_t EraseKeyReq(hseKeyHandle_t keyHandle, hseEraseKeyOptions_t eraseKeyOptions);
    hseSrvResponse_t SheExportRamKey(uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5);
    hseSrvResponse_t GetRngNum(uint8_t *rngNum, uint32_t rngNumSize, hseRngClass_t rngClass);
    hseSrvResponse_t getRandomNumReq(hseRngClass_t rngClass, uint32_t rngNumSize, uint8_t *rngNum);
    hseSrvResponse_t SymCipherReq(hseAccessMode_t accessMode, hseCipherAlgo_t cipherAlgo, hseCipherBlockMode_t cipherBlockMode,
                                  hseCipherDir_t cipherDir, hseKeyHandle_t keyHandle, const uint8_t *pIV,
                                  uint32_t inputLength, const uint8_t *pInput, uint8_t *pOutput, hseSGTOption_t inputSgtType);

    hseSrvResponse_t SysAuthorizationReq(hseSysAuthOption_t sysAuthOption, hseSysRights_t sysAccess, hseKeyHandle_t authorizationKeyHandle,
                                         hseAuthScheme_t *pSignScheme, uint8_t *pChallenge);
    hseSrvResponse_t SysAuthorizationResp(uint8_t *pSign0, uint32_t sign0Length, uint8_t *pSign1, uint32_t sign1Length);

    hseSrvResponse_t AesFastCmacGenerate(hseKeyHandle_t keyHandle, uint32_t msgLength,
                                         const uint8_t *pMsg, uint8_t tagLength, uint8_t *pTag);
    hseSrvResponse_t Hash_Req(hseAccessMode_t accessMode, hseHashAlgo_t hashAlgo,
                              uint32_t streamId, uint32_t inputLength,
                              const uint8_t *pInput, uint32_t *pHashLength,
                              uint8_t *pHash, hseSGTOption_t inputSgtType);
    hseSrvResponse_t Get_M1_M2_M3(const uint8_t *pAuthKey, uint8_t *pKeyNew, uint8_t KeyId, uint8_t AuthId, uint32_t count_val, uint8_t flag_val,
                                  uint8_t *pM1, uint8_t *pM2, uint8_t *pM3);
    hseSrvResponse_t Get_M4_M5(const uint8_t *pAuthKey, uint8_t *pKeyNew, uint8_t KeyId, uint8_t AuthId, uint32_t count_val,
                               uint8_t flag_val, uint8_t *pM4, uint8_t *pM5);
#ifdef __cplusplus
}
#endif

#endif /* HOST_COMMON_H */

/** @} */
