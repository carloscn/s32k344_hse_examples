################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/shecommandapp/hse_host_common.c \
../services/src/shecommandapp/hse_host_test.c \
../services/src/shecommandapp/hse_host_wrappers.c \
../services/src/shecommandapp/hse_memory_update_protocol.c \
../services/src/shecommandapp/hse_she_command_main.c \
../services/src/shecommandapp/hse_she_commands.c 

OBJS += \
./services/src/shecommandapp/hse_host_common.o \
./services/src/shecommandapp/hse_host_test.o \
./services/src/shecommandapp/hse_host_wrappers.o \
./services/src/shecommandapp/hse_memory_update_protocol.o \
./services/src/shecommandapp/hse_she_command_main.o \
./services/src/shecommandapp/hse_she_commands.o 

C_DEPS += \
./services/src/shecommandapp/hse_host_common.d \
./services/src/shecommandapp/hse_host_test.d \
./services/src/shecommandapp/hse_host_wrappers.d \
./services/src/shecommandapp/hse_memory_update_protocol.d \
./services/src/shecommandapp/hse_she_command_main.d \
./services/src/shecommandapp/hse_she_commands.d 


# Each subdirectory must supply rules for building sources it contributes
services/src/shecommandapp/%.o: ../services/src/shecommandapp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@services/src/shecommandapp/hse_host_common.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


