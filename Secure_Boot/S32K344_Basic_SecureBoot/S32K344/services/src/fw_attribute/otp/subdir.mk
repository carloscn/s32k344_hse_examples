################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/fw_attribute/otp/hse_advance_LC.c \
../services/src/fw_attribute/otp/hse_boot_auth.c \
../services/src/fw_attribute/otp/hse_debug_auth_mode.c \
../services/src/fw_attribute/otp/hse_debug_key.c \
../services/src/fw_attribute/otp/hse_extend_cust_security_policy.c 

OBJS += \
./services/src/fw_attribute/otp/hse_advance_LC.o \
./services/src/fw_attribute/otp/hse_boot_auth.o \
./services/src/fw_attribute/otp/hse_debug_auth_mode.o \
./services/src/fw_attribute/otp/hse_debug_key.o \
./services/src/fw_attribute/otp/hse_extend_cust_security_policy.o 

C_DEPS += \
./services/src/fw_attribute/otp/hse_advance_LC.d \
./services/src/fw_attribute/otp/hse_boot_auth.d \
./services/src/fw_attribute/otp/hse_debug_auth_mode.d \
./services/src/fw_attribute/otp/hse_debug_key.d \
./services/src/fw_attribute/otp/hse_extend_cust_security_policy.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/fw_attribute/otp/%.o: ../services/src/fw_attribute/otp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/fw_attribute/otp/hse_advance_LC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


