################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/framework/host_hse/hse_host.c 

OBJS += \
./src/framework/host_hse/hse_host.o 

C_DEPS += \
./src/framework/host_hse/hse_host.d 


# Each subdirectory must supply rules for building sources it contributes
src/framework/host_hse/%.o: ../src/framework/host_hse/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/framework/host_hse/hse_host.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


