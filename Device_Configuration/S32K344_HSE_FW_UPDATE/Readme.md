# HSE FW Update

## 1. Objective
The main purpose of this example is to allow the user to update the HSE FW in their MCU sample by generating the proper configuration depending on the update type required by the user (FULL_MEMORY_TO_FULL_MEMORY, FULL_MEMORY_TO_AB_SWAP or AB_SWAP_TO_AB_SWAP).

Once selected the proper build cofiguration and build the project the .elf will contain the selected pink image by the user (defined in the linker file) and the user just needs to run the code, it can be debugged step by step or run entirely and after this the HSE is updated.

## 2. Procedure

Prior to build and execute the code, **the user needs to** :
- Select the proper build configuration to match the memory configuration they need for their application (either FULL_MEMORY_TO_FULL_MEMORY, FULL_MEMORY_TO_AB_SWAP or AB_SWAP_TO_AB_SWAP).
- Access the proper linker file (FULL_MEM or AB_SWAP) located in /Project_Settings/Linker_Files/ and change the current address where the pink binary file is located to match a location in their computers (line 39 and 79 of the linker file).

The steps followed by the application in this example are: 
1. Verify status of the HSE
2. Get current version of the HSE
3. If the update to be done is AB_SWAP related, then the application will make sure that the Passive region contains application to run when the switch happens.
4. Request HSE_UPDATE service
5. Wait until the update has finished.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
