/**
*   @file    hse_host_ecc_.h
*
*   @brief   This file contains tests of monotonic counters services: IncrementCnt, ReadCnt, Publish/LoadCntTbl.
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
/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/

#include "hse_host.h"

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

/*****************************************************************************************
 *                                      Generic
 ****************************************************************************************/

uint32_t KeyBitLen(uint32_t eccCurveId);

hseSrvResponse_t GenerateEccKey(
    hseKeyHandle_t *pTargetKeyHandle,
    bool_t isNvmKey,
    hseEccCurveId_t eccCurveId,
    uint32_t usageFlags
);

hseSrvResponse_t GenerateEccKeyAndExportPublic(
    hseKeyHandle_t targetKeyHandle,
    hseEccCurveId_t eccCurveId,
    uint32_t usageFlags,
    uint8_t* pPubKey 
);

hseSrvResponse_t LoadEccUserCurve(
    hseEccCurveId_t eccCurveId,
    hseKeyBits_t nBitLength,
    hseKeyBits_t pBitLength,
    const uint8_t* pA,
    const uint8_t* pB,
    const uint8_t* pG,
    const uint8_t* pN,
    const uint8_t* pP
);
