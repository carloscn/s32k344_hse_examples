/**
    @file        main.c
    @version     1.0.0

    @brief       SBAF Update Demo Application.
    @details     Sample application demonstrating host request to execute sBAF update.
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


/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

typedef struct
{
    uint8_t     reserved1;
    uint8_t     socTypeId;
    uint16_t    reserved2;
    uint8_t     majorVersion;
    uint8_t     minorVersion;
    uint16_t    patchVersion;
} sbafVersion_t;


/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

#define ASSERT(condition)   \
    do {                    \
        if(!(condition))    \
            while(1);       \
    } while(0)


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

/* Variable to store SBAF version details */
sbafVersion_t gsbafVersion = {0U};

/*=============================================================================
 *                        GLOBAL FUNCTIONS
 * ==========================================================================*/
hseSrvResponse_t sbafUpdateExample();

int main(void)
{
    /* Wait for HSE to initialize(read status bits) after installation */
    while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0){}

    /* Get the current installed SBAF version */
    memcpy(&gsbafVersion, (uint8_t*)0x4039C020, sizeof(sbafVersion_t));

    /* SBAF Update Request Example */
    sbafUpdateExample();

    /* At this point sbaf update service was executed.
     * Reset the part for the new sBAF FW to boot
     */

    while(1);
    return 0;
}


/******************************************************************************
 * Function:    sbafUpdateExample
 * Description: Example usage of the hseSbafUpdate service
******************************************************************************/
hseSrvResponse_t sbafUpdateExample()
{
	hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];
    hseSbafUpdateSrv_t *psbafUpdateSrv;

    MuInstance = 0;

    /* Get a free channel on Message Unit instance 0*/
    MuChannel = HSE_MU_GetFreeChannel(MuInstance);

    pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_SBAF_UPDATE;
    psbafUpdateSrv = &(pHseSrvDesc->hseSrv.sbafUpdateReq);
    psbafUpdateSrv->pInFwFile = (HOST_ADDR)0x400000;
    psbafUpdateSrv->accessMode = HSE_ACCESS_MODE_ONE_PASS;

    srvResponse = HSE_Send(MuInstance, MuChannel, gSyncTxOption, pHseSrvDesc);

    ASSERT(HSE_SRV_RSP_OK == srvResponse);

    return srvResponse;
}
