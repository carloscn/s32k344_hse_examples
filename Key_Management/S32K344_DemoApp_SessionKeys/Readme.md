 # Session keys

## 1. Objective
The main purpose of this example is to show the steps required to properly configure the HSE to show the functionality of the session key services.
It formats the keys and then generate the ECC key pair. Then import the ECC keys, compute the DH Shared Secret and derive key using SP800_108 KDF.
Finally, it extract from the derived key material 2 keys, a 192-bits AES and a 256-bit AES, and then encrypts and decrypt using AES GCM using both keys.

## 2. Procedure
The steps followed to achieve this are: 
1. Format Key Catalogs.
2. Generate an ECC key pair in RAM.
3. Import the ECC key.
4. Compute the DH Shared Secret
5. Derive key using SP800_108 KDF
6. Extract from the derive key material, 2 keys: 192-bit AES and 256-bit AES.
7. Encrypt a plain text using AES GCM using the derived AES 256-bit key.
8. Decrypt the previous data using AES GCM with the 256-bit key.
9. Encrypt a plain text using AES GCM using the derived AES 192-bit key.
10. Decrypt the previous data using AES GCM with the 192-bit key.

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
