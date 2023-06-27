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

        /* HSE extend CUST security policies attribute */
        hseAttrExtendCustSecurityPolicy_t gHSEextendCustSecurityPolicy;
        extern volatile hseSrvResponse_t gsrvResponse;
        extern volatile bool_t write_attr;
        volatile hseAttrExtendCustSecurityPolicy_t ReadSecurityPolicy = {0};
        extern volatile int8_t GetStartAsUserBit;
        extern volatile int8_t GetEnableAdkmBit;
        volatile bool_t gStartAsUserBit = FALSE;
        volatile bool_t SetEnableAdkmBit = FALSE;
        /*=============================================================================
        *                                   LOCAL FUNCTION PROTOTYPES
        =============================================================================*/

        /*=============================================================================
        *                                       LOCAL FUNCTIONS
        =============================================================================*/

        /*=============================================================================
        *                                       GLOBAL FUNCTIONS
        =============================================================================*/

        /******************************************************************************
         * Function:    HSE_AttrExtendCustSecurityPolicy
         * Warning:     This is one time configurable only, the reverse is not possible
         * Description: Function for programming ADK/P (Application debug key/password)
         *              request. When Debug Authorization Mode bit is not set,
         *              it is interpreted as a password.
         *              When Debug Authorization Mode bit is set, it is interpreted as
         *              a key for challenge-response mechanism.
         ******************************************************************************/
        hseSrvResponse_t HSE_AttrExtendCustSecurityPolicy(bool_t EnableAdkmBit, bool_t StartAsUserBit)
        {
                hseSrvResponse_t srvResponse;
                /* enable ASKP master */
                gHSEextendCustSecurityPolicy.enableADKm = EnableAdkmBit;
                /* Host granted Super User rights, one time programmable,
                 * operation not reversible
                 */
                gHSEextendCustSecurityPolicy.startAsUser = StartAsUserBit;
                /* WARNING: This operation is irreversible */
                srvResponse = SetAttr(
                    HSE_EXTEND_CUST_SECURITY_POLICY_ATTR_ID,
                    sizeof(hseAttrExtendCustSecurityPolicy_t),
                    (void *)&gHSEextendCustSecurityPolicy);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
                return srvResponse;
        }

        /******************************************************************************
         * Function:    HSE_ReadAttrExtendCustSecurityPolicy
         * Description: Returns extended customer security policy value
         ******************************************************************************/
        hseSrvResponse_t HSE_ReadAttrExtendCustSecurityPolicy(hseAttrExtendCustSecurityPolicy_t *pSecurityPolicy)
        {
                hseSrvResponse_t srvResponse;
                /* Read extended customer security policy attribute value */
                srvResponse = Get_Attr(
                    HSE_EXTEND_CUST_SECURITY_POLICY_ATTR_ID,
                    sizeof(hseAttrExtendCustSecurityPolicy_t),
                    (void *)pSecurityPolicy);
                ASSERT(HSE_SRV_RSP_OK == srvResponse);
                return srvResponse;
        }

        void ExtendCustomerSecurityPolicyService(void)
        {
                gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
                (void)HSE_ReadAttrExtendCustSecurityPolicy((hseAttrExtendCustSecurityPolicy_t *)&ReadSecurityPolicy);
                /*user requested to extend security policy*/
                /*check if security policy is already extended, if yes then do not request SetAttribute to HSE*/
                if ((FALSE == ReadSecurityPolicy.enableADKm) && (ADKP_PROGRAMMING_SUCCESS != (testStatus & ADKP_PROGRAMMING_SUCCESS)))
                {
                        if (TRUE == write_attr)
                        {
                                gsrvResponse = HSE_AttrExtendCustSecurityPolicy(SetEnableAdkmBit, gStartAsUserBit);
                                if (HSE_SRV_RSP_OK == gsrvResponse)
                                {
                                        testStatus |= EXTEND_CUST_SECURE_POLICY_ENABLED;
                                        (void)HSE_ReadAttrExtendCustSecurityPolicy((hseAttrExtendCustSecurityPolicy_t *)&ReadSecurityPolicy);
                                }
                        }
                }
                /*security policy already extended*/
                else if (TRUE == ReadSecurityPolicy.enableADKm)
                {
                        testStatus |= EXTEND_CUST_SECURE_POLICY_ENABLED;
                }
                GetStartAsUserBit = ReadSecurityPolicy.startAsUser;
                GetEnableAdkmBit = ReadSecurityPolicy.enableADKm;
        }

#ifdef __cplusplus
}
#endif

/** @} */
