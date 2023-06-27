/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K344.h"
#include <typedefs.h>
#include <string.h>
#include "hse_host_services.h"

/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

#define ADKP_PROGRAMMING 		(0)
#define LC_ADVANCE		 		(0)

#define HSE_NVM_CATALOG \
		{HSE_MU0_MASK, 	 HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PAIR,	10U, HSE_KEY256_BITS },	\
		{0U,				 0U,				0U,		0U			 					 }


#define HSE_RAM_CATALOG	\
		{HSE_MU0_MASK,    HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_ECC_PUB,	10U, HSE_KEY256_BITS },	\
		{0U,				 0U,				0U,		0U			 					 }

typedef enum
{
    ADKP_NOT_PROGRAMMED = 0,
	ADKP_PROGRAMMING_SUCCESS = 1
}adkpstatus_t;

//Argument for the async hash callback function
typedef struct
{
    uint8_t u8MuInstance;
    uint8_t u8MuChannel;
} hashCallbackParams_t;

/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

#define ASSERT(condition)   \
    do {                    \
        if(!(condition))    \
            while(1);       \
    } while(0)

#define ADKP_LENGTH						(uint8_t)16U

/*=============================================================================
*                         LOCAL VARIABLES
=============================================================================*/

uint32_t length_adkphash = ADKP_LENGTH;

/*=============================================================================
*                         GLOBAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/

/* Variable to store HSE FW version details */
hseAttrFwVersion_t gHseFwVersion = {0U};

volatile adkpstatus_t gAdkpKeyTest = ADKP_NOT_PROGRAMMED;

/* ADKP Key/Password required variables */
volatile uint8_t programmed_appdebugkey[ADKP_LENGTH] = {0U}; //Store the reading of the ADKP
volatile uint8_t adkp_hash[ADKP_LENGTH]              = {0U}; //Store the hash conversion of the ADKP
volatile uint8_t applicationDebugKeyPassword[16U] =
{
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
	0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x21
};

/* HASH Required Variables */
static uint32_t numberOfResponses = 0;
hashCallbackParams_t callbackParams[HSE_NUM_OF_MU_INSTANCES]
                                    [HSE_NUM_OF_CHANNELS_PER_MU];
volatile hseSrvResponse_t asyncResponses[HSE_NUM_OF_MU_INSTANCES]
                                         [HSE_NUM_OF_CHANNELS_PER_MU] = {0};

/* LC monitoring variables */
hseAttrSecureLifecycle_t gHseCurrentLC = HSE_LC_CUST_DEL;

hseAttrDebugAuthMode_t gDebugAuthMode;
bool_t DynamicAuth = FALSE; //Change to TRUE only if you want to activate Dynamic Authentication

hseSrvResponse_t gSrvResp;

const hseKeyGroupCfgEntry_t NVMcatalog[] = {HSE_NVM_CATALOG};
const hseKeyGroupCfgEntry_t RAMcatalog[] = {HSE_RAM_CATALOG};

/*=============================================================================
 *                        GLOBAL FUNCTIONS
 * ==========================================================================*/
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion );
boolean check_DebugPasswordProgrammed_Status(void);
hseSrvResponse_t HSE_ReadDebugAuthMode(hseAttrDebugAuthMode_t *pDebugAuthMode);
hseSrvResponse_t HSE_setDebugAuthMode(hseAttrDebugAuthMode_t DebugAuthMode);
hseSrvResponse_t HSE_ProgramAdkp(void);
hseSrvResponse_t HSE_ReadAdkp( uint8_t *pDebugKey );
hseSrvResponse_t HSE_CalculateHASH( uint8_t *pAdkpHash );
bool_t HSE_CompareAdkp( uint8_t *pDebugKey, uint8_t *pAdkpHash );
hseSrvResponse_t HSE_HashDataNonBlocking
(
    uint8_t u8MuInstance,
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseHashAlgo_t hashAlgo,
    const uint8_t *pInput,
    uint32_t inputLength,
    uint8_t *pHash,
    uint32_t *pHashLength
);
static void HSE_HashRequestCallback(hseSrvResponse_t srvResponse,void* pArg);
hseSrvResponse_t HSE_ReadLifecycle( hseAttrSecureLifecycle_t *plifecycle );
void HSE_AdvanceLifecycle(hseAttrSecureLifecycle_t targetLifeCycle);

