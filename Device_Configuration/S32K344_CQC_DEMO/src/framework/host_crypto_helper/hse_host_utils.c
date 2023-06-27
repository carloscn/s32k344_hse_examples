/**
 *   @file    hse_host_utils.c
 *
 *   @brief   Function definitions for hse-host interface
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
#include    "hse_host_utils.h"

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
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/
/*******************************************************************************
 * Prepare a scatter gather list using blocks from the message
 ******************************************************************************/
void HSE_PrepareSgtList(uint16_t plainTextLen, hseScatterList_t *pSgtList, uint8_t chunksize, const uint8_t *plaintext)
{
    uint32_t index              = 0;
    uint16_t tempPlainTextLen   = plainTextLen;


    while(tempPlainTextLen != 0)
    {
        if(tempPlainTextLen <= chunksize)
        {
                /* Create data input for SGT entries  */
                pSgtList[index].length   = tempPlainTextLen | SGT_SET_FINAL_BIT_MASK;
                pSgtList[index].pPtr     = (HOST_ADDR)&plaintext[chunksize * index];
                tempPlainTextLen = 0;
        }
        else
        {
                    /* Create data input for SGT entries  */
                pSgtList[index].length   = chunksize;
                pSgtList[index].pPtr     = (HOST_ADDR)&plaintext[chunksize * index];
                tempPlainTextLen = tempPlainTextLen - chunksize;
        }
        index++;
    }
}

#ifdef __cplusplus
}
#endif
