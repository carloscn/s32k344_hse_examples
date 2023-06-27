/**
*   @file    hse_host_attrs.c
*
*   @brief   This file will verify set/get attribute host requests on the HSE.
*   @details This file contains the test suite for set/get attribute requests from host.
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "hse_host.h"
#include "string.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

static const uint8_t u8MuInstance = 0;
static const uint8_t u8MuChannel = 0;

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
 * Function:    SetAttr
 * Description: Sets the specified attribute
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t SetAttr
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr
)
{
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = NULL;

    pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId                      = HSE_SRV_ID_SET_ATTR;
    pHseSrvDesc->hseSrv.setAttrReq.attrId   = attrId;
    pHseSrvDesc->hseSrv.setAttrReq.attrLen  = attrLen;
    pHseSrvDesc->hseSrv.setAttrReq.pAttr    = (HOST_ADDR)pAttr;

    hseSrvResponse = HSE_Send(u8MuInstance, u8MuChannel, gSyncTxOption, pHseSrvDesc);
    return hseSrvResponse;
}

/*******************************************************************************
 * Function:    GetAttr
 * Description: Gets the specified attribute
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t GetAttr
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr
)
{
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[u8MuInstance][u8MuChannel];

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId                      = HSE_SRV_ID_GET_ATTR;
    pHseSrvDesc->hseSrv.getAttrReq.attrId   = attrId;
    pHseSrvDesc->hseSrv.getAttrReq.attrLen  = attrLen;
    pHseSrvDesc->hseSrv.getAttrReq.pAttr    = (HOST_ADDR)pAttr;

    hseSrvResponse = HSE_Send(u8MuInstance, u8MuChannel, gSyncTxOption, pHseSrvDesc);
    return hseSrvResponse;
}
/*******************************************************************************
 * Function:    GetSetAttrByMu
 * Description: Gets/Sets the specified attribute on specified MU interface and channel
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t GetSetAttrByMu
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr,
    bool_t bSet,
    uint8_t muInstance,
    uint8_t muChannel
)
{
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = NULL;

    pHseSrvDesc = &gHseSrvDesc[muInstance][muChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    if(bSet)
    {
        pHseSrvDesc->srvId = HSE_SRV_ID_SET_ATTR;
    }
    else
    {
        pHseSrvDesc->srvId = HSE_SRV_ID_GET_ATTR;
    }
    
    pHseSrvDesc->hseSrv.getAttrReq.attrId   = attrId;
    pHseSrvDesc->hseSrv.getAttrReq.attrLen  = attrLen;
    pHseSrvDesc->hseSrv.getAttrReq.pAttr    = (HOST_ADDR)pAttr;

    hseSrvResponse = HSE_Send(muInstance, muChannel, gSyncTxOption, pHseSrvDesc);
    return hseSrvResponse;
}

#ifdef __cplusplus
}
#endif

/** @} */
