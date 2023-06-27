/* *********************************************************************
 *  Copyright 2017-2021 NXP
 *  All Rights Reserved
 * *********************************************************************
 *!\file    typedefs.h
 *!\brief   This file contains various type defines for datatypes
 *
 * TYPE: Header File
 * *********************************************************************
 * PURPOSE:  This file contains various type defines for datatypes
 * *********************************************************************/
 
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
