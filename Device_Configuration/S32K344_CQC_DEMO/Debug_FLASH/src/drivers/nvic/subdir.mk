################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/nvic/nvic.c 

OBJS += \
./src/drivers/nvic/nvic.o 

C_DEPS += \
./src/drivers/nvic/nvic.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/nvic/%.o: ../src/drivers/nvic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/nvic/nvic.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


