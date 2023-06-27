################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/utest/hse_utest.c 

OBJS += \
./services/src/utest/hse_utest.o 

C_DEPS += \
./services/src/utest/hse_utest.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/utest/%.o: ../services/src/utest/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/utest/hse_utest.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


