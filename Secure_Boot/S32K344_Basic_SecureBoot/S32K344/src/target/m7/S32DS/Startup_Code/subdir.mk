################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/target/m7/S32DS/Startup_Code/boot_header.c \
../src/target/m7/S32DS/Startup_Code/startup_ARMCM7.c \
../src/target/m7/S32DS/Startup_Code/system_ARMCM7.c 

OBJS += \
./src/target/m7/S32DS/Startup_Code/boot_header.o \
./src/target/m7/S32DS/Startup_Code/startup_ARMCM7.o \
./src/target/m7/S32DS/Startup_Code/system_ARMCM7.o 

C_DEPS += \
./src/target/m7/S32DS/Startup_Code/boot_header.d \
./src/target/m7/S32DS/Startup_Code/startup_ARMCM7.d \
./src/target/m7/S32DS/Startup_Code/system_ARMCM7.d 


# Each subdirectory must supply rules for building sources it contributes
src/target/m7/S32DS/Startup_Code/%.o: ../src/target/m7/S32DS/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/target/m7/S32DS/Startup_Code/boot_header.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


