/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2018                *
*                        All Rights Reserved                            *
*************************************************************************

*************************************************************************
*                                                                       *
*               Standard Software Driver for C40                        *
*                                                                       *
* FILE NAME     :  Fls_StdMacro.h                                       *
* DATE          :  July 31, 2018                                        *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  nxa27472@freescale.com                               *
*                                                                       *
*************************************************************************/

/******************************* CHANGES *********************************
  1.0.0       31.07.2018         FPT Team      Initial Version For S32K2XX
*************************************************************************/

#ifndef _FLS_STDMACROS_H_
#define _FLS_STDMACROS_H_

/*************************************************************************/
/*                 Define                                                */
/*************************************************************************/

#ifndef STD_OFF
#define STD_OFF 0
#endif

#ifndef STD_ON
#define STD_ON (!STD_OFF)
#endif

#ifndef NULL_PTR
#define NULL_PTR 0x0U
#endif

#ifndef NULL
#define NULL 0x0U
#endif
/*********************************************************************************************************************************/
/*                                    SSD general data types                                                                              */
/*********************************************************************************************************************************/
typedef unsigned char boolean;

typedef signed char int8;
typedef unsigned char uint8;

typedef signed long int32;
typedef unsigned long uint32;

/*********************************************************************************************************************************/
/*                   Other Macros for SSD functions                                                                              */
/*********************************************************************************************************************************/
#define REG_READ32(address)               (*(volatile uint32*)(address))   /*  @brief 32 bits memory read macro. */
//#define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32*)(address))&= (~(mask)))   /* @brief 32 bits bits clearing macro.*/
inline void REG_BIT_CLEAR32(uint32 address, uint32 mask)    {*(volatile uint32*)(address)&= ~(mask);}   /* @brief 32 bits bits clearing macro.*/
#define REG_BIT_GET32(address, mask)      ((*(volatile uint32*)(address))& (mask))      /* @brief 32 bits bits getting macro.*/
inline void  REG_WRITE32(uint32 address, uint32 value)       {(*(volatile uint32*)(address))= (value);}    /* @brief 32 bits memory write macro.*/
inline void REG_BIT_SET32(uint32 address, uint32 mask)      {(*(volatile uint32*)(address))|= (mask);}    /* @brief 32 bits bits setting macro.*/

#endif  /* _FLS_STDMACROS_H_ */
