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
 * main.c for Core M7_0 Application to be authenticated
 ***************************************************
 * Author: GPIS Applications
 * Date: May 5th, 2023
 * Version 1.0
 ***************************************************
 * This project includes an example of configuring
 * Secure boot using SHE standard.
 *
 * Some memory regions are defined on the Linker File
 * (S32K344_flash.ld). PFLASH address was modified to fit
 * in the Secure Boot Configuration App.
 *
 * This code was developed and tested using the
 * following hardware:
 *
 * S32K3X4EVB-Q172
 * S32K3X4EVB-T172
 ***************************************************/

#include "S32K344.h"

#if defined (__ghs__)
    #define __INTERRUPT_SVC  __interrupt
    #define __NO_RETURN__ _Pragma("ghs nowarning 111")
#elif defined (__ICCARM__)
    #define __INTERRUPT_SVC  __svc
    #define __NO_RETURN__ _Pragma("diag_suppress=Pe111")
#elif defined (__GNUC__)
    #define __INTERRUPT_SVC  __attribute__ ((interrupt ("SVC")))
    #define __NO_RETURN__
#else
    #define __INTERRUPT_SVC
    #define __NO_RETURN__
#endif

/* Structure of the Application boot header*/
typedef struct
{
    uint8_t                 hdrTag;                  /**< @brief App header tag shall be 0xD5. */
    uint8_t                 reserved1[2];            /**< @brief Reserved field has no impact.*/
    uint8_t                 hdrVersion;              /**< @brief App header version shall be 0x60. */
    uint32_t                pAppDestAddres;          /**< @brief The destination address where the application is copied.
                                                                 @note For HSE-B, it is NULL (the code is executed from flash) */
    uint32_t                pAppStartEntry;          /**< @brief The address of the first instruction to be executed.*/
    uint32_t                codeLength;              /**< @brief Length of application image. */
    uint8_t		            coreId;                  /**< @brief The application core ID that is un-gated.
                                                                 @note Valid for HSE-B devices only. For HSE-H/M core id defined in IVT*/
    uint8_t                 reserved2[47];           /**< @brief Reserved field has no impact. Set to all zeroes. */
} hseAppHeader_t;

/*Gets the start address of the Flash section of the application*/
extern uint32_t __text_start;

const hseAppHeader_t __attribute__((section("._app_boot_header"))) app_header =
{
        .hdrTag = 0xD5 , 								/*Header TAG as specified in RM*/
        .reserved1 = {0xFF, 0xFF},
        .hdrVersion = 0x60 ,
        .pAppDestAddres = 0x00 ,
        .pAppStartEntry = (uint32_t)( &__text_start ) , /*Start Address of the Application*/
        .codeLength = (uint32_t)(0x91F40), 				/*Application Length*/
        .coreId = 0x00u , 								/*Core ID (M7_0 -> 0x00)*/
        .reserved2 = {0},
};

/*Counter variables*/
int counter, accumulator = 0, limit_value = 1000000;

int main(void) {

    counter = 0;

    for (;;) {
        counter++;
        /*GPIO initialization*/
    	IP_SIUL2->MSCR[31] |= SIUL2_MSCR_OBE_MASK;

        if (counter >= limit_value) {
            __asm volatile ("svc 0");
            counter = 0;
            /*GPIO Toggle*/
            IP_SIUL2->GPDO31 ^= 1;
        }
    }
    __NO_RETURN__
    return 0;
}

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
}
