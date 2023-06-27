/**
 *   @file    hse_global_variables.c
 *
 *   @brief   Contains definitions of global variables.
 *   @details Contains definitions of global variables.
 *
 *   @addtogroup security_installer
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
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "hse_demo_app_services.h"
#include "hse_global_variables.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 * ===============================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 * ===============================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 * ===============================================================================================*/

/*==================================================================================================
 *                                      LOCAL VARIABLES
 * ===============================================================================================*/

/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 * ===============================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 * ===============================================================================================*/
#ifdef GHS
#pragma ghs section bss = ".ivt"
    ivt_t IVT;
#pragma ghs section bss = default
#else
ivt_t IVT __attribute__((section("ivt")));
#endif

#ifdef GHS
#pragma ghs section bss = ".fwversion"
    hseAttrFwVersion_t fwversion[2];
#pragma ghs section bss = default
#else
hseAttrFwVersion_t fwversion[2] __attribute__((section(".fwversion")));
#endif

#ifdef GHS
#pragma ghs section bss = ".teststatus"
    testStatus_t testStatus;
#pragma ghs section bss = default
#else
testStatus_t testStatus __attribute__((section(".teststatus")));
#endif

#ifdef GHS
#pragma ghs section bss = ".testexecuted"
    int16_t gRunExampleTest;
#pragma ghs section bss = default
#else
int16_t gRunExampleTest __attribute__((section(".testexecuted")));
#endif

#ifdef GHS
#pragma ghs section bss = ".testcompleted"
    char allTestExecuted;
#pragma ghs section bss = default
#else
char allTestExecuted __attribute__((section(".testcompleted")));
#endif

    /*
        The application debug key/password (ADK/P) to be programmed - 128-bits
        Used by `HSE_ProgramAdkp` function to program ADK/P in fuses
    */

#ifdef GHS
#pragma ghs section bss = "._adkp_key"
    volatile uint8_t applicationDebugKeyPassword[16U];
#pragma ghs section bss = default
#else
volatile uint8_t applicationDebugKeyPassword[16U] __attribute__((section("_adkp_key")));
#endif

    /*Separate file for keys*/
    const uint8_t gAES128ProvisionKey[] = {0x6f, 0xe1, 0x2c, 0x66, 0x07, 0x19, 0x1f, 0x4f, 0x08, 0x00, 0x81, 0x21, 0x40, 0x25, 0x8a, 0x98};
    const uint16_t gAESProvisionKeyLength = ARRAY_SIZE(gAES128ProvisionKey);
    hseKeyInfo_t gAES128ProvisionKeyInfo =
        {
            .keyFlags = HSE_KF_USAGE_KEY_PROVISION | HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY | HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DECRYPT,
            .keyBitLen = 8U * sizeof(gAES128ProvisionKey) / sizeof(gAES128ProvisionKey[0]),
            .keyType = HSE_KEY_TYPE_AES};

    uint8_t gAES128AuthorizationKey[16] = {0xc4, 0x91, 0x29, 0x50, 0xf2, 0x8c, 0x6f, 0x42, 0xde, 0x7f, 0x9b, 0x9f, 0x93, 0xee, 0xb9, 0xac};

    hseKeyInfo_t gAES128AuthorizationKeyInfo =
        {
            .keyFlags = HSE_KF_USAGE_AUTHORIZATION | HSE_KF_USAGE_VERIFY,
            .keyBitLen = 8U * sizeof(gAES128AuthorizationKey) / sizeof(gAES128AuthorizationKey[0]),
            .keyType = HSE_KEY_TYPE_AES};
    /* ECC NIST-P256 Key Pair */
    uint8_t gEccP256BootKeyPub[] =
        {
            0xd6, 0x60, 0x62, 0x71, 0x13, 0x1e, 0x7e, 0x7e, 0x61, 0x7a, 0x81, 0xaa, 0x11, 0xf0, 0x9e, 0x7e, 0xd5, 0x63, 0x11, 0x82, 0x88, 0x23, 0x36, 0x7a, 0x86, 0x9b, 0x45, 0x40, 0x40, 0xb3, 0xf9, 0x05,
            0xcf, 0x48, 0x97, 0x76, 0x61, 0x31, 0xaa, 0x8b, 0x7f, 0x80, 0x45, 0x3a, 0x15, 0xbf, 0x90, 0xf7, 0x51, 0x78, 0x78, 0x57, 0x9d, 0x5a, 0x4f, 0x97, 0x3a, 0xea, 0x5b, 0xb1, 0x15, 0x42, 0xe0, 0x7f};
    uint8_t gEccP256BootKeyPriv[] =
        {
            0x00, 0xd0, 0x07, 0xe1, 0xb9, 0xaf, 0xcc, 0x31, 0x2e, 0xec, 0x9c, 0xec, 0xff, 0xa0, 0x28, 0x07, 0x52, 0xbb, 0xd1, 0x95, 0x31, 0x82, 0xed, 0xef, 0x12, 0xf3, 0xfc, 0x36, 0x6e, 0x8f, 0x43, 0x56};

    uint8_t gAES128BootKey[16] = {0x6a, 0x73, 0xfe, 0x7b, 0xe2, 0x0a, 0x54, 0xaf, 0xe0, 0xad, 0xac, 0x7e, 0xa8, 0x61, 0xad, 0x58};
    hseKeyInfo_t gAES128BootKeyInfo =
        {
            .keyFlags = HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY,
            .keyBitLen = 8U * sizeof(gAES128BootKey) / sizeof(gAES128BootKey[0]),
            .keyType = HSE_KEY_TYPE_AES};

    /*==================================================================================================
     *                                   LOCAL FUNCTION PROTOTYPES
     * ===============================================================================================*/

    /*==================================================================================================
     *                                       LOCAL FUNCTIONS
     * ===============================================================================================*/

    /*==================================================================================================
     *                                       GLOBAL FUNCTIONS
     * ===============================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
