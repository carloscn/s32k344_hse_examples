/**************************************************************************//**
 * @file     startup_ARMCM7.c
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM7 Device
 * @version  V5.3.1
 * @date     04. June 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined (ARMCM7)
  #include "ARMCM7.h"
#elif defined (ARMCM7_SP)
  #include "ARMCM7_SP.h"
#elif defined (ARMCM7_DP)
  #include "ARMCM7_DP.h"
#else
  #error device not specified!
#endif

#include "S32K344.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  Peripheral MC_RGM base pointer
 *----------------------------------------------------------------------------*/

#ifndef MC_RGM
#define MC_RGM IP_MC_RGM
#endif

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
#ifdef INIT_STDBY_RAM
extern uint32_t __STDBYRAM_START, __STDBYRAM_SIZE;
#endif

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
#if defined ( __GNUC__ )
void __NAKED __NO_RETURN __attribute__((target("general-regs-only"))) Reset_Handler(void);
#else
void __NAKED __NO_RETURN Reset_Handler(void);
#endif

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* ARM CORE Exceptions */
void __NO_RETURN NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void __NO_RETURN SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

/* SoC Interrupts */
void __NO_RETURN INT0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN INT1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN INT2_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN INT3_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD0_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD1_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD2_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD3_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD4_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD5_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD6_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD7_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD8_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD9_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD10_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD11_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD12_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD13_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD14_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD15_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD16_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD17_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD18_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD19_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD20_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD21_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD22_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD23_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD24_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD25_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD26_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD27_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD28_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD29_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD30_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN DMATCD31_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ERM_0_Handler      (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ERM_1_Handler      (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MCM_Handler        (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN STM0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN STM1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SWT0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SWT1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FLASH_0_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FLASH_1_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FLASH_2_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN RGM_Handler        (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN PMC_Handler        (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SIUL_0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SIUL_1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SIUL_2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SIUL_3_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_2_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_3_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_4_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_5_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_6_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS0_7_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_2_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_3_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_4_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_5_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_6_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS1_7_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_2_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_3_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_4_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_5_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_6_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN EMIOS2_7_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN WKPU_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN CMU0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN CMU1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN CMU2_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN BCTU_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LCU0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LCU1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN PIT0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN PIT1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN PIT2_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN RTC_Handler        (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ENET_0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ENET_1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ENET_2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ENET_3_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN0_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN0_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN0_2_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN0_3_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN1_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN1_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN1_2_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN2_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN2_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN2_2_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN3_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN3_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN4_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN4_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN5_0_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FlexCAN5_1_Handler (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FLEXIO_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART0_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART1_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART2_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART3_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART4_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART5_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART6_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART7_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART8_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART9_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART10_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART11_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART12_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART13_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART14_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPUART15_Handler   (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPI2C0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPI2C1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI3_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI4_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPSPI5_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN QSPI_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SAI0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN SAI1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN JDC_Handler        (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ADC0_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ADC1_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN ADC2_Handler       (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPCMP0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPCMP1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN LPCMP2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FCCU_0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN FCCU_1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_0_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_1_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_2_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_3_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_4_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN HSE_B_5_Handler    (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_A_0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_A_1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_A_2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_B_0_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_B_1_Handler     (void) __attribute__((weak, alias ("Default_Handler")));
void __NO_RETURN MU_B_2_Handler     (void) __attribute__((weak, alias ("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const pFunc __VECTOR_TABLE[240];
       const pFunc __VECTOR_TABLE[240] __VECTOR_TABLE_ATTRIBUTE =
{
  (pFunc)(&__INITIAL_SP),                   /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Initial Program Counter: Reset Handler */

  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  MemManage_Handler,                        /* -12 MPU Fault Handler */
  BusFault_Handler,                         /* -11 Bus Fault Handler */
  UsageFault_Handler,                       /* -10 Usage Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  DebugMon_Handler,                         /*  -4 Debug Monitor Handler */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
  INT0_Handler,       /**< CPU to CPU int0 - CPU to CPU int0 */
  INT1_Handler,       /**< CPU to CPU int1 - CPU to CPU int1 */
  INT2_Handler,       /**< CPU to CPU int2 - CPU to CPU int2 */
  INT3_Handler,       /**< CPU to CPU int3 - CPU to CPU int3 */
  DMATCD0_Handler,    /**< DMA TCD 0 - DMA transfer complete and error CH0 */
  DMATCD1_Handler,    /**< DMA TCD 1 - DMA transfer complete and error CH1 */
  DMATCD2_Handler,    /**< DMA TCD 2 - DMA transfer complete and error CH2 */
  DMATCD3_Handler,    /**< DMA TCD 3 - DMA transfer complete and error CH3 */
  DMATCD4_Handler,    /**< DMA TCD 4 - DMA transfer complete and error CH4 */
  DMATCD5_Handler,    /**< DMA TCD 5 - DMA transfer complete and error CH5 */
  DMATCD6_Handler,    /**< DMA TCD 6 - DMA transfer complete and error CH6 */
  DMATCD7_Handler,    /**< DMA TCD 7 - DMA transfer complete and error CH7 */
  DMATCD8_Handler,    /**< DMA TCD 8 - DMA transfer complete and error CH8 */
  DMATCD9_Handler,    /**< DMA TCD 9 - DMA transfer complete and error CH9 */
  DMATCD10_Handler,   /**< DMA TCD 10 - DMA transfer complete and error CH10 */
  DMATCD11_Handler,   /**< DMA TCD 11 - DMA transfer complete and error CH11 */
  DMATCD12_Handler,   /**< DMA TCD 12 - DMA transfer complete and error CH12 */
  DMATCD13_Handler,   /**< DMA TCD 13 - DMA transfer complete and error CH13 */
  DMATCD14_Handler,   /**< DMA TCD 14 - DMA transfer complete and error CH14 */
  DMATCD15_Handler,   /**< DMA TCD 15 - DMA transfer complete and error CH15 */
  DMATCD16_Handler,   /**< DMA TCD 16 - DMA transfer complete and error CH16 */
  DMATCD17_Handler,   /**< DMA TCD 17 - DMA transfer complete and error CH17 */
  DMATCD18_Handler,   /**< DMA TCD 18 - DMA transfer complete and error CH18 */
  DMATCD19_Handler,   /**< DMA TCD 19 - DMA transfer complete and error CH19 */
  DMATCD20_Handler,   /**< DMA TCD 20 - DMA transfer complete and error CH20 */
  DMATCD21_Handler,   /**< DMA TCD 21 - DMA transfer complete and error CH21 */
  DMATCD22_Handler,   /**< DMA TCD 22 - DMA transfer complete and error CH22 */
  DMATCD23_Handler,   /**< DMA TCD 23 - DMA transfer complete and error CH23 */
  DMATCD24_Handler,   /**< DMA TCD 24 - DMA transfer complete and error CH24 */
  DMATCD25_Handler,   /**< DMA TCD 25 - DMA transfer complete and error CH25 */
  DMATCD26_Handler,   /**< DMA TCD 26 - DMA transfer complete and error CH26 */
  DMATCD27_Handler,   /**< DMA TCD 27 - DMA transfer complete and error CH27 */
  DMATCD28_Handler,   /**< DMA TCD 28 - DMA transfer complete and error CH28 */
  DMATCD29_Handler,   /**< DMA TCD 29 - DMA transfer complete and error CH29 */
  DMATCD30_Handler,   /**< DMA TCD 30 - DMA transfer complete and error CH30 */
  DMATCD31_Handler,   /**< DMA TCD 31 - DMA transfer complete and error CH31 */
  ERM_0_Handler,      /**< Error Reporting Module 0 - Single bit ECC error */
  ERM_1_Handler,      /**< Error Reporting Module 1 - Multi bit ECC error */
  MCM_Handler,        /**< MCM - Multi bit ECC error */
  STM0_Handler,       /**< System Timer Module 0 - Single interrupt vector for all four channels */
  STM1_Handler,       /**< System Timer Module 1 - Single interrupt vector for all four channels */
  0,                  /**< Reserved */
  SWT0_Handler,       /**< Watchdog 0 - Platform watchdog initial time-out */
  SWT1_Handler,       /**< Watchdog 1 - Platform watchdog initial time-out */
  0,                  /**< Reserved */
  Default_Handler,    /**< CTI Interrupt 0 - Reserved */
  Default_Handler,    /**< CTI interrupt 1 - Reserved */
  0,                  /**< Reserved */
  FLASH_0_Handler,    /**< Flash - Program or erase operation is completed */
  FLASH_1_Handler,    /**< Flash - Main watchdog timeout interrupt */
  FLASH_2_Handler,    /**< Flash - Alternate watchdog timeout interrupt */
  RGM_Handler,        /**< Reset Generation Module - Interrupt request to the system */
  PMC_Handler,        /**< PMC - One interrupt for all LVDs, One interrupt for all HVDs */
  SIUL_0_Handler,     /**< SIUL IRQ0 - External Interrupt Vector 0 */
  SIUL_1_Handler,     /**< SIUL IRQ1 - External Interrupt Vector 1 */
  SIUL_2_Handler,     /**< SIUL IRQ2 - External Interrupt Vector 2 */
  SIUL_3_Handler,     /**< SIUL IRQ3 - External Interrupt Vector 3 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  EMIOS0_2_Handler,   /**< EMIOS0 - Interrupt request 23,22,21,20 */
  EMIOS0_3_Handler,   /**< EMIOS0 - Interrupt request 19,18,17,16 */
  EMIOS0_4_Handler,   /**< EMIOS0 - Interrupt request 15,14,13,12 */
  EMIOS0_5_Handler,   /**< EMIOS0 - Interrupt request 11,10,9,8 */
  EMIOS0_6_Handler,   /**< EMIOS0 - Interrupt request 7,6,5,4 */
  EMIOS0_7_Handler,   /**< EMIOS0 - Interrupt request 3,2,1,0 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  EMIOS1_2_Handler,   /**< EMIOS1 - Interrupt request 23,22,21,20 */
  EMIOS1_3_Handler,   /**< EMIOS1 - Interrupt request 19,18,17,16 */
  EMIOS1_4_Handler,   /**< EMIOS1 - Interrupt request 15,14,13,12 */
  EMIOS1_5_Handler,   /**< EMIOS1 - Interrupt request 11,10,9,8 */
  EMIOS1_6_Handler,   /**< EMIOS1 - Interrupt request 7,6,5,4 */
  EMIOS1_7_Handler,   /**< EMIOS1 - Interrupt request 3,2,1,0 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  EMIOS2_2_Handler,   /**< EMIOS2 - Interrupt request 23,22,21,20 */
  EMIOS2_3_Handler,   /**< EMIOS2 - Interrupt request 19,18,17,16 */
  EMIOS2_4_Handler,   /**< EMIOS2 - Interrupt request 15,14,13,12 */
  EMIOS2_5_Handler,   /**< EMIOS2 - Interrupt request 11,10,9,8 */
  EMIOS2_6_Handler,   /**< EMIOS2 - Interrupt request 7,6,5,4 */
  EMIOS2_7_Handler,   /**< EMIOS2 - Interrupt request 3,2,1,0 */
  WKPU_Handler,       /**< Wakeup Unit - Interrupts from pad group 0,1,2,3, Interrupts from pad group 0_64, Interrupts from pad group 1_64, Interrupts from pad group 2_64, Interrupts from pad group 3_64 */
  CMU0_Handler,       /**< CMU0 - CMU0 interrupt */
  CMU1_Handler,       /**< CMU1 - CMU1 interrupt */
  CMU2_Handler,       /**< CMU2 - CMU2 interrupt */
  BCTU_Handler,       /**< Body Cross Triggering Unit - An interrupt is requested when a conversion is issued to the ADC, An interrupt is requested when new data is available from ADC0 conversion, An interrupt is requested when new data is available from ADC1 conversion, An interrupt is requested when new data is available from ADC2 conversion, An interrupt is requested when the last command of a list is issued to the ADC,An Interrupt output for FIFO1,An Interrupt output for FIFO2 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  LCU0_Handler,       /**< Logic Control Unit 0 - Interrupt 0, Interrupt 1 Interrupt 2 */
  LCU1_Handler,       /**< Logic Control Unit 1 - Interrupt 0, Interrupt 1 Interrupt 2 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  PIT0_Handler,       /**< PIT0 - Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3,Interrupt for Channel4 */
  PIT1_Handler,       /**< PIT1 - Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  PIT2_Handler,       /**< PIT2 - Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  RTC_Handler,        /**< RTC - RTCF or ROVRF interrupt to be serviced by the system controller, APIF interrupt to be serviced by the system controller */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  ENET_0_Handler,     /**< ENET 0 - Common interrupt */
  ENET_1_Handler,     /**< ENET 1 - Tx interrupt 0, Tx interrupt 1 */
  ENET_2_Handler,     /**< ENET 2 - Rx interrupt 0, Rx interrupt 1 */
  ENET_3_Handler,     /**< ENET 3 - Safety interrupt correctable, Safety interrupt un-correctable */
  FlexCAN0_0_Handler, /**< FlexCAN0_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN0_1_Handler, /**< FlexCAN0_1 - Message Buffer Interrupt line 0-31,ORed Interrupt for Message Buffers */
  FlexCAN0_2_Handler, /**< FlexCAN0_2 - Message Buffer Interrupt line 32-63 */
  FlexCAN0_3_Handler, /**< FlexCAN0_3 - Message Buffer Interrupt line 64-95 */
  FlexCAN1_0_Handler, /**< FlexCAN1_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN1_1_Handler, /**< FlexCAN1_1 - Message Buffer Interrupt line 0-31 */
  FlexCAN1_2_Handler, /**< FlexCAN1_2 - Message Buffer Interrupt line 32-63 */
  FlexCAN2_0_Handler, /**< FlexCAN2_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN2_1_Handler, /**< FlexCAN2_1 - Message Buffer Interrupt line 0-31 */
  FlexCAN2_2_Handler, /**< FlexCAN2_2 - Message Buffer Interrupt line 32-63 */
  FlexCAN3_0_Handler, /**< FlexCAN3_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN3_1_Handler, /**< FlexCAN3_1 - Message Buffer Interrupt line 0-31 */
  FlexCAN4_0_Handler, /**< FlexCAN4_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN4_1_Handler, /**< FlexCAN4_1 - Message Buffer Interrupt line 0-31 */
  FlexCAN5_0_Handler, /**< FlexCAN5_0 - Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN5_1_Handler, /**< FlexCAN5_1 - Message Buffer Interrupt line 0-31 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  FLEXIO_Handler,     /**< Flexible IO - FlexIO Interrupt */
  0,                  /**< Reserved */
  LPUART0_Handler,    /**< LPUART0 - TX and RX interrupt */
  LPUART1_Handler,    /**< LPUART1 - TX and RX interrupt */
  LPUART2_Handler,    /**< LPUART2 - TX and RX interrupt */
  LPUART3_Handler,    /**< LPUART3 - TX and RX interrupt */
  LPUART4_Handler,    /**< LPUART4 - TX and RX interrupt */
  LPUART5_Handler,    /**< LPUART5 - TX and RX interrupt */
  LPUART6_Handler,    /**< LPUART6 - TX and RX interrupt */
  LPUART7_Handler,    /**< LPUART7 - TX and RX interrupt */
  LPUART8_Handler,    /**< LPUART8 - TX and RX interrupt */
  LPUART9_Handler,    /**< LPUART9 - TX and RX interrupt */
  LPUART10_Handler,   /**< LPUART10 - TX and RX interrupt */
  LPUART11_Handler,   /**< LPUART11 - TX and RX interrupt */
  LPUART12_Handler,   /**< LPUART12 - TX and RX interrupt */
  LPUART13_Handler,   /**< LPUART13 - TX and RX interrupt */
  LPUART14_Handler,   /**< LPUART14 - TX and RX interrupt */
  LPUART15_Handler,   /**< LPUART15 - TX and RX interrupt */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  LPI2C0_Handler,     /**< LPI2C0 - LPI2C Master Interrupt */
  LPI2C1_Handler,     /**< LPI2C1 - LPI2C Master Interrupt */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  LPSPI0_Handler,     /**< LPSPI0 - LPSPI Interrupt */
  LPSPI1_Handler,     /**< LPSPI1 - LPSPI Interrupt */
  LPSPI2_Handler,     /**< LPSPI2 - LPSPI Interrupt */
  LPSPI3_Handler,     /**< LPSPI3 - LPSPI Interrupt */
  LPSPI4_Handler,     /**< LPSPI4 - LPSPI Interrupt */
  LPSPI5_Handler,     /**< LPSPI5 - LPSPI Interrupt */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  QSPI_Handler,       /**< QSPI - TX Buffer Fill interrupt, Transfer Complete / Transaction Finished, RX Buffer Drain interrupt, Buffer Overflow / Underrun interrupt, Serial Flash Communication Error interrupt, All interrupts ORed output */
  SAI0_Handler,       /**< Synchronous Audio Interface 0 - RX interrupt,TX interrupt */
  SAI1_Handler,       /**< Synchronous Audio Interface 1 - RX interrupt,TX interrupt */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  JDC_Handler,        /**< JDC (JTAG) - Indicates new data to be read from JIN_IPS register or can be written to JOUT_IPS register */
  0,                  /**< Reserved */
  ADC0_Handler,       /**< ADC0 - End of conversion, Error interrupt, Watchdog interrupt */
  ADC1_Handler,       /**< ADC1 - End of conversion, Error interrupt, Watchdog interrupt */
  ADC2_Handler,       /**< ADC2 - End of conversion, Error interrupt, Watchdog interrupt */
  LPCMP0_Handler,     /**< LPCMP0 - Async interrupt */
  LPCMP1_Handler,     /**< LPCMP1 - Async interrupt */
  LPCMP2_Handler,     /**< LPCMP2 - Async interrupt */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  FCCU_0_Handler,     /**< Fault Collection Control Unit 0 - Interrupt request(ALARM state) */
  FCCU_1_Handler,     /**< Fault Collection Control Unit 1 - Interrupt request(miscellaneous conditions) */
  0,                  /**< Reserved */
  HSE_B_0_Handler,    /**< HSE_B exception 0 - ORed TX interrupt to MU-0 */
  HSE_B_1_Handler,    /**< HSE_B exception 1 - ORed RX interrupt to MU-0 */
  HSE_B_2_Handler,    /**< HSE_B exception 2 - ORed general purpose interrupt request to MU-0 */
  HSE_B_3_Handler,    /**< HSE_B exception 3 - ORed TX interrupt to MU-1 */
  HSE_B_4_Handler,    /**< HSE_B exception 4 - ORed RX interrupt to MU-1 */
  HSE_B_5_Handler,    /**< HSE_B exception 5 - ORed general purpose interrupt request to MU-1 */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  0,                  /**< Reserved */
  MU_A_0_Handler,     /**< MU_A exception 0 - ORed TX interrupt to MUA */
  MU_A_1_Handler,     /**< MU_A exception 1 - ORed RX interrupt to MUA */
  MU_A_2_Handler,     /**< MU_A exception 2 - ORed general purpose interrupt request to MUA */
  MU_B_0_Handler,     /**< MU_B exception 0 - ORed TX interrupt to MUB */
  MU_B_1_Handler,     /**< MU_B exception 1 - ORed RX interrupt to MUB */
  MU_B_2_Handler      /**< MU_B exception 2 - ORed general purpose interrupt request to MUB */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
*----------------------------------------------------------------------------*/
#if defined (__ICCARM__)
#pragma diag_suppress=Pe1305
#endif
#if defined ( __GNUC__ )
void __NAKED __NO_RETURN __attribute__((target("general-regs-only"))) Reset_Handler(void)
#else
void __NAKED __NO_RETURN Reset_Handler(void)
#endif
{
#ifdef INIT_STDBY_RAM
  register uint32_t cnt;
  register uint64_t *pDest;

  /* Initialize STANDBY RAM if chip comes from POR */
  if (MC_RGM->DES & MC_RGM_DES_F_POR_MASK)
  {
    /* Initialize STANDBY RAM */
    cnt = (( uint32_t)(&__STDBYRAM_SIZE)) / 8U;
    pDest = (uint64_t *)(&__STDBYRAM_START);
    while (cnt--)
    {
      *pDest = (uint64_t)0xDEADBEEFCAFEFEEDULL;
      pDest++;
    }
    MC_RGM->DES = MC_RGM_DES_F_POR_MASK; /* Write 1 to clear F_POR */
  }
#endif

  __EARLY_INIT();

  /* SP initialization is required for S32Debugger when program loaded into RAM by debugger*/
  __set_MSP((uint32_t)&__INITIAL_SP);

  SystemInit();                             /* CMSIS System Initialization */

  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}
#if defined (__ICCARM__)
#pragma diag_default=Pe1305
#endif

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
