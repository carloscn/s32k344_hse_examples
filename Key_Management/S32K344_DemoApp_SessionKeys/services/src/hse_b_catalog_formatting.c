
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

#include "hse_host_format_key_catalogs.h"
#include "hse_b_catalog_formatting.h"
#include "global_defs.h"

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
  const hseKeyGroupCfgEntry_t nvmKeyCatalog[] = {HSE_DEMO_NVM_KEY_CATALOG_CFG};
  const hseKeyGroupCfgEntry_t ramKeyCatalog[] = {HSE_DEMO_RAM_KEY_CATALOG_CFG};
#endif

  /**
   * @brief         Wrapper for FormatKeyCatalogs.
   * @details
   */
  hseSrvResponse_t FormatKeyCatalogs_(void)
  {
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
    hseSrvResponse_t status;
    status = FormatKeyCatalogs(nvmKeyCatalog, ramKeyCatalog);
    status = ParseKeyCatalogs();
    ASSERT(HSE_SRV_RSP_OK == status);
    return status;
#else
  return HSE_SRV_RSP_NOT_SUPPORTED;
#endif
  }

  /**
   * @brief         Wrapper for KeyCatalogParsing
   * @details
   */

  hseSrvResponse_t ParseKeyCatalogs(void)
  {
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
    hseSrvResponse_t status;
    status = HKF_Init(nvmKeyCatalog, ramKeyCatalog);
    return status;
#else
  return HSE_SRV_RSP_NOT_SUPPORTED;
#endif
  }

#ifdef __cplusplus
}
#endif

/** @} */
