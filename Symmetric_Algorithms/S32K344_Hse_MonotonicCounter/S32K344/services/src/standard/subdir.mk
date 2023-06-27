################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/standard/hse_fwType_config.c 

OBJS += \
./services/src/standard/hse_fwType_config.o 

C_DEPS += \
./services/src/standard/hse_fwType_config.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/standard/%.o: ../services/src/standard/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/standard/hse_fwType_config.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


