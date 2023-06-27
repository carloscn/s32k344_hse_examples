################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/fw_crypto/hse_crypto.c \
../services/src/fw_crypto/hse_host_sys_authorization.c 

OBJS += \
./services/src/fw_crypto/hse_crypto.o \
./services/src/fw_crypto/hse_host_sys_authorization.o 

C_DEPS += \
./services/src/fw_crypto/hse_crypto.d \
./services/src/fw_crypto/hse_host_sys_authorization.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/fw_crypto/%.o: ../services/src/fw_crypto/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/fw_crypto/hse_crypto.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


