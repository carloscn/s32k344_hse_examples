/**
 *   @file    hse_she_commands.h
 *
 *   @brief   Function prototypes for SHE Commands.
 *   @details Function prototypes for SHE Commands.
 *
 */
/*==================================================================================================
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

#ifndef _SHE_COMMANDS_H_
#define _SHE_COMMANDS_H_
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "std_typedefs.h"
#include "hse_common_types.h"
#include "hse_srv_random.h"
#include "hse_srv_responses.h"
    /*==================================================================================================
    *                                          CONSTANTS
    ==================================================================================================*/

    /*==================================================================================================
    *                                      DEFINES AND MACROS
    ==================================================================================================*/

    /*==================================================================================================
    *                                             ENUMS
    ==================================================================================================*/

    /*==================================================================================================
    *                                STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/

    /*==================================================================================================
    *                                GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/

    /*==================================================================================================
    *                                    FUNCTION PROTOTYPES
    ==================================================================================================*/

    hseSrvResponse_t SheLoadMasterEcuKey(void);
    hseSrvResponse_t SheLoadNVMKey_ECB(void);
    hseSrvResponse_t SheLoadNVMKey_CBC(void);
    hseSrvResponse_t SheLoadNVMKey_CMAC(void);
    hseSrvResponse_t EraseAllSheKeys(void);
    hseSrvResponse_t Load_Relevant_Keys(void);

    hseSrvResponse_t she_cmd_enc_ecb(uint32_t keyId, uint32_t num_of_blocks, const uint8_t *pInput, uint8_t *pOutput);
    hseSrvResponse_t she_cmd_dec_ecb(uint32_t keyId, uint32_t num_of_blocks, const uint8_t *pInput, uint8_t *pOutput);
    hseSrvResponse_t she_cmd_enc_cbc(uint32_t keyId, const uint8_t *pIV, uint32_t num_of_blocks, const uint8_t *pInput, uint8_t *pOutput);
    hseSrvResponse_t she_cmd_dec_cbc(uint32_t keyId, const uint8_t *pIV, uint32_t num_of_blocks, const uint8_t *pInput, uint8_t *pOutput);
    hseSrvResponse_t cmd_generate_mac(uint32_t keyId, uint32_t message_length_in_bits, const uint8_t *pInput, uint8_t *pTag);
    hseSrvResponse_t cmd_verify_mac(uint32_t keyId, uint32_t message_length_in_bits, const uint8_t *pInput, uint8_t *pTag);
    hseSrvResponse_t cmd_load_key(uint8_t sheGroupId, uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5);
    hseSrvResponse_t cmd_load_plain_key(const uint8_t *pKey);
    hseSrvResponse_t cmd_export_ram_key(uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5);
    hseSrvResponse_t cmd_extend_seed(uint8_t *rngNum);
    hseSrvResponse_t cmd_rnd(uint8_t *rngNum);
    hseSrvResponse_t cmd_trng_rnd(uint8_t *rngNum);
    hseSrvResponse_t cmd_get_id(uint8_t *pChallenge, uint8_t *pId, uint8_t *pSreg, uint8_t *pMac);
    hseSrvResponse_t cmd_debug_chal(uint8_t *pChallenge);
    hseSrvResponse_t cmd_debug_auth(uint8_t *pAuthVal);
    hseSrvResponse_t cmd_debug_chal_auth(void);

    extern uint8_t DEBUG_KEY_C[];
#ifdef __cplusplus
}
#endif

#endif /* #ifndef _SHE_COMMANDS_H_ */

/** @} */
