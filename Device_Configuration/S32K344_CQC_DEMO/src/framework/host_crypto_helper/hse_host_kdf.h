
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
#ifndef _HSE_HOST_KDF_H_
#define _HSE_HOST_KDF_H_

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
#ifdef HSE_SPT_KDF_IKEV2
hseSrvResponse_t HSEKeyDeriveIKEv2Req
(
    hseKdfIKEV2Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KEY_DERIVE
hseSrvResponse_t HSEKeyDeriveExtractKeyReq
(
    hseKeyHandle_t      keyHandle,
    uint16_t            startOffset,
    hseKeyHandle_t      targetKeyHandle,
    hseKeyInfo_t        keyInfo
);
#endif
#ifdef HSE_SPT_KDF_ISO18033_KDF1
hseSrvResponse_t HSEKdfISO_KDF1Req
(
    hseKdfISO18033_KDF1Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_ISO18033_KDF2
hseSrvResponse_t HSEKdfISO_KDF2Req
(
    hseKdfISO18033_KDF2Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_NXP_GENERIC
hseSrvResponse_t HSEKdfNXP_KDFReq
(
    hseKdfNxpGenericScheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_SP800_56C_ONESTEP
hseSrvResponse_t HSEKdfSP800_56COneStepReq
(
    hseKdfSP800_56COneStepScheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_ANS_X963
hseSrvResponse_t HSEKdfANS_X963Req
(
    hseKdfANSX963Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_SP800_56C_TWOSTEP
hseSrvResponse_t HSEKdfSP800_56C_TwoStepReq
(
    hseKdfSP800_56CTwoStepScheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_SP800_108
hseSrvResponse_t HSEKdfSP800_108Req
(
    hseKdfSP800_108Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KEY_DERIVE
hseSrvResponse_t HSEKdfExtract_StepReq
(
    hseKdfExtractStepScheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_PBKDF2
hseSrvResponse_t HSE_PBKDF2Req
(
    hsePBKDF2Scheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_KDF_TLS12_PRF
hseSrvResponse_t HSE_TLS12_PRFReq
(
    hseKdfTLS12PrfScheme_t *pKdfScheme
);
#endif
#ifdef HSE_SPT_HKDF
hseSrvResponse_t HSE_HKDFReq
(
    hseHKDF_ExpandScheme_t *pKdfScheme
);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _HSE_HOST_KDF_H_ */

/** @} */
