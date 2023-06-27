#ifndef _FLS_API_H_
#define _FLS_API_H_

#include"Fls_type.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
extern Fls_CheckStatusType FlashInit ( const FLASH_CONFIG *pConfig );
extern Fls_CheckStatusType ClearLock( uint32 Fls_VirtualSectors, uint8 u8DomainIdValue );
extern Fls_GetStatusLockBitType GetLock( uint32 Fls_VirtualSectors );
extern Fls_CheckStatusType SetLock( uint32 Fls_VirtualSectors, uint8 u8DomainIdValue);
extern uint32 GetBaseAddressOfSector( uint32 Fls_VirtualSectors);
extern Fls_CheckStatusType FlashErase ( volatile uint32 u32LogicalAddress , const uint32 u32Length, boolean bEnableBlankCheckAfterErasing, uint8 u8DomainIdValue);
extern Fls_CheckStatusType FlashEraseAlternate ( volatile uint32 u32LogicalAddress , const uint32 u32Length, boolean bEnableBlankCheckAfterErasing, uint8 u8DomainIdValue);
extern Fls_CheckStatusType FlashProgram 
(
    volatile uint32 u32LogicalAddress, const uint8 *pSourceAddressPtr, uint32 u32Length, boolean bEnableBlankCheckBeforeWriting, boolean bProgramVerifyAfterWriting, uint8 u8DomainIdValue
);
extern Fls_CheckStatusType BlankCheck ( volatile uint32 u32LogicalAddress, uint32 u32Length);
extern Fls_CheckStatusType ProgramVerify ( volatile uint32 u32LogicalAddress ,const uint8 *pSourceAddressPtr, uint32 u32Length);
extern Fls_CheckStatusType FlashExpressProgram 
(
    volatile uint32 u32LogicalAddress, const uint8 *pSourceAddressPtr, uint32 u32Length, boolean bEnableBlankCheckBeforeWriting, boolean bProgramVerifyAfterWriting, uint8 u8DomainIdValue
);
extern Fls_CheckStatusType FlashProgramAlternate
(
    volatile uint32 u32LogicalAddress, const uint8 *pSourceAddressPtr, uint32 u32Length, boolean bEnableBlankCheckBeforeWriting, boolean bProgramVerifyAfterWriting, uint8 u8DomainIdValue
);
extern Fls_CheckStatusType FlashArrayIntegrityCheck
( 
    Fls_FlashBlocksType eSelectBlock,
    const uint8 *pMisrRegDesiredValues, 
    const uint8 *pMisrExpectValues,
    Fls_ArrayIntegritySequenceType eAddressSequence,
    Fls_FlashBreakPointsType eBreakPoints
);
extern Fls_CheckStatusType SetLockHseCore( uint32 Fls_VirtualSectors, uint8 DomainIdOfHseCore);
extern Fls_CheckStatusType ClearAllErrorFlags(void);
/*==================================================================================================
*                                    GLOBAL VARIABLES
==================================================================================================*/
extern boolean bEnableTimeOut;
extern uint32 u32ValueWaitDoneBitOrDomainIDsTimeOut;
extern const uint32 *pAllSectors;
extern uint32 u32NumberOfconfiguredSectors;
extern uint8 u8SecureCounter;
extern Fls_InterfaceAccessType eInterfaceAccess;

#endif  /* _FLS_API_H_ */
