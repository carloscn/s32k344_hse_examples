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
#include "hse_b_catalog_formatting.h"
#include "hse_keys_allocator.h"
#include "hse_host_import_key.h"
#include "hse_host_cipher.h"
#include "hse_host_mac.h"
#include "hse_common_types.h"
#include <string.h>
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define NVM_HMAC_KEY0           GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 2, 0)


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/



/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
//HMAC key 1 - initial and second version - Update NVM key example
const uint8_t hmacKeyInitial_demo[] =
{ 0x9a, 0x8c, 0xd4, 0x01, 0x8b, 0x1d, 0xe0, 0xaf, 0x06, 0xbb, 0xd7, 0x7a, 0xd3,
        0x28, 0x94, 0xb0, 0x36, 0xb2, 0x1e, 0xc7, 0x29, 0xbb, 0xd1, 0x09, 0x7b,
        0x34, 0xf2, 0x0e, 0x07, 0x0e, 0xbb, 0x29, 0xf9, 0x18, 0xda, 0xb1, 0x02,
        0xe0, 0x60, 0x4f, 0x19, 0x19, 0xc4, 0x58, 0x05, 0x80, 0xbf, 0x69, 0x2e,
        0xad
};
const uint32_t hmacKeyInitial_demoLength = ARRAY_SIZE(hmacKeyInitial_demo);
const uint8_t hmacKeyUpdated_demo[] =
{ 0xf8, 0x69, 0x02, 0xe5, 0xe5, 0xdb, 0x47, 0x8e, 0xc6, 0xe2, 0x78, 0x69, 0x27,
        0x28, 0xa8, 0x12, 0xc4, 0xcd, 0x87, 0x45, 0xf9, 0x0a, 0x7d, 0x9f, 0x79,
        0x15, 0xf5, 0xa9, 0x43, 0x45, 0xfc, 0x12, 0xd2, 0x77, 0x0a, 0x3c, 0x94,
        0xb0, 0x1f, 0xfb, 0x9e, 0x04, 0x12, 0x99, 0x9e, 0xb6, 0x26, 0x1d, 0x11,
        0xa0
};
static const uint8_t iv_demo[] =
{ 0xff, 0xbc, 0x51, 0x6a, 0x8f, 0xbe, 0x61, 0x52, 0xaa, 0x42, 0x8c, 0xdd, 0x80,
        0x0c, 0x06, 0x2d
};
const hseKeyGroupCfgEntry_t NVM_Catalog [] =
{
        /*  keyType                 numOfKeySlots   maxKeyBitLen  */                                                                      \
        /* CUST keys */                                                                                                                   \
        {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 12U, HSE_KEY128_BITS}, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */ \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 4U, HSE_KEY128_BITS},                                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 7U, HSE_KEY256_BITS},  /* HMAC key */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC, 2U, HSE_KEY512_BITS}, /* ECC keys */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PAIR, 3U, WRP_ECC_KEY_SIZE},                                           \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, WRP_KEY_TYPE_ECC_PUB_EXT, 1U, WRP_ECC_KEY_SIZE}, /* RSA keys */                         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR, 2U, HSE_KEY4096_BITS},                                           \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB, 1U, HSE_KEY4096_BITS},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS}, /* OEM keys */                         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES, 3U, HSE_KEY128_BITS},                                                  \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_AES, 3U, HSE_KEY256_BITS},   /* HMAC key */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_HMAC, 1U, HSE_KEY1024_BITS}, /* ECC keys */                                 \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PAIR, 1U, WRP_ECC_KEY_SIZE},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB_EXT, 1U, WRP_ECC_KEY_SIZE}, /* RSA keys */                          \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PAIR, 1U, HSE_KEY4096_BITS},                                            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB, 1U, HSE_KEY4096_BITS},                                             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_OEM, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY4096_BITS},                                         \
            {HSE_MU0_MASK, HSE_KEY_OWNER_OEM, WRP_KEY_TYPE_ECC_PUB, 1U, WRP_ECC_KEY_SIZE},                                                \
        {                                                                                                                                 \
                0U, 0U, 0U, 0U, 0U                                                                                                        \
        }

};
const hseKeyGroupCfgEntry_t RAM_Catalog [] =
{
        /*  keyType                   numOfKeySlots maxKeyBitLen*/                                        \
        /* Symetric key */                                                                                \
        {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 1U, HSE_KEY128_BITS}, /* KEY_RAM */        \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10U, HSE_KEY128_BITS},                 \
            {HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 10U, HSE_KEY256_BITS},     /* HMAC key */ \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_HMAC, 6U, HSE_KEY1024_BITS}, /* RSA key */  \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB, 2U, HSE_KEY2048_BITS},             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_RSA_PUB_EXT, 1U, HSE_KEY1024_BITS},         \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, WRP_KEY_TYPE_ECC_PAIR, 2U, WRP_ECC_KEY_SIZE},            \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, WRP_KEY_TYPE_ECC_PUB, 5U, WRP_ECC_KEY_SIZE},             \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 2U, HSE_KEY638_BITS},        \
            {HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 1U, HSE_KEY2048_BITS},       \
        {                                                                                                 \
                0U, 0U, 0U, 0U, 0U                                                                        \
        }
};


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/



