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
#ifndef STDREGMACROS_H
#define STDREGMACROS_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file        StdRegMacros.h
* @brief Include platform types
*/
#include "Platform_Types.h"


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define REG_WRITE8(address, value)        ((*(volatile uint8*)(address))=  (value))

#define REG_WRITE16(address, value)       ((*(volatile uint16*)(address))= (value))

#define REG_WRITE32(address, value)       ((*(volatile uint32*)(address))= (value))

#define REG_READ8(address)                (*(volatile uint8*)(address))

#define REG_READ16(address)               (*(volatile uint16*)(address))

#define REG_READ32(address)               (*(volatile uint32*)(address))

#define REG_AWRITE8(address, i, value)     (REG_WRITE8 ((address)+(i), (value)))

#define REG_AWRITE16(address, i, value)    (REG_WRITE16((address)+((uint32)((i)<<1U)), (value)))

#define REG_AWRITE32(address, i, value)    (REG_WRITE32((address)+((uint32)((i)<<2U)), (value)))

#define REG_AREAD8(address, i )            (REG_READ8 ((address)+(i)))

#define REG_AREAD16(address, i)            (REG_READ16((address)+((uint32)((i)<<1U))))

#define REG_AREAD32(address, i)            (REG_READ32((address)+((uint32)((i)<<2U))))

#define REG_BIT_CLEAR8(address, mask)     ((*(volatile uint8*)(address))&= (~(mask)))

#define REG_BIT_CLEAR16(address, mask)    ((*(volatile uint16*)(address))&= (~(mask)))

#define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32*)(address))&= (~(mask)))

#define REG_BIT_GET8(address, mask)       ((*(volatile uint8*)(address))& (mask))

#define REG_BIT_GET16(address, mask)      ((*(volatile uint16*)(address))& (mask))

#define REG_BIT_GET32(address, mask)      ((*(volatile uint32*)(address))& (mask))

#define REG_BIT_SET8(address, mask)       ((*(volatile uint8*)(address))|= (mask))

#define REG_BIT_SET16(address, mask)      ((*(volatile uint16*)(address))|= (mask))

#define REG_BIT_SET32(address, mask)      ((*(volatile uint32*)(address))|= (mask))

#define REG_RMW8(address, mask, value)    (REG_WRITE8((address), ((REG_READ8(address)& ((uint8)~(mask)))| (value))))

#define REG_RMW16(address, mask, value)   (REG_WRITE16((address), ((REG_READ16(address)& ((uint16)~(mask)))| (value))))

#define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32)~(mask)))| (value))))


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef STDREGMACROS_H */

/** @} */
