# AES Encryption and Decryption

## 1. Objective
The main purpose of this example is to show the steps required to properly configure the HSE to show the functionality of the AES ECB encryption with a 128-bits Aes Key on a Plain text provided by the Host and then decrypt the result to compare it with the original input. 
In this example the host also generates and loads two different predefined key into the Key Catalog and generates the encryption and decryption operations.

## 2. Procedure
The steps followed to achieve this are: 
1. Format Key Catalogs.
2. Generate an AES key with a HSE service request to a specific key slot.
3. Load a predefined (by the host) key to a specific key slot.
4. Request the service to generate an AES ECB encryption to the Plaintext.
5. Save the encryption result into RAM.
6. Request the service to generate an AES ECB decryption to the cyphertext provided in step 4.
7. Compare the result of the decryption with the initial plaintext.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 




