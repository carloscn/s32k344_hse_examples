/*================================================================================================*/
/**
*   @file    sys_init.c
*   @version M4_SRC_SW_VERSION_MAJOR.M4_SRC_SW_VERSION_MINOR.M4_SRC_SW_VERSION_PATCH
*
*   @brief   AUTOSAR M4_SRC_MODULE_NAME - MCAL auxiliary APIs used for MCAL testing
*   @details MCAL auxiliary APIs used for MCAL testing
*            This file contains sample code only. It is not part of the production code deliverables
*   @addtogroup BUILD_ENV
*   @{
*/
/*==================================================================================================

==================================================================================================*/
/*==================================================================================================
ifdef(`M4_SRC_KEEP_REVISION_HISTORY', `dnl - DO NOT modify this M4 line!
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes

',)dnl - DO NOT modify this M4 line!
==================================================================================================*/

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
#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "sys_init.h"
#include "Mcal.h"
#include "StdRegMacros.h"
//#include "S32K344.h"
#include "hse_target.h"
#include "nvic.h"
#include "hse_mu.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define LINFLEX_NVIC_ID                59
#define NUM_MSCM_SPI_IRQ               ((uint32)240U)
#define NUM_MSCM_SPI_IRQ               ((uint32)240U)
#define MSCM_BASEADDR                  ((uint32)0x40260000UL)
#define HOST_SIUL_MIDR_VAL             ((*(volatile uint32_t *)(0x40290004U))>>(0x10U) & (0x3FFU))
#define HOST_SI_ID_S32K312             (0x138U)
#define MU_INSTANCE1_AIPS2_AVAIL       ((uint32_t)0x404EC000UL)
#define MU_INSTANCE1_AIPS2_UNAVAIL     ((uint32_t)0x40390000UL)

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
extern void HSE_ReceiveInterruptHandler(uint8 u8MuInstance);
extern void HSE_GeneralPurposeInterruptHandler(uint8 u8MuInstance);
/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

volatile uint8_t interrupt_occured = 0;

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void Enable_MU_Interrupts(void);
static void Enable_STM0_Interrupts(void);
static void EnableInterrupt(uint8 id, uint8 prio);

#ifdef GHS
void mu0ReceiveInterrupt(void);
void mu1ReceiveInterrupt(void);
void mu0GeneralPurposeInterrupt(void);
void mu1GeneralPurposeInterrupt(void);
void stm_irq(void);
#else
void mu0ReceiveInterrupt(void) __attribute__ ((interrupt ("IRQ")));
void mu1ReceiveInterrupt(void) __attribute__ ((interrupt ("IRQ")));
void mu0GeneralPurposeInterrupt(void) __attribute__ ((interrupt ("IRQ")));
void mu1GeneralPurposeInterrupt(void) __attribute__ ((interrupt ("IRQ")));
void stm_irq(void) __attribute__ ((interrupt ("IRQ")));
#endif
void Start_Stm(int t, uint8_t ps);
uint32_t Read_StmCnt(void);
void Stop_Stm(void);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
void Start_Stm(int t, uint8_t ps)
{
    if (t == 0)
    {
    	STM_0.CHANNEL[0].CCR.R = 0xFFFFFFFF; /* setup CMP for t cycles */
    }
    else
    {
        STM_0.CHANNEL[0].CMP.R = t; /* setup CMP for t cycles */
    }
    interrupt_occured = 0;
    STM_0.CHANNEL[0].CCR.R = 1;     /* Enable the Channel in channel control register */
    STM_0.CR.B.CPS = ps;            /* Set Prescaler value */
    STM_0.CR.B.TEN = 1;             /* Enable the Timer counter */
}

uint32_t Read_StmCnt(void)
{
    return ((uint32_t)STM_0.CNT.R);
}

void Stop_Stm(void)
{
    STM_0.CR.B.TEN = 0x0U;          /* Disable the Timer counter */
    STM_0.CNT.R = 0x00U;            /* setup CMP for t cycles */
    STM_0.CHANNEL[0].CCR.R = 0x0U;  /* Disable the Channel in channel control register */
    STM_0.CHANNEL[0].CMP.R = 0x00U; /* Setup CMP for 0 cycles */
}

