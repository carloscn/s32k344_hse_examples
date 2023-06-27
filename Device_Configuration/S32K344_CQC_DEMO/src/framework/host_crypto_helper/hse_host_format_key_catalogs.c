
/*==================================================================================================
*
*   Copyright 2020-2021 NXP.
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
 ==================================================================================================*/

#include "hse_host.h"

#include "hse_default_config.h"

#include "string.h" //memset
#include "hse_host_format_key_catalogs.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS

const hseKeyGroupCfgEntry_t nvmCatalog[] = {HSE_NVM_KEY_CATALOG_CFG};
const hseKeyGroupCfgEntry_t ramCatalog[] = {HSE_RAM_KEY_CATALOG_CFG};
#ifdef HSE_SPT_SMR_CR
static const hseKeyGroupCfgEntry_t sbRamCatalog[] = {HSE_SB_RAM_KEY_CATALOG_CFG};
static const hseKeyGroupCfgEntry_t sbnvmCatalog[] = {HSE_SB_NVM_KEY_CATALOG_CFG};
#endif/*#ifdef HSE_SPT_SMR_CR*/
static const hseKeyGroupCfgEntry_t nvmSheCatalog[] = {HSE_SHE_NVM_KEY_CATALOG_CFG};
static const hseKeyGroupCfgEntry_t ramSheCatalog[] = {HSE_SHE_RAM_KEY_CATALOG_CFG};

#if defined(HSE_SPT_INTERNAL_FLASH_DEV)
const hseKeyGroupCfgEntry_t nvmCatalog4[] = {HSE_NVM_KEY_CATALOG_CFG4};
#endif /* HSE_SPT_INTERNAL_FLASH_DEV */

/*==================================================================================================
 *                                      LOCAL VARIABLES
 ==================================================================================================*/
static uint8_t          muIf = 0U;
static uint8_t          muChannelIdx = 1U;
/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 ==================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/



/**
* @brief         This function formats the key catalogs.
* @details
*/
hseSrvResponse_t FormatKeyCatalogs(const hseKeyGroupCfgEntry_t* pNvmCatalog, const hseKeyGroupCfgEntry_t* pRamCatalog)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseFormatKeyCatalogsSrv_t*  pFormatKeyCatalogsReq = &pHseSrvDesc->hseSrv.formatKeyCatalogsReq;
    hseSrvResponse_t status;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    //Use the same default catalog configurations to re-format the NVM and RAM catalogs
    pHseSrvDesc->srvId = HSE_SRV_ID_FORMAT_KEY_CATALOGS;
    pFormatKeyCatalogsReq->pNvmKeyCatalogCfg= (HOST_ADDR)pNvmCatalog;
    pFormatKeyCatalogsReq->pRamKeyCatalogCfg= (HOST_ADDR)pRamCatalog;

    status = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);

    return status;
}

/**
* @brief         Wrapper for FormatKeyCatalogs.
* @details
*/
hseSrvResponse_t FormatKeyCatalogs_W(void)
{
    #ifdef HSE_SPT_FORMAT_KEY_CATALOGS
    hseSrvResponse_t status;
    status = FormatKeyCatalogs(nvmCatalog, ramCatalog);

    return status;
    #else
    return HSE_SRV_RSP_NOT_SUPPORTED;
    #endif
}

#ifdef HSE_SPT_SMR_CR

/**
* @brief         This function formats the key catalogs.
* @details
*/
hseSrvResponse_t SBFormatKeyCatalogs(void)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseFormatKeyCatalogsSrv_t*  pFormatKeyCatalogsReq = &pHseSrvDesc->hseSrv.formatKeyCatalogsReq;
    hseSrvResponse_t status;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    //Use the same default catalog configurations to re-format the NVM and RAM catalogs
    pHseSrvDesc->srvId = HSE_SRV_ID_FORMAT_KEY_CATALOGS;
    pFormatKeyCatalogsReq->pNvmKeyCatalogCfg= (HOST_ADDR)sbnvmCatalog;
    pFormatKeyCatalogsReq->pRamKeyCatalogCfg= (HOST_ADDR)sbRamCatalog;

    status = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);

    return status;
}

#endif/*#ifdef HSE_SPT_SMR_CR*/
/**
 * @brief         This function formats the SHE key catalogs.
 * @details
 */
hseSrvResponse_t SHEFormatKeyCatalogs(void)
{
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muIf][muChannelIdx];
    hseFormatKeyCatalogsSrv_t* pFormatKeyCatalogsReq = &pHseSrvDesc->hseSrv.formatKeyCatalogsReq;
    hseSrvResponse_t status;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    //Use the same default catalog configurations to re-format the NVM and RAM catalogss
    pHseSrvDesc->srvId = HSE_SRV_ID_FORMAT_KEY_CATALOGS;
    pFormatKeyCatalogsReq->pNvmKeyCatalogCfg = (HOST_ADDR) nvmSheCatalog;
    pFormatKeyCatalogsReq->pRamKeyCatalogCfg = (HOST_ADDR) ramSheCatalog;

    status = HSE_Send(muIf, muChannelIdx, gSyncTxOption, pHseSrvDesc);

    return status;
}

#endif

#ifdef __cplusplus
}
#endif

/** @} */

