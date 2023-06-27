/**
 *   @file    hse_host_sys_authorization.c
 *
 *   @brief   This file implements wrappers for SYS authorization request/response services.
 *
 *   @addtogroup [HOST_FRAMEWORK]
 *   @{
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

#ifdef __cplusplus
extern "C"
{
#endif

    /*==================================================================================================
     *                                        INCLUDE FILES
     ==================================================================================================*/

#include "hse_demo_app_services.h"
#include "string.h"
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

    /*************************************************************************************************
     * Description:  Performs a system authorization request
     ************************************************************************************************/
    hseSrvResponse_t HSE_SysAuthorizationReq(
        const hseSysAuthOption_t sysAuthOption,
        const hseSysRights_t sysAccess,
        const hseKeyHandle_t authorizationKeyHandle,
        const hseAuthScheme_t *pAuthScheme,
        uint8_t *pChallenge)
    {
        uint8_t u8MuChannel;
        hseSrvDescriptor_t *pHseSrvDesc;
        hseSysAuthorizationReqSrv_t *pSysAuthReqSrv;
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

        /* Get a free channel on MU0 */
        u8MuChannel = HSE_MU_GetFreeChannel(MU0);
        if (HSE_INVALID_CHANNEL == u8MuChannel)
        {
            goto exit;
        }

        /* Alloc free descriptor */
        pHseSrvDesc = &gHseSrvDesc[MU0][u8MuChannel];
        pSysAuthReqSrv = &(pHseSrvDesc->hseSrv.sysAuthorizationReq);
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        /* Complete service parameters */
        pHseSrvDesc->srvId = HSE_SRV_ID_SYS_AUTH_REQ;
        pSysAuthReqSrv->sysAuthOption = sysAuthOption;
        pSysAuthReqSrv->sysRights = sysAccess;
        pSysAuthReqSrv->ownerKeyHandle = authorizationKeyHandle;
        pSysAuthReqSrv->pChallenge = (HOST_ADDR)(pChallenge);
        if (NULL != pAuthScheme)
        {
            memcpy(&pSysAuthReqSrv->authScheme, pAuthScheme, sizeof(hseAuthScheme_t));
        }
        /* Send the request synchronously */
        srvResponse = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);

        return srvResponse;
    exit:
        return srvResponse;
    }

    /*************************************************************************************************
     * Description:  Sends the system authorization response
     ************************************************************************************************/
    hseSrvResponse_t HSE_SysAuthorizationResp(
        const uint8_t *pSign0,
        const uint8_t *pSign1,
        const uint16_t sign0Length,
        const uint16_t sign1Length)
    {
        uint8_t u8MuChannel;
        hseSrvDescriptor_t *pHseSrvDesc;
        hseSysAuthorizationRespSrv_t *pSysAuthRespSrv;
        hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

        /* Get a free channel on MU0 */
        u8MuChannel = HSE_MU_GetFreeChannel(MU0);
        if (HSE_INVALID_CHANNEL == u8MuChannel)
        {
            goto exit;
        }

        /* Alloc free descriptor */
        pHseSrvDesc = &gHseSrvDesc[MU0][u8MuChannel];
        pSysAuthRespSrv = &(pHseSrvDesc->hseSrv.sysAuthorizationResp);
        memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

        /* Complete service parameters */
        pHseSrvDesc->srvId = HSE_SRV_ID_SYS_AUTH_RESP;
        pSysAuthRespSrv->pAuth[0] = (HOST_ADDR)pSign0;
        pSysAuthRespSrv->pAuth[1] = (HOST_ADDR)pSign1;
        pSysAuthRespSrv->authLen[0] = sign0Length;
        pSysAuthRespSrv->authLen[1] = sign1Length;

        /* Send the request synchronously */
        srvResponse = HSE_Send(MU0, u8MuChannel, gSyncTxOption, pHseSrvDesc);

    exit:
        return srvResponse;
    }

#ifdef __cplusplus
}
#endif

/** @} */
