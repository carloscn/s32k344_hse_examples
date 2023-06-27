################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/hse_b_catalog_formatting.c \
../services/src/hse_demo_app_config.c \
../services/src/hse_host_flash.c 

OBJS += \
./services/src/hse_b_catalog_formatting.o \
./services/src/hse_demo_app_config.o \
./services/src/hse_host_flash.o 

C_DEPS += \
./services/src/hse_b_catalog_formatting.d \
./services/src/hse_demo_app_config.d \
./services/src/hse_host_flash.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/%.o: ../services/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/hse_b_catalog_formatting.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


