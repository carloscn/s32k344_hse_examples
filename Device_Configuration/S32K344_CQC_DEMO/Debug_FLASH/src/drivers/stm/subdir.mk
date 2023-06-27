################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/stm/host_stm.c 

OBJS += \
./src/drivers/stm/host_stm.o 

C_DEPS += \
./src/drivers/stm/host_stm.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/stm/%.o: ../src/drivers/stm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/stm/host_stm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


