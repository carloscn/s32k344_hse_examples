# ECC Key Management Example

## 1. Objective

The main purpose of this example is to show the monotionic counter functionalities.

## 2. Procedure

The steps followed in this implementation are: 
1. Configures the monotonic counter with a Rollover Protection size of 28 bits.
2. Increments the counter in 256 (100h).
3. Reads the counter, writting the value in memory.
4. Check the service response and set a green LED if there is no error, otherwise it turns red. 

## 3. Hardware

This example was tested in the following hardware:
- S32K344EVB-T172
- S32K344EVB-Q172
- An external debugger can be used (PEmicro Multilink rev. C) or used the debug port on board if available. 