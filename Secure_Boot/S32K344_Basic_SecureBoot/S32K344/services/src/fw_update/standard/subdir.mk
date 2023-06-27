################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/fw_update/standard/hse_fw_update.c 

OBJS += \
./services/src/fw_update/standard/hse_fw_update.o 

C_DEPS += \
./services/src/fw_update/standard/hse_fw_update.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/fw_update/standard/%.o: ../services/src/fw_update/standard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/fw_update/standard/hse_fw_update.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


