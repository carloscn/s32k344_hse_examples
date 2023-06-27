################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/boot_header.c \
../Project_Settings/Startup_Code/startup_ARMCM7.c \
../Project_Settings/Startup_Code/system_ARMCM7.c 

OBJS += \
./Project_Settings/Startup_Code/boot_header.o \
./Project_Settings/Startup_Code/startup_ARMCM7.o \
./Project_Settings/Startup_Code/system_ARMCM7.o 

C_DEPS += \
./Project_Settings/Startup_Code/boot_header.d \
./Project_Settings/Startup_Code/startup_ARMCM7.d \
./Project_Settings/Startup_Code/system_ARMCM7.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Project_Settings/Startup_Code/boot_header.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


