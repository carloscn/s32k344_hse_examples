/* ****************************************************************************
 * (c) Copyright NXP 2020
 *  All Rights Reserved
 * ****************************************************************************
 *!\file    boot_header.c
 *!\brief   This file contains boot header structure definition
 *
 * TYPE: Source File
 * ****************************************************************************
 * PURPOSE:  This file contains boot header structure definition
 * ***************************************************************************/

#include "typedefs.h"

extern const uint32_t CM7_START_ADDRESS;
extern const uint32_t __HSE_BIN_START;

/******************************************************************************
 * Boot header
 ******************************************************************************/
typedef const struct
{
  const uint32_t  Header;                   /* Header of boot header structure */
  const uint32_t  BootConfig;               /* Boot Configuration Word */
  const uint32_t  Reserved3;                /* Reserved */
  const uint32_t* CM7_0_StartAddress;       /* Start address of application on CM7_0 core */
  const uint32_t  Reserved4;                /* Reserved */
  const uint32_t* CM7_1_StartAddress;       /* Start address of application on CM7_1 core */
  const uint32_t  Reserved5;                /* Reserved */
  const uint32_t* CM7_2_StartAddress;       /* Start address of application on CM7_2 core */
  const uint32_t* XRDCConfig_StartAddress;  /* Address of XRDC configuration data */
  const uint32_t* LCConfig;                 /* Address of LC configuration */
  const uint32_t  Reserved1;                /* Reserved */
  const uint32_t* HseFwHeader_StartAddress; /* Start address of HSE-FW image */
  const uint8_t   Reserved[192];            /* Reserved for future use */
  const uint8_t   CMAC[16];                 /* CMAC */
} boot_header_t;

/******************************************************************************
 * XRDC Configuration
 ******************************************************************************/
typedef struct
{
  uint32_t  Header;
  uint32_t  MDAConfig_ProcessorCore0;
  uint32_t  MDAConfig_eDMA_AHB;
  uint32_t  MDAConfig_TestPort_AHB;
  uint32_t  MDAConfig_ProcessorCore1;
  uint32_t  MDAConfig_ENET_AHB;
  uint32_t  Reserved0[10];
  uint32_t  PDAC[14][2];
  uint32_t  Reserved2[20];
  uint8_t   CMAC[16];
} xrdc_config_t;

/******************************************************************************
 * LC Configuration
 ******************************************************************************/
typedef uint32_t lc_config_t;

/******************************************************************************
 * LC Configuration
 ******************************************************************************/
const lc_config_t lc_config = 0xffffffff;

/******************************************************************************
 * XRDC Configuration
 ******************************************************************************/
const xrdc_config_t xrdc_config =
{
  .Header = 0xffffffff
};

#if defined (__ghs__)
#pragma ghs section rodata =".boot_header"
const boot_header_t  boot_header = {
#elif defined (__GNUC__)
const boot_header_t __attribute__((section (".boot_header"))) boot_header = {
#elif defined (__ICCARM__)
#pragma location = ".boot_header"
const boot_header_t boot_header = {
#endif
  .Header = 0x5AA55AA5,
  .BootConfig = 1, /* Booting core is always core CM7 */
  .CM7_0_StartAddress = (const uint32_t*)&CM7_START_ADDRESS,
  .XRDCConfig_StartAddress  = (const uint32_t*)&xrdc_config,
  .LCConfig                 = (const uint32_t*)&lc_config,
  .HseFwHeader_StartAddress = (const uint32_t*)&__HSE_BIN_START,
};
#if defined (__ghs__)
#pragma ghs section rodata =default
#endif
