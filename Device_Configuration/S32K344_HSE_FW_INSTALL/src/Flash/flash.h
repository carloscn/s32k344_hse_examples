/******************************************************************************
 * (c) Copyright 2018-2019, NXP Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      flash.h
 * @brief     Embedded Flash Memory (FLASH) driver header file.
 ******************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "S32K344_FLASH.h"
#include "S32K344_PFLASH.h"

/******************************************************************************
* Flash error conditions
*
*//*! @addtogroup flash_status
* @{
*******************************************************************************/
/*! tFLASH_STATUS type declaration                                            */
typedef enum
{
  FLASH_RE_ST   = (uint32_t)(1UL <<  0),  ///< Reset Error status
  FLASH_TSP_ST  = (uint32_t)(1UL <<  8),  ///< UTest NVM Program and Erase Lock status
  FLASH_WDI_ST  = (uint32_t)(1UL << 12),  ///< Watchdog Timer had expired status
  FLASH_PEG_ST  = (uint32_t)(1UL << 14),  ///< Program/Erase Good status (set if PGM/ERS operation was successful, cleared otherwise)
  FLASH_DONE_ST = (uint32_t)(1UL << 15),  ///< State Machine status
  FLASH_PES_ERR = (uint32_t)(1UL << 16),  ///< Program and Erase Sequence error
  FLASH_PEP_ERR = (uint32_t)(1UL << 17),  ///< Program and Erase Protection error
  FLASH_RWE_ERR = (uint32_t)(1UL << 20),  ///< Read-While-Write Event error
  FLASH_RRE_ERR = (uint32_t)(1UL << 24),  ///< Read Reference error
  FLASH_RVE_ERR = (uint32_t)(1UL << 25),  ///< Read Voltage error
  FLASH_EEE_ERR = (uint32_t)(1UL << 28),  ///< EDC after ECC error
  FLASH_AEE_ERR = (uint32_t)(1UL << 29),  ///< Address Encode error
  FLASH_SBC_ERR = (uint32_t)(1UL << 30),  ///< Single Bit Correction error
  FLASH_EER_ERR = (uint32_t)(1UL << 31)   ///< ECC Event error
} tFLASH_STATUS;
/*! @} End of flash_status                                                    */

/******************************************************************************
* Flash express error conditions
*
*//*! @addtogroup flash_xstatus
* @{
*******************************************************************************/
/*! tFLASH_XSTATUS type declaration                                           */
typedef enum
{
  FLASH_XWDI_ST = (uint32_t)(1UL << 12),  ///< Watchdog Timer for Express Program had expired status
  FLASH_XDOK_ST = (uint32_t)(1UL << 13),  ///< Express Data OK status
  FLASH_XPEG_ST = (uint32_t)(1UL << 14),  ///< Express Program Good status (set if XPGM operation was successful, cleared otherwise)
  FLASH_XDONE_ST= (uint32_t)(1UL << 15)   ///< Express State Machine status
} tFLASH_XSTATUS;
/*! @} End of flash_xstatus                                                   */

/******************************************************************************
* Crash Log Data type
*
*//*! @addtogroup flash_crash_log
* @{
*******************************************************************************/
/*! tCRASHLOG_RECORDS type declaration                                        */
typedef uint32_t tCRASH_LOG[128];         ///< Crash log records
/*! @} End of flash_crash_log                                                 */

/******************************************************************************
* Watchdog operating modes
*
*//*! @addtogroup flash_wdog_modes
* @{
*******************************************************************************/
#define FLASH_WDOG_4E2CLKS  (uint8_t)0x0  ///< Watchdog enabled and timeout set to 400 clocks (default)
#define FLASH_WDOG_2E2CLKS  (uint8_t)0x2  ///< Watchdog enabled and timeout set to 200 clocks
#define FLASH_WDOG_4E3CLKS  (uint8_t)0x4  ///< Watchdog enabled and timeout set to 4000 clocks
#define FLASH_WDOG_4E4CLKS  (uint8_t)0x6  ///< Watchdog enabled and timeout set to 40000 clocks
#define FLASH_WDOG_DISABLE  (uint8_t)0x1  ///< Watchdog disabled
/*! @} End of flash_wdog_modes                                               */

