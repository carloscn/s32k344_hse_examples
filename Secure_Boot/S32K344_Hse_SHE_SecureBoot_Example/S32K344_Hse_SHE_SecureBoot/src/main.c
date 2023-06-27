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
 * S32K344_Hse_SHE_SecureBoot
 * main.c for Core M7_0 Secure Boot Configuration
 ***************************************************
 * Author: GPIS Applications
 * Date: May 5th, 2023
 * Version 1.0
 ***************************************************
 * This project includes an example of configuring
 * Secure boot using SHE standard.
 *
 * Some memory regions are defined on the Linker File
 * (S32K344_flash.ld), including IVT and the
 * application to be authenticated. Also, the secure
 * boot bit in the IVT was set in the boot_header.c
 *
 * This code was developed and tested using the
 * following hardware:
 *
 * S32K3X4EVB-Q172
 * S32K3X4EVB-T172
 ***************************************************/

#include "S32K344.h"
#include "hse_host_format_key_catalogs.h"
#include "hse_keys_allocator.h"
#include "hse_host.h"
#include "hse_host_mac.h"
#include "hse_host_boot.h"
#include "hse_host_attrs.h"
#include "hse_demo_app_services.h"
#include "hse_host_wrappers.h"
#include "hse_memory_update_protocol.h"

#define NOP __asm("NOP")

#define APPBL_ADDR	0x004420C0;
#define APPBL_LEN	0x91F40;


/* This example formats the key catalog with the SHE standard.
 * In order to configure SHE Secure Boot, the BOOT MAC Key needs
 * to be formatted in an specific slot of the Key Catalog with
 * the SHE format. Also, this examples uses an AES key to generate
 * the CMAC Tag used to authenticate the SMR.
 */

/* NVM catalog format*/
const hseKeyGroupCfgEntry_t nvmKeyCatalog_she[] = {
		{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 12U, HSE_KEY128_BITS}, /* MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10 */
		{HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 4U, HSE_KEY128_BITS},
		{0,0,0,0,0}
};
/*RAM catalog format*/
const hseKeyGroupCfgEntry_t ramKeyCatalog_she[] = {
		{HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 1U, HSE_KEY128_BITS}, /*Dummy key group*/
		{0,0,0,0,0}
};

