# Advanced Secure Boot

## 1. Objective
The main purpose of this example is to show the steps required to properly configure the Advanced Secure Boot while working with the HSE. In this specific secure boot mode, it is required to install a secure memory region (SMR) of the flash memory to be verified and the Core Reset entry table to indicate the booting address and the saction in case the secure boot fails.

The host application defines a proper CMAC key to be used in the SMR0 and generates the TAG corresponding to the provided application in that memory region. Then the tag is verified and the installation of the SMR as well as the CR is done.

The separate binary (S32K344_SecureBootBlinky.bin) file can be found in alongside the examples folders, also the design studio project for the Secure Boot blinky can be found alongside the examples in case the user wants to modify it or use as a template for secure boot applications.

## 2. Procedure

Prior to build and execute the code, **the user needs to** :
- Access the linker file and change the current address where the security file is located to match a location in their computers.

The steps followed to achieve this are: 
1. Format key catalogs
2. Load an AES key to generate a CMAC TAG and another to make the verification of the TAG, aswell as to be used as a verification key during secure boot
3. Generate a signature TAG over the secure application.
4. Save the TAG in flash memory at the end of the AppBL (Secure Application).
5. Verify the generated TAG over the AppBL to make sure that the TAG generated correctly.
6. Fillout the missing information for the Secure Memory Region
7. Install the Secure Memory Region 0
8. Install the Core Reset Entry
9. Verify the status of the Secure Boot and the Core Reset.

After this **the user needs to** generate a reset and then the secure boot will take place.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
