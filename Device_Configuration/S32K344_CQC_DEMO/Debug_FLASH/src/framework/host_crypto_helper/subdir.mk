################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/framework/host_crypto_helper/hse_host_aead.c \
../src/framework/host_crypto_helper/hse_host_attrs.c \
../src/framework/host_crypto_helper/hse_host_authenc.c \
../src/framework/host_crypto_helper/hse_host_cipher.c \
../src/framework/host_crypto_helper/hse_host_ecc.c \
../src/framework/host_crypto_helper/hse_host_format_key_catalogs.c \
../src/framework/host_crypto_helper/hse_host_hash.c \
../src/framework/host_crypto_helper/hse_host_import_key.c \
../src/framework/host_crypto_helper/hse_host_kdf.c \
../src/framework/host_crypto_helper/hse_host_mac.c \
../src/framework/host_crypto_helper/hse_host_monotonic_counters.c \
../src/framework/host_crypto_helper/hse_host_rng.c \
../src/framework/host_crypto_helper/hse_host_rsa_cipher.c \
../src/framework/host_crypto_helper/hse_host_sign.c \
../src/framework/host_crypto_helper/hse_host_utils.c 

OBJS += \
./src/framework/host_crypto_helper/hse_host_aead.o \
./src/framework/host_crypto_helper/hse_host_attrs.o \
./src/framework/host_crypto_helper/hse_host_authenc.o \
./src/framework/host_crypto_helper/hse_host_cipher.o \
./src/framework/host_crypto_helper/hse_host_ecc.o \
./src/framework/host_crypto_helper/hse_host_format_key_catalogs.o \
./src/framework/host_crypto_helper/hse_host_hash.o \
./src/framework/host_crypto_helper/hse_host_import_key.o \
./src/framework/host_crypto_helper/hse_host_kdf.o \
./src/framework/host_crypto_helper/hse_host_mac.o \
./src/framework/host_crypto_helper/hse_host_monotonic_counters.o \
./src/framework/host_crypto_helper/hse_host_rng.o \
./src/framework/host_crypto_helper/hse_host_rsa_cipher.o \
./src/framework/host_crypto_helper/hse_host_sign.o \
./src/framework/host_crypto_helper/hse_host_utils.o 

C_DEPS += \
./src/framework/host_crypto_helper/hse_host_aead.d \
./src/framework/host_crypto_helper/hse_host_attrs.d \
./src/framework/host_crypto_helper/hse_host_authenc.d \
./src/framework/host_crypto_helper/hse_host_cipher.d \
./src/framework/host_crypto_helper/hse_host_ecc.d \
./src/framework/host_crypto_helper/hse_host_format_key_catalogs.d \
./src/framework/host_crypto_helper/hse_host_hash.d \
./src/framework/host_crypto_helper/hse_host_import_key.d \
./src/framework/host_crypto_helper/hse_host_kdf.d \
./src/framework/host_crypto_helper/hse_host_mac.d \
./src/framework/host_crypto_helper/hse_host_monotonic_counters.d \
./src/framework/host_crypto_helper/hse_host_rng.d \
./src/framework/host_crypto_helper/hse_host_rsa_cipher.d \
./src/framework/host_crypto_helper/hse_host_sign.d \
./src/framework/host_crypto_helper/hse_host_utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/framework/host_crypto_helper/%.o: ../src/framework/host_crypto_helper/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/framework/host_crypto_helper/hse_host_aead.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