int main(void) {

	/* Wait for HSE to initialize(read status bits)*/
	while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0) {}

	(void)HSE_GetVersion_Example(&gHseFwVersion);

	/*=============================================================================
	 *                        	HSE Configuration
	 * ==========================================================================*/

	/* Check if NVM and RAM keys already formatted */
	/* format NVM and RAM key catalog */
	gSrvResp = FormatKeyCatalogs(NVMcatalog, RAMcatalog);
	//Generate or import appropriate keys for the application

	//Check the current Debug Authentication Mode
	gSrvResp = HSE_ReadDebugAuthMode(&gDebugAuthMode);
	if((gSrvResp == HSE_SRV_RSP_OK) && (gDebugAuthMode == HSE_DEBUG_AUTH_MODE_PW) && (DynamicAuth == TRUE)){
		gSrvResp = HSE_setDebugAuthMode(HSE_DEBUG_AUTH_MODE_CR);
		ASSERT(HSE_SRV_RSP_OK == gSrvResp);
	}

	/*=============================================================================
	 *                        	ADKP Programming
	 * ==========================================================================*/
	#if (1==ADKP_PROGRAMMING)
	if(FALSE == check_DebugPasswordProgrammed_Status()){
		gSrvResp = HSE_ProgramAdkp();
	}

	gSrvResp = HSE_ReadAdkp((uint8_t *)&programmed_appdebugkey);

	if(HSE_SRV_RSP_OK == gSrvResp){
		gSrvResp = HSE_CalculateHASH((uint8_t *)&adkp_hash);
		ASSERT(HSE_SRV_RSP_OK == gSrvResp);
	}

	if( ( HSE_SRV_RSP_OK == gSrvResp )&&\
		( TRUE == HSE_CompareAdkp( (uint8_t *)&programmed_appdebugkey, (uint8_t *)&adkp_hash ) )
	){
		gAdkpKeyTest = ADKP_PROGRAMMING_SUCCESS;
	}
	#endif

	/*=============================================================================
	 *                        	Application
	 * ==========================================================================*/

	//Here goes the customer's application

	/*=============================================================================
	 *                        	LC Advancing
	 * ==========================================================================*/
#if (1 == LC_ADVANCE)
	gSrvResp = HSE_ReadLifecycle(&gHseCurrentLC);
	if((gHseCurrentLC == HSE_LC_CUST_DEL) && (gAdkpKeyTest == ADKP_PROGRAMMING_SUCCESS)){
		HSE_AdvanceLifecycle(HSE_LC_OEM_PROD);
	} else if((gHseCurrentLC == HSE_LC_OEM_PROD) && (gAdkpKeyTest == ADKP_PROGRAMMING_SUCCESS)){
		HSE_AdvanceLifecycle(HSE_LC_IN_FIELD);
	}
#endif

	while(1){
	}
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
 * Function:    check_DebugPasswordProgrammed_Status
 * Description: checks if debug key is programmed
 ******************************************************************************/
boolean check_DebugPasswordProgrammed_Status (void)
{
    //clear the buffers
    boolean status = FALSE;
    memset((void *)&programmed_appdebugkey,0U,ADKP_LENGTH);
    memset((void *)&adkp_hash,0U,ADKP_LENGTH);
    hseSrvResponse_t srvResponse = HSE_ReadAdkp((uint8_t *)&programmed_appdebugkey);
    //read ADKP hash value
    if( HSE_SRV_RSP_OK == srvResponse )
    {
        //calculate ADKP hash
        //srvResponse = HSE_CalculateHASH(&adkp_hash);
        //compare ADKP hashes, if matches then ADKP is programmed
        //if( HSE_SRV_RSP_OK == srvResponse)
        //{
            //status = HSE_CompareAdkp(&programmed_appdebugkey,&adkp_hash);
            status = TRUE;
        //}
    }
    return status;
}

/******************************************************************************
 * Function:    HSE_ReadDebugAuthMode
 * Description: Function to read the debug authentication mode (static/dynamic).
******************************************************************************/

