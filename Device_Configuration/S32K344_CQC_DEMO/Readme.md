# HSE ADKP, Life Cycle and Secure Debug Configuration.

## 1. Objective
The main purpose of this example is to show different possible configurations that can be done over the HSE and the functionality of the MCU. These possible configuirations are:
- Key Catalog Formatting
- Plain ADKP provisioning
- Secure Debug Mode selection (Static or Dynamic)
- Life Cycle Advancement (Starting from CUST_DEL can advance the life cycle to OEM_PROD or IN_FIELD)

## 2. Procedure

Prior to build and execute the code, **the user needs to** configure several macros and variables depending on which configuration wants to be executed.

### 2.1 Key Catalog
The first thing is always to Format the Key Catalog to the defined in the main file, if the user wants to set a specific Key Catalog then the ***HSE_NVM_CATALOG*** and ***HSE_RAM_CATALOG*** macros needs to be modified to match the desired catalog.

### 2.2 ADKP Provisioning
If the user does not want to provide an ADKP to the device, set the macro ***ADKP_PROGRAMMING*** to 0.

Otherwise, if the user wants to provide a specific ADKP to the device, then change the value of the array ***applicationDebugKeyPassword*** to the desired 16-bytes value of the ADKP to be provisioned.

Finally set the macro ***ADKP_PROGRAMMING*** to 1.

### 2.3 Debug Authentication Mode
If the user wants to enable the Dynamic Secure Debug, then look for the variable ***DynamicAuth*** and set the value to TRUE.

### 2.4 Life Cycle Advancement
If the user does not want to advance the life cycle of the device, set the macro ***LC_ADVANCE*** to 0.

Otherwise, if the user wants to advance the current life cycle of the device, then first of all the ADKP must be provisioned and the steps of 2.2 ADKP provisioning needs to be followed. If the ADKP has already been provided, then the user needs to set the macro ***LC_ADVANCE*** to 1.

### 2.5 Application code flow:
The steps followed by the application code are: 
1. Wait for the HSE to initialize
2. Get the current version of the HSE FW
3. Format Key Catalogs with provided configuration
4. Read current Authentication mode to the device
5. If ***DynamicAuth*** is set to TRUE, then enable Dynamic Authentication
6. If ***ADKP_PROGRAMMING*** is set to 1, then verify the ADKP status, if not provided yet then provide the configured ADKP and verify that the provisioning was successful
7. If ***LC_ADVANCE*** is set to 1, read current Life Cycle and if possible then proceed to request a life cycle advancement through HSE service.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
