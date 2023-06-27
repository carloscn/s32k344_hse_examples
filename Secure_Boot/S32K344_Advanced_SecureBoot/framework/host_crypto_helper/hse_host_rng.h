/**
 *   @file    hse_host_rng.c
 *
 *   @brief   This file is used to verify Random number operations
 *   @details
 *
 *   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
 *   @{
 */
/*==================================================================================================
 *   Project              : HSE 16FFC
 *   Platform             : Arm Architecture
 *   Peripheral           : CortexM7
 *   Dependencies         : none
 *
 *
 *
 *   (c) Copyright 2018 NXP.
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

#ifndef _HSE_HOST_RNG_H_
#define _HSE_HOST_RNG_H_

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

hseSrvResponse_t GetRngNum(uint8_t *rngNum, uint32_t rngNumSize, hseRngClass_t rngClass);

/*******************************************************************************
 * Function:    GetRngDRG3Num
 *
 * Description: This function is used to get random number of class DRG3.
 *
 * Returns:
 * HSE_SRV_RSP_OK                        HSE service successfully executed with no error
 * HSE_SRV_RSP_INVALID_PARAM             The HSE request parameters are invalid (e.g
 *                                 misaligned, invalid range)
 * HSE_SRV_RSP_SMALL_BUFFER              The provided buffer is too small
 * HSE_SRV_RSP_NOT_ENOUGH_SPACE          There is no enough space to perform operation
 *                                 (e.g. load a key)
 * HSE_SRV_RSP_READ_FAILURE              The service request failed because read access
 *                                 was denied
 * HSE_SRV_RSP_WRITE_FAILURE             The service request failed because write access
 *                                 was denied
 * HSE_SRV_RSP_STREAMING_MODE_FAILURE    The service request that uses streaming mode
 *                                 failed (e.g. UPDATES and FINISH steps do not use
 *                                 the same HSE interface ID and channel ID as START step)
 * HSE_SRV_RSP_VERIFY_FAILED             HSE signals that a verification request fails (e.g.
 *                                 MAC and Signature verification)
 * HSE_SRV_RSP_KEY_NOT_AVAILABLE         This error code is returned if a key is locked due
 *                                 to failed boot measurement or an active debugger
 * HSE_SRV_RSP_KEY_INVALID               Specified key slot is either not valid or not available
 *                                 due to a key usage flags restrictions
 * HSE_SRV_RSP_KEY_EMPTY                 Specified key slot is empty
 * HSE_SRV_RSP_BUSY                      HSE request issued when the HSE is in busy state (on
 *                                 that HSE channel)
 * HSE_SRV_RSP_MEMORY_FAILURE            Detect physical errors, flipped bits etc., during
 *                                 memory read or write operations
 * HSE_SRV_RSP_GENERAL_ERROR             This error code is returned if an error not covered by
 *                                 the error codes above is detected inside HSE
 *
 ******************************************************************************/
hseSrvResponse_t GetRngDRG3Num(uint8_t *rngNum, uint32_t rngNumSize);

/*******************************************************************************
 * Function:    GetRngDRG4Num
 *
 * Description: This function is used to get random number of class DRG4.
 *
 * Returns:
 * HSE_SRV_RSP_OK                        HSE service successfully executed with no error
 * HSE_SRV_RSP_INVALID_PARAM             The HSE request parameters are invalid (e.g
 *                                 misaligned, invalid range)
 * HSE_SRV_RSP_SMALL_BUFFER              The provided buffer is too small
 * HSE_SRV_RSP_NOT_ENOUGH_SPACE          There is no enough space to perform operation
 *                                 (e.g. load a key)
 * HSE_SRV_RSP_READ_FAILURE              The service request failed because read access
 *                                 was denied
 * HSE_SRV_RSP_WRITE_FAILURE             The service request failed because write access
 *                                 was denied
 * HSE_SRV_RSP_STREAMING_MODE_FAILURE    The service request that uses streaming mode
 *                                 failed (e.g. UPDATES and FINISH steps do not use
 *                                 the same HSE interface ID and channel ID as START step)
 * HSE_SRV_RSP_VERIFY_FAILED             HSE signals that a verification request fails (e.g.
 *                                 MAC and Signature verification)
 * HSE_SRV_RSP_KEY_NOT_AVAILABLE         This error code is returned if a key is locked due
 *                                 to failed boot measurement or an active debugger
 * HSE_SRV_RSP_KEY_INVALID               Specified key slot is either not valid or not available
 *                                 due to a key usage flags restrictions
 * HSE_SRV_RSP_KEY_EMPTY                 Specified key slot is empty
 * HSE_SRV_RSP_BUSY                      HSE request issued when the HSE is in busy state (on
 *                                 that HSE channel)
 * HSE_SRV_RSP_MEMORY_FAILURE            Detect physical errors, flipped bits etc., during
 *                                 memory read or write operations
 * HSE_SRV_RSP_GENERAL_ERROR             This error code is returned if an error not covered by
 *                                 the error codes above is detected inside HSE
 *
 ******************************************************************************/
hseSrvResponse_t GetRngDRG4Num(uint8_t *rngNum, uint32_t rngNumSize);

/*******************************************************************************
 * Function:    GetRngPTG3Num
 *
 * Description: This function is used to get random number of class PTG3.
 *
 * Returns:
 * HSE_SRV_RSP_OK                        HSE service successfully executed with no error
 * HSE_SRV_RSP_INVALID_PARAM             The HSE request parameters are invalid (e.g
 *                                 misaligned, invalid range)
 * HSE_SRV_RSP_SMALL_BUFFER              The provided buffer is too small
 * HSE_SRV_RSP_NOT_ENOUGH_SPACE          There is no enough space to perform operation
 *                                 (e.g. load a key)
 * HSE_SRV_RSP_READ_FAILURE              The service request failed because read access
 *                                 was denied
 * HSE_SRV_RSP_WRITE_FAILURE             The service request failed because write access
 *                                 was denied
 * HSE_SRV_RSP_STREAMING_MODE_FAILURE    The service request that uses streaming mode
 *                                 failed (e.g. UPDATES and FINISH steps do not use
 *                                 the same HSE interface ID and channel ID as START step)
 * HSE_SRV_RSP_VERIFY_FAILED             HSE signals that a verification request fails (e.g.
 *                                 MAC and Signature verification)
 * HSE_SRV_RSP_KEY_NOT_AVAILABLE         This error code is returned if a key is locked due
 *                                 to failed boot measurement or an active debugger
 * HSE_SRV_RSP_KEY_INVALID               Specified key slot is either not valid or not available
 *                                 due to a key usage flags restrictions
 * HSE_SRV_RSP_KEY_EMPTY                 Specified key slot is empty
 * HSE_SRV_RSP_BUSY                      HSE request issued when the HSE is in busy state (on
 *                                 that HSE channel)
 * HSE_SRV_RSP_MEMORY_FAILURE            Detect physical errors, flipped bits etc., during
 *                                 memory read or write operations
 * HSE_SRV_RSP_GENERAL_ERROR             This error code is returned if an error not covered by
 *                                 the error codes above is detected inside HSE
 *
 ******************************************************************************/
hseSrvResponse_t GetRngPTG3Num(uint8_t *rngNum, uint32_t rngNumSize);

#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_RNG_H_ */

/** @} */
