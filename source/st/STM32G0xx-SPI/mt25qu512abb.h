/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file implementes the programming routines for the
 * MT25QU512ABB SPI eeprom.
 */

#include <stdint.h>

#ifndef MT25QU512ABB_H
#define MT25QU512ABB_H

int mt25qu512abb_init(void);

int mt25qu512abb_deinit(void);

int mt25qu512abb_erase_chip();

int mt25qu512abb_erase_sector(uint32_t sector);

int mt25qu512abb_program(uint32_t addr, const uint8_t *data, uint32_t len);

int mt25qu512abb_read(uint32_t addr, uint8_t *data, uint32_t len);

#endif /* MT25QU512ABB_H */
