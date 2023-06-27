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
#ifndef _FLS_TYPE_H_
#define _FLS_TYPE_H_

#include "Platform_Types.h"
#include "host_soc_fls_type.h"
/*==================================================================================================
                                 DEFINE TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 STANDARD TYPEDEFS
==================================================================================================*/
#ifndef TRUE
    /** 
    * @brief Boolean true value
    */
    #define TRUE 1
#endif
#ifndef FALSE
    /** 
    * @implements TRUE_FALSE_enumeration
    */
    #define FALSE 0
#endif
#ifndef STD_ON
    /** 
    * @brief Boolean STD_ON value
    */
    #define STD_ON 1
#endif
#ifndef STD_OFF
    /** 
    * @brief Boolean STD_OFF value
    */
    #define STD_OFF 0
#endif
#ifndef NULL_PTR
    /** 
    * @brief NULL_PTR value
    */
    #define NULL_PTR ((void *)0)
#endif


/*==================================================================================================
                                 ENUM TYPEDEFS
==================================================================================================*/
typedef enum                             
{                                      
    FLS_WRITE_DOUBLE_WORD = 8U,    /* Support to write double word mode */
    FLS_WRITE_PAGE        = 32U,   /* Support to write page mode */
    FLS_WRITE_QPAGE       = 128U   /* Support to write quad page mode */
} Fls_ProgSizeType;
/**
    @brief Enumeration of checking status errors or not.
*/
typedef enum
{
    FLS_JOB_OK                = 0x5AA5U,    /* Successful job */
    FLS_JOB_FAILED            = 0x27E4U,    /* Errors because of failed hardware */
    FLS_TIMEOUT_FAILED        = 0x2BD4U,    /* Errors because of failed timeout */
    FLS_INPUT_PARAM_FAILED    = 0x2DB4U,    /* Errors because of input parma */
    FLS_BLANK_CHECK_FAILED    = 0x2E74U,    /* Errors because of failed blank check */
    FLS_PROGRAM_VERIFY_FAILED = 0x33CCU,    /* Errors because of failed program verify */
    FLS_USER_TEST_BREAK_SBC   = 0x35ACU,    /* Break single bit correction */
    FLS_USER_TEST_BREAK_DBD   = 0x366CU     /* Break double bit detection */
} Fls_CheckStatusType;
/**
* @brief the number of bytes uses to compare.    
*
*/
typedef enum
{
    FLS_SIZE_1BYTE = 1U,
    FLS_SIZE_4BYTE = 4U
} Fls_DataBytesType;
/**
    @brief Enumeration of Getting status of lock bits .
*/
typedef enum
{
    FLS_UNPROTECT_SECTOR        = 0xD42BU,
    FLS_PROTECT_SECTOR          = 0xD81BU,
    FLS_NO_CHECK_PROTECT_SECTOR = 0xE187U
} Fls_GetStatusLockBitType;
/**
    @brief Enumeration of Array Integrity Sequence(proprietary sequence or sequential) .
*/
typedef enum
{
    FLS_PROPRIETARY_SEQENCE = 0U,
    FLS_SEQUENTIAL
} Fls_ArrayIntegritySequenceType;
/**
    @brief Enumeration of Blocks of memory flash .
*/
typedef enum
{
    FLS_BLOCK_0  = 0U,
    FLS_BLOCK_1  = 0x100000U,
    FLS_BLOCK_2  = 0x200000U,
    FLS_BLOCK_3  = 0x300000U,
    FLS_BLOCK_4  = 0x10000000U,
    FLS_UTEST    = 0x1B000000U
} Fls_FlashBlocksType;

/**
    @brief Enumeration breakpoints .
*/
typedef enum
{
    FLS_BREAKPOINTS_ON_DBD = 0U,
    FLS_BREAKPOINTS_ON_DBD_SBC,
    FLS_NO_BREAKPOINTS
} Fls_FlashBreakPointsType;

/**
    @brief Main or Alternate interfaces / express program.
*/
typedef enum
{
    FLS_MAIN_INTERFACE      = 0U,    /* Using main interface */
    FLS_ALTERNATE_INTERFACE = 1U     /* Using alternate interface  */
} Fls_InterfaceAccessType;

/*==================================================================================================
                                 STRUCTURES TYPEDEFS
==================================================================================================*/

/* FLS Configuration Structure */
typedef struct
{
   boolean Fls_bEnableTimeOut;                            /* Enable to use timeout when waiting for the Done bit of not(STD_ON/STD_OFF)*/
   uint32 Fls_u32ValueWaitDoneBitOrDomainIDsTimeOut;      /* value the timeout to wait for the Done bit or Domain IDs(this field will be used when Fls_EnableTimeOut is enabled )*/
   const uint32 *Fls_pAllSectors;                         /* All the sectors need Ex:  AllSectors[2] ={ FLS_CODE_ARRAY_0_BLOCK_3_S499, FLS_CODE_ARRAY_0_BLOCK_3_S503}*/
   uint32 Fls_u32NumberOfconfiguredSectors;               /* Number of the configured sectors (ex: 5 sectors so will fill this field = 5 )*/
   Fls_InterfaceAccessType Fls_InterfaceAccess;           /* FLS_MAIN_INTERFACE: Use APIs for main interface (the application cores) and FLS_ALTERNATE_INTERFACE use APIs for alter interface (the HSE core) */
} FLASH_CONFIG;


#endif  /* _FLS_TYPE_H_ */
