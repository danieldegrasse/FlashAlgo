#!/bin/bash

# Builds the patched STM32 DFP pack with the STM32G0 flash algorithm
set -e

progen build -t make_gcc_arm stm32g0xx_spi
arm-none-eabi-objcopy --strip-debug  projectfiles/make_gcc_arm/stm32g0xx_spi/build/stm32g0xx_spi.elf \
	flash-algo/STM32G0Bx_SPI_EEPROM.FLM
