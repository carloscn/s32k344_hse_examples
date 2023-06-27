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

/*=============================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=============================================================================*/
#include "hse_demo_app_services.h"
#include "hse_b_catalog_formatting.h"
#include "hse_global_variables.h"
#include "hse_host_attrs.h"
#include "string.h"
#include "hse_common_types.h"
#include "hse_host_import_key.h"
#include "hse_host_cipher.h"
#include "hse_host_boot.h"
#include "hse_demo_app_services.h"

/*=============================================================================
*                 LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

/*=============================================================================
*                         LOCAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         LOCAL VARIABLES
=============================================================================*/

/*=============================================================================
*                         GLOBAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/
uint32_t length_adkphash = ADKP_LENGTH;
volatile uint8_t programmed_appdebugkey[ADKP_LENGTH] = {0U};
hseSrvResponse_t keyprog_srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
extern volatile bool_t write_attr;
volatile uint8_t adkp_hash[ADKP_LENGTH] = {0U};
extern volatile hseSrvResponse_t gsrvResponse;
/*=============================================================================
*                      LOCAL FUNCTION PROTOTYPES
=============================================================================*/

/*=============================================================================
*                      LOCAL FUNCTIONS
=============================================================================*/

/*=============================================================================
*                      GLOBAL FUNCTIONS
=============================================================================*/


/******************************************************************************
 * Function:    HSE_ReadAdkp
 * Description: Function for programming ADK/P request.
 *              It is a write-once operation.
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
    srvResponse = Get_Attr
            (
                    HSE_APP_DEBUG_KEY_ATTR_ID,
                    sizeof(hseAttrApplDebugKey_t),
                    (void *)pDebugKey
            );
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
                    MU0,
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
 * Function:    check_debug_password_programmed_status
 * Description: checks if debug key is programmed
 ******************************************************************************/
bool_t check_debug_password_programmed_status(void)
{
    //clear the buffers
    bool_t status = FALSE;
    memset((void *)&programmed_appdebugkey,0U,ADKP_LENGTH);
    memset((void *)&adkp_hash,0U,ADKP_LENGTH);
    hseSrvResponse_t srvResponse = HSE_ReadAdkp((uint8_t *)&programmed_appdebugkey);
    //read ADKP hash value
    if( HSE_SRV_RSP_OK == srvResponse )
    {
     status = TRUE;
    }
    return status;
}


static hseSrvResponse_t HSE_CalculateAdkpHash( uint8_t *pDebugKey )
{
    uint8_t local_adkp_hash[32] = {0U};
    uint32_t hash_length = 32U;
    uint8_t uid[8] = {0};
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    uint8_t output[32] = {0U};
    uint8_t uid_hash[32] = {0U};
    hseAttrExtendCustSecurityPolicy_t hseSecurityPolicy = {0};

    (void)HSE_ReadAttrExtendCustSecurityPolicy((hseAttrExtendCustSecurityPolicy_t *)&hseSecurityPolicy);

    if(hseSecurityPolicy.enableADKm == TRUE)
    {
        /* calculate SHA256 hash of ADKP */
        srvResponse = HSE_HashDataBlocking
                    (
                            MU0,
                            HSE_ACCESS_MODE_ONE_PASS,
                            0,
                            HSE_HASH_ALGO_SHA2_256,
                            (const uint8_t *)&applicationDebugKeyPassword[0],
                            sizeof(hseAttrApplDebugKey_t),
                            (uint8_t *)&local_adkp_hash,
                            &hash_length
                    );

        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* calculate SHA256 hash of UID */
        memcpy((uint8_t*)uid, (uint8_t*)(UTEST_BASE_ADDRESS + UID_OFFSET), 8UL);
        srvResponse = HSE_HashDataBlocking
                (
                        MU0,
                        HSE_ACCESS_MODE_ONE_PASS,
                        0,
                        HSE_HASH_ALGO_SHA2_256,
                        (const uint8_t *)(uid),
                        8UL,
                        (uint8_t *)&uid_hash,
                        &hash_length
                );

        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* encrypt UID hash with ADKP hash as key */
        /* import key */
        srvResponse = ImportPlainSymKeyReq(
                HSE_DEMO_RAM_AES128_ADKP_KEY,
                HSE_KEY_TYPE_AES,
                HSE_KF_USAGE_ENCRYPT,
                hash_length,
                local_adkp_hash,
                0U);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        srvResponse = AesEncrypt( HSE_DEMO_RAM_AES128_ADKP_KEY, HSE_CIPHER_BLOCK_MODE_ECB,
                0UL, 16UL, uid_hash, output, HSE_SGT_OPTION_NONE);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);

        /* calculate SHA224  */
        srvResponse = HSE_HashDataBlocking
                (
                        MU0,
                        HSE_ACCESS_MODE_ONE_PASS,
                        0,
                        HSE_HASH_ALGO_SHA2_224,
                        (const uint8_t *)&output[0],
                        16UL,
                        pDebugKey,
                        &hash_length
                );
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
    }
    else
    {
        //read adkp hash simple
        srvResponse = HSE_CalculateHASH(pDebugKey);
        ASSERT(HSE_SRV_RSP_OK == srvResponse);
    }
    return HSE_SRV_RSP_OK;
}

void ProgramADKPService(void)
{
    /*
    * Program Application debug key/password example.
    * Current Life-cycle shall be Customer Delivery.
    * Check if ADKP is programmed already
    */
     keyprog_srvResponse = HSE_ReadAdkp((uint8_t *)&programmed_appdebugkey);
     /*
      * First time when ADKP is not programmed,
      * read adkp will always result in not allowed
      * If ADKP is not programmed then do so
      */
      if( (HSE_SRV_RSP_NOT_ALLOWED == keyprog_srvResponse) && (TRUE == write_attr) )
      {
       gsrvResponse = HSE_ProgramAdkp();
      }
      /*generate IVT CMAC and take backup*/
       gsrvResponse = generateIvtSign();
      /*
      *  if adkp is read or adkp is programmed,
      *  adkp hash is calculated to verify if correct adkp is written
      */
      if((HSE_SRV_RSP_OK == gsrvResponse) ||( HSE_SRV_RSP_OK == keyprog_srvResponse))
      {
      /*
      * SHA2_224 algorithm used for HASH calculation,
      * service id HSE_SRV_ID_HASH requested to HSE to generate hash in adkp_hash
      */
      gsrvResponse = HSE_CalculateAdkpHash((uint8_t *)&adkp_hash);
      }
      /*read adkp hash*/
      gsrvResponse = HSE_ReadAdkp((uint8_t *)&programmed_appdebugkey);
     /*compare hash calculated with hash read, if correct then ADKP program successful*/
     if( ( HSE_SRV_RSP_OK == gsrvResponse )&&\
         ( TRUE == HSE_CompareAdkp( (uint8_t *)&programmed_appdebugkey, (uint8_t *)&adkp_hash ) )
            )
      {
      testStatus |= (ADKP_PROGRAMMING_SUCCESS|ADKP_KEY_VERIFIED);
      }

}

 


#ifdef __cplusplus
}
#endif

/** @} */
