/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file implementes the programming routines for the
 * MT25QU512ABB SPI eeprom.
 */

#include "eeprom_hal.h"

static int mt25qu512abb_init(void)
{
    return 0; /* No init required */
}

static int mt25qu512abb_deinit(void)
{
    return 0; /* No deinit required */
}

static int mt25qu512abb_erase_chip(void)
{
    return -1; /* Chip erase not implemented */
}

static int mt25qu512abb_erase_sector(uint32_t sector)
{
    return -1; /* Sector erase not implemented */
}

static int mt25qu512abb_program(uint32_t addr, const uint8_t *data, uint32_t len)
{
    return -1; /* Programming not implemented */
}

static int mt25qu512abb_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    return -1; /* Reading not implemented */
}

struct eeprom_hal_fns mt25qu512abb_hal_fns = {
    .init = mt25qu512abb_init,
    .deinit = mt25qu512abb_deinit,
    .erase_chip = mt25qu512abb_erase_chip,
    .erase_sector = mt25qu512abb_erase_sector,
    .program = mt25qu512abb_program,
    .read = mt25qu512abb_read,
};
