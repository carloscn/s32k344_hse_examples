################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/fw_attribute/non-otp/hse_get_capabilities.c \
../services/src/fw_attribute/non-otp/hse_get_version.c \
../services/src/fw_attribute/non-otp/hse_mu_config.c 

OBJS += \
./services/src/fw_attribute/non-otp/hse_get_capabilities.o \
./services/src/fw_attribute/non-otp/hse_get_version.o \
./services/src/fw_attribute/non-otp/hse_mu_config.o 

C_DEPS += \
./services/src/fw_attribute/non-otp/hse_get_capabilities.d \
./services/src/fw_attribute/non-otp/hse_get_version.d \
./services/src/fw_attribute/non-otp/hse_mu_config.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/fw_attribute/non-otp/%.o: ../services/src/fw_attribute/non-otp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/fw_attribute/non-otp/hse_get_capabilities.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


