# ECC Key Management Example

## 1. Objective

The main purpose of this example is to show the steps required to generate, export and import an ECC key and perform an ECDSA signature with the local key pair to a mesage and verify that message with the imported public key.

## 2. Procedure

The steps followed in this implementation are: 
1. Format Key Catalogs with the ECC format.
2. Generate the ECC key pair and export the public part to memory.
3. Load the public key into the RAM catalog.
4. Request the ECDSA sign service with the ECC key pair and store the signature into memory.
5. Verify the message and the signature with the generated message and the public key.
4. Check the service response and set a green LED if there is no error, otherwise it turns red. 

## 3. Hardware

This example was tested in the following hardware:
- S32K344EVB-T172
- S32K344EVB-Q172
- An external debugger can be used (PEmicro Multilink rev. C) or used the debug port on board if available. 