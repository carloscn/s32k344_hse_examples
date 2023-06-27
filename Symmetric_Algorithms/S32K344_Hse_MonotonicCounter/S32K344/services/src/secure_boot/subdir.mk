################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/secure_boot/hse_boot_mac_key_update.c \
../services/src/secure_boot/hse_host_boot.c \
../services/src/secure_boot/hse_secure_boot.c 

OBJS += \
./services/src/secure_boot/hse_boot_mac_key_update.o \
./services/src/secure_boot/hse_host_boot.o \
./services/src/secure_boot/hse_secure_boot.o 

C_DEPS += \
./services/src/secure_boot/hse_boot_mac_key_update.d \
./services/src/secure_boot/hse_host_boot.d \
./services/src/secure_boot/hse_secure_boot.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/secure_boot/%.o: ../services/src/secure_boot/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/secure_boot/hse_boot_mac_key_update.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


