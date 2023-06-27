################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/common/hse_config.c \
../services/src/common/hse_global_variables.c 

OBJS += \
./services/src/common/hse_config.o \
./services/src/common/hse_global_variables.o 

C_DEPS += \
./services/src/common/hse_config.d \
./services/src/common/hse_global_variables.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/common/%.o: ../services/src/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/common/hse_config.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


