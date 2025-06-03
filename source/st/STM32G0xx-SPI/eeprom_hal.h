/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef EEPROM_HAL_H
#define EEPROM_HAL_H

#include <stdint.h>
#include "spi_hal.h"

/*
 * This file contains the HAL interface for SPI EEPROMs.
 * It includes initialization, deinit and data transfer functions.
 */

#ifdef MT25QU512ABB

#include "mt25qu512abb.h"
#define eeprom_init mt25qu512abb_init
#define eeprom_deinit mt25qu512abb_deinit
#define eeprom_erase_chip mt25qu512abb_erase_chip
#define eeprom_erase_sector mt25qu512abb_erase_sector
#define eeprom_program mt25qu512abb_program

#else
#error "No EEPROM HAL implementation defined. Please define MT25QU512ABB or implement your own."

#endif

#endif /* EEPROM_HAL_H */
