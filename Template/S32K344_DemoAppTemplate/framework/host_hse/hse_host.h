/**
*   @file    hse_host.h
*   
*   @version 1.0.0
*   @brief   HSE HOST API functions.
*   @details This file contains the HSE HOST APIs.
*
*   @addtogroup HSE_HOST_APIs HSE HOST APIs
*   @{
*/
/*==================================================================================================
*
*   Copyright 2018-2021 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with 
*   the applicable license terms. By expressly accepting such terms or by downloading, installing, 
*   activating and/or otherwise using the software, you are agreeing that you have read, and that 
*   you agree to comply with and are bound by, such license terms. If you do not agree to 
*   be bound by the applicable license terms, then you may not retain, install, activate or 
*   otherwise use the software.
==================================================================================================*/

#ifndef HSE_HOST_H
#define HSE_HOST_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           hse_host.h
*/
#include "hse_interface.h"
#include "hse_mu.h"

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

#define BYTES_TO_BITS(byteLen)    ((byteLen) << 3UL)
#define BITS_TO_BYTES(bitLen)     ((((bitLen) + 7UL) >> 3UL))

/* Uncomment this macro to enable the HSE-Host shared memory */
// #define HSE_ENABLE_SHARED_MEM

#if HSE_NUM_OF_MU_INSTANCES > 4
#define HSE_SHARED_MEM_CHUNK_SIZE  2048U
#else
#define HSE_SHARED_MEM_CHUNK_SIZE  4096U
#endif 

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/** @brief    Synchronous or asynchronous transmission. */
typedef enum
{
    HSE_TX_SYNCHRONOUS           = 0UL, 
    HSE_TX_ASYNCHRONOUS
} hseTxOp_t;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* @brief   HSE Notifications callback */
typedef void (*pfGeneralPurposeCallback_t) (uint8_t u8MuInstance, uint32_t u32HseNotifEvents);

/* @brief   Asynchronous callback */
typedef void (*pfAsyncCallback_t) (hseSrvResponse_t status, void* pArg);

/*
 * @brief   Host transmission options
 */
typedef struct
{
    hseTxOp_t          txOp;               /**< @brief    Selects the transmission option .*/
    pfAsyncCallback_t  pfAsyncCallback;    /**< @brief    The callback for Asynchronous TX.  */
    void*              pCallbackpArg;      /**< @brief    Parameter used to call the asynchronous callback(can be NULL) */
} hseTxOptions_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/* Placed in system RAM or shared memory */
/* User can use this memory space to  fill the command (e.g gHseSrvDesc[u8MuIf][u8Channel]) */
extern hseSrvDescriptor_t* const gHseSrvDesc[HSE_NUM_OF_MU_INSTANCES];

/* Global sync TX options */
extern const hseTxOptions_t gSyncTxOption;

/* Global HSE notify events */
extern volatile uint32_t gHseEvents;

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/**
* @brief        Send an HSE message.
* @details      Send an HSE service request.
* 
* @param[in]    u8MuInstance    HSE MU Instance.
* @param[in]    u8MuChannel     The channel index.
* @param[in]    txOptions       Tx options: synchronous or asynchronous.
* @param[in]    pHseSrvDesc     Pointer to HSE message. It can be an entry of gHseSrvDesc[] or not.
* 
* @return       hseSrvResponse_t  HSE available errors
*
* @pre          The channel must be a free channel (Use HSE_GetFreeChannel).
*               For asynchronous transmission, a callback function (pfAsyncCallback) must be set; but pCallbackpArg can be NULL.
*               The application must fill the HSE message fields (e.g selecting the HSE command, priority etc).
*                                
*/
hseSrvResponse_t HSE_Send(uint8_t u8MuInstance, uint8_t u8MuChannel, hseTxOptions_t txOptions, hseSrvDescriptor_t* pHseSrvDesc);

/**
* @brief        Get a free channel.
* @details      Returns the next free service channel (ch) available from the HOST point of view.
*               NOTE: Channel 0 is not returned by this function (it is reserved for administrative services).
                      A channel is considered free only after the response is received or the callback function executed.
*
* @param[in]    u8MuInstance        The MU instance (MU): 0 <= MU < HSE_NUM_OF_MU_INSTANCES.
*
* @return       The index of the free channel (ch): 1 <= ch <= HSE_NUM_OF_CHANNELS_PER_MU.
*               In case no free channel is available returns HSE_INVALID_CHANNEL.
*/
uint8_t HSE_GetFreeChannel(uint8_t u8MuInstance);

/**
* @brief        Handler of the Receive Interrupt.
* @details      Handles the Receive Interrupt.
*
* @param[in]    u8MuInstance      HSE MU Instance.
*
* @return       NULL
*
*/
void HSE_ReceiveInterruptHandler(uint8_t u8MuInstance);

/**
* @brief        Handler of the General Purpose Interrupt.
* @details      Handles the General Purpose Interrupt, triggered by HSE
*               in order to notify host of unexpected errors/events.
*
* @param[in]    u8MuInstance      HSE MU Instance.
*
* @return       NULL
*
*/
void HSE_GeneralPurposeInterruptHandler(uint8_t u8MuInstance);

/**
* @brief        Register a GPI callback.
* @details      Register a General Purpose Interrupt callback per MU Instance.
*               The signature of the callback should be:
*                   void callback(uint8_t u8MuInstance, uint32_t u32HseNotifEvents)
*               The callback should process the event.
*
* @param[in]    u8MuInstance                HSE MU Instance.
* @param[in]    u32ErrorsMask               HSE Errors to be enabled.
* @param[in]    pfGeneralPurposeCallback    Pointer to the callback function.
*
* @return       NULL
*
*/
void HSE_RegisterGeneralPurposeCallback(uint8_t u8MuInstance, uint32_t u32ErrorsMask,
    pfGeneralPurposeCallback_t pfGeneralPurposeCallback);

#ifdef __cplusplus
}
#endif

#endif /* HSE_HOST_H */

/** @} */
