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

/***************************************************
 * S32K344_Hse_Ecc_Example
 * main.c for Core M7_0
 ***************************************************
 * Author: GPIS Applications
 * Date: May 5th, 2023
 * Version 1.0
 ***************************************************
 * This project includes an ECDSA Generation and
 * verification using ECC keys example code.
 *
 * This code was developed and tested using the
 * following hardware:
 *
 * S32K3X4EVB-Q172
 * S32K3X4EVB-T172
 ***************************************************/
#include "S32K344.h"

#include "hse_host_format_key_catalogs.h"
#include "hse_host_ecc.h"
#include "hse_keys_allocator.h"
#include "hse_host_import_key.h"
#include "hse_host_sign.h"

#define NOP __asm("NOP")
/* This example formats the key catalog in a way that the ECC key pair
 * is generated and sore in the NVM catalog, then, the public key is exported
 * and stored in the ram catalog.
 */
/* NVM catalog format*/
const hseKeyGroupCfgEntry_t nvmKeyCatalog_ecc[] = {
		{HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PAIR, 10, HSE_KEY256_BITS}, /* ECC Key Pair Group*/
		{0,0,0,0,0}
};
/*RAM catalog format*/
const hseKeyGroupCfgEntry_t ramKeyCatalog_ecc[] = {
		{HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_ECC_PUB, 10, HSE_KEY521_BITS}, /* ECC Public Key Group*/
		{0,0,0,0,0}
};

/*Global variable to keep record of the services status*/
hseSrvResponse_t gStatus = HSE_SRV_RSP_OK;

/*Message to be signed*/
const uint8_t msg[] = "Do or do not, there is no try";

/*Q Point of the ECC curve (public key)*/
uint8_t Q [2*256/8];

/*Arrays with the R and S coordinates of the signature*/
static uint8_t signR[256] = {0};
static uint8_t signS[256] = {0};
/*Size of the R and S coordinates of the signature, used as parameters of the sign and verify functions*/
static uint32_t signRLen = sizeof(signR);
static uint32_t signSLen = sizeof(signS);

/*Functions*/
/* init_indicators
 *
 * Initializes the LED pins
 * */
void init_indicators(void);

/* check_status
 *
 * Displays the status in the LEDs on board. If the parameter is
 * to HSE_SRV_RSP_OK it will display a green color, otherwise it
 * the LED will turn red
 *
 *  Params:
 * 		stat = input of the status that is being compared.*/
void check_status(hseSrvResponse_t stat);


/*Main application*/
int main(void) {

	/*Key Handle for ECC key pair in NVM Catalog*/
	hseKeyHandle_t keyPairHandle = GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM,0,0);
	/*Key Handle for Public Key in RAM catalog*/
	hseKeyHandle_t keyPubHandle = GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_RAM,0,0);

	/*Initializes LEDs*/
	init_indicators();

	/*Formats the Key catalogs */
	gStatus = FormatKeyCatalogs(nvmKeyCatalog_ecc,ramKeyCatalog_ecc);

	/*Initializes the Key Allocator Driver for Hanfdling Keys in the framework*/
	gStatus = HKF_Init(nvmKeyCatalog_ecc, ramKeyCatalog_ecc);

	/*Generates ECC Key in the NVM Catalog and exports the public Key into the Q array*/
	gStatus = GenerateEccKeyAndExportPublic(keyPairHandle,HSE_EC_SEC_SECP256R1,(HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY | HSE_KF_ACCESS_EXPORTABLE),Q);

	/*Loads ECC Public Key stored in the Q array in the RAM catalog*/
	gStatus = LoadEccPublicKey(&keyPubHandle,0,HSE_EC_SEC_SECP256R1,256,Q);

	/* Signs the message using the Key Pair in the NVM catalog with SHA256 algorithm
	 * The signature is stored in the signR and signS arrays*/
	gStatus = EcdsaSign(keyPairHandle,HSE_HASH_ALGO_SHA2_256,sizeof(msg),msg,FALSE,0,&signRLen, signR, &signSLen, signS);

	/* Verifies the signature with the public Key stored inn the RAM catalog using the signature generated above*/
	gStatus = EcdsaVerify(keyPubHandle,HSE_HASH_ALGO_SHA2_256,sizeof(msg),msg,FALSE,0,&signRLen, signR, &signSLen, signS);

	/*Checks the status variable to display the error status*/
	check_status(gStatus);

	for (;;) {
		NOP; /*No Operation*/
    }

    return 0;
}

void init_indicators(void)
{
	/*Red LED*/
	IP_SIUL2->MSCR[29] |= SIUL2_MSCR_OBE_MASK;
	/*Green LED*/
	IP_SIUL2->MSCR[30] |= SIUL2_MSCR_OBE_MASK;
}

void check_status(hseSrvResponse_t stat)
{
	if(HSE_SRV_RSP_OK != stat)
	{
		/*An error has occurred*/
		IP_SIUL2->GPDO30 = 0;
		IP_SIUL2->GPDO29 = 1;
	}
	else
	{
		/*No Error*/
		IP_SIUL2->GPDO29 = 0;
		IP_SIUL2->GPDO30 = 1;
	}
}
