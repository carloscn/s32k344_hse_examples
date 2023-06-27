/* Copyright 2022 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/
/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K344.h"
#include "hse_host.h"
#include "hse_interface.h"
#include "hse_demo_app_services.h"
#include "hse_host_format_key_catalogs.h"
#include "hse_keys_allocator.h"
#include "hse_host_import_key.h"
#include "hse_host_cipher.h"
#include "hse_host_mac.h"
#include "hse_host_boot.h"
#include <string.h>
#include "pflash.h"
#include "flash.h"

#define AESKEY_BYTE_LENGTH	(16U)

#define APPBL_ADDRESS 		(0x005040C0)
#define APPBL_LENGTH 		(0x1000)
#define APP_HEADER_LENGTH 	0x40U

typedef struct{
	uint8_t isNVM;
	uint32_t keyBitLen;
	hseKeyFlags_t keyFlags;
	uint8_t *pKeyValue;
}AesKeyCfg;

const hseKeyGroupCfgEntry_t NVM_Catalog [] =
{
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10, 256},
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10, 128},
	{0, 0, 0, 0, 0}
};


const hseKeyGroupCfgEntry_t RAM_Catalog [] =
{
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10, 256},
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10, 256},
	{0, 0, 0, 0, 0}
};

uint8_t LoadedAesKeyValue[AESKEY_BYTE_LENGTH] =
{
	0x42, 0x27, 0x6E, 0xEF, 0x73, 0xFB, 0x1C, 0x8D,
	0x1A, 0x6C, 0xCD, 0xC9, 0x69, 0xB0, 0x1E, 0xE6,
};

AesKeyCfg MacGenAesKey = {
	.isNVM = 1,
	.keyBitLen = 128,
	.keyFlags = HSE_KF_USAGE_SIGN,
	.pKeyValue = &LoadedAesKeyValue[0]
};

AesKeyCfg MacVerAesKey = {
	.isNVM = 1,
	.keyBitLen = 128,
	.keyFlags = HSE_KF_USAGE_VERIFY,
	.pKeyValue = &LoadedAesKeyValue[0]
};

uint8_t Cmac_Tag[16];
uint32_t Cmac_TagLength = 16;
uint32_t CmacTagFlashAddress;
uint8_t * pCmacTag;

hseSmrEntry_t SMR_0 = {
	.pSmrSrc = (uint32_t)APPBL_ADDRESS,
	.smrSize = (uint32_t)APPBL_LENGTH,
	.configFlags = HSE_SMR_CFG_FLAG_INSTALL_AUTH,
	.pSmrDest = 0,
	.checkPeriod = 0,
};

hseCrEntry_t CrEntry = {
	.coreId = 0,
	.preBootSmrMap = (1<<0),  						/* (1 << 0) SMR 0 */
	.pPassReset = 0x00504100,  						/* The start address is the address of the Application + size of the application header (0x40) */
	.altPreBootSmrMap = 0, 						/* There will be no alternative verification if the defined preboot verification fails */
	.pAltReset = 0,		  						/* There will be no alternative starting address */
	.postBootSmrMap = 0,	  						/* No post boot verification required */
	.startOption = HSE_CR_AUTO_START,				/* The core is to be set out of reset automatically after the verification */
	.crSanction = HSE_CR_SANCTION_DIS_INDIV_KEYS		/* Sanction to apply if the verification fails */
};

int main(void) {
	hseSrvResponse_t HseResponse;
	hseKeyHandle_t MacGenKeyHandle;
	hseKeyHandle_t MacVerKeyHandle;
	hseAppCore_t app_core = HSE_APP_CORE0;
	tFLASH_STATUS status;
	hseAttrSmrCoreStatus_t smrCoreStatus;


	 /*Check Fw Install Status*/
	WaitForHSEFWInitToFinish();

	HseResponse = FormatKeyCatalogs(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	HseResponse = HKF_Init(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	MacGenKeyHandle = (hseKeyHandle_t)(GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 0));
	MacVerKeyHandle = (hseKeyHandle_t)(GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 1));

	/* Load key used to verify the generated TAG */
	HseResponse = ImportPlainSymKeyReq(MacGenKeyHandle,
									   HSE_KEY_TYPE_AES,
									   MacGenAesKey.keyFlags,
									   (MacGenAesKey.keyBitLen>>3),
									   MacGenAesKey.pKeyValue,
									   0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Load key used to verify the generated TAG */
	HseResponse = ImportPlainSymKeyReq(MacVerKeyHandle,
									   HSE_KEY_TYPE_AES,
									   MacVerAesKey.keyFlags,
									   (MacGenAesKey.keyBitLen>>3),
									   MacVerAesKey.pKeyValue,
									   0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	CmacTagFlashAddress = (uint32_t)(APPBL_ADDRESS + APP_HEADER_LENGTH + APPBL_LENGTH);

	/* SMR Configuration */
	SMR_0.authKeyHandle = MacVerKeyHandle;
	SMR_0.authScheme.macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
	SMR_0.authScheme.macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;
	SMR_0.pInstAuthTag[0] = CmacTagFlashAddress;
	SMR_0.pInstAuthTag[1] = (uint32_t)NULL;

	/* TAG generation and verification */
	HseResponse = AesCmacGenerate(MacGenKeyHandle,
								  SMR_0.smrSize,
								  (const uint8_t *)SMR_0.pSmrSrc,
								  &Cmac_TagLength,
								  &Cmac_Tag[0],
								  0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	HseResponse = AesCmacVerify(MacVerKeyHandle,
								SMR_0.smrSize,
								(const uint8_t *)SMR_0.pSmrSrc,
								&Cmac_TagLength,
								&Cmac_Tag[0],
								0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	pCmacTag = (uint8_t *)CmacTagFlashAddress;

	/* Write TAG in the expected location at the end of the image */
	PFLASH_Unlock(PFLASH_BL1, PFLASH_SS0, PFLASH_S0);
	status = FLASH_Write (pCmacTag,
						  Cmac_Tag,
						  sizeof(Cmac_Tag));
	(void)status;

	/* Install Secure Memory Region */
	HseResponse = HSE_InstallSmrEntry(0,
									  &SMR_0,
									  (const uint8_t *)SMR_0.pSmrSrc,
									  SMR_0.smrSize,
									  pCmacTag,
									  NULL,
									  Cmac_TagLength,
									  0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Install CR Entry */
	HseResponse = HSE_InstallCoreResetEntry(app_core, &CrEntry);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Get status of the Secure Memory Region and Core Reset Entry installation */
	HseResponse = Get_Attr(
	            HSE_SMR_CORE_BOOT_STATUS_ATTR_ID,
	            sizeof(hseAttrSmrCoreStatus_t),
	            (void *)(&smrCoreStatus));
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

    for (;;) {

    }

    return 0;
}