/*-----------------------------------------------------------------------*/
/* Initialize the MC_CGM */
/*-----------------------------------------------------------------------*/
void McMe_Enable_Periph()
{
    /* STM 0 Clock Enable */
    MC_ME.PRTN1_COFB0_CLKEN.R |= (1<<29);
    /* MSCM Clock Enable */
    MC_ME.PRTN1_COFB0_CLKEN.R |= (1<<24);

    /* FXOSC Clock Enable */
    //MC_ME.PRTN1_COFB1_CLKEN.R |= (1<<21);
    /* PLL Clock Enable */
    //MC_ME.PRTN1_COFB1_CLKEN.R |= (1<<24);

    /* Mode Transition */
    MC_ME.PRTN1_PCONF.B.PCE = 1U;

    MC_ME.PRTN1_PUPD.B.PCUD = 1U;

    /* Mode Transition */
    MC_ME.CTL_KEY.B.KEY = 0x5AF0U;
    MC_ME.CTL_KEY.B.KEY = 0xA50FU;
}

/*-----------------------------------------------------------------------*/
/* Initialize & start the Xtal FXSOC=?MHz*/
/*-----------------------------------------------------------------------*/
int Init_FXOSC(void){
	uint32 timeout = 0xFFFF;

    /* FXOSC Initialization */
	FXOSC.CTRL.B.EOCV       = 0x80;			/* EOCV value = 0x80; interrupt masked*/
    FXOSC.CTRL.B.OSC_BYP    = 0;
    FXOSC.CTRL.B.COMP_EN    = 1;
    FXOSC.CTRL.B.OSCON      = 1;
    while((FXOSC.STAT.B.OSC_STAT != 1) && (timeout--)) {}
    if(timeout < 1) return 1; /*FXOSC_TIMEOUT*/
    timeout = 0xFFFF; /*reset timeout*/

    return 0; /*Success*/
}

