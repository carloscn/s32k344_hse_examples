/**
 *   @file    hse_memory_update_protocol.h
 *
 *   @brief   Function prototypes for She Memory Update protocol
 *   @details Function prototypes for She Memory Update protocol
 *
 *   @{
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

#ifndef _MEMORY_UPDATE_PROTOCOL_H_
#define _MEMORY_UPDATE_PROTOCOL_H_
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "std_typedefs.h"
#include "hse_common_types.h"
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

#define RAM_KEY_ID 0x0E
#define KEY_SIZE_IN_WORD 4
#define AES_BLOCK_SIZE 16

        typedef struct
        {
                uint8_t uid[15];
                uint8_t KeyId;
                uint8_t AuthId;
                uint32_t count_val;
                uint8_t flag_val;
                uint8_t sheGroupId;
                uint8_t AuthKey[AES_BLOCK_SIZE];
                uint8_t KeyNew[AES_BLOCK_SIZE];
        } MemoryUpdate_t;

        hseSrvResponse_t MemoryUpdateProtocol(MemoryUpdate_t *pMemUpdate);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _MEMORY_UPDATE_PROTOCOL_H_ */

/** @} */
