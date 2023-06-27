
/*==================================================================================================
*   @file    nvic.h
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - nvic driver
*   @details nvic driver
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup BUILD_ENV
*   @{
*/
/*==================================================================================================
*   Project              : M4_SRC_PROJECT_NAME
*   Platform             : M4_SRC_MCU_FAMILY
*   Peripheral           : M4_SRC_USED_PERIPHERAL
*   Dependencies         : M4_SRC_AR_MODULE_DEPENDENCY
*
*   Autosar Version      : M4_SRC_AR_SPEC_VERSION_MAJOR.M4_SRC_AR_SPEC_VERSION_MINOR.M4_SRC_AR_SPEC_VERSION_PATCH
*   Autosar Revision     : M4_SRC_AR_RELEASE_REVISION
*   Autosar Conf.Variant :
*   SW Version           : M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*   Build Version        : M4_SRC_BUILD_ID
*
*   (c) Copyright M4_SRC_YEAR_ID M4_SRC_COPYRIGHTED_TO
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Marius Rotaru (rtrm001)       08/06/2015    ENGR00345201  Create NVIC driver
---------------------------   ----------    ------------  ------------------------------------------
',)dnl - DO NOT modify this M4 line!
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