/*-----------------------------------------------------------------------*/
/* Initialize the PLL*/
/*XSOC =16MHz, Core=160MHz, VCO=480MHz*/
/*-----------------------------------------------------------------------*/
int Init_PLL(void){
    uint32 timeout = 0xFFFF;    
    
    /* Analog PLL for Core
     * <SDMEN=0, SSCGBYP=1 => PLL in integer-only mode>
     * Fvco = Fref x (PLLDV[MFI] / PLLDV[RDIV])
     * Fclkout = Fvco / (PLLODIV_n[DIV] + 1)
     * Fvco(CORE_PLL) = 960MHz
     * f(pll_ref) = 16Mhz
     * PLLDV[RDIV] = 1
     * PLLDV[MFI] = 60d
     */
    
    if(1 == PLL.PLLSR.B.LOCK)
        goto exit;
    PLL.PLLCR.B.PLLPD    = 1;                   /* Disable PLL */
    PLL.PLLODIV[0].B.DE  = 0;                   /* Disable PLL output for A53 core */
    PLL.PLLODIV[1].B.DE  = 0;                   /* not used */

    /* PLL initialization steps */
    /* Confirm that PLLODIV_n[DE] = 0 for all dividers */
    PLL.PLLODIV[0].B.DIV = 2;                  /* PLLDIV 0 = 160 MHz */   
    PLL.PLLODIV[1].B.DIV = 1;                  /* PLLDIV 1 = 240 MHz */ 
    
	/* Set as 0 */
	PLL.PLLDV.R = 0;

    /* program following, plldv, pllfd and pllfm */
    PLL.PLLDV.B.RDIV = 1;
    PLL.PLLDV.B.MFI = 60;
    PLL.PLLDV.B.ODIV2 = 2;
	PLL.PLLFD.B.MFN = 0;

    PLL.PLLFD.B.SDMEN = 0;
    PLL.PLLFM.B.SSCGBYP = 1;                   
    PLL.PLLFM.B.STEPNO = 0;
    PLL.PLLFM.B.STEPSIZE = 0;

    PLL.PLLODIV[0].B.DE = 1;                   /* Enable PLL output */
	PLL.PLLODIV[1].B.DE = 1;                   /* Enable PLL output */
				
	PLL.PLLCR.B.PLLPD = 0;                     /* Enable PLL */

	while((PLL.PLLSR.B.LOCK != 1) && (timeout--)) {}
    if(timeout < 1) return 1; /*CORE_PLL_TIMEOUT*/
    timeout = 0xFFFF; /*reset timeout*/
exit:    
    return 0; /*Success*/
}
/*-----------------------------------------------------------------------*/
/* Initialize the MC_CGM */
/*-----------------------------------------------------------------------*/
int Init_MC_CGM(void){
#if 0
	/* PRAM Controller Config */
    PRAMC_0.PRCR1.B.FT_DIS = 0x1;
    PRAMC_1.PRCR1.B.FT_DIS = 0x1;

    /* Halt Handshake to Prevent any sequence or tarnsactions between XBAR */
    MC_CGM.MUX_0_DIV_TRIG_CTRL.R = 0x80000001;

	MC_CGM.MUX_0_CSC.B.SELCTL = 8;	/*Select PLLODIV_0 CLK */            

    MC_CGM.MUX_0_CSC.B.CLK_SW =  1;    /* Trigger the clock switch */    

    while(MC_CGM.MUX_0_CSS.B.CLK_SW  != 1) {}      /* Wait for acknowledge to be cleared*/       

    /* Disable all mux dividers */
    MC_CGM.MUX_0_DC_0.B.DE  = 0;     /*CORE_CLK*/
    MC_CGM.MUX_0_DC_1.B.DE  = 0;     /*AIPS_PLAT_CLK*/
    MC_CGM.MUX_0_DC_2.B.DE  = 0;     /*AIPS_SLOW_CLK*/
    MC_CGM.MUX_0_DC_3.B.DE  = 0;     /*HSE_CLK*/
    MC_CGM.MUX_0_DC_4.B.DE  = 0;     /*DCM_CLK*/
    MC_CGM.MUX_0_DC_5.B.DE  = 0;     /*LBIST CLK*/
    MC_CGM.MUX_0_DC_6.B.DE =  0;     /*QSPI_CLK*/
    
    while(MC_CGM.MUX_0_CSS.B.SWIP  != 0) {}    /* Verify that we don't have switching in progress*/

	MC_CGM.MUX_0_DC_0.B.DIV = (1-1);    /*CORE_CLK @ Freq 160MHz */
    MC_CGM.MUX_0_DC_1.B.DIV = (2-1);    /*AIPS_PLAT_CLK @ Freq 80MHz */    
    MC_CGM.MUX_0_DC_2.B.DIV = (4-1);    /*AIPS_SLOW_CLK @ Freq 80MHz */
	MC_CGM.MUX_0_DC_4.B.DIV = (4-1);    /*DCM_CLK @ Freq 40MHz */
    MC_CGM.MUX_0_DC_5.B.DIV = (4-1);    /*LBIST CLK @ Freq 40 MHz */
    MC_CGM.MUX_0_DC_6.B.DIV = (1-1);    /*QSPI CLK @ Freq 40 MHz */
	
	/* Configuring @ Option A - High-performance mode */
    MC_CGM.MUX_0_DC_3.B.DIV = (2-1);    /*HSE_CLK @ Freq 80MHz */
  
    /* Enable all mux dividers */
    MC_CGM.MUX_0_DC_0.B.DE  = 1;     /*CORE_CLK*/
    MC_CGM.MUX_0_DC_1.B.DE  = 1;     /*AIPS_PLAT_CLK*/
    MC_CGM.MUX_0_DC_2.B.DE  = 1;     /*AIPS_SLOW_CLK*/
    MC_CGM.MUX_0_DC_3.B.DE  = 1;     /*HSE_CLK*/
    MC_CGM.MUX_0_DC_4.B.DE  = 1;     /*DCM_CLK*/
    MC_CGM.MUX_0_DC_5.B.DE  = 1;     /*LBIST CLK*/ 
    MC_CGM.MUX_0_DC_6.B.DE =  1;     /*QSPI_CLK*/

    /* Giving an actual Trigger so that it takes affect */
    MC_CGM.MUX_0_DIV_TRIG.R = 0xFFFFFFFF;
    
    while(MC_CGM.MUX_0_DIV_UPD_STAT.B.DIV_STAT  != 0) {}  /* Wait for acknowledge to be cleared*/
#endif

    /* Enable mux1 dividers */
    MC_CGM.MUX_1_DC_0.B.DE  = 1;

    /* Clock source selection control. Required to enable STM0. */
    MC_CGM.MUX_1_CSC.B.SELCTL = 0x0;	/* Select FIRC_CLK CLK */

    MC_CGM.MUX_1_CSC.B.CLK_SW =  1;     /* Trigger the clock switch */

    while(MC_CGM.MUX_1_CSS.B.CLK_SW  != 1) {}      /* Wait for acknowledge to be cleared*/

    while(MC_CGM.MUX_1_CSS.B.SWIP  != 0) {}       /* Verify that clock switch completed*/

    return 0; /*Success*/
}
/*
 * Enable ISR
 */
