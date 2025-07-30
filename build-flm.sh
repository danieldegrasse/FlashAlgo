#!/bin/bash

# Builds the patched STM32 DFP pack with the STM32G0 flash algorithm
set -e

progen build -t make_gcc_arm stm32g0xx_spi1
arm-none-eabi-objcopy --strip-debug  projectfiles/make_gcc_arm/stm32g0xx_spi1/build/stm32g0xx_spi1.elf \
	flash-algo/STM32G0Bx_SPI1_EEPROM.FLM

progen build -t make_gcc_arm stm32g0xx_spi_combo
arm-none-eabi-objcopy --strip-debug  projectfiles/make_gcc_arm/stm32g0xx_spi_combo/build/stm32g0xx_spi_combo.elf \
	flash-algo/STM32G0Bx_SPI_COMBO_EEPROM.FLM
