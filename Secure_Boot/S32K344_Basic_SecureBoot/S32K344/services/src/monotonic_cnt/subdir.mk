################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/monotonic_cnt/hse_monotonic_cnt.c 

OBJS += \
./services/src/monotonic_cnt/hse_monotonic_cnt.o 

C_DEPS += \
./services/src/monotonic_cnt/hse_monotonic_cnt.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/monotonic_cnt/%.o: ../services/src/monotonic_cnt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/monotonic_cnt/hse_monotonic_cnt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