static void EnableInterrupt(uint8 id, uint8 prio)
{

    NVIC_EnableIRQ(id);
    NVIC_SetPriority(id, prio);
}

void stm_irq(void)
{
    STM_0.CHANNEL[0].CIR.R = 1;
    Stop_Stm();
    interrupt_occured = 1;
    EXIT_INTERRUPT();
}
///*
// * MU0 Receive Interrupt
// */
//void mu0ReceiveInterrupt(void)
//{
//	HSE_ReceiveInterruptHandler(0);
//}
//
///*
// * MU1 Receive Interrupt
// */
//void mu1ReceiveInterrupt(void)
//{
//	HSE_ReceiveInterruptHandler(1);
//}
//
///*
// * MU0 General Purpose Interrupt
// */
//void mu0GeneralPurposeInterrupt(void)
//{
//    HSE_GeneralPurposeInterruptHandler(0);
//}
//
///*
// * MU1 General Purpose Interrupt
// */
//void mu1GeneralPurposeInterrupt(void)
//{
//    HSE_GeneralPurposeInterruptHandler(1);
//}

/*
 * Enable MU Interrupts
 */
static void Enable_MU_Interrupts(void)
{
    uint8 MU0_ReceiveInterrupt_ID;
    uint8 MU1_ReceiveInterrupt_ID;
    uint8 MU2_ReceiveInterrupt_ID;
    uint8 MU3_ReceiveInterrupt_ID;

    uint8 MU0_GeneralPurposeInterrupt_ID;
    uint8 MU1_GeneralPurposeInterrupt_ID;
    uint8 MU2_GeneralPurposeInterrupt_ID;
    uint8 MU3_GeneralPurposeInterrupt_ID;



 /* M7 - NVIC */
    /* MU0 - 103 (tx) 104 (rx) 105 (general) */
    MU0_ReceiveInterrupt_ID = 193;
    MU0_GeneralPurposeInterrupt_ID = 194;

    /* MU1 - 106 (tx) 107 (rx) 108 (general) */
    MU1_ReceiveInterrupt_ID = 196;
    MU1_GeneralPurposeInterrupt_ID = 197;

    /* MU2 - 109 (tx) 110 (rx) 111 (general) */
    MU2_ReceiveInterrupt_ID = 210;
    MU2_GeneralPurposeInterrupt_ID = 211;

    /* MU3 - 112 (tx) 113 (rx) 114 (general) */
    MU3_ReceiveInterrupt_ID = 213;
    MU3_GeneralPurposeInterrupt_ID = 214;

     /* Enable Receive Interrupts */
    EnableInterrupt(MU0_ReceiveInterrupt_ID, 0xF0);
    //RegisterInterruptHandler(MU0_ReceiveInterrupt_ID, mu0ReceiveInterrupt);

    EnableInterrupt(MU1_ReceiveInterrupt_ID, 0xF0);
    //RegisterInterruptHandler(MU1_ReceiveInterrupt_ID, mu1ReceiveInterrupt);

    EnableInterrupt(MU2_ReceiveInterrupt_ID, 0xF0);
    //RegisterInterruptHandler(MU2_ReceiveInterrupt_ID, mu2ReceiveInterrupt);

    EnableInterrupt(MU3_ReceiveInterrupt_ID, 0xF0);
    //RegisterInterruptHandler(MU3_ReceiveInterrupt_ID, mu3ReceiveInterrupt);

    /* Enable General Purpose Interrupts */
    EnableInterrupt(MU0_GeneralPurposeInterrupt_ID, 0xFF);
    //RegisterInterruptHandler(MU0_GeneralPurposeInterrupt_ID, mu0GeneralPurposeInterrupt);

    EnableInterrupt(MU1_GeneralPurposeInterrupt_ID, 0xFF);
    //RegisterInterruptHandler(MU1_GeneralPurposeInterrupt_ID, mu1GeneralPurposeInterrupt);

    EnableInterrupt(MU2_GeneralPurposeInterrupt_ID, 0xFF);
    //RegisterInterruptHandler(MU2_GeneralPurposeInterrupt_ID, mu2GeneralPurposeInterrupt);

    EnableInterrupt(MU3_GeneralPurposeInterrupt_ID, 0xFF);
    //RegisterInterruptHandler(MU3_GeneralPurposeInterrupt_ID, mu3GeneralPurposeInterrupt);


}

