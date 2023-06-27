################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mu/hse_mu.c 

OBJS += \
./drivers/mu/hse_mu.o 

C_DEPS += \
./drivers/mu/hse_mu.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mu/%.o: ../drivers/mu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@drivers/mu/hse_mu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


