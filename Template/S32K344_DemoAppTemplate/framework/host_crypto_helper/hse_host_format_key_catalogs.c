
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
#include "hse_keys_allocator.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/
#if (HSE_FWTYPE == 8U) && !defined(HSE_SPT_FORMAT_KEY_CATALOGS)
extern const hseKeyGroupCfgEntry_t nvmCatalog[] = {HSE_NVM_KEY_CATALOG_CFG};
#endif /* (HSE_FWTYPE == 8U) */

#ifdef HSE_SPT_FORMAT_KEY_CATALOGS

extern const hseKeyGroupCfgEntry_t nvmCatalog[] = {HSE_NVM_KEY_CATALOG_CFG};
extern const hseKeyGroupCfgEntry_t ramCatalog[] = {HSE_RAM_KEY_CATALOG_CFG};
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

    if(HSE_SRV_RSP_OK == status)
    {
       status = HKF_Init(sbnvmCatalog, sbRamCatalog);
    }

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

