/**
*   @file    hse_srv_bootdatasig.h
*
*   @brief   HSE Boot images signature generate/verify
*   @details This file contains the service used to Generate Signature for different boot images(e.g. for HSE-H/M, IVT/DCD/ST/AppBSB image; for HSE-B, IVT/XRD/AppBSB image).
*
*   @addtogroup hse_srv_secureboot HSE Boot Images Signature Generate/Verify
*   @ingroup class_admin_services
*   @{
*/
/*==================================================================================================
*
*   Copyright 2019 - 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef HSE_SRV_BOOT_DATA_SIG_H
#define HSE_SRV_BOOT_DATA_SIG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "hse_common_types.h"

#define HSE_START_PRAGMA_PACK
#include "hse_compiler_abs.h"

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

/** @brief The Application Image header that keeps information about the Basic Secure Booting (BSB)
 *        (e.g. header information, source and destination addresses, app code length, tag location). */
#ifdef HSE_SPT_BSB
typedef struct
{
    uint8_t                 hdrTag;                  /**< @brief App header tag shall be 0xD5. */
    uint8_t                 reserved1[2];            /**< @brief Reserved field has no impact. Set to all zeroes.*/
    uint8_t                 hdrVersion;              /**< @brief App header version shall be 0x60. */
    uint32_t                pAppDestAddres;          /**< @brief The destination address where the application is copied.
                                                                 @note For HSE-B, it is NULL (the code is executed from flash) */
    uint32_t                pAppStartEntry;          /**< @brief The address of the first instruction to be executed.*/
    uint32_t                codeLength;              /**< @brief Length of application image. */
    hseAppCore_t            coreId;                  /**< @brief The application core ID that is un-gated.
                                                                 @note Valid for HSE-B devices only. For HSE-H/M core id defined in IVT*/
    uint8_t                 reserved2[47];           /**< @brief Reserved field has no impact. Set to all zeroes. */
} hseAppHeader_t;
#endif /* HSE_SPT_BSB */

/** @brief HSE Boot Data Image GMAC generation.
 *  @details This service is used to generate the GMAC tag for different Boot Data Images. <br>
 *             For HSE-H and HSE-M, the following Boot Data Images can be signed:
 *           - IVT, DCD, SELF-TEST and Application Image (also referred below as App BSB Image).
 *           - LPPDR4 QSPI Flash image for S32Z/E(HSE-H) devices.
 *             The computed GMAC tag must be placed/copied at the end of the image (for images format, refer to HSE FW Reference Manual). <br><br>
 *             For HSE-B, the following Boot Data Images can be signed: 
 *           - IVT and Application Image (also referred below as App BSB Image). 
 *             The computed random IV and GMAC tag must be placed/copied at the end of the image.
 *             The 12 bytes of random IV and 16 bytes of GMAC are generated by HSE Firmware.
 *             The random IV is also part of GMAC calculation (for images format, refer to HSE FW Reference Manual). <br>
 *      @note
 *           - SuperUser rights (for NVM Configuration) are needed to perform this service.
 */
#ifdef HSE_SPT_BOOTDATASIGN
typedef struct
{
    /** @brief  INPUT:  The address of the Boot Data Image. The Boot Data Image can be:
     *                  - For HSE-H/M, IVT or DCD or SELF-TEST or App BSB or LPDDR4(for S32Z/E devices)  image; the address may be a QSPI-FLASH (external flash) or system RAM address. <br>
     *                  - For HSE-B, the IVT or App BSB image; the address can be a flash or 
     *                    system RAM address. <br>
     *                  The length of the pInImage is not provided. HSE uses the information 
     *                  from the provided pInImage to compute the image length. <br>
     *                  The length of each image is computed in the below manner:
     *                  1. For HSE-H/M:
     *                      - the IVT Image length must be 256 bytes (IVT Image header (4bytes) + IVT Image data (236 bytes) + GMAC(16 bytes))
     *                      - DCD/SELF-TEST Image length must be maximum 8192 bytes (DCD/ST Image header(4 bytes) + maximum DCD/ST Image data (8188 byte))
     *                      - For S32Z/E devices (HSE_H), the maximum length of the LPDDR4 QSPI Flash must be smaller or equal to (7MB + 336bytes)(Image header(336 bytes) + code length(maximum 7MB))
     *                      - pInImage can point to the App BSB Image that contains the App header and App code:
     *                      - App image header shall be specified as hseAppHeader_t. It has a fixed size of 64 bytes.
     *                      - App image code shall follow the App image header and has a variable length specified by "codelength" parameter.
     *                      - The computed GMAC tag for App BSB Image includes both App header, App code.<br>
     *                  2. For HSE-B:
     *                      - The IVT image length must be 256 bytes (IVT Image header (4bytes) + IVT Image data (224 bytes) + IV (12 bytes) + GMAC(16 bytes)). 
     *                        The computed GMAC tag is over IVT Image header and data (228 bytes) and IV (12 bytes).
     *                      - pInImage can point to the App BSB Image that contains the App header and App code:
     *                      - App image header shall be specified as hseAppHeader_t. It has a fixed size of 64 bytes.
     *                      - App image code shall follow the App image header and has a variable length specified by "codelength" parameter.
     *                      - The computed GMAC tag for App BSB Image includes App header, App code and IV (12 bytes)
     **/
    HOST_ADDR              pInImage;
    /** @brief  INPUT:  The length in bytes of the IV + GMAC tag.
     *                  This length must be equal to or greater than
     *                  - for HSE-H and HSE-M, 16 bytes <br>
     *                  - for HSE-B, 28 bytes*/
    uint32_t               inTagLength;
    /** @brief  OUTPUT: For HSE-H and HSE-M: The address where GMAC tag is generated.<br>
     *                  For HSE-B: The address where the random IV (12 bytes), followed by 
     *                  the GMAC tag (16 bytes) are generated. It must be a system RAM address.<br>
                       @note For any boot data, the computed GMAC tag shall be copied at the end of boot data image.*/
    HOST_ADDR              pOutTagAddr;
}hseBootDataImageSignSrv_t;

/** @brief HSE Boot Data Image GMAC verification.
 *  @details This service can be used to verify the GMAC tag generated using the hseBootDataImageSignSrv_t service.
 */
typedef struct
{
    /** @brief   INPUT: The address of the HSE Boot Data Image (for more details about the HSE Boot Data Images refer to pInImage parameter from hseBootDataImageSignSrv_t service).
     *                  @note
     *                  - For any boot data, the GMAC tag of the Boot Data Image must be placed at the end of the image.
     *                  - HSE uses the Boot Data Image information (provided by #pInImage) to compute the length of the image and to verify the authentication TAG. */
    HOST_ADDR            pInImage;
}hseBootDataImageVerifySrv_t;
#endif /* HSE_SPT_BOOTDATASIGN */

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define HSE_STOP_PRAGMA_PACK
#include "hse_compiler_abs.h"

#ifdef __cplusplus
}
#endif

#endif /* HSE_SRV_BOOT_DATA_SIG_H */

/** @} */
