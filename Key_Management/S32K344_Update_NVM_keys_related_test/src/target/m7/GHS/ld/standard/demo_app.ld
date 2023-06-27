/*==================================================================================================
*
*   Copyright 2020-2021 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with 
*   the applicable license terms. By expressly accepting such terms or by downloading, installing, 
*   activating and/or otherwise using the software, you are agreeing that you have read, and that 
*   you agree to comply with and are bound by, such license terms. If you do not agree to 
*   be bound by the applicable license terms, then you may not retain, install, activate or 
*   otherwise use the software.
==================================================================================================*/


DEFAULTS
{
    DEMO_APP_BSS_MEM_START=0x21001000 ;
    DEMO_APP_BSS_SIZE = 56K;

    IVT_START_ADDR = 0x20400000 ;
    IVT_SIZE = 256;   

    ADKP_START_ADDR = IVT_START_ADDR + IVT_SIZE;
    ADKP_SIZE = 16;

    DEMO_APP_SRAM_START_ADDR = 0x20401000;
    DEMO_APP_SRAM_SIZE = 24K;
    HSE_FW_VERSION_START_ADDR = DEMO_APP_SRAM_START_ADDR + DEMO_APP_SRAM_SIZE;
    HSE_FW_VERSION_SIZE =32;
    TEST_STATUS_START_ADDR = HSE_FW_VERSION_START_ADDR + HSE_FW_VERSION_SIZE;
    TEST_STATUS_START_LENGTH = 0x4;
    TEST_STATUS_EXECUTED_ADDR = TEST_STATUS_START_ADDR + TEST_STATUS_START_LENGTH;
    TESTEXECUTED_LENGTH = 0x4;
    TESTCOMPLETED_START_ADDR = TEST_STATUS_EXECUTED_ADDR + TESTEXECUTED_LENGTH;
}

MEMORY {
    /* code flash area and data flash area for application given below resepectively */
    flash_memory         : org = 0x00402000,/*0x00434000,*/ len = 0x18000   /* code section for demo app, 12 sectors */
    int_sram             : org = DEMO_APP_BSS_MEM_START, len = DEMO_APP_BSS_SIZE    /* 4KB reserved for flash driver used in scripts */
    ivt_addr             : org = IVT_START_ADDR, len = IVT_SIZE     /*fixed address for IVT structure*/
    adkp_key             : org = ADKP_START_ADDR, len = ADKP_SIZE      /*fixed address for key input by user*/
    APP_CODE_SRAM        : org = DEMO_APP_SRAM_START_ADDR, len = DEMO_APP_SRAM_SIZE    /* Secure ram memory */
    HSE_FW_VERSION       : org = HSE_FW_VERSION_START_ADDR, len = HSE_FW_VERSION_SIZE
    TESTSTATUS           : org = TEST_STATUS_START_ADDR, len = TEST_STATUS_START_LENGTH
    TESTEXECUTED         : org = TEST_STATUS_EXECUTED_ADDR, len = TESTEXECUTED_LENGTH
    TESTCOMPLETED        : org = TESTCOMPLETED_START_ADDR, len = 0x1
}


/**
 Program layout for starting in ROM, copying data to RAM,
 and continuing to execute out of ROM.
*/

