################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Flash/flash.c \
../src/Flash/pflash.c 

OBJS += \
./src/Flash/flash.o \
./src/Flash/pflash.o 

C_DEPS += \
./src/Flash/flash.d \
./src/Flash/pflash.d 


# Each subdirectory must supply rules for building sources it contributes
src/Flash/%.o: ../src/Flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/Flash/flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


