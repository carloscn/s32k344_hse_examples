/**
*   @file    hse_host_utils.h
*   
*   @version 1.0.0
*   @brief   HSE HOST utils.
*   @details This file contains the metods used to create SGT entries.
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

#ifndef HSE_HOST_UTILS_H
#define HSE_HOST_UTILS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "string.h"
#include "hse_common_types.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define SGT_SET_FINAL_BIT_MASK (0x40000000UL)    
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*******************************************************************************
 * Mempcy + reverse
 ******************************************************************************/
void ReverseMemCpy(uint8_t* dst, const uint8_t* src, uint32_t len);

#ifdef HSE_SPT_SGT_OPTION
void HSE_PrepareSgtList(uint16_t plainTextLen, hseScatterList_t *pSgtList, uint8_t chunksize, const uint8_t *plaintext);
#endif /* HSE_SPT_SGT_OPTION */

/*******************************************************************************
 * Prepare HSE before Stand-By
 ******************************************************************************/
#if defined(HSE_SPT_FLASHLESS_DEV)
hseSrvResponse_t HSE_PrepareForStandBy(void);
#endif /* HSE_SPT_FLASHLESS_DEV */

#ifdef __cplusplus
}
#endif

#endif /* HSE_HOST_UTILS_H */

/** @} */
