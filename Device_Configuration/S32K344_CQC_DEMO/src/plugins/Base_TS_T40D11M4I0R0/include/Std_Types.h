/**
*   @file    Std_Types.h
*   @implements     Std_Types.h_Artifact
*   @version 0.4.0
*
*   @brief   AUTOSAR Base - Standard types definition.
*   @details AUTOSAR standard types header file. It contains all types that are used across several
*                modules of the basic software and that are platform and compiler independent
*
*/
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

/*==================================================================================================
==================================================================================================*/

/**
* @page misra_violations MISRA-C:2004 violations
*
*
* @section Std_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Std_Types_h_REF_2
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for identifiers
*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Platform_Types.h"
/**
* @brief Include compiler abstraction
* @violates @ref Std_Types_h_REF_1 MISRA 2004 Required Rule 19.15, Precautions shall be taken in
* order to prevent the contents of a header being included twice.
*/
#include "Compiler.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the standard types header file and also in the
*        module's description file
*/
//#define DISABLE_MCAL_INTERMODULE_ASR_CHECK
//#define PLATFORM_AR_RELEASE_MAJOR_VERSION  4
#define STD_VENDOR_ID                     43
/*
 * @violates @ref Std_Types_h_REF_2 This is required as per autosar Requirement, 
 */
#define STD_AR_RELEASE_MAJOR_VERSION      4
/*
 * @violates @ref Std_Types_h_REF_2 This is required as per autosar Requirement, 
 */
#define STD_AR_RELEASE_MINOR_VERSION      2
/*
 * @violates @ref Std_Types_h_REF_2 This is required as per autosar Requirement, 
 */
#define STD_AR_RELEASE_REVISION_VERSION   2
#define STD_SW_MAJOR_VERSION              0
#define STD_SW_MINOR_VERSION              4
#define STD_SW_PATCH_VERSION              0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Platform_Types header file are of the same Autosar version */
#if ((STD_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || (STD_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Std_Types.h and Platform_Types.h are different"
#endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Compiler header file are of the same Autosar version */
#if ((STD_AR_RELEASE_MAJOR_VERSION != COMPILER_AR_RELEASE_MAJOR_VERSION) || \
    (STD_AR_RELEASE_MINOR_VERSION != COMPILER_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Std_Types.h and Compiler.h are different"
#endif
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/**
* @brief Physical state 5V or 3.3V
* @implements SymbolDefinitions_enumeration
*/
#define STD_HIGH    0x01

/**
* @brief Physical state 0V.
* @implements SymbolDefinitions_enumeration
*/
#define STD_LOW     0x00

/**
* @brief Logical state active.
* @implements SymbolDefinitions_enumeration
*/
#define STD_ACTIVE  0x01

/**
* @brief Logical state idle.
* @implements SymbolDefinitions_enumeration
*/
#define STD_IDLE    0x00

/**
* @brief ON State.
* @implements SymbolDefinitions_enumeration
*/
#define STD_ON      0x01

/**
* @brief OFF state.
* @implements SymbolDefinitions_enumeration
*/
#define STD_OFF     0x00

/**
* @brief Return code for failure/error.
* @implements SymbolDefinitions_enumeration
*/
#define E_NOT_OK    0x01

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid
*        name clashes and redefinition problems, the symbols have to be defined in the following way
*       (approved within implementation).
*/
#ifndef STATUSTYPEDEFINED
    #define STATUSTYPEDEFINED
    /**
    * @brief Success return code
    */
    #define E_OK      0x00
    /**
    * @brief This type is defined for OSEK compliance.
    */
    typedef unsigned char StatusType;
#endif

/**
* @brief This type can be used as standard API return type which is shared between the RTE and the
*        BSW modules.
* @implements Std_ReturnType_type
*/
typedef uint8 Std_ReturnType;

/**
* @brief This type shall be used to request the version of a BSW module using the
*       "ModuleName"_GetVersionInfo() function.
* @implements Std_VersionInfoType_structure
*/
typedef struct
{
    uint16  vendorID;               /**< @brief vendor ID */
    uint16  moduleID;               /**< @brief BSW module ID */
    uint8   sw_major_version;       /**< @brief BSW module software major version */
    uint8   sw_minor_version;       /**< @brief BSW module software minor version */
    uint8   sw_patch_version;       /**< @brief BSW module software patch version */
} Std_VersionInfoType;

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STD_TYPES_H */

/** @} */
