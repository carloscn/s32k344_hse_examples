################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/stm/host_stm.c 

OBJS += \
./drivers/stm/host_stm.o 

C_DEPS += \
./drivers/stm/host_stm.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/stm/%.o: ../drivers/stm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@drivers/stm/host_stm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


