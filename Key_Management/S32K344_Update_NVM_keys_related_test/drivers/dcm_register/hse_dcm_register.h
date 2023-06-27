/*============================================================================*/

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
/*============================================================================*/

/*=============================================================================
                                   Description
==============================================================================*/
/**
 *   @file    dcm_register.h
 *
 *   @brief   This file contains dcm register.
 */

#ifndef HSE_DCM_REGISTER_H
#define HSE_DCM_REGISTER_H
/*=============================================================================
 *                                 INCLUDE FILES
 =============================================================================*/
#include "std_typedefs.h"
/*=============================================================================
                                      MACROS
==============================================================================*/
#define DCM_STATUS_REGISTER_BASE (0x402AC000U)
#define DCM_GPR_POR_DCMRWP6_ADDRESS (0x400A4414U)

#define DCM_FORCE_TEMP_LC_NEXT_ONE (0x1U)
#define DCM_FORCE_TEMP_LC_NEXT_TWO (0x2U)
/*=============================================================================
 *                        TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 =============================================================================*/
typedef union {
    vuint32_t Word;
    struct
    {
        vuint32_t dcmdone : 1;
        vuint32_t dcmerr : 1;
        vuint32_t reserved1 : 2;
        vuint32_t dcmlcst : 1;
        vuint32_t dcmtds : 1;
        vuint32_t dcmtsds : 1;
        vuint32_t dcmmrks : 1;
        vuint32_t dcmuts : 1;
        vuint32_t dcmotas : 1;
        vuint32_t reserved2 : 6;
        vuint32_t dcmotaa : 1;
        vuint32_t dcmotar : 1;
    } Bit;
} DCMSTAT_T;

typedef union {
    vuint32_t Word;
    struct
    {
        vuint32_t dcmclc : 3;
        vuint32_t dcmlcfn : 1;
        vuint32_t dcmrlc : 3;
        vuint32_t reserved1 : 1;
        vuint32_t dcmflc : 2;
    } Bit;
} DCMLCC_T;

typedef struct
{
    DCMSTAT_T dcmstat; /* 0x00 */
    DCMLCC_T dcmlcc;   /* 0x04 */
} DCM_REGISTER_T;

typedef union {
    vuint32_t Word;
    struct
    {
        vuint32_t cm330 : 1;
        vuint32_t cm331 : 1;
        vuint32_t cm7 : 1;
    } Bit;
} DCMRWP6_REGISTER_T;

typedef uint32_t DCM_LIFECYCLE_T;
#define DCM_LIFECYCLE_FA (DCM_LIFECYCLE_T)(0x00000000U)
#define DCM_LIFECYCLE_RESERVED_1 (DCM_LIFECYCLE_T)(0x00000001U)
#define DCM_LIFECYCLE_OEM_PROD (DCM_LIFECYCLE_T)(0x00000002U)
#define DCM_LIFECYCLE_CUST_DEL (DCM_LIFECYCLE_T)(0x00000003U)
#define DCM_LIFECYCLE_RESERVED_2 (DCM_LIFECYCLE_T)(0x00000004U)
#define DCM_LIFECYCLE_RESERVED_3 (DCM_LIFECYCLE_T)(0x00000005U)
#define DCM_LIFECYCLE_PRODUCTION (DCM_LIFECYCLE_T)(0x00000006U)
#define DCM_LIFECYCLE_INFIELD (DCM_LIFECYCLE_T)(0x00000007U)

typedef uint32_t DCM_TEMP_FORCE_LC_T;
#define DCM_TEMP_FORCE_LC_ONE (DCM_TEMP_FORCE_LC_T)(0x00000000U)
#define DCM_TEMP_FORCE_LC_TWO_CUST_DEL (DCM_TEMP_FORCE_LC_T)(0x00000002U)

typedef uint32_t DCMRWP6_BIT_POSITION_T;
#define DCMRWP6_BIT_CM330 ((DCMRWP6_BIT_POSITION_T)(0x00000000U))
#define DCMRWP6_BIT_CM331 ((DCMRWP6_BIT_POSITION_T)(0x00000001U))
#define DCMRWP6_BIT_CM7 ((DCMRWP6_BIT_POSITION_T)(0x00000002U))

typedef uint32_t DCM_BIT_STATUS_SCANNING_T;
#define DCM_STATUS_SCAN_RUNNING ((DCM_BIT_STATUS_SCANNING_T)(0x00000000U))
#define DCM_STATUS_SCAN_COMPLETED ((DCM_BIT_STATUS_SCANNING_T)(0x00000001U))

typedef uint32_t DCM_BIT_STATUS_OTA_T;
#define DCM_STATUS_OTA_NOT_ACTIVE ((DCM_BIT_STATUS_OTA_T)(0x00000000U))
#define DCM_STATUS_OTA_ACTIVE ((DCM_BIT_STATUS_OTA_T)(0x00000001U))

typedef uint32_t DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T;
#define DCM_BIT_LOW_ADDRESS_OTA_ACTIVE ((DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T)(0xA5A5A5A5U))
#define DCM_BIT_HIGH_ADDRESS_OTA_ACTIVE ((DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T)(0x5A5A5A5AU))

/*=============================================================================
                                     CONSTANTS
==============================================================================*/

/*=============================================================================
 *                               GLOBAL VARIABLES
 =============================================================================*/

/*=============================================================================
                                FUNCTION PROTOTYPES
==============================================================================*/
DCM_LIFECYCLE_T Dcm_GetCurrentLifecycle(void);
DCM_BIT_STATUS_SCANNING_T Dcm_StatusScanning(void);
DCM_BIT_STATUS_OTA_T Dcm_StatusIsOTAEnabled(void);
DCM_BIT_ACTIVE_ADDRESS_OTA_REGION_T Dcm_ActiveAddressOTARegion(void);
uint32_t Dcm_GetBitStatusDcmrwp6(DCMRWP6_BIT_POSITION_T position);

#endif
