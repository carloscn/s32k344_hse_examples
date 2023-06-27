################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/dcm_register/hse_dcm_register.c 

OBJS += \
./src/drivers/dcm_register/hse_dcm_register.o 

C_DEPS += \
./src/drivers/dcm_register/hse_dcm_register.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/dcm_register/%.o: ../src/drivers/dcm_register/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/dcm_register/hse_dcm_register.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


