################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/mu/hse_mu.c 

OBJS += \
./src/drivers/mu/hse_mu.o 

C_DEPS += \
./src/drivers/mu/hse_mu.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/mu/%.o: ../src/drivers/mu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/mu/hse_mu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