hseSrvResponse_t HSE_ReadDebugAuthMode(hseAttrDebugAuthMode_t *pDebugAuthMode)
{
	hseSrvResponse_t srvResponse;
	    srvResponse = GetAttr
	            (
	            		HSE_DEBUG_AUTH_MODE_ATTR_ID,
	                    sizeof(hseAttrDebugAuthMode_t),
	                    (void *)pDebugAuthMode
	            );
	    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_setDebugAuthMode
 * Description: Function for setting the appropriate authentication mode.
 * 				0 - Static / 1 - Dynamic.
 * 				Once the mode is set to dynamic it can't be undone.
******************************************************************************/
hseSrvResponse_t HSE_setDebugAuthMode(hseAttrDebugAuthMode_t DebugAuthMode)
{
    hseSrvResponse_t srvResponse;

    /* WARNING: If you wish to set auth mode to dynamic it will be irreversible */
    /* set up the appropriate Debug Authentication Mode (static or dynamic) */
    srvResponse = SetAttr(HSE_DEBUG_AUTH_MODE_ATTR_ID ,
        sizeof(hseAttrDebugAuthMode_t), (void *)&DebugAuthMode);
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_ProgramAdkp
 * Description: Function for programming ADK/P request.
 * 				This is a one time only operation.
******************************************************************************/
hseSrvResponse_t HSE_ProgramAdkp(void)
{
    hseSrvResponse_t srvResponse;

    /* WARNING: This operation is irreversible */
    /* Program the ADK/P (Application debug key/password) */
    srvResponse = SetAttr(HSE_APP_DEBUG_KEY_ATTR_ID,
        sizeof(hseAttrApplDebugKey_t), (void *)&applicationDebugKeyPassword);
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_ReadAdkp
 * Description: Reads ADKP hash
 ******************************************************************************/
hseSrvResponse_t HSE_ReadAdkp( uint8_t *pDebugKey )
{
    hseSrvResponse_t srvResponse;
    srvResponse = GetAttr
            (
                    HSE_APP_DEBUG_KEY_ATTR_ID,
                    sizeof(hseAttrApplDebugKey_t),
                    (void *)pDebugKey
            );
    return srvResponse;
}

static void HSE_HashRequestCallback(hseSrvResponse_t srvResponse,void* pArg)
{
   /*  Argument is a callbackInfo_t pointer which contains the MU interface
     * and the channel on which the request was sent*/
    hashCallbackParams_t *pCallbackParams = (hashCallbackParams_t *) pArg;
    uint8_t u8MuInstance = pCallbackParams->u8MuInstance;
    uint8_t u8MuChannel = pCallbackParams->u8MuChannel;

     /*Log the response*/
    asyncResponses[u8MuInstance][u8MuChannel] = srvResponse;
    numberOfResponses += 1;

     /*Check the HSE response*/
    if (HSE_SRV_RSP_OK != srvResponse)
    {

    }
}

/******************************************************************************
 * Function:    HSE_HashDataNonBlocking
 * Description: Non-blocking hash request.
 *****************************************************************************/
hseSrvResponse_t HSE_HashDataNonBlocking
(
    uint8_t u8MuInstance,
    hseAccessMode_t accessMode,
    uint32_t streamId,
    hseHashAlgo_t hashAlgo,
    const uint8_t *pInput,
    uint32_t inputLength,
    uint8_t *pHash,
    uint32_t *pHashLength
)
{
    uint8_t u8MuChannel = 1U;
    hseTxOptions_t asyncTxOptions;
    hseSrvDescriptor_t *pHseSrvDesc;
    hseHashSrv_t *pHashSrv;
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    //Complete the service descriptor placed in shared memory
    pHseSrvDesc = &gHseSrvDesc[0U][u8MuChannel];
    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHashSrv = &(pHseSrvDesc->hseSrv.hashReq);

    pHseSrvDesc->srvId      = HSE_SRV_ID_HASH;
    pHashSrv->accessMode    = accessMode;
    pHashSrv->streamId      = streamId;
    pHashSrv->hashAlgo      = hashAlgo;
    pHashSrv->inputLength   = inputLength;
    pHashSrv->pInput        = HSE_PTR_TO_HOST_ADDR(pInput);
    pHashSrv->pHash         = HSE_PTR_TO_HOST_ADDR(pHash);
    pHashSrv->pHashLength   = HSE_PTR_TO_HOST_ADDR(pHashLength);

    //Complete callback info and async txOptions*/
    callbackParams[u8MuInstance][u8MuChannel].u8MuInstance  = u8MuInstance;
    callbackParams[u8MuInstance][u8MuChannel].u8MuChannel   = u8MuChannel;
    asyncTxOptions.txOp              = HSE_TX_ASYNCHRONOUS;
    asyncTxOptions.pfAsyncCallback   = &(HSE_HashRequestCallback);
    asyncTxOptions.pCallbackpArg     =
            (void *)(&(callbackParams[u8MuInstance][u8MuChannel]));

    //Send the request asynchronously
    srvResponse = HSE_Send(u8MuInstance,u8MuChannel,asyncTxOptions,pHseSrvDesc);
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_CalculateHASH
 * Description: Calculates hash of programmed ADKP key
 ******************************************************************************/
hseSrvResponse_t HSE_CalculateHASH( uint8_t *pAdkpHash )
{
    hseSrvResponse_t srvResponse;
    srvResponse = HSE_HashDataNonBlocking
            (
            		0U,
                    HSE_ACCESS_MODE_ONE_PASS,
                    0,
                    HSE_HASH_ALGO_SHA2_224,
                    (const uint8_t *)&applicationDebugKeyPassword[0],
                    sizeof(hseAttrApplDebugKey_t),
                    pAdkpHash,
                    &length_adkphash
            );

    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

/******************************************************************************
 * Function:    HSE_CompareAdkp
 * Description: compares ADKP hashes
 ******************************************************************************/
bool_t HSE_CompareAdkp( uint8_t *pDebugKey, uint8_t *pAdkpHash )
{
    bool_t status = FALSE;
    if ( 0U == memcmp((void *)pDebugKey, (void *)pAdkpHash, ADKP_LENGTH) )
    {
     status = TRUE;
    }
    return status;
}

/******************************************************************************
 * Function:    HSE_ReadLifecycle
 * Description: Function for reading current Lifecycle.
******************************************************************************/
hseSrvResponse_t HSE_ReadLifecycle( hseAttrSecureLifecycle_t *plifecycle )
{
    hseSrvResponse_t srvResponse;

    /* Read the LC issuing a get attribute request to HSE */
    srvResponse = GetAttr(HSE_SECURE_LIFECYCLE_ATTR_ID, sizeof(hseAttrSecureLifecycle_t), (void *)plifecycle);

    return srvResponse;
}

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
