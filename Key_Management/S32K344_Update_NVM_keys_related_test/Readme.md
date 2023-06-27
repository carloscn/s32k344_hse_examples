# Update NVM keys.

## 1. Objective
The main purpose of this example is to a import symmetric key and AES GMAC generate keys.

## 2. Procedure
The steps followed to achieve this are: 
1. Format Key Catalogs.
2. Declare the HMAC key info that will update initial version.
3. Declare a key container.
4. Copy the key info to the key container.
5. Copy the key data in the container.
6. *You can add any other data to the container*.
7. Import in RAM a copy of the AES provision key to sign the container using the HSE.
8. Sign the container and generate GMAC

## 3. Hardware
This example requires the following hardware in order to properly execute:
- S32K344-EVB or S32K344-CVB.
- If using S32K344-CVB, then an external debugger is also required (PEmicro Multilink rev. C). 
