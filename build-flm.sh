#!/bin/bash

# Builds the patched STM32 DFP pack with the STM32G0 flash algorithm
set -e

progen build -t make_gcc_arm stm32g0xx_spi
arm-none-eabi-objcopy --strip-debug  projectfiles/make_gcc_arm/stm32g0xx_spi/build/stm32g0xx_spi.elf \
	stm32g0-pack/CMSIS/Flash/STM32G0Bx_SPI_EEPROM.FLM
SHASUM=$(sha1sum stm32g0-pack/CMSIS/Flash/STM32G0Bx_SPI_EEPROM.FLM | awk '{print $1}')
sed -i "s/.*STM32G0Bx_SPI_EEPROM.FLM/$SHASUM *.\/CMSIS\/Flash\/STM32G0Bx_SPI_EEPROM.FLM/" \
	stm32g0-pack/Keil.STM32G0xx_DFP.sha1
zip -r projectfiles/stm32_dfp_patched.pack stm32g0-pack/*
