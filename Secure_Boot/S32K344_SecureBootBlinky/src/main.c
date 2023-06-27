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

typedef struct
{
    uint8_t                 hdrTag;                  /**< @brief App header tag shall be 0xD5. */
    uint8_t                 reserved1[2];            /**< @brief Reserved field has no impact. Set to all zeroes.*/
    uint8_t                 hdrVersion;              /**< @brief App header version shall be 0x60. */
    uint32_t                pAppDestAddres;          /**< @brief The destination address where the application is copied.
                                                                 @note For HSE-B, it is NULL (the code is executed from flash) */
    uint32_t                pAppStartEntry;          /**< @brief The address of the first instruction to be executed.*/
    uint32_t                codeLength;              /**< @brief Length of application image. */
    uint8_t	            	coreId;                  /**< @brief The application core ID that is un-gated.
                                                                 @note Valid for HSE-B devices only. For HSE-H/M core id defined in IVT*/
    uint8_t                 reserved2[47];           /**< @brief Reserved field has no impact. Set to all zeroes. */
} hseAppHeader_t;

extern uint32_t __text_start;

const hseAppHeader_t __attribute__((section("._app_boot_header"))) app_header =
{
	.hdrTag = 0xD5 ,
	.reserved1 = {0xFF, 0xFF},
	.hdrVersion = 0x60 ,
	.pAppDestAddres = 0x00,
	.pAppStartEntry = (uint32_t)(&__text_start) ,
	.codeLength = (uint32_t)(0x1000),
	.coreId = 0x00u ,
	.reserved2 = {0},
};

int main(void) {

	uint32_t i = 0;

	IP_SIUL2->MSCR[31] = SIUL2_MSCR_OBE_MASK;

    for (;;) {
    	i = 100000;

		IP_SIUL2->GPDO31 ^= 1;
		while(--i != 0);


    }
    return 0;
}



