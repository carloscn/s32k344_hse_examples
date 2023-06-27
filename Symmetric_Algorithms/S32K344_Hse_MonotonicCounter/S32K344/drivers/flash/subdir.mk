################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/flash/BlankCheck.c \
../drivers/flash/ClearAllErrorFlags.c \
../drivers/flash/ClearLock.c \
../drivers/flash/FlashErase.c \
../drivers/flash/FlashInit.c \
../drivers/flash/FlashProgram.c \
../drivers/flash/GetBaseAddressOfSector.c \
../drivers/flash/GetLock.c \
../drivers/flash/ProgramVerify.c \
../drivers/flash/SetLock.c 

OBJS += \
./drivers/flash/BlankCheck.o \
./drivers/flash/ClearAllErrorFlags.o \
./drivers/flash/ClearLock.o \
./drivers/flash/FlashErase.o \
./drivers/flash/FlashInit.o \
./drivers/flash/FlashProgram.o \
./drivers/flash/GetBaseAddressOfSector.o \
./drivers/flash/GetLock.o \
./drivers/flash/ProgramVerify.o \
./drivers/flash/SetLock.o 

C_DEPS += \
./drivers/flash/BlankCheck.d \
./drivers/flash/ClearAllErrorFlags.d \
./drivers/flash/ClearLock.d \
./drivers/flash/FlashErase.d \
./drivers/flash/FlashInit.d \
./drivers/flash/FlashProgram.d \
./drivers/flash/GetBaseAddressOfSector.d \
./drivers/flash/GetLock.d \
./drivers/flash/ProgramVerify.d \
./drivers/flash/SetLock.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/flash/%.o: ../drivers/flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@drivers/flash/BlankCheck.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