/*Master ECU Key used to authenticate the MAC Boot Key*/
uint8_t HSE_MASTER_ECU_KEY[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

/*Authentication tag for the SMR*/
uint8_t __attribute__((aligned(4))) AuthTag[2U][BITS_TO_BYTES(4096U)] ;

/*Authentication tag length array*/
uint32_t AuthTagLen[2U]  ;

/* SMR Entry Table
 * For HE Secure boot, only one entry is required
 * since there can only be 1 SMR
 * */
hseSmrEntry_t smrEntry_she[8U] ;

/* Core Reset configuration
 * Since S32K344 only has one core, only one
 * CR entry is needed
 * */
hseCrEntry_t crEntry_she[2U] ;

/*Variable to keep track of the SMR status*/
static hseAttrSmrCoreStatus_t smrCoreStatus_Get;

/*Functions*/

/* init_indicators
 *
 * Initializes the LED pins
 * */
void init_indicators(void);

/* LoadSheMasterEcuKey
 *
 * Loads the Master ECU Key to the Key Catalog
 * */
hseSrvResponse_t LoadSheMasterEcuKey(void);

/* LoadSheBootMacKey
 *
 * Loads the Boot MAC Key to the Key Catalog
 * */
hseSrvResponse_t LoadSheBootMacKey(void);

/* ConfigSHESecureBoot
 *
 * Configures the SHE Secure Boot
 * */
hseSrvResponse_t ConfigSHESecureBoot(void);


/*Global variable to keep track of the services status*/
hseSrvResponse_t gStatus = HSE_SRV_RSP_OK;

int main(void) {

	/*Initializes LEDs*/
	init_indicators();

	/*Grant super user rights to configure Secure Boot*/
	gStatus = Grant_SuperUser_Rights();

	/*Formats the Key catalogs */
	gStatus = FormatKeyCatalogs(nvmKeyCatalog_she,ramKeyCatalog_she);

	/*Initializes the Key Allocator Driver for Handling Keys in the framework*/
	gStatus = HKF_Init(nvmKeyCatalog_she, ramKeyCatalog_she);

	/*Loads the required keys*/
	gStatus = LoadSheMasterEcuKey();
	gStatus = LoadSheBootMacKey();

    /*Configures Secure boot*/
	gStatus = ConfigSHESecureBoot();

    for (;;) {
    	NOP; /*No operation*/
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

hseSrvResponse_t ConfigSHESecureBoot(void)
{
    uint8_t smr;                        /* Will use SMR#1 */
    hseSrvResponse_t srvResponse = HSE_SRV_RSP_GENERAL_ERROR;
    hseAppHeader_t *pAppHeader[HSE_APP_CORE1];
    hseAppCore_t app_core = HSE_APP_CORE0;


    smr = 0U;
    pAppHeader[HSE_APP_CORE0] = (hseAppHeader_t *)APPBL_ADDR; 					/*Application Address*/
    /*SMR configuration*/
    smrEntry_she[smr].configFlags = HSE_SMR_CFG_FLAG_INSTALL_AUTH;				/* Indicate that verification should be done on provided signature */
    smrEntry_she[smr].pSmrDest = 0U;                                      		/* destination address shall be NULL for flashed based devices */
    smrEntry_she[smr].checkPeriod = 0U;
	smrEntry_she[smr].pSmrSrc = pAppHeader[smr]->pAppStartEntry;           		/* Start of APP code */
    smrEntry_she[smr].smrSize = pAppHeader[smr]->codeLength;                    /* Length of APP code */
	smrEntry_she[smr].authKeyHandle = GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 0, 1); /*Key Handle for NVM_SHE_AES128_BOOT_KEY*/
	smrEntry_she[smr].authScheme.macScheme.macAlgo = HSE_MAC_ALGO_CMAC;
	smrEntry_she[smr].authScheme.macScheme.sch.cmac.cipherAlgo = HSE_CIPHER_ALGO_AES;

	/*Application CMAC tag generation*/
	AuthTagLen[0] = sizeof(AuthTag[0]);
    srvResponse = AesCmacGenerate(GET_KEY_HANDLE(HSE_KEY_CATALOG_ID_NVM, 1, 0), smrEntry_she[smr].smrSize, (const uint8_t*) (smrEntry_she[smr].pSmrSrc), &AuthTagLen[0],
            AuthTag[0], 0U);
    /*Authentication Tag is loaded to the SMR entry*/
	smrEntry_she[smr].pInstAuthTag[0] = (uint32_t)AuthTag[0];     			/* NR for SHE */
	smrEntry_she[smr].pInstAuthTag[1] = (uint32_t)NULL;                   	/* NR for SHE */

    /* Configure CR entry */
    crEntry_she[app_core].coreId = app_core;                                /* Define the behavior for core 0 - M33_0, core 1 - M33_1 */
    crEntry_she[app_core].preBootSmrMap = HSE_KF_SMR_0;                     /* Tie it to the verification of SMR defined above (index 0) */
    crEntry_she[app_core].pPassReset = pAppHeader[smr]->pAppStartEntry;     /* Entry point - address of the first instruction */
    crEntry_she[app_core].crSanction = HSE_CR_SANCTION_KEEP_CORE_IN_RESET;  /* Sanction in case SMR verification fails - keep core in reset */
    crEntry_she[app_core].altPreBootSmrMap = 0x0UL;                         /* Not used here - configuration in case boot fails */
    crEntry_she[app_core].pAltReset = pAppHeader[smr]->pAppStartEntry;
    crEntry_she[app_core].startOption = HSE_CR_AUTO_START;

    /* Import keys and Install SMR Entry */
    srvResponse = HSE_InstallSmrEntry(
                    smr,
                    (const hseSmrEntry_t *)&smrEntry_she[smr],
                    (const uint8_t *)smrEntry_she[smr].pSmrSrc,
                    smrEntry_she[smr].smrSize,
                    (const uint8_t *)NULL,
                    (const uint8_t *)NULL,
                    0U,
                    0U );

    /* Install CR Entry */
    srvResponse = HSE_InstallCoreResetEntry( smr,&(crEntry_she[app_core]) );

    /* Reads the SMR status*/
    srvResponse = GetAttr(
            HSE_SMR_CORE_BOOT_STATUS_ATTR_ID,
            sizeof(hseAttrSmrCoreStatus_t),
            (void *)(&smrCoreStatus_Get)
            );

	return srvResponse;
}

hseSrvResponse_t LoadSheMasterEcuKey(void)
{
    hseSrvResponse_t hseResponse;
    MemoryUpdate_t MemUpdate;
    /*UID’ is the wildcard value 0*/
    uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    /*initial value of Master Ecu Key*/
    uint8_t MASTER_ECU_KEY_EMPTY[AES_BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(MemUpdate.uid, t_uid, ARRAY_SIZE(MemUpdate.uid));
    memcpy(MemUpdate.KeyNew, HSE_MASTER_ECU_KEY, 16);
    memcpy(MemUpdate.AuthKey, MASTER_ECU_KEY_EMPTY, 16);
    /*The key ID for the key to be updated i.e. MasterEcuKey*/
    MemUpdate.KeyId = 0x01;
    /*The key ID for the Auth Key i.e. MasterEcuKey as Master EcuKey can Authenticate the same*/
    MemUpdate.AuthId = 0x01;
    /*CID’*/
    MemUpdate.count_val = 0x01;
    MemUpdate.sheGroupId = 0x00;
    /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
    MemUpdate.flag_val = 0x00;
    hseResponse = MemoryUpdateProtocol(&MemUpdate);

    return hseResponse;
}

hseSrvResponse_t LoadSheBootMacKey(void)
{
    hseSrvResponse_t hseResponse;
    MemoryUpdate_t MemUpdate;
    /*UID’ is the wildcard value 0*/
    uint8_t t_uid[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    /*The new key value to be updated*/
    uint8_t t_KeyNew_1[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    /*initial value of Master Ecu Key*/
    memcpy(MemUpdate.uid, t_uid, 15);
    memcpy(MemUpdate.KeyNew, t_KeyNew_1, 16);
    memcpy(MemUpdate.AuthKey, HSE_MASTER_ECU_KEY, 16);
    /*The key ID for the key to be updated i.e. MasterEcuKey*/
    MemUpdate.KeyId = 0x02;
    /*The key ID for the Auth Key i.e. MasterEcuKey as Master EcuKey can Authenticate the same*/
    MemUpdate.AuthId = 0x01;
    /*CID’*/
    MemUpdate.count_val = 0x01;
    MemUpdate.sheGroupId = 0x00;
    /*FID’ = WRITE_PROTECTION|BOOT_ PROTECTION|DEBUGGER_PROTECTION|KEY_USAGE|WILDCARD|VERIFY_ONLY*/
    MemUpdate.flag_val = 0x00;
    hseResponse = MemoryUpdateProtocol(&MemUpdate);

    return hseResponse;
}
