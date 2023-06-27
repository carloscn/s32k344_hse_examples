/**
    @file        main.c
    @version     1.0.0

    @brief       HSE - FW Install project.
    @details     Sample project demonstrating how to install HSE Firmware to S32K3 device
*/
/*=============================================================================
                                         INCLUDE FILES
=============================================================================*/

#include "S32K344.h"
#include <typedefs.h>
#include <string.h>

#include "hse_mu.h"
#include "hse_host_attrs.h"
#include "pflash.h"
#include "flash.h"


/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

typedef enum
{
    FW_NOT_INSTALLED = 0,
    FW_INSTALLED
}fwteststatus_t;


/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

#define ASSERT(condition)   \
    do {                    \
        if(!(condition))    \
            while(1);       \
    } while(0)


#define UTEST_BASE_ADDRESS		        0x1B000000UL

/*=============================================================================
*                         LOCAL VARIABLES
=============================================================================*/
/* HSE FW feature usage flag to be loaded in UTEST */
static uint8_t hseFwFeatureFlagEnabledValue[8] = {0xAA, 0xBB, 0xCC, 0xDD,
										   0xDD, 0xCC, 0xBB, 0xAA};

/*=============================================================================
*                         GLOBAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/

/* Variable to store HSE FW version details */
hseAttrFwVersion_t gHseFwVersion = {0U};

volatile fwteststatus_t gInstallHSEFwTest = FW_NOT_INSTALLED;

/*=============================================================================
 *                        GLOBAL FUNCTIONS
 * ==========================================================================*/
boolean checkHseFwFeatureFlagEnabled(void);
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion );


int main(void)
{
	/* Status variable for flash interface */
	tFLASH_STATUS status;

    /* Check if HSE FW usage flag is already enabled. Otherwise program the flag */
    if(FALSE == checkHseFwFeatureFlagEnabled())
    {
    	  /* unlock UTEST data flash sector */
    	  PFLASH_Unlock (PFLASH_BL5, PFLASH_SS0, PFLASH_S0);

    	  /* Write in UtestSector using main interface */
    	  status = FLASH_Write ((uint32_t*)UTEST_BASE_ADDRESS,
    			  	  	  	  	  	  	   hseFwFeatureFlagEnabledValue,
    	                                   sizeof(hseFwFeatureFlagEnabledValue));

    	  (void)status;	// Dummy read to remove warning
    }

    /* Wait for HSE to initialize(read status bits) after installation */
    while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0)
    {
        gInstallHSEFwTest = FW_NOT_INSTALLED;
        /* Please generate a reset to allow installation */
    }

    (void)HSE_GetVersion_Example(&gHseFwVersion);

    while(1);
    return 0;
}


/******************************************************************************
 * Function:    checkHseFwFeatureFlagEnabled
 * Description: Verifies whether hse fw feature flag is already enabled or not
 *****************************************************************************/
boolean checkHseFwFeatureFlagEnabled(void)
{
    boolean fw_enabled = FALSE;
    uint64_t default_val = 0xFFFFFFFFFFFFFFFFUL;
    uint64_t hsefwfeatureflag = *(uint64_t*)(UTEST_BASE_ADDRESS);

    //check the default value
    if(FALSE != memcmp((void *)&hsefwfeatureflag, (void *)&default_val, 0x8U))
    {
        fw_enabled = TRUE;
    }
    return fw_enabled;
}

/******************************************************************************
 * Function:    HSE_GetVersion_Example
 * Description: Example of HSE service - get FW version
******************************************************************************/
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion )
{
    hseSrvResponse_t srvResponse;
    srvResponse = GetAttr(
            HSE_FW_VERSION_ATTR_ID,
            sizeof(hseAttrFwVersion_t),
            pHseFwVersion );
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

