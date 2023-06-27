# HSE FW Installation

## 1. Objective
The main purpose of this example is to allow the user to install the HSE FW in their MCU sample using the IVT method for FULL_MEMORY configuration or AB_SWAP depending on the build configuration selected.

Once selected the proper build cofiguration and build the project the .elf will contain the selected pink image by the user (defined in the linker file) and the user just needs to run the code and generate a Power-On Reset on the MCU. After this the sBAF will proceed to install the HSE FW in secure Flash memory.

## 2. Procedure

Prior to build and execute the code, **the user needs to** :
- Select the proper build configuration to match the memory configuration they need for their application (either FULL_MEMORY or AB_SWAP).
- Access the proper linker file (FULL_MEM or AB_SWAP) located in /Project_Settings/Linker_Files/ and change the current address where the pink binary file is located to match a location in their computers (line 39 and 79 of the linker file).

The steps followed by the application in this example are: 
1. Verify the HSE USAGE flag in the UTEST memory
2. If the HSE USAGE flag value is the default one, then it will unlock the UTEST memory to be able to write to it and change the value of the flag to 0xAABBCCDDDDCCBBAA
3. Verify the status of the HSE
4. If the HSE has not started, then it means that it hasn't been installed and the user needs to generate a reset in order to trigger the installation.
5. If the HSE has started, then it will request for the version attribute of the HSE and save the details of the version into a variable.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
