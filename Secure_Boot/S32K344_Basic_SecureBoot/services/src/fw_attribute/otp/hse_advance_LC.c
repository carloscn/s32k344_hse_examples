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
#include "hse_dcm_register.h"
#include "hse_global_variables.h"
#include "hse_host_attrs.h"
#include "string.h"
#include "hse_demo_app_services.h"


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

  /* Variables to enable fuse programming at run-time - Proceed with caution */
  volatile uint8_t gProgramFuses = 0U;
  volatile uint8_t gAdvanceLifecycleToOemProd = 0U;
  volatile uint8_t gAdvanceLifecycleToInField = 0U;
  extern volatile hseSrvResponse_t gsrvResponse;
  extern volatile bool_t write_attr;
  /* Current Life Cycle value */
  hseAttrSecureLifecycle_t gHseCurrentLC = HSE_LC_CUST_DEL;
  volatile hseAttrSecureLifecycle_t programLC = 0U;

  /*==================================================================================================
  *                                   LOCAL FUNCTION PROTOTYPES
  ==================================================================================================*/

  /*==================================================================================================
  *                                       LOCAL FUNCTIONS
  ==================================================================================================*/

  /*==================================================================================================
  *                                       GLOBAL FUNCTIONS
  ==================================================================================================*/

  /******************************************************************************
   * Description: Function for advancing Lifecycle. It is an irreversible operation.
   *              targetLifecycle = HSE_LC_OEM_PROD : Advance to OEM Production LC.
   *              targetLifecycle = HSE_LC_IN_FIELD : Advance to INFIELD LC.
   *
   *              Transitions allowed are :
   *              HSE_LC_CUST_DEL -> HSE_LC_OEM_PROD
   *              HSE_LC_CUST_DEL -> HSE_LC_IN_FIELD
   *              HSE_LC_OEM_PROD -> HSE_LC_IN_FIELD
   ******************************************************************************/
  void HSE_AdvanceLifecycle(hseAttrSecureLifecycle_t targetLifeCycle)
  {
    hseSrvResponse_t srvResponse;
    hseAttrSecureLifecycle_t lifeCycleToSet;

    /* WARNING: This operation is irreversible */
    /* Advance the Life Cycle to target value */
    lifeCycleToSet = targetLifeCycle;
    srvResponse = SetAttr(HSE_SECURE_LIFECYCLE_ATTR_ID,
                          sizeof(hseAttrSecureLifecycle_t), (void *)&lifeCycleToSet);
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
  }

  /******************************************************************************
   * Description: Function for reading current Lifecycle.
   ******************************************************************************/
  hseSrvResponse_t HSE_ReadLifecycle(hseAttrSecureLifecycle_t *plifecycle)
  {
    hseSrvResponse_t srvResponse;

    /* Read the LC issuing a get attribute request to HSE */
    srvResponse = Get_Attr(HSE_SECURE_LIFECYCLE_ATTR_ID, sizeof(hseAttrSecureLifecycle_t), (void *)plifecycle);

    return srvResponse;
  }

  void Advance_LifeCycle_Service()
  {
    /*
     * check if LC is CUST_DEL and ADKP is programmed
     * Note: This is one-time programmable only and
     * LC can only be advanced and not reversed back
     */
    gsrvResponse = HSE_ReadLifecycle(&gHseCurrentLC);
    if (((testStatus & (ADKP_PROGRAMMING_SUCCESS | LIFECYCLE_ADVANCED_TO_INFIELD)) == ADKP_PROGRAMMING_SUCCESS) 
    && ((gHseCurrentLC == HSE_LC_CUST_DEL) || 
    (gHseCurrentLC == HSE_LC_OEM_PROD)) && (TRUE == write_attr))
    {
      gsrvResponse = HSE_SRV_RSP_GENERAL_ERROR;
      /*Advances Life cycle to OEM Production Life cycle*/
      HSE_AdvanceLifecycle(programLC);
      gsrvResponse = HSE_ReadLifecycle(&gHseCurrentLC);
      if ((HSE_SRV_RSP_OK == gsrvResponse) && (HSE_LC_IN_FIELD == gHseCurrentLC))
      {
        testStatus |= LIFECYCLE_ADVANCED_TO_INFIELD;
      }
      else if ((HSE_SRV_RSP_OK == gsrvResponse) && (HSE_LC_OEM_PROD == gHseCurrentLC))
      {
        testStatus |= LIFECYCLE_ADVANCED_TO_OEM_PROD;
      }
    }
    else if (gHseCurrentLC == HSE_LC_IN_FIELD)
    {
      /*Life cycle is already advanced from CUST_DEL*/
      testStatus |= LIFECYCLE_ADVANCED_TO_INFIELD;
    }
    else if (gHseCurrentLC == HSE_LC_OEM_PROD)
    {
      testStatus |= LIFECYCLE_ADVANCED_TO_OEM_PROD;
    }
  }
#ifdef __cplusplus
}
#endif

/** @} */
