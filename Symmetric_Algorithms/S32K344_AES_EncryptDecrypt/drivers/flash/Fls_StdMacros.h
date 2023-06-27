/*==================================================================================================
*
*   Copyright 2022 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

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
