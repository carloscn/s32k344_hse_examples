# Basic Secure Boot

## 1. Objective
The main purpose of this example is to show the steps required to properly configure the Basic Secure Boot while working with the HSE. For this a previous installation of the ADKP is required in the device aswell as a separate binary file (S32K344_SecureBootBlinky.bin) containing the application to be executed after the secure boot process is finished. 

In this case the ADKP must already be installed in the device, in the current implementation the ADKP programmed is the following:

The separate binary (S32K344_SecureBootBlinky.bin) file can be found in alongside the examples folders, also the design studio project for the Secure Boot blinky can be found alongside the examples in case the user wants to modify it or use as a template for secure boot applications.

## 2. Procedure

Prior to build and execute the code, the user needs to :
- Provide an ADKP to the device as this is the key used to generate the Tag over the application.
- Access the linker file and change the current address where the security file is located to match a location in their computers.

The steps followed to achieve this are: 
1. Verify if the ADKP is already programmed in the device, if not it will be stuck on an infinite loop.
2. Generate a signature TAG over the secure application.
3. Save the TAG in flash memory at the end of the AppBL (Secure Application).
4. Verify the generated TAG over the AppBL to make sure that the TAG generated correctly.

After this the user needs to generate a reset and then the secure boot will take place.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
