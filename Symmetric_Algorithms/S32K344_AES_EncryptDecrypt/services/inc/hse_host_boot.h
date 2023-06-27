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

#ifndef HSE_HOST_BOOT_H
#define HSE_HOST_BOOT_H

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
#define NON_SECURE_IVT_BACKUPADDR_OFFSET 0x20000UL
#define SECURE_IVT_BACKUPADDR_OFFSET 0x22000UL
    /*==================================================================================================
    *                                             ENUMS
    ==================================================================================================*/

    /*==================================================================================================
                                     STRUCTURES AND OTHER TYPEDEFS
    ==================================================================================================*/
    /** @brief The Application Image header that keeps information about the Basic Secure Booting (BSB)
     *        (e.g. header information, source and destination addresses, app code length, tag location). */

    typedef struct
    {
        uint8_t hdrTag;          /**< @brief App header tag shall be 0xD5. */
        uint8_t reserved1[2];    /**< @brief Reserved field has no impact. Set to all zeroes.*/
        uint8_t hdrVersion;      /**< @brief App header version shall be 0x60. */
        uint32_t pAppDestAddres; /**< @brief The destination address where the application is copied.
                                             @note For HSE-B, it is NULL (the code is executed from flash) */
        uint32_t pAppStartEntry; /**< @brief The address of the first instruction to be executed.*/
        uint32_t codeLength;     /**< @brief Length of application image. */
        hseAppCore_t coreId;     /**< @brief The application core ID that is un-gated.
                                             @note Valid for HSE-B devices only. For HSE-H/M core id defined in IVT*/
        uint8_t reserved2[47];   /**< @brief Reserved field has no impact. Set to all zeroes. */

    } hseApplHeader_t;
    /*==================================================================================================
                                     GLOBAL VARIABLE DECLARATIONS
    ==================================================================================================*/

    /*==================================================================================================
                                         FUNCTION PROTOTYPES
    ==================================================================================================*/

    /*******************************************************************************
     * Description: Installs a SMR entry used for Advanced Secure Boot.
     ******************************************************************************/
    hseSrvResponse_t HSE_InstallSmrEntry(
        const uint8_t entryIndex,
        const hseSmrEntry_t *pSmrEntry,
        const uint8_t *pData,
        const uint32_t dataLen,
        const uint8_t *pSign0,
        const uint8_t *pSign1,
        const uint32_t SignLen0,
        const uint32_t SignLen1);

    hseSrvResponse_t smrVerifyTest(uint32_t smrentry);
    /*******************************************************************************
     * Description: Installs a core reset entry used for Advanced Secure Boot.
     ******************************************************************************/
    hseSrvResponse_t HSE_InstallCoreResetEntry(
        const uint8_t entryIndex,
        const hseCrEntry_t *pCrEntry);

    /*******************************************************************************
     * Description: Signs IVT/DCD/SelfTest images or Application image for Basic Secure Boot (AppBSB)
     ******************************************************************************/
    /*hseSrvResponse_t HSE_SignBootImage
    (
        const uint8_t *pInImage,
        const uint32_t inTagLength,
        uint8_t *pOutTagAddr
    );*/

    /*******************************************************************************
     * Description: Verifies the MAC, generated over IVT/DCD/SelfTest/AppBSB images via hseBootDataImageSign Service
     ******************************************************************************/
    hseSrvResponse_t HSE_VerifyBootImage(
        const uint8_t *pInImage);

    hseSrvResponse_t generateIvtSign(void);

#ifdef __cplusplus
}
#endif

#endif /* HSE_HOST_BOOT_H */

/** @} */
