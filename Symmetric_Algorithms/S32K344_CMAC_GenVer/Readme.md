# CMAC Generation and Verification

## 1. Objective
The main purpose of this example is to show the steps required to properly configure the HSE to show the functionality of the CMAC TAG generation with a 128-bits Aes Key on a Plain text provided by the Host and then verify that generated TAG with the provided message.

## 2. Procedure
The steps followed to achieve this are: 
1. Format Key Catalogs.
2. Generate an AES key with a HSE service request to a specific key slot.
3. Request the service to generate a CMAC TAG over the provided Plaintext.
4. Save the TAG result in RAM.
5. Request the service to verify the generated CMAC TAG in step 4.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
