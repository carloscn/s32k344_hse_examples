################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../framework/host_keymgmt/hse_keys_allocator.c 

OBJS += \
./framework/host_keymgmt/hse_keys_allocator.o 

C_DEPS += \
./framework/host_keymgmt/hse_keys_allocator.d 


# Each subdirectory must supply rules for building sources it contributes
framework/host_keymgmt/%.o: ../framework/host_keymgmt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@framework/host_keymgmt/hse_keys_allocator.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


