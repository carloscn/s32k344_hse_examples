# ECC Key Management Example

## 1. Objective

The main purpose of this example is to show how to configure a secure memory region using the SHE standard. This memory region is verified during the boot process of the system, if the verification is passed, the MCU will execute the main program as usual, if not, it will keep the MCU in reset as it is program in the sanctions.

## 2. Procedure

The steps followed in this implementation are: 
1. Generate the main application and modify its linker file so it is stored in the Secure Memory Region (by modifying the PFLASH). The boot header for the SMR must be also added at the begining of the code flash.
2. Generate a project in which the configuration of the Secure Boot will be done. The linker file must be updated in order to have the region for the IVT, the configuration code and the application that is being verifyied. Add the binnary file to the linker file.
3. Format the Key Catalogs with the SHE standard.
4. Grant for Super User Rights.
5. Loads the Master ECU Key and the SHE boot MAC key in their respective slots.
6. Generates an AES CMAC of the SMR using the SHE Boot MAC Key.
7. Configure the SMR Entry of the Application.
8. Configure the Core Reset Entry.
9. Program the device and perform a RESET.

## 3. Hardware

This example was tested in the following hardware:
- S32K344EVB-T172
- S32K344EVB-Q172
- An external debugger can be used (PEmicro Multilink rev. C) or used the debug port on board if available. 

## 4. Files

This example uses 2  projects, the configuration project named S32K344_Hse_SHE_SecurBoot and the application to be verifyied named S32K344_SecureBoot_AppBL. Before compiling the configuration project, the AppBL needs to be built first, then verify that the Application BL address in the linker file of the S32K344_Hse_SHE_SecurBoot project (S32K344_Hse_SHE_SecurBoot/src/target/m7/S32DS/Linker_Files/standard/S32K344_flash.ld) point to the address where the binary of the AppBL has been generated. There are two lines with the legends **MODIFY TO YOUR ADDRESS**, those are the lines with the application address.

If the code is seccessfully built, the blue LED should blink when programming the board.