static void Enable_STM0_Interrupts(void)
{
	uint8 stm0_ReceiveInterrupt_ID;

	//STM0 all channels
    stm0_ReceiveInterrupt_ID = 39;
    //Enable STM0 interrupts
    EnableInterrupt(stm0_ReceiveInterrupt_ID,0xF0);
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

//extern ISR(LINFLEX_SCI_Isr_UART_TX);

///*
// * system initialization : system clock, interrupt router ...
// */
//
//__attribute__ ((section (".systeminit")))
//
//void SystemInit(void)
//{
//	uint32 i = 0U;
//	volatile short *mscm_addr;
//    u32BaseAddr[1U] = (HOST_SIUL_MIDR_VAL==HOST_SI_ID_S32K312)? MU_INSTANCE1_AIPS2_UNAVAIL:MU_INSTANCE1_AIPS2_AVAIL;
//    NVIC_SetPriorityGrouping(0); /* 0 means 7 bits for prio, 1 for sub-prio */
//    /**< NONBASETHRDENA = 1; processor can enter Thread mode from any level under the control of an EXC_RETURN value.*/
//    S32_SCB->CCR |=  1;
//    /** Set PendSV priority set to 0, to ensure the software triggered interrupt, for user mode entry,*/
//    REG_BIT_CLEAR32(&(S32_SCB->SHPR3), S32_SCB_SHPR3_PRI_14_MASK);
//
//    McMe_Enable_Periph();
//#if 0
//    Init_FXOSC();
//    Init_PLL();
//#endif
//
//    Init_MC_CGM();
//
//    /* fill the interrupts_vector with the default interrupt routine */
//    for(i=0U; i < NUM_MSCM_SPI_IRQ; i++)
//    {
//        /* Route the interrupt lines to all three cores. */
//        mscm_addr  = (volatile short*)(MSCM_BASEADDR + 0x880U + (i*2));
//        *mscm_addr = 0x0007U;
//    }
//
//    /* Setup all the needed interrupts(and their priorities) */
//    sys_disableAllInterrupts();
//
//    /* Enable MU Interrupts */
//    Enable_MU_Interrupts();
//
//    /* Enable STM0 Interrupt */
//    Enable_STM0_Interrupts();
//
//    /* Enable external Interrupts */
//    sys_enableAllInterrupts();
//
//    //clear functional reset counter
//    MC_RGM.FREC.B.FREC = 0xFU;
//}

/**
* @brief sys_init
* @details function used to enable all interrupts
*/
void sys_enableAllInterrupts(void)
{
    ResumeAllInterrupts();
}
/**
* @brief sys_init
* @details function used to disable all interrupts
*/
void sys_disableAllInterrupts(void)
{
    SuspendAllInterrupts();
}

void default_interrupt_routine(void)
{
    while (1);

}
void NMI_Handler(void)
{
    while(1);
}
void HardFault_Handler(void)
{
    while(1);
}
void MemManage_Handler(void)
{
    while(1);
}
void BusFault_Handler(void)
{
    while(1);
}
void UsageFault_Handler(void)
{
    while(1);
}
void SVC_Handler(void)
{
    while(1);
}
void DebugMon_Handler(void)
{
    while(1);
}
void PendSV_Handler(void)
{
    while(1);
}
void SysTick_Handler(void)
{
    while(1);
}
void undefined_handler(void)
{
   while(1);
}
/*================================================================================================*/

#ifdef __cplusplus
}
#endif
