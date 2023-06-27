/******************************************************************************
 * (c) Copyright 2018-2020, NXP Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      pflash.c
 * @brief     Embedded Flash Memory (FLASH) driver source code.
 ******************************************************************************/
#include "S32K344_XRDC.h"
#include "S32K344_COMMON.h"
#include "flash.h"


/******************************************************************************
 * private defines and macros                                                 *
 ******************************************************************************/
#define FLASH_DATAX_MASK  0x7CUL  /* bit mask of words within 128 bytes area  */
#define FLASH_BYTES_MASK  0x03UL  /* bit mask of bytes within a word (4bytes) */
#define FLASH_InitSeq(addr)                                                   \
do{                                                                           \
  register uint8_t domain_id = XRDC->HWCFG1;                                  \
  /* entry semaphore loop                                               */    \
  do{ FLASH_WritePEADR (addr); } while(FLASH_GetPEID () != domain_id);        \
  /* clear any pending program & erase errors                           */    \
  FLASH_ClrStatus (FLASH_PES_ERR|FLASH_PEP_ERR);                              \
 }while(0)

#define FLASH_XInitSeq(addr)                                                  \
do{                                                                           \
  register uint8_t domain_id = XRDC->HWCFG1;                                  \
  /* entry semaphore loop                                               */    \
  do{ FLASH_WriteXPEADR (addr); } while(FLASH_GetXPEID () != domain_id);      \
  /* wait until the XMCR[XDOK] bit goes high                            */    \
  while(!(FLASH_GetXStatus () & FLASH_XDOK_ST));                              \
 }while(0)

/******************************************************************************
 * static function definitions                                                *
 ******************************************************************************/
tFLASH_STATUS FLASH_ExecSeq (register uint32_t mask)//__tcm(func) tFLASH_STATUS FLASH_ExecSeq (register uint32_t mask)
{
  register tFLASH_STATUS status;

  FLASH->MCR |= mask;                          /* initiate sequence             */
  FLASH->MCR |= FLASH_MCR_EHV_MASK;            /* enable high voltage           */
  while(!(FLASH->MCRS&FLASH_MCRS_DONE_MASK));  /* wait until MCRS[DONE]=1       */
  FLASH->MCR &=~FLASH_MCR_EHV_MASK;            /* disable high voltage          */
  status = FLASH_GetStatus();                  /* read main interface status    */
  FLASH->MCR &=~mask;                          /* close sequence                */
  
  return status;
}

tFLASH_XSTATUS FLASH_XExecPgm (void)//__tcm(func) tFLASH_XSTATUS FLASH_XExecPgm (void)
{
  register tFLASH_XSTATUS xstatus;

  FLASH->XMCR |= FLASH_XMCR_XPGM_MASK;         /* initiate express programming  */
  FLASH->XMCR |= FLASH_XMCR_XEHV_MASK;         /* enable high voltage           */
  while(!(FLASH->XMCR&FLASH_XMCR_XDONE_MASK)); /* wait until XMCR[XDONE]=1      */
  FLASH->XMCR &=~FLASH_XMCR_XEHV_MASK;         /* disable high voltage          */
  xstatus = FLASH_GetXStatus();                /* read express interface status */
  FLASH->XMCR &=~FLASH_XMCR_XPGM_MASK;         /* close express programming     */
  
  return xstatus;
}

/******************************************************************************
 * public function definitions                                                *
 ******************************************************************************/
tFLASH_STATUS FLASH_ErsSector (const void *dst)
{
  FLASH_InitSeq(dst);
  FLASH->DATA[0] = 0UL;               /* one and only one DATA register written */
  return FLASH_ExecSeq(FLASH_MCR_ERS_MASK);
}

tFLASH_STATUS FLASH_ErsBlock (const void *dst)
{
  FLASH_InitSeq(dst);
  FLASH->DATA[0] = 0UL;               /* one and only one DATA register written */
  return FLASH_ExecSeq(FLASH_MCR_ERS_MASK|FLASH_MCR_ESS_MASK);
}

extern tFLASH_STATUS FLASH_Wr (const void *dst, void *src, int32_t nbytes)
{
  register tFLASH_STATUS status = FLASH_PEG_ST;
  register uint8_t *pDst = (uint8_t*)dst, *pSrc = (uint8_t*)src, *pTmp;
  register uint32_t *pData;
  uint32_t tmp;

  while ((nbytes > 0L) && (status & FLASH_PEG_ST))
  {
    pData = (uint32_t*)((uint32_t)&FLASH->DATA[0] + ((uint32_t)pDst & FLASH_DATAX_MASK));
    FLASH_InitSeq (pDst);
    do {
      tmp = 0xffffffffUL;
      pTmp = (uint8_t*)((uint32_t)&tmp + ((uint32_t)pDst & FLASH_BYTES_MASK));
      do {
        *pTmp++ = *pSrc++; pDst++;
      } while ((nbytes-- > 0L) && ((uint32_t)pTmp & FLASH_BYTES_MASK));
      *pData++ = tmp;
    } while ((nbytes > 0L) && ((uint32_t)pData & FLASH_DATAX_MASK));
    status = FLASH_ExecSeq (FLASH_MCR_PGM_MASK);
  }
  return status;
}

tFLASH_XSTATUS FLASH_WrOnceCrashLog (const tCRASH_LOG dst, tCRASH_LOG src)
{
  register tFLASH_XSTATUS xstatus = FLASH_XPEG_ST;
  register int32_t logs = sizeof(tCRASH_LOG)/sizeof(src[0]);
  register uint32_t *pData;

  while ((logs > 0L) && (xstatus & FLASH_XPEG_ST))
  {
    pData = (uint32_t*)((uint32_t)&FLASH->DATA[0] + ((uint32_t)dst & FLASH_DATAX_MASK));
    FLASH_XInitSeq (dst);
    do {
      *(uint32_t*)pData++ = *(uint32_t*)src++; dst++;
    } while ((logs-- > 0L) && ((uint32_t)pData & FLASH_DATAX_MASK));
    xstatus = FLASH_XExecPgm ();
  }
  return xstatus;
}
/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/
