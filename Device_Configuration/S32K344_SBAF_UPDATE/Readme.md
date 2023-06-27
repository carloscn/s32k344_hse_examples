# Secure BAF Update

## 1. Objective
The main purpose of this example is to allow the user to show the update process of the sBAF by the HSE FW in their MCU sample by generating configuring the proper parameters on the specific service request.

Once selected the proper sbaf image by the user (defined in the linker file), then the user just needs to run the code and it can be debugged step by step or run entirely. After this the sBAF is up to date.

## 2. Procedure

Prior to build and execute the code, **the user needs to** :
- Access the linker file located in /Project_Settings/Linker_Files/ and change the current address where the pink binary file is located to match a location in their computers (line 39 and 79 of the linker file).

The steps followed by the application in this example are: 
1. Verify status of the HSE
2. Get current version of the sBAF
3. Request sBAF update service to the HSE
4. Wait until the update has finished

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
