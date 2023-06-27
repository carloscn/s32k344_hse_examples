################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/flash/BlankCheck.c \
../src/drivers/flash/ClearAllErrorFlags.c \
../src/drivers/flash/ClearLock.c \
../src/drivers/flash/FlashErase.c \
../src/drivers/flash/FlashInit.c \
../src/drivers/flash/FlashProgram.c \
../src/drivers/flash/GetBaseAddressOfSector.c \
../src/drivers/flash/GetLock.c \
../src/drivers/flash/ProgramVerify.c \
../src/drivers/flash/SetLock.c 

OBJS += \
./src/drivers/flash/BlankCheck.o \
./src/drivers/flash/ClearAllErrorFlags.o \
./src/drivers/flash/ClearLock.o \
./src/drivers/flash/FlashErase.o \
./src/drivers/flash/FlashInit.o \
./src/drivers/flash/FlashProgram.o \
./src/drivers/flash/GetBaseAddressOfSector.o \
./src/drivers/flash/GetLock.o \
./src/drivers/flash/ProgramVerify.o \
./src/drivers/flash/SetLock.o 

C_DEPS += \
./src/drivers/flash/BlankCheck.d \
./src/drivers/flash/ClearAllErrorFlags.d \
./src/drivers/flash/ClearLock.d \
./src/drivers/flash/FlashErase.d \
./src/drivers/flash/FlashInit.d \
./src/drivers/flash/FlashProgram.d \
./src/drivers/flash/GetBaseAddressOfSector.d \
./src/drivers/flash/GetLock.d \
./src/drivers/flash/ProgramVerify.d \
./src/drivers/flash/SetLock.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/flash/%.o: ../src/drivers/flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/flash/BlankCheck.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


