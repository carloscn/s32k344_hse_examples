/**
 *   @file    hse_rng_test.c
 *
 *   @brief   This file is used to verify Random number operations
 *   @details
 *
 */
/*==================================================================================================
*
*   Copyright 2020-2021 NXP.
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
/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL VARIABLES
 ==================================================================================================*/
static uint8_t muIf = 0U;
static uint8_t muChannelIdx = 1U;

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

/*******************************************************************************
 * Function:    GetRngNum
 *
 * Description: This function is used to get random number.
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
 ******************************************************************************/
hseSrvResponse_t GetRngNum(uint8_t *rngNum, uint32_t rngNumSize, hseRngClass_t rngClass)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseGetRandomNumSrv_t* pGetRndSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));
    pHseSrvDesc->srvId = HSE_SRV_ID_GET_RANDOM_NUM;

    pGetRndSrv = &(pHseSrvDesc->hseSrv.getRandomNumReq);

    pGetRndSrv->rngClass = rngClass;
    pGetRndSrv->pRandomNum = (HOST_ADDR)rngNum;
    pGetRndSrv->randomNumLength = rngNumSize;

    hseStatus = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);
    return hseStatus;
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/

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
hseSrvResponse_t GetRngDRG3Num(uint8_t *rngNum, uint32_t rngNumSize)
{
    return GetRngNum(rngNum, rngNumSize, HSE_RNG_CLASS_DRG3);
}

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
hseSrvResponse_t GetRngDRG4Num(uint8_t *rngNum, uint32_t rngNumSize)
{
    return GetRngNum(rngNum, rngNumSize, HSE_RNG_CLASS_DRG4);
}

/*******************************************************************************
 * Function:    GetRngPTG3Num
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
hseSrvResponse_t GetRngPTG3Num(uint8_t *rngNum, uint32_t rngNumSize)
{
    return GetRngNum(rngNum, rngNumSize, HSE_RNG_CLASS_PTG3);
}

#ifdef __cplusplus
}
#endif

/** @} */

