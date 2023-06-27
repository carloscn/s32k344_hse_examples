################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../framework/host_crypto_helper/hse_host_aead.c \
../framework/host_crypto_helper/hse_host_attrs.c \
../framework/host_crypto_helper/hse_host_cipher.c \
../framework/host_crypto_helper/hse_host_cmac_with_counter.c \
../framework/host_crypto_helper/hse_host_ecc.c \
../framework/host_crypto_helper/hse_host_format_key_catalogs.c \
../framework/host_crypto_helper/hse_host_hash.c \
../framework/host_crypto_helper/hse_host_impex_stream.c \
../framework/host_crypto_helper/hse_host_import_key.c \
../framework/host_crypto_helper/hse_host_kdf.c \
../framework/host_crypto_helper/hse_host_mac.c \
../framework/host_crypto_helper/hse_host_monotonic_counters.c \
../framework/host_crypto_helper/hse_host_rng.c \
../framework/host_crypto_helper/hse_host_rsa_cipher.c \
../framework/host_crypto_helper/hse_host_sign.c \
../framework/host_crypto_helper/hse_host_utils.c 

OBJS += \
./framework/host_crypto_helper/hse_host_aead.o \
./framework/host_crypto_helper/hse_host_attrs.o \
./framework/host_crypto_helper/hse_host_cipher.o \
./framework/host_crypto_helper/hse_host_cmac_with_counter.o \
./framework/host_crypto_helper/hse_host_ecc.o \
./framework/host_crypto_helper/hse_host_format_key_catalogs.o \
./framework/host_crypto_helper/hse_host_hash.o \
./framework/host_crypto_helper/hse_host_impex_stream.o \
./framework/host_crypto_helper/hse_host_import_key.o \
./framework/host_crypto_helper/hse_host_kdf.o \
./framework/host_crypto_helper/hse_host_mac.o \
./framework/host_crypto_helper/hse_host_monotonic_counters.o \
./framework/host_crypto_helper/hse_host_rng.o \
./framework/host_crypto_helper/hse_host_rsa_cipher.o \
./framework/host_crypto_helper/hse_host_sign.o \
./framework/host_crypto_helper/hse_host_utils.o 

C_DEPS += \
./framework/host_crypto_helper/hse_host_aead.d \
./framework/host_crypto_helper/hse_host_attrs.d \
./framework/host_crypto_helper/hse_host_cipher.d \
./framework/host_crypto_helper/hse_host_cmac_with_counter.d \
./framework/host_crypto_helper/hse_host_ecc.d \
./framework/host_crypto_helper/hse_host_format_key_catalogs.d \
./framework/host_crypto_helper/hse_host_hash.d \
./framework/host_crypto_helper/hse_host_impex_stream.d \
./framework/host_crypto_helper/hse_host_import_key.d \
./framework/host_crypto_helper/hse_host_kdf.d \
./framework/host_crypto_helper/hse_host_mac.d \
./framework/host_crypto_helper/hse_host_monotonic_counters.d \
./framework/host_crypto_helper/hse_host_rng.d \
./framework/host_crypto_helper/hse_host_rsa_cipher.d \
./framework/host_crypto_helper/hse_host_sign.d \
./framework/host_crypto_helper/hse_host_utils.d 


# Each subdirectory must supply rules for building sources it contributes
framework/host_crypto_helper/%.o: ../framework/host_crypto_helper/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@framework/host_crypto_helper/hse_host_aead.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


