/* Copyright 2022 - 2023 NXP */
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
#include <string.h>

#define AESKEY_BYTE_LENGTH				(32U)

typedef struct{
	uint8_t isNVM;
	uint16_t keyBitLen;
	hseKeyFlags_t keyFlags;
	uint8_t *pKeyValue;
}AesKeyCfg;

const hseKeyGroupCfgEntry_t NVM_Catalog [] =
{
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10, 256},
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10, 256},
	{0, 0, 0, 0, 0}
};


const hseKeyGroupCfgEntry_t RAM_Catalog [] =
{
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10, 256},
	{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10, 256},
	{0, 0, 0, 0, 0}
};

uint32_t PlaintextLength = 16;

uint32_t Cmac_TagLength = 16;

const uint8_t Plaintext[16] =
{ 		0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
		0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};

uint8_t Cmac_Tag[16];

AesKeyCfg GeneratedAesKey = {
	.isNVM = 1,
	.keyBitLen = 256,
	.keyFlags = HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DECRYPT | HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY,
	.pKeyValue = NULL
};

int main(void) {
	hseSrvResponse_t HseResponse;
	hseKeyHandle_t GeneratedKeyHandle;

	 /*Check Fw Install Status*/
	WaitForHSEFWInitToFinish();

	/* Format Key Catalogs with the application's configuration */
	HseResponse = FormatKeyCatalogs(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Initialize HKF for Key management */
	HseResponse = HKF_Init(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Obtained the Generated Key handler for later use */
	GeneratedKeyHandle = (hseKeyHandle_t)(GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 0));

	/* Generate AES key for CMAC Generation and Verification */
	HseResponse = GenerateAesKey(&GeneratedKeyHandle, (bool_t)GeneratedAesKey.isNVM, GeneratedAesKey.keyBitLen, GeneratedAesKey.keyFlags, HSE_KU_AES_BLOCK_MODE_ECB);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Generate CMAC Tag over Plain text */
	HseResponse = AesCmacGenerate(GeneratedKeyHandle, PlaintextLength, &Plaintext[0], &Cmac_TagLength, &Cmac_Tag[0], 0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	/* Verify CMAC Tag provided against a generated tag over Plain text */
	HseResponse = AesCmacVerify(GeneratedKeyHandle, PlaintextLength, &Plaintext[0], &Cmac_TagLength, &Cmac_Tag[0], 0);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

    for (;;) {

    }

    return 0;
}
