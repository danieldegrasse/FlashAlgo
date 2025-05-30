/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef EEPROM_HAL_H
#define EEPROM_HAL_H

#include <stdint.h>

/*
 * This file contains the HAL interface for SPI EEPROMs.
 * It includes initialization, deinit and data transfer functions.
 */

struct eeprom_hal_fns {
    int (*init)(void);
    int (*deinit)(void);
    int (*erase_chip)(void);
    int (*erase_sector)(uint32_t sector);
    int (*program)(uint32_t addr, const uint8_t *data, uint32_t len);
    int (*read)(uint32_t addr, uint8_t *data, uint32_t len);
};

#endif /* EEPROM_HAL_H */
