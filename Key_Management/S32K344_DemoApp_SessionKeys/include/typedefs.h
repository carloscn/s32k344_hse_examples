/* Copyright 2017-2022 NXP */
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

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#ifdef __MWERKS__    /* Metrowerk CodeWarrior */
    #include <stdint.h>

    /* Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;

#else
#ifdef __ghs__    /* GreenHills */
    #include <stdint.h>

    /* Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;

    typedef int32_t int24_t;
    typedef uint32_t uint24_t;
    typedef vint32_t vint24_t;
    typedef vuint32_t vuint24_t;

    typedef signed char int8;
    typedef unsigned char uint8;
    typedef volatile signed char vint8;
    typedef volatile unsigned char vuint8;

    typedef signed short int16;
    typedef unsigned short uint16;
    typedef volatile signed short vint16;
    typedef volatile unsigned short vuint16;

    typedef signed int int32;
    typedef unsigned int uint32;
    typedef volatile signed int vint32;
    typedef volatile unsigned int vuint32;
    typedef volatile signed long long vint64_t;
    typedef volatile unsigned long long vuint64_t;
    
#else
#ifdef __GNUC__    /* GCC */
    #include <stdint.h>

    /* Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;

    typedef volatile signed long long vint64_t;
    typedef volatile unsigned long long vuint64_t;
#else

    /* This is needed for compilers that don't have a stdint.h file */
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef volatile signed char vint8_t;
    typedef volatile unsigned char vuint8_t;

    typedef signed short int16_t;
    typedef unsigned short uint16_t;
    typedef volatile signed short vint16_t;
    typedef volatile unsigned short vuint16_t;

    typedef signed int int32_t;
    typedef unsigned int uint32_t;
    typedef volatile signed int vint32_t;
    typedef volatile unsigned int vuint32_t;
    typedef volatile signed long long vint64_t;
    typedef volatile unsigned long long vuint64_t;

#endif
#endif
#endif

typedef unsigned long  boolean;  /* Machine representation of a boolean */
#define SUCCESS  0
#define FAILURE  1
#endif  /*_TYPEDEFS_H_*/
