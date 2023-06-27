/**
*   @file    hse_host_cmac_with_counter.h
*
*   @brief   Function definitions for CMAC with counter service tests.
*   @details
*
*   @addtogroup [SECURITY_FIRMWARE_UNITTEST]
*   @{
*/
/*==================================================================================================
*   (c) Copyright 2021-2022 NXP.
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

#ifndef _HSE_HOST_CMAC_WITH_COUNTER_H_
#define _HSE_HOST_CMAC_WITH_COUNTER_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "hse_interface.h"
#include "hse_host_utils.h"

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

hseSrvResponse_t CmacWithCounter(hseKeyHandle_t keyHandle, hseAuthDir_t authDir, uint32_t cntIndex, uint8_t rpOffset,
                                 uint32_t msgLength, const uint8_t *pMsg,
                                 uint8_t tagLength, const uint8_t *pTag,
                                 uint32_t *pVolatileCnt, hseSGTOption_t inputSgtType);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _HSE_HOST_CMAC_WITH_COUNTER_H_ */

/** @} */