/******************************************************************************
* FLASH function and macro definitions
*
*//*! @addtogroup flash_macro
* @{
*******************************************************************************/
/***************************************************************************//*!
 * @brief   Initiates express program sequence.
 * @details This macro initiates express program sequence.
 * @param   dst   Pointer to flash memory (const void *).
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_WriteXPEADR(dst)  do{ PFLASH->PFCPGM_XPEADR_L=(uint32_t)dst; }while(0)

/***************************************************************************//*!
 * @brief   Returns Domain ID of the core that has started the express program
 *          sequence.
 * @details This macro returns Domain ID of the core that has started the
 *          express program sequence.
 * @return  uint8_t  Domain ID; 0xff is returned if flash interface is idle
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_GetXPEID()  ((FLASH->XMCR&FLASH_XMCR_XPEID_MASK)>>FLASH_XMCR_XPEID_SHIFT)

/***************************************************************************//*!
 * @brief   Returns express program interface status.
 * @details This macro returns express program interface status.
 * @return  @ref tFLASH_XSTATUS.
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_GetXStatus()                                                    \
  (tFLASH_XSTATUS)(FLASH->XMCR&(FLASH_XWDI_ST|FLASH_XDOK_ST|FLASH_XPEG_ST|FLASH_XDONE_ST))

/***************************************************************************//*!
 * @brief   Initiates program or erase sequence.
 * @details This macro initiates program or erase sequence.
 * @param   dst   Pointer to flash memory (const void *).
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_WritePEADR(dst)  do{ PFLASH->PFCPGM_PEADR_L=(uint32_t)dst; }while(0)

/***************************************************************************//*!
 * @brief   Returns Domain ID of the core that has started the program or erase
 *          sequence.
 * @details This macro returns Domain ID of the core that has started the
 *          program or erase sequence.
 * @return  uint8_t  Domain ID; 0xff is returned if flash interface is idle.
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_GetPEID()  ((FLASH->MCR&FLASH_MCR_PEID_MASK)>>FLASH_MCR_PEID_SHIFT)

/***************************************************************************//*!
 * @brief   Returns main program and erase interface status.
 * @details This macro returns main program and erase interface status.
 * @return  @ref tFLASH_STATUS.
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_GetStatus()  (tFLASH_STATUS)FLASH->MCRS

/***************************************************************************//*!
 * @brief   Clears main program and erase interface status.
 * @details This macro clears main program and erase interface status.
 * @param   mask  Mask of @ref FLASH_EER_ERR|@ref FLASH_SBC_ERR|@ref FLASH_AEE_ERR|
 *                        @ref FLASH_EEE_ERR|@ref FLASH_RVE_ERR|@ref FLASH_RRE_ERR|
 *                        @ref FLASH_RWE_ERR|@ref FLASH_PEP_ERR|@ref FLASH_PES_ERR.
 * @note    Implemented as a macro.
 ******************************************************************************/
#define FLASH_ClrStatus(mask)  do{ FLASH->MCRS=mask; }while(0)

/***************************************************************************//*!
 * @brief   Configures watchdog operation.
 * @details This macro configures watchdog operation. It uses alternate program
 *          and erase interface.
 * @param   mode  One of @ref flash_wdog_modes.
 * @note    Implemented as a macro.
 * @warning Because it uses alternate program and erase interface, calling this 
 *          macro on S32K2TV secured samples will cause bus error.
 ******************************************************************************/
#define FLASH_ConfigWatchdog(mode)                                            \
    REG_RMW32(FLASH_ALT->AMCR,FLASH_AMCR_WDD_MASK|FLASH_AMCR_WDT_MASK,((mode)<<FLASH_AMCR_WDD_SHIFT))

/***************************************************************************//*!
 * @brief   Erases 8 KB flash sector.
 * @details This function erases 8 KB flash sector pointed by address (dst).
 *          Function uses main program and erase interface. This function 
 *          executes flash erase state-machine from RAM.
 * @param   dst   Pointer to address within a flash sector (const void *).
 * @return  @ref tFLASH_STATUS.
 * @note    Implemented as a function call.
 ******************************************************************************/
#define FLASH_EraseSector(dst) FLASH_ErsSector(dst)

/***************************************************************************//*!
 * @brief   Erases physical flash block.
 * @details This function erases physical flash block pointed by address (dst).
 *          Function uses main program and erase interface. This function 
 *          executes flash erase state-machine from RAM.
 * @param   dst   Pointer to address with a flash block (const void *).
 * @return  @ref tFLASH_STATUS.
 * @note    Implemented as a function call.
 ******************************************************************************/
#define FLASH_EraseBlock(dst)  FLASH_ErsBlock(dst)

/***************************************************************************//*!
 * @brief   Writes source data into flash memory.
 * @details This function writes source data (src) starting at address (dst) to 
 *          flash. Function uses main program and erase interface. This function 
 *          executes flash program state-machine from RAM.
 * @param   dst     Pointer to flash memory (const void *).
 * @param   src     Pointer to source data (void *).
 * @param   nbytes  Number of bytes.
 * @return  @ref tFLASH_STATUS.
 * @note    Implemented as a function call.
 ******************************************************************************/
#define FLASH_Write(dst,src,nbytes)  FLASH_Wr(dst,src,nbytes)

/***************************************************************************//*!
 * @brief   Write-once crash log to flash.
 * @details This function write-once crash log (src) starting at address (dst)
 *          to flash. Function uses express programming interface. It executes
 *          flash programming state-machine from RAM.
 * @param   dst       Pointer to flash memory (const @ref tCRASH_LOG).
 * @param   src       Pointer to crash log  (@ref tCRASH_LOG).
 * @return  @ref tFLASH_XSTATUS.
 * @note    Implemented as a function call.
 * @warning Because express programming interface has higher priority than main
 *          program and erase interface this function will abort execution of
 *          other flash program and erase running in parallel.
 * @warning This function shall be called once during software execution - the
 *          count of use is initialized by device reset.
 * @warning If this function is called one more time during software execution,
 *          then function never returns.
 ******************************************************************************/
#define FLASH_WriteOnceCrashLog(dst,src)  FLASH_WrOnceCrashLog(dst,src)
/*! @} End of flash_macro                                                     */

/******************************************************************************
 * public function prototypes                                                 *
 ******************************************************************************/
extern tFLASH_STATUS FLASH_ErsSector  (const void *dst);
extern tFLASH_STATUS FLASH_ErsBlock   (const void *dst);
extern tFLASH_STATUS FLASH_Wr         (const void *dst, void *src, int32_t nbytes);
extern tFLASH_XSTATUS FLASH_WrOnceCrashLog (const tCRASH_LOG dst, tCRASH_LOG src);

#endif /* __FLASH_H */