SECTIONS
{
    
/***********************************************************************************************************************************************/
/*                              RAM SECTIONS                                                                                                   */
/***********************************************************************************************************************************************/
    .bss                                            : > int_sram
    .data                                ALIGN(8)   : > .
    .stack_main  ALIGN(16)                          : > .
     _Stack_end    = addr(.stack_main);
    _Stack_start  = addr(.stack_main)+sizeof(.stack_main);   
    
    
/***********************************************************************************************************************************************/
/*                              ROM SECTIONS                                                                                                   */
/***********************************************************************************************************************************************/
    ._intc_vector_start_                ALIGN(8)            : > flash_memory    
    .ROM.intc_vector                      ROM(.intc_vector)     : > .
    ._intc_vector_end_                  ALIGN(8)                    : > .
    
    .startup                                                    : > ./* Reset code */
    .systeminit                                             : > ./* SystemInit */
    .text.startup                                               : > .
    .text                                                       : > .
    .rodata                                                     : > .
    
    ._const_flash_driver_flash_start_     ALIGN(8)                  : > .
    .ROM.flash_driver_text                ROM(.flash_driver_text)   : > .
    ._const_flash_driver_flash_end_       ALIGN(8)                  : > .


    ._const_hse_host_send_start_     ALIGN(8)                       : > .
    .ROM.hse_host_send_text          ROM(.hse_host_send_text)       : > .
    .ROM.hse_host_send_rodata        ROM(.hse_host_send_rodata)     : > .
    ._const_hse_host_send_end_       ALIGN(8)                       : > .
 
    
    .ROM.data                        ROM(.data) ALIGN(4)            : > .
    
    
/***********************************************************************************************************************************************/
/*                              RAM SECTIONS                                                                                                   */
/***********************************************************************************************************************************************/
    ._HSERAM_start                                        : > APP_CODE_SRAM

    .intc_vector              : > .
    
    ._const_flash_driver_ram_start_      ALIGN(8)         : > .    
    .flash_driver_text                                    : { FlashErase.o(.text)  FlashProgram.o(.text) } > .
    ._const_flash_driver_ram_end_        ALIGN(8)         : > .

    


    ._const_hse_host_send_ram_start_     ALIGN(8)         : > .    
    .hse_host_send_text                                   : { hse_host.o(.text)   "hse_mu*(.text)" } > .
    .hse_host_send_rodata                                 : { hse_host.o(.rodata) "hse_mu*(.rodata)"  } > .
    ._const_hse_host_send_ram_end_       ALIGN(8)         : > .

    

/*******************************************************************************/
/*                              RAM SECTION FOR ADKP KEY                       */
/*******************************************************************************/
    ._adkp_key                                        : > adkp_key
    
    ADKP_RAM_START          = ADDR(._adkp_key);
    ADKP_DATA_SIZE          = 16;
    ADKP_RAM_END            = ADKP_RAM_START + ADKP_DATA_SIZE; 
    
    /*******************************************************************************/
/*                              RAM SECTION FOR IVT                           */
/*******************************************************************************/
    .ivt                                            : > ivt_addr
    IVT_RAM_START          = ADDR(.ivt);
    IVT_AND_APP_DATA_SIZE  = 0x100 + 0x1000;
    APP_RAM_END            = IVT_RAM_START + IVT_AND_APP_DATA_SIZE;

    .fwversion                                       : > HSE_FW_VERSION
    .teststatus                                      : > TESTSTATUS
    .testexecuted                                    : > TESTEXECUTED
    .testcompleted                                   : > TESTCOMPLETED
/***********************************************************************************************************************************************/
/*                              SYMBOLS                                                                                                        */
/***********************************************************************************************************************************************/

    INT_SRAM_START          = ADDR(int_sram);
    _bss_start              = ADDR(.bss);
    _bss_end                = ADDR(.bss) + SIZEOF(.bss);   // Init 4 bytes at a time
      
    RC_DATA_SRC             = ADDR(.ROM.data);
    RC_DATA_DEST            = ADDR(.data);
    RC_DATA_SIZE            = SIZEOF(.data);
    RC_DATA_SRC_END         = RC_DATA_SRC + RC_DATA_SIZE ;

    INT_VECTOR_DST_START_ADDR   = ADDR(.intc_vector);
    INT_VECTOR_SRC_START_ADDR   = ADDR(._intc_vector_start_);
    INT_VECTOR_SRC_END_ADDR = INT_VECTOR_SRC_START_ADDR + SIZEOF(.intc_vector);
      
    FLASH_DRIVER_RAM_DST_START_ADDRESS   = addr(._const_flash_driver_ram_start_); /*Start Address in HSE RAM for flash driver to be copied to*/
    FLASH_DRIVER_FLASH_SRC_START_ADDRESS = addr(._const_flash_driver_flash_start_); /*Start Address in flash for flash drivera to be copied from*/
    FLASH_DRIVER_FLASH_SRC_END_ADDRESS   = addr(._const_flash_driver_flash_end_); /*End Address in flash for flash driver to be copied from*/
    
    HSE_HOST_RAM_DST_START_ADDR       = addr(._const_hse_host_send_ram_start_);
    HSE_HOST_FLASH_SRC_START_ADDR     = addr(._const_hse_host_send_start_);
    HSE_HOST_FLASH_SRC_END_ADDR       = addr(._const_hse_host_send_end_);
}

