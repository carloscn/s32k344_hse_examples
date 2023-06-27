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
/*===========================================================================*/

/*=============================================================================
                                        Description
=============================================================================*/
/**
 *
 */

/*=============================================================================
 *                                        INCLUDE FILES
 ============================================================================*/
#include "hse_srv_attr.h"
#include "std_typedefs.h"
#include "hse_host_flashSrv.h"
#include "hse_demo_app_services.h"
#include "string.h"
#include "hse_mu.h"
/*=============================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ============================================================================*/

/*=============================================================================
 *                                       LOCAL MACROS
 ============================================================================*/

/*=============================================================================
 *                                      LOCAL CONSTANTS
 ============================================================================*/
#define RAM_ADDRESS_FOR_UTEST 0x2100F000U
#define HSE_GPR_FIRMWARE_INSTALL_STAT (0x4039C028UL)

/*=============================================================================
 *                                      LOCAL VARIABLES
 ============================================================================*/

/*=============================================================================
 *                                      GLOBAL CONSTANTS
 ============================================================================*/

/*=============================================================================
 *                                      GLOBAL VARIABLES
 ============================================================================*/
volatile uint32_t FirmwarePresent;
/*=============================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ============================================================================*/
static uint32_t IsFirmwarePresent(void);

/*=============================================================================
 *                                       LOCAL FUNCTIONS
 ============================================================================*/
static uint32_t IsFirmwarePresent(void)
{
    FirmwarePresent = (*(volatile uint32_t *)(HSE_GPR_FIRMWARE_INSTALL_STAT));

    if ((FirmwarePresent & 0x1) != 0x1)
    {
        return 1UL;
    }

    if ((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) != 0)
    {
        return 1UL;
    }
    else
    {
        return 0UL;
    }
}
/*=============================================================================
 *                                       GLOBAL FUNCTIONS
 ============================================================================*/

/******************************************************************************
 * Function:    EnableHSEFWUsage
 * Description: Enables HSE FW feature by programming UTEST area
 *****************************************************************************/
hseSrvResponse_t EnableHSEFWUsage(void)
{
    Fls_CheckStatusType write_status = FLS_JOB_FAILED;

    /* copy HSE FW feature flag value in UTEST area offset 0 */
    MU_REG_WRITE64(RAM_ADDRESS_FOR_UTEST, HSEFWFEATUREFLAG_ENABLED_VALUE);
    write_status = HostFlash_Program(UTEST_MEMORY,
                                     (uint32_t)UTEST_BASE_ADDRESS,
                                     (uint8_t *)RAM_ADDRESS_FOR_UTEST,
                                     (uint32_t)8U);
    /* check if flash write was successful else will be stuck */
    ASSERT(write_status == FLS_JOB_OK);
    return HSE_SRV_RSP_OK;
}

/******************************************************************************
 * Function:    checkHseFwFeatureFlagEnabled
 * Description: Verifies whether hse fw feature flag is already enabled or not
 *****************************************************************************/
bool_t checkHseFwFeatureFlagEnabled(void)
{
    bool_t fw_enabled = FALSE;
    uint64_t default_val = UINT64_MAX_VAL;

    while (1UL != IsFirmwarePresent());

    uint64_t hsefwfeatureflag = MU_REG_READ64(UTEST_BASE_ADDRESS);

    /* check the default value */
    if (FALSE != memcmp((void *)&hsefwfeatureflag, (void *)&default_val, 0x8U))
    {
        fw_enabled = TRUE;
    }
    return fw_enabled;
}
