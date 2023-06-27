# HSE Demo App for PEmicro

## Objective
The purpose of this project is to provide different use-case scenarios and examples to showcase the capabilities of the HSE FW in different devices. This is a port of the well known HSE DEMO APP which requires T32 Lauterbach in order to work, in this case we are working with PEmicro and Design Studio as this two tools work well with eachother allowing debugging directly using Design Studio IDE.

## What is required to run this use-cases?
It is required to have the following:
- A valid device with the latest HSE FW version installed (otherwise install it with the proper project). 
- A PEmicro debugger, it can be the embedded one with the EVB of the device
- Design Studio IDE

## Devices covered
Currently this repository covers the following members of the S32K3 family:
- S32K344

## Examples covered
The current implementation of the Demo Application showcases examples covering the following areas for a FULL MEMORY HSE configuration (AB SWAP is still on testing phase):
- Symmetric Algorithms: Aes encryption, Aes decryption, CMAC generation, CMAC verification
- Asymmetric Algorithms: ECC ECDSA
- Secure Boot: Basic Secure Boot, Advanced Secure Boot, SHE-based Secure Boot
- Key Management: Session Keys, NVM Key update
- Device Configuration: HSE installation (FULL_MEM and AB_SWAP), HSE update (FULL_MEM and AB_SWAP), sBAF update, Key Catalog Formating, ADKP provisioning, Life Cycle Advancement, Secure Debug selection (static or dynamic)

## More Information about HSE
If you wish more information about working with the HSE in the S32K3 it is recommended to consult the HSE Reference Manual available in docstore as well as the API reference that comes along each HSE FW release.
