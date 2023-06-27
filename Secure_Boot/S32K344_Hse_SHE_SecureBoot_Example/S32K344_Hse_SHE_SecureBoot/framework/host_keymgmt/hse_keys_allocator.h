/**
 *   @file    hse_keys_allocator.h
 *
 *   @brief   Function definitions for host keys allocator
 *   @details This file will help with handling of key handles.
 *
 *   @addtogroup [KEYMGMT_FRAMEWORK]
 *   @{
 */
/*==================================================================================================
 *   (c) Copyright 2020 NXP.
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


#ifndef HSE_KEYS_ALLOCATOR_H
#define HSE_KEYS_ALLOCATOR_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
==================================================================================================*/
#include "hse_interface.h"

/*==================================================================================================
 *                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                      DEFINES AND MACROS
==================================================================================================*/
#define NVM_KEY 1U
#define RAM_KEY 0U

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
/* Does not check for NULL pointers */
hseSrvResponse_t HKF_Init(
    const hseKeyGroupCfgEntry_t *pNvmCatalog,
    const hseKeyGroupCfgEntry_t *pRamCatalog
);

hseSrvResponse_t HKF_AllocKeySlotAdvanced(
    uint8_t isNvmKey,
    hseMuMask_t muMask,
    bool_t strictMuMask,
    hseKeyGroupOwner_t groupOwner,
    hseKeyType_t keyType,
    uint16_t maxKeyBitLength,
    hseKeyHandle_t *pKeyHandle
);

hseSrvResponse_t HKF_AllocKeySlot(
    bool_t isNvmKey,                /* IN  */
    hseKeyType_t keyType,           /* IN  */
    uint16_t maxKeyBitLength,       /* IN  */
    hseKeyHandle_t *pKeyHandle      /* OUT */
);

hseSrvResponse_t HKF_FreeKeySlot(
    hseKeyHandle_t *keyHandle       /* IN */
);

hseSrvResponse_t HKF_IsKeyHandleAllocated(
    hseKeyHandle_t keyHandle       /* IN */
);

void HKF_FreeAllKeys(void);

hseSrvResponse_t HKF_MarkAsAllocated(
    hseKeyHandle_t keyHandle       /* IN */
);

#ifdef __cplusplus
}
#endif

#endif /* HSE_KEYS_ALLOCATOR_H */

/** @} */
