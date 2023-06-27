################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/target/m7/src/sys_init.c 

OBJS += \
./src/target/m7/src/sys_init.o 

C_DEPS += \
./src/target/m7/src/sys_init.d 


# Each subdirectory must supply rules for building sources it contributes
src/target/m7/src/%.o: ../src/target/m7/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/target/m7/src/sys_init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