/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/




int main(void) {
	/*Check Fw Install Status*/
	WaitForHSEFWInitToFinish();

	hseSrvResponse_t HseResponse;
	//Format the key catalog
	HseResponse = FormatKeyCatalogs(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	HseResponse = HKF_Init(NVM_Catalog, RAM_Catalog);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);


	/* Update NVM Key Example */

    /*Declare the HMAC key info that will update initial version*/
   hseKeyInfo_t keyInfo = {
       .keyType = HSE_KEY_TYPE_HMAC,                        //Will generate a HMAC key
       .keyFlags = (HSE_KF_USAGE_SIGN|HSE_KF_USAGE_VERIFY), //Usage flags for this key - Sign/Verify
       .keyBitLen = BYTES_TO_BITS(NUM_OF_ELEMS(hmacKeyUpdated_demo)), //Key size in bits
       .keyCounter = 1U                                     //The key counter must be incremented(greater than current counter of the key in NVM slot)*/
   };

   uint8_t tag[16U] = {0U};
   uint32_t tagLen = 16UL;

   /*
    * Declare a key container:
    * Authenticated buffer that MUST contain:
    *          - key data (i.e. pKey[0], pKey[1], pKey[2], depending on key type)
    *          - key info (which should have a higher key counter)
    *              - optional for public keys (RSA/ECC_PUB)
    * Optional, may contain any other information
    * For more details checkout `hse_srv_key_import_export.h` or dedicated chapter in HSE RM
    */
   uint8_t keyContainer[1056] = {0U};
   /*   uint16_t keyInfoOffset, keyDataOffset;*/
   uint16_t offset = 0U;

   /*
    * Fill the container with the necessary data
    * (Optional) - leave some space for any specific data
    */
   offset += 50U;

   //HMAC - Symmetric key - Must copy the key info
   //keyInfoOffset = offset;
   (void)memcpy(&keyContainer[offset], &keyInfo, sizeof(keyInfo));
   offset += sizeof(keyInfo);

   //(Optional) - leave some space for any specific data
   offset += 100U;

   //HMAC - Symmetric key - Must copy the key data in the container
   //keyDataOffset = offset;
   (void)memcpy(&keyContainer[offset], hmacKeyUpdated_demo, NUM_OF_ELEMS(hmacKeyUpdated_demo));

	/*
	 * (Optional) - add any other data
	 * Key container is ready - it must be authenticated
	 * Import in RAM a copy of the AES provision key to sign the
	 * container using HSE
	 * NOTE: Intended use case: The container comes already signed
	 * (/ is signed externally)
	 */
	HseResponse = ImportPlainSymKeyReq(HSE_DEMO_RAM_AES128_KEY1,
			HSE_KEY_TYPE_AES,
			HSE_KF_USAGE_SIGN, gAESProvisionKeyLength, gAES128ProvisionKey, 0U);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);

	//Sign the container - generate GMAC
	HseResponse = AesGmacGenerate(HSE_DEMO_RAM_AES128_KEY1,
			NUM_OF_ELEMS(iv_demo), iv_demo, NUM_OF_ELEMS(keyContainer),
			keyContainer, &tagLen, tag, HSE_SGT_OPTION_NONE);
	ASSERT(HSE_SRV_RSP_OK == HseResponse);
	for (;;) {

	}

    return 0;
}
