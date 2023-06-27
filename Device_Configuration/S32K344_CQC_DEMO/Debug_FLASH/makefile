################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/target/m7/src/subdir.mk
-include src/framework/host_hse/subdir.mk
-include src/framework/host_crypto_helper/subdir.mk
-include src/drivers/stm/subdir.mk
-include src/drivers/nvic/subdir.mk
-include src/drivers/mu/subdir.mk
-include src/drivers/flash/subdir.mk
-include src/drivers/dcm_register/subdir.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
S32K344_CQC_DEMO.siz \


# All Target
all: S32K344_CQC_DEMO.elf secondary-outputs

# Tool invocations
S32K344_CQC_DEMO.elf: $(OBJS) C:/Users/nxf63523/Documents/Seguridad/SecurityWorkspace/S32K344_CQC_DEMO/Project_Settings/Linker_Files/S32K344_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "S32K344_CQC_DEMO.elf" "@S32K344_CQC_DEMO.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

S32K344_CQC_DEMO.siz: S32K344_CQC_DEMO.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley S32K344_CQC_DEMO.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
