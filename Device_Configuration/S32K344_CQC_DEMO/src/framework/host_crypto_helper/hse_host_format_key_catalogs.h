
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
#ifndef _HSE_HOST_FORMAT_KEY_CATALOGS_H_
#define _HSE_HOST_FORMAT_KEY_CATALOGS_H_

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "hse_interface.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/* Formats the key Catalogs with default configuration */
hseSrvResponse_t FormatKeyCatalogs(const hseKeyGroupCfgEntry_t* nvmCatalog, const hseKeyGroupCfgEntry_t* ramCatalog);
hseSrvResponse_t FormatKeyCatalogs_W(void);
#ifdef HSE_SPT_SMR_CR
hseSrvResponse_t SBFormatKeyCatalogs(void);
#endif/*#ifdef HSE_SPT_SMR_CR*/
hseSrvResponse_t SHEFormatKeyCatalogs(void);

#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_FORMAT_KEY_CATALOGS_H_ */

/** @} */

