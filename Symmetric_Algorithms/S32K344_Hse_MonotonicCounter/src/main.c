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
 * S32K344_Hse_MonotonicCounter
 * main.c for Core M7_0
 ***************************************************
 * Author: GPIS Applications
 * Date: May 5th, 2023
 * Version 1.0
 ***************************************************
 * This project includes an example using the monotonic
 * counter.
 *
 * This code was developed and tested using the
 * following hardware:
 *
 * S32K3X4EVB-Q172
 * S32K3X4EVB-T172
 ***************************************************/

#include "S32K344.h"
#include "hse_host.h"
#include "hse_host_monotonic_counters.h"

#define MONOTONIC_CNT_INSTANCE	0U
#define MONOTONIC_RP_SIZE 		48U
#define NOP __asm("NOP")

/*Global variable to keep record of the services status*/
hseSrvResponse_t gStatus = HSE_SRV_RSP_OK;


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



int main(void) {

	/*Variable to keep track of the counter value*/
	uint64_t cnt_val = 0;

	/*Initializes the LEDs*/
	init_indicators();

	/*Configures the counter RolloverProtection size*/
	gStatus = ConfigCounterReq(MONOTONIC_CNT_INSTANCE,MONOTONIC_RP_SIZE);

	/*Increments counter in 512*/
	gStatus = IncCounterReq(MONOTONIC_CNT_INSTANCE,0x100U);

	/*Reads counter and stores value in variable*/
	gStatus = ReadCounterReq(MONOTONIC_CNT_INSTANCE,&cnt_val);

	/*Checks the status variable to display the error status*/
	check_status(gStatus);

    for (;;) {
    	NOP;
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
