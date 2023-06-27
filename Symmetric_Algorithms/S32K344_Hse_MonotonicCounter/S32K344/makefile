################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/target/m7/src/subdir.mk
-include src/target/m7/S32DS/Startup_Code/subdir.mk
-include src/target/m7/S32DS/Linker_Files/standard/subdir.mk
-include src/Flash/subdir.mk
-include src/subdir.mk
-include services/src/utest/subdir.mk
-include services/src/standard/subdir.mk
-include services/src/shecommandapp/subdir.mk
-include services/src/secure_boot/subdir.mk
-include services/src/monotonic_cnt/subdir.mk
-include services/src/fw_update/standard/subdir.mk
-include services/src/fw_crypto/subdir.mk
-include services/src/fw_attribute/otp/subdir.mk
-include services/src/fw_attribute/non-otp/subdir.mk
-include services/src/common/subdir.mk
-include services/src/subdir.mk
-include framework/host_keymgmt/subdir.mk
-include framework/host_hse/subdir.mk
-include framework/host_crypto_helper/subdir.mk
-include drivers/stm/subdir.mk
-include drivers/nvic/subdir.mk
-include drivers/mu/subdir.mk
-include drivers/flash/subdir.mk
-include drivers/dcm_register/subdir.mk
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
S32K344_DemoAppTemplate.siz \


# All Target
all: S32K344_DemoAppTemplate.elf secondary-outputs

# Tool invocations
S32K344_DemoAppTemplate.elf: $(OBJS) C:/Users/nxf86749/OneDrive\ -\ NXP/S32K3/SW/Security/DemoApp/S32K344_DemoAppTemplate/Project_Settings/Linker_Files/S32K344_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "S32K344_DemoAppTemplate.elf" "@S32K344_DemoAppTemplate.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

S32K344_DemoAppTemplate.siz: S32K344_DemoAppTemplate.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley S32K344_DemoAppTemplate.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
