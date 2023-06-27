

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
.globl VTABLE
.section ".startup","ax"
.thumb

/************************************************************************/
/* Startup code                     									*/
/************************************************************************/
.set VTOR_REG, 0xE000ED08
.align 2

.globl Reset_Handler
Reset_Handler:
.globl _start
_start:

    ldr r5, =0xFFFFFF
startup_loop:
    subs r5, r5, 0x1
    bne startup_loop

 mov   r0, #0
 mov   r1, #0
 mov   r2, #0
 mov   r3, #0
 mov   r4, #0
 mov   r5, #0
 mov   r6, #0
 mov   r7, #0


CH0_ENABLE       .equ    (0x40280000)
TCD0_CH0_BASE    .equ    (0x40210000)
TCD0_CH1_BASE    .equ    (0x40214000)
TCD0_CH2_BASE    .equ    (0x40218000)
DMA_MUX0_BASE    .equ    (0x40280000)
MC_ME_BASE       .equ    (0x402DC000)

    /* Configure Mode Entry Module */
    ldr R0, =0x402DC000
    
    /* clock enable of all peripherals in partition 0*/
    ldr R0, =0x402DC330
    ldr R4, =0xFFFFFFFF
    str R4, [R0]

    /* clock enable of peripheral in partition 1 */
    ldr R0, =0x402DC334
    ldr R1, =0xFFFFFFFF
    str R1, [R0]

    /* Partition clock update - Trigger the hardware process */
    ldr R0, =0x402DC304
    ldr R1, =0x00000001
    str R1, [R0]

    /* Writing Key for starting the hardware processes.
       Writes with a value other than key or inverted key are
       ignored. 
    */
    ldr R0, =0x402DC000
    ldr R1, =0x00005AF0
    str R1, [R0]

    /* Writing Inverted Key for starting the hardware processes */
    ldr R0, =0x402DC000
    ldr R1, =0x0000A50F
    str R1, [R0]

    /* DMA DTCM MemoryECC clear  */
    /* Channel 0 Enable*/
    ldr R0, =CH0_ENABLE
    ldr R1, =0x80000000
    str R1, [R0]
    
    /* Source Address */
    ldr R0, =TCD0_CH0_BASE
    /* Clear Channel DONE bit */
    mov r1, 0
    str r1, [r0]
    
    /* Memory address pointing to the source data. */
    ldr R1, =0x40290040 /*Value at this address is 0 */
    str R1,[R0, 0x20]
    
    /* Source Address Signed Offset.
       Sign-extended offset applied to the current source
       address to form the next-state value as each source
       read is completed.
    */
    ldr R1, =0x03030000 /*Source pointer will not increase */
    str R1,[R0, 0x24]

    /* Number of Bytes To Transfer Per Service Request */
    ldr R1, =0x0000F000
    str R1,[R0, 0x28]

    /* Source last address adjustment or the system memory
       address for destination address (DADDR)
       storage.*/
    ldr R1, =0x00000000
    str R1,[R0, 0x2C]

    /* Destination Address */
    ldr R1, =0x21001000
    str R1,[R0, 0x30]

    /* Destination Address Signed Offset */
    ldr R1, =0x00010008
    str R1,[R0, 0x34]

    /* Last Destination Address Adjustment */
    ldr R1, =0x00000000
    str R1,[R0, 0x38]

    /* Channel Start */
    ldr R1, =0x00020001
    str R1,[R0, 0x3C]
    
    /*Wait for Ch[0] to complete */
    ldr r5, =0xFFFFFF
loop_wait_1:
    subs r5, r5, 0x1
    bne loop_wait_1
 /* DMA SRAM ECC Clear */
    /* Channel 0 Enable*/
    ldr R0, =CH0_ENABLE
    ldr R1, =0x80000000
    str R1, [R0]
    
    /* Source Address */
    ldr R0, =TCD0_CH0_BASE
    /* Clear Channel DONE bit */
    mov r1, 0
    str r1, [r0]
    
    /* Memory address pointing to the source data. */
    ldr R1, =0x40290040 /*Value at this address is 0 */
    str R1,[R0, 0x20]
    
    /* Source Address Signed Offset.
       Sign-extended offset applied to the current source
       address to form the next-state value as each source
       read is completed.
    */
    ldr R1, =0x03030000 /*Source pointer will not increase */
    str R1,[R0, 0x24]

    /* Number of Bytes To Transfer Per Service Request */
    ldr R1, =0x00008000
    str R1,[R0, 0x28]

    /* Source last address adjustment or the system memory
       address for destination address (DADDR)
       storage.*/
    ldr R1, =0x00000000
    str R1,[R0, 0x2C]

    /* Destination Address */
    ldr R1, =0x20400000
    str R1,[R0, 0x30]

    /* Destination Address Signed Offset */
    ldr R1, =0x00010008
    str R1,[R0, 0x34]

    /* Last Destination Address Adjustment */
    ldr R1, =0x00000000
    str R1,[R0, 0x38]

    /* Channel Start */
    ldr R1, =0x00020001
    str R1,[R0, 0x3C]
    
    /*Wait for Ch[0] to complete */
    ldr r5, =0xFFFFFF
loop_wait_2:
    subs r5, r5, 0x1
    bne loop_wait_2

/*
test_loop:
        wfi
    bl test_loop
*/
    /* Zero fill the RAM bss segment */
    ldr r1, =0x21000000
    ldr r3, =0x2100FFFF
    mov r2, #0
    bl FillMemRangeR1R3withR2

    ldr r1, =INT_VECTOR_SRC_START_ADDR
    ldr r2, =INT_VECTOR_DST_START_ADDR
    ldr r3, =INT_VECTOR_SRC_END_ADDR
    bl  CopyAtR2MemRangeR1R3
    
    /* relocate vector table to RAM */
    ldr  r0, =VTOR_REG
    ldr  r1, =VTABLE
    /* ;ldr  r2, =(1 << 29) */
    /*;orr  r1, r2 *//* r1 = r1 | r2 */
    str  r1,[r0]

    /* set up stack; r13 SP*/
    ldr  r0, =_Stack_start
    msr MSP, r0

    ldr r1, =RC_DATA_SRC
    ldr r2, =RC_DATA_DEST
    ldr r3, =RC_DATA_SRC_END
    bl  CopyAtR2MemRangeR1R3

    /* Zero fill the CAAM RAM bss segment */
    ldr r1, =_bss_start
    ldr r3, =_bss_end
    mov r2, #0
    bl FillMemRangeR1R3withR2

    /* Copy functions of file HSE_Host.c into SRAM from Flash */
    bl CopyFlashToSRAMHseHost
bl SystemInit



bl main

.endf Reset_Handler

FillMemRangeR1R3withR2:
      str r2, [r1]
      add r1, r1, #4
      cmp r1, r3
      bcc FillMemRangeR1R3withR2
    bx  lr

CopyAtR2MemRangeR1R3:
    cmp r1, r3
    beq DoneCopyAt
    1:
       ldr r4, [r1]
       str r4, [r2]
       add r1, r1, #4
       add r2, r2, #4
       cmp r1, r3
       bcc 1b
    DoneCopyAt:
       bx lr
 
.section ".stack_main","aw"
.thumb
.align 4

#ifdef __STACK_SIZE
.set Stack_Size, __STACK_SIZE
#else
.set Stack_Size, 0x1000
#endif

.space Stack_Size

