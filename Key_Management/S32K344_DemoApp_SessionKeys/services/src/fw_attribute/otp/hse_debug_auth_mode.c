/**
*   @file    hse_fuses.c
*
*   @brief   Examples of HSE fuses programming.
*
*   @addtogroup [hse_fuses]
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
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "hse_global_variables.h"
#include "hse_host_attrs.h"
#include "hse_demo_app_services.h"
#include "hse_host.h"
#include "hse_srv_attr.h"
#include <string.h>


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
extern volatile hseSrvResponse_t gsrvResponse;
extern volatile bool_t write_attr;
hseAttrDebugAuthMode_t gDebugAuthMode = 0U;
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
 * Description: Function for setting debug-authorization mode bit to Challenge Response.
 *              When Debug Authorization Mode bit is not set, ADK/P is interpreted as a password.
 *              When Debug Authorization Mode bit is set, ADK/P is interpreted as a key for challenge
 *              -response mechanism.
*************************************************************************************************/
/********************************************************************************************/
/*************************************** WARNING ********************************************/
/********************************************************************************************/
/* The following examples update HSE attributes in fuses. These operation are irreversible. */
/********************************************************************************************/

hseSrvResponse_t HSE_SetDebugAuthModeToChalResp( void )
{
    hseSrvResponse_t srvResponse;
    hseAttrDebugAuthMode_t debugAuthMode;

    /* WARNING: This operation is irreversible */
    /* Set debug-authorization mode attribute to Challenge Response */
    debugAuthMode = HSE_DEBUG_AUTH_MODE_CR;
    srvResponse = SetAttr(HSE_DEBUG_AUTH_MODE_ATTR_ID, sizeof(hseAttrDebugAuthMode_t), (void *)&debugAuthMode);
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

hseSrvResponse_t HSE_GetDebugAuthMode( hseAttrDebugAuthMode_t*pDebugAuthValue )
{
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    /* Read debug-authorization mode */
    srvResponse = Get_Attr(HSE_DEBUG_AUTH_MODE_ATTR_ID, sizeof(hseAttrDebugAuthMode_t), (void *)pDebugAuthValue);
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return HSE_SRV_RSP_OK;
}


void Debug_Auth_Service()
{
   gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
   /*check if debug auth mode already set to Challenge Response mode*/
   gsrvResponse = HSE_GetDebugAuthMode(&gDebugAuthMode);
   /*ADKP should be programmed in order to update debug mode*/
   if( ( ( (testStatus & (ADKP_PROGRAMMING_SUCCESS | CR_DEBUG_AUTH_MODE)) == ADKP_PROGRAMMING_SUCCESS )\
        &&  ( HSE_DEBUG_AUTH_MODE_PW == gDebugAuthMode )  && (TRUE == write_attr) ) )
        {
        gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
       /*change debug authorization mode to CR*/
        gsrvResponse = HSE_SetDebugAuthModeToChalResp();
       testStatus |= CR_DEBUG_AUTH_MODE;
        }
       /*if debug auth mode already set to CR*/
        else if(HSE_DEBUG_AUTH_MODE_CR == gDebugAuthMode)
        {
    	/*mode already configured to CR*/
        testStatus |= CR_DEBUG_AUTH_MODE;
       /*reponse udpate*/
        gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
       }
}

#ifdef __cplusplus
}
#endif

/** @} */
