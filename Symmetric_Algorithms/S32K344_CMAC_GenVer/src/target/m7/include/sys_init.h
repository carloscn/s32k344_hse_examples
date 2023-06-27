/*==================================================================================================
*   @file    sys_init.h
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - MCAL auxiliary APIs used for MCAL testing
*   @details MCAL auxiliary APIs used for MCAL testing
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup BUILD_ENV
*   @{
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

#ifndef SYS_INIT_H
#define SYS_INIT_H

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
#include "S32K344.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define INT_NUM_SOURCES (224)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/



    
/** @brief system clock sources */
typedef enum
{
    FIRC_CLK,
    FXOSC_CLK,
    SIRC_CLK,
    SXOSC_CLK,
    PLL2_PFD_CLK,
    PLL2_CLK,
    PLL1_PFD_CLK,
    PLL3_CLK
} system_clock_selector_t;

/** @brief output clock sources */
typedef enum
{
    FAST_XOSC_CLK
} output_clock_selector_t;

/** @brief pll reference clock sources */
typedef enum
{
    FAST_IRC_CLK
} pll_reference_clock_selector_t;

 /** @brief system clock values */
typedef enum
{
    SYS_CLK_16M,
    SYS_CLK_24M,
    SYS_CLK_32M,
    SYS_CLK_40M,
    SYS_CLK_48M,
    SYS_CLK_56M,
    SYS_CLK_64M,
    SYS_CLK_80M,
    SYS_CLK_120M     
} system_clock_values_t;



typedef void (*int_function_t)(void);

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
extern int_function_t g_INT_vectors[INT_NUM_SOURCES];

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
/** 
* @brief Scatter_Loading
* @details function used to initialize RAM variables and RAM functions 
*/
#ifdef __ICCARM__ 
    void Scatter_Loading(void);
#endif    
void SystemInit(void);
void default_interrupt_routine(void);

/** 
* @brief sys_disableIsrSource
* @details function used to disable the interrupt number id
*/
void sys_disableIsrSource(uint8 id);  
/** 
* @brief sys_init
* @details function used to enable the interrupt number id and set up the priority
*/
void sys_enableIsrSource(uint8 id, uint8 prio);
/** 
* @brief sys_init
* @details function used to register the interrupt handler in the interrupt vectors
*/
void sys_registerIsrHandler(uint8 irq_id, int_function_t isr_handler);
/** 
* @brief sys_init
* @details function used to enable all interrupts
*/
void sys_enableAllInterrupts(void);
/** 
* @brief sys_init
* @details function used to disable all interrupts
*/
void sys_disableAllInterrupts(void);

/** 
* @brief sys_init
* @details function used to initialize clocks, system clock is system Pll 120 MHz
*/
extern Std_ReturnType sys_init(void);

/** 
* @brief sys_init_ext
* @details function used to initialize clocks, system clock is system Pll and  secondary Pll with different values.
* @return E_NOT_OK/E_OK
*/
Std_ReturnType sys_init_ext(system_clock_values_t sys_pll_clk_value,\
                            system_clock_values_t sec_pll_clk_value) ;
                            
/** 
* @brief sys_select_source
* @details function used to set the system clock to the specified source
* @param[in] source system clock source
* @return E_OK/E_NOT_OK
*/
extern Std_ReturnType sys_select_source_clock(system_clock_selector_t source);

/** 
* @brief sys_set_peripheral_div
* @details function used to set the peripheral dividers
* @param[in] div_set1 divider for Peripheral BridgeX clock
* @param[in] div_set2 divider for motor control clock
* @param[in] div_set3 divider for sine wave generator clock
* @param[in] div_set4 divider for ADC clock
* @param[in] div_set5 divider for Flexray PLL clock
* @param[in] div_set6 divider for SENT clock
* @param[in] div_set7 divider for FlexCAN clock
* @param[in] div_set8 divider for DigRF clock
* @param[in] div_set9 divider for Output clock
* @return E_OK/E_NOT_OK
*/
extern Std_ReturnType sys_set_peripheral_div(vuint32_t div_set1, vuint32_t div_set2,  vuint32_t div_set3, \
                                             vuint32_t div_set4, vuint32_t div_set5, vuint32_t div_set6, \
                                              vuint32_t div_set7,  vuint32_t div_set8, vuint32_t div_set9);

/** 
* @brief sys_halt
* @details function used to enter halt mode
*/
extern void sys_halt(void);

/** 
* @brief sys_stop
* @details function used to enter stop mode
*/
extern void sys_stop(void);

/** 
* @brief sys_select_source
* @details function used to set the output clock to the specified source
* @param[in] source output clock source
* @return E_OK/E_NOT_OK
*/
extern Std_ReturnType sys_select_output_clock(output_clock_selector_t source);

/** 
* @brief sys_set_output_div
* @details function used to set the output clock divider
* @param[in] div divider for output clock
* @return E_OK/E_NOT_OK
*/
extern Std_ReturnType sys_set_output_div(vuint32_t div);

/* Handlers */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void undefined_handler(void);

#ifdef __cplusplus
}
#endif

#endif /*SYS_INIT_H*/
