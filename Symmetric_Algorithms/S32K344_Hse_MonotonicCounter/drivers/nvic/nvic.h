
/*==================================================================================================
*   @file    nvic.h
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - nvic driver
*   @details nvic driver
*            This file contains sample code only. It is not part of the production code deliverables
*
*/
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

#ifndef NVIC_H
#define NVIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "std_typedefs.h"
#include "Std_Types.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define NVIC_BASEADDR 0xE000E100
#define NVIC_ISER_OFFSET(id) (uint8)((id >> 5) << 2)
#define NVIC_ICER_OFFSET(id) (0x80 + (uint8)((id >> 5) << 2))
#define NVIC_IPRO_OFFSET(id) (0x300 + (uint8)((id >> 2) << 2))
#define NVIC_IPRO_MASK(id) (uint32)(0xFF << ((id % 4)*8))

/* S32_SCB - Peripheral instance base addresses */
/** Peripheral S32_SCB base address */
#define S32_SCB_BASE                             (0xE000E000UL)
/** Peripheral S32_SCB base pointer */
#define S32_SCB                                  ((S32_SCB_Type *)S32_SCB_BASE)

#define S32_SCB_AIRCR_PRIGROUP_MASK              (0x700UL)
#define S32_SCB_AIRCR_PRIGROUP_SHIFT             (8U)

#define S32_SCB_SHPR3_PRI_14_MASK                (0xFF0000UL)
/*==================================================================================================
*                                             TYPEDEFS
==================================================================================================*/
typedef struct {
            uint8 RESERVED_0[8];
volatile    uint32 ACTLR;                             /**< Auxiliary Control Register,, offset: 0x8 */
            uint8 RESERVED_1[3316];
volatile    uint32 CPUID;                             /**< CPUID Base Register, offset: 0xD00 */
volatile    uint32 ICSR;                              /**< Interrupt Control and State Register, offset: 0xD04 */
volatile    uint32 VTOR;                              /**< Vector Table Offset Register, offset: 0xD08 */
volatile    uint32 AIRCR;                             /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
volatile    uint32 SCR;                               /**< System Control Register, offset: 0xD10 */
volatile    uint32 CCR;                               /**< Configuration and Control Register, offset: 0xD14 */
volatile    uint32 SHPR1;                             /**< System Handler Priority Register 1, offset: 0xD18 */
volatile    uint32 SHPR2;                             /**< System Handler Priority Register 2, offset: 0xD1C */
volatile    uint32 SHPR3;                             /**< System Handler Priority Register 3, offset: 0xD20 */
volatile    uint32 SHCSR;                             /**< System Handler Control and State Register, offset: 0xD24 */
volatile    uint32 CFSR;                              /**< Configurable Fault Status Registers, offset: 0xD28 */
volatile    uint32 HFSR;                              /**< HardFault Status register, offset: 0xD2C */
volatile    uint32 DFSR;                              /**< Debug Fault Status Register, offset: 0xD30 */
volatile    uint32 MMFAR;                             /**< MemManage Address Register, offset: 0xD34 */
volatile    uint32 BFAR;                              /**< BusFault Address Register, offset: 0xD38 */
volatile    uint32 AFSR;                              /**< Auxiliary Fault Status Register, offset: 0xD3C */
            uint8 RESERVED_2[72];
volatile    uint32 CPACR;                             /**< Coprocessor Access Control Register, offset: 0xD88 */
            uint8 RESERVED_3[424];
volatile    uint32 FPCCR;                             /**< Floating-point Context Control Register, offset: 0xF34 */
volatile    uint32 FPCAR;                             /**< Floating-point Context Address Register, offset: 0xF38 */
volatile    uint32 FPDSCR;                            /**< Floating-point Default Status Control Register, offset: 0xF3C */
} S32_SCB_Type;


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

void NVIC_SetPriorityGrouping(uint32 PriorityGroup);
void NVIC_EnableIRQ(uint8 IRQn);
void NVIC_DisableIRQ(uint8 IRQn);
void NVIC_SetPriority(uint8 IRQn, uint8 priority);


#ifdef __cplusplus
}
#endif

#endif /*NVIC_H*/
