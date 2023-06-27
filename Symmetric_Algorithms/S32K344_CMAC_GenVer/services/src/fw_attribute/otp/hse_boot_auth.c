/**
 *   @file    hse_fuses.c
 *
 *   @brief   Examples of HSE UTEST  programming.
 *
 *   @addtogroup [hse_utest]
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
        * 1) system and project includes
        * 2) needed interfaces from external units
        * 3) internal and external interfaces from this unit
        ==================================================================================================*/

#include "hse_global_variables.h"
#include "hse_host_attrs.h"
#include "string.h"


        /*=============================================================================
        *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
        =============================================================================*/

        /*=============================================================================
        *                                       LOCAL MACROS
        =============================================================================*/

        /*=============================================================================
        *                                      LOCAL CONSTANTS
        =============================================================================*/

        /*=============================================================================
        *                                      LOCAL VARIABLES
        =============================================================================*/

        /*=============================================================================
        *                                      GLOBAL CONSTANTS
        =============================================================================*/

        /*=============================================================================
        *                                      GLOBAL VARIABLES
        =============================================================================*/
        extern volatile hseSrvResponse_t gsrvResponse;
        hseAttrConfigBootAuth_t gIVTauthvalue = 0U;
        extern volatile bool_t write_attr;
        /*=============================================================================
        *                                   LOCAL FUNCTION PROTOTYPES
        =============================================================================*/

        /*=============================================================================
        *                                       LOCAL FUNCTIONS
        =============================================================================*/

        /*=============================================================================
        *                                       GLOBAL FUNCTIONS
        =============================================================================*/

        /*****************************************************************************
         * Function:    HSE_EnableIVTAuthentication
         * Description: Function for enabling IVT authentication
         *              When authentication of IVT is enabled, during startup,
         *              IVT will be authenticated
         *              and then only execution will go to HSE FW
         *****************************************************************************/
        hseSrvResponse_t HSE_EnableIVTAuthentication(void)
        {
                hseSrvResponse_t srvResponse;
                hseAttrConfigBootAuth_t configIvtAth;

                /* WARNING: This operation is irreversible */
                /* Enable IVT authentication */
                configIvtAth = HSE_IVT_AUTH;

                srvResponse = SetAttr(
                    HSE_ENABLE_BOOT_AUTH_ATTR_ID,
                    sizeof(hseAttrConfigBootAuth_t),
                    (void *)&configIvtAth);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
                return srvResponse;
        }

        /******************************************************************************
         * Function:    HSE_GetIVTauthbit
         * Description: Function for reading IVT authentication bit
         ******************************************************************************/
        hseSrvResponse_t HSE_GetIVTauthbit(hseAttrConfigBootAuth_t *pIvtValue)
        {
                hseSrvResponse_t srvResponse;

                srvResponse = Get_Attr(
                    HSE_ENABLE_BOOT_AUTH_ATTR_ID,
                    sizeof(hseAttrConfigBootAuth_t),
                    (void *)pIvtValue);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
                return srvResponse;
        }

        void IVT_Auth_Service()
        {
                /*read first to confirm if IVT auth already enabled*/
                gsrvResponse = HSE_GetIVTauthbit(&gIVTauthvalue);
                /*check if ADKP is programmed*/
                if ((ADKP_PROGRAMMING_SUCCESS == (testStatus & ADKP_PROGRAMMING_SUCCESS)) && (TRUE == write_attr) && (0U == gIVTauthvalue))
                {
                        /*S
                         * only if IVT auth bit is not set and ADKP is programmed,
                         * will the user be allowed to change enable boot auth
                         */
                        if ((HSE_IVT_NO_AUTH == gIVTauthvalue) &&
                            (HSE_SRV_RSP_OK == gsrvResponse))
                        {
                                gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
                                gsrvResponse = UpdateIvt(NON_SECURE_IVT);
                                /*
                                 * write IVT auth bit executed and then read back to
                                 * confirm that value was written as expected
                                 */
                                gsrvResponse = HSE_EnableIVTAuthentication();
                                if (HSE_SRV_RSP_OK == gsrvResponse)
                                {
                                        (void)HSE_GetIVTauthbit(&gIVTauthvalue);
                                        if (HSE_IVT_AUTH == gIVTauthvalue)
                                        {
                                                testStatus |= IVT_AUTHENTICATION_ENABLED;
                                        }
                                }
                        }
                        else if (HSE_IVT_AUTH == gIVTauthvalue)
                        {
                                testStatus |= IVT_AUTHENTICATION_ENABLED;
                                gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
                        }
                }
        }

#ifdef __cplusplus
}
#endif

/** @} */
