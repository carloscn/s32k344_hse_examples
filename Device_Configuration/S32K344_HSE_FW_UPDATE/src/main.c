/**
    @file        main.c
    @version     1.0.0

    @brief       HSE - FW Update Demo Application.
    @details     Sample application demonstrating host request to execute HSE FW update service.
*/
/*=============================================================================
                                         INCLUDE FILES
=============================================================================*/

#include "S32K344.h"
#include <typedefs.h>
#include <string.h>

#include "hse_mu.h"
#include "hse_host.h"
#include "hse_host_attrs.h"

#include "pflash.h"
#include "flash.h"


/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/


/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

#define ASSERT(condition)   \
    do {                    \
        if(!(condition))    \
            while(1);       \
    } while(0)

#define	PASSIVE_BLOCK_APP_START_ADDRESS	(0x600000)
#define APP_CODE_SIZE	(uint32_t)(&__TOTAL_FLASH_USED)

#define BLOCK2_START	(0x600000)

/*=============================================================================
*                         LOCAL VARIABLES
=============================================================================*/
static uint8_t MuInstance;
static uint8_t MuChannel;
/*=============================================================================
*                         GLOBAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/

extern const uint32_t CM7_START_ADDRESS;
extern const uint32_t __TOTAL_FLASH_USED;

extern uint32_t __HSE_BIN_START;	// Address obtained from linker file, where HSE encrypted bin is stored

/* Variable to store HSE FW version details */
hseAttrFwVersion_t gHseFwVersion = {0U};

/*=============================================================================
 *                        GLOBAL FUNCTIONS
 * ==========================================================================*/
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion );
hseSrvResponse_t HSE_FwUpdateExample();


int main(void)
{
    /* Wait for HSE to initialize */
    while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0){}

    /* Get the current installed HSE FW version  */
    (void)HSE_GetVersion_Example(&gHseFwVersion);

    /* HSE FW Update Request Example */
    HSE_FwUpdateExample();

    /* At this point FW update service was executed.
     * Reset the part for the new HSE FW version to be executed
     */

    while(1);
    return 0;
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

/******************************************************************************
 * Function:    HSE_FwUpdateExample
 * Description: Example usage of the hseFirmwareUpdate service
******************************************************************************/
hseSrvResponse_t HSE_FwUpdateExample()
{
	hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];
    hseFirmwareUpdateSrv_t *pFwUpdateSrv;

	/* Status variable for flash interface */
    __attribute__((unused)) tFLASH_STATUS status;

#ifdef AB_SWAP_TO_AB_SWAP
	/* For an update from AB_SWAP to AB_SWAP version, the application needs to make a copy of itself in passive partition. */

    /* Unlock flash memory in block 2 (from passive partition) */
    PFLASH_Unlock(PFLASH_BL2, PFLASH_ALL_SS, PFLASH_ALL_S);

    /* Erase flash block 2 */
	FLASH_EraseBlock((uint32_t*)BLOCK2_START);

	/* Copy application from active blocks to passive blocks */
	status = FLASH_Write((uint32_t*)PASSIVE_BLOCK_APP_START_ADDRESS, (uint32_t*)&CM7_START_ADDRESS, APP_CODE_SIZE);
#endif

    MuInstance = 0;

    /* Get a free channel on Message Unit instance 0*/
    MuChannel = HSE_MU_GetFreeChannel(MuInstance);

    pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_FIRMWARE_UPDATE;
    pFwUpdateSrv = &(pHseSrvDesc->hseSrv.firmwareUpdateReq);
    pFwUpdateSrv->pInFwFile = (HOST_ADDR)&__HSE_BIN_START;

    srvResponse = HSE_Send(MuInstance, MuChannel, gSyncTxOption, pHseSrvDesc);

    ASSERT(HSE_SRV_RSP_OK == srvResponse);

#ifdef AB_SWAP_TO_AB_SWAP
    /* Activate the passive blocks through the dedicated HSE service
     * After next reset, a swap would be executed and the new HSE firmware would run.
     */

    MuChannel = HSE_MU_GetFreeChannel(MuInstance);

    pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK;

    srvResponse = HSE_Send(MuInstance, MuChannel, gSyncTxOption, pHseSrvDesc);

    ASSERT(HSE_SRV_RSP_OK == srvResponse);
#endif

    return srvResponse;
}

