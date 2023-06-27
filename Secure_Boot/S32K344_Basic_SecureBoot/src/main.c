/* Copyright 2020 NXP */
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
#include "hse_host_attrs.h"
#include "hse_demo_app_services.h"
#include "hse_host_flashSrv.h"
#include "hse_interface.h"
#include "hse_host_boot.h"
#include <string.h>
#include "pflash.h"
#include "flash.h"

/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

#define GENERATE_TAG 		1
#define VERIFY_TAG			1

#define TAG_LENGTH 			28
#define APP_HEADER_LENGTH 	0x40U
/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/
extern bool_t IsTagLocationErased;

/* RAM address for GMAC */
uint8_t temp_addr_of_app_image[32] = {0xFF};

const uint8_t* pAppBL = 0x005040C0;
uint32_t AppBL_codeLength = 0x1000;

/*=============================================================================
*                    GLOBAL FUNCTIONS DEFINITION
=============================================================================*/

/*=============================================================================
 *                        MAIN APPLICATION
 * ==========================================================================*/

int main(void) {
hseSrvResponse_t srvResponse;
tFLASH_STATUS status;

/* Verify ADKP */
if(FALSE == check_debug_password_programmed_status()){
	while(1);
}

#if GENERATE_TAG
/* Generate Tag of size 32 over the provided APPBL */
srvResponse = HSE_SignBootImage(pAppBL, TAG_LENGTH, temp_addr_of_app_image);
ASSERT(HSE_SRV_RSP_OK == srvResponse);

/* Write the generated TAG to the end of the application in FLASH */
PFLASH_Unlock(PFLASH_BL1, PFLASH_SS0, PFLASH_S0);
status = FLASH_Write (pAppBL + APP_HEADER_LENGTH + AppBL_codeLength,
					  temp_addr_of_app_image,
					  sizeof(temp_addr_of_app_image));
(void)status;
#endif

/* Verify that the generated TAG is valid for the APPBL */
#if VERIFY_TAG
srvResponse = HSE_VerifyBootImage(pAppBL);
ASSERT(HSE_SRV_RSP_OK == srvResponse);
#endif

/*Successful executions means that the secure boot is properly configured and the user can generate a Reset
  in order to start secure boot on the next boot                                                
*/

    for (;;) {

    }

    return 0;
}
