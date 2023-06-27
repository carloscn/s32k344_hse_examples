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
#ifndef _HSE_HOST_ATTRS_H_
#define _HSE_HOST_ATTRS_H_

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

/*******************************************************************************
 * Function:    SetAttr
 * Description: Sets the specified attribute
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t SetAttr
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr
);

/*******************************************************************************
 * Function:    GetAttr
 * Description: Gets the specified attribute
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t GetAttr
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr
);

/*******************************************************************************
 * Function:    GetSetAttrByMu
 * Description: Gets/Sets the specified attribute on specified MU interface and channel
 * Returns:     Service response code of the operation.
 ******************************************************************************/
hseSrvResponse_t GetSetAttrByMu
(
    hseAttrId_t attrId,
    uint32_t attrLen,
    void *pAttr,
    bool_t bSet,
    uint8_t muInstance,
    uint8_t muChannel
);
#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_ATTRS_H_ */

/** @} */
