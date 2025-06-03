/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file implementes the programming routines for the
 * MT25QU512ABB SPI eeprom.
 */

#include <stddef.h>
#include "spi_hal.h"

int mt25qu512abb_init(void)
{
    struct spi_buf buf[2];
    uint8_t jedec_buf[3];
    int ret;
    uint8_t cmd = 0x9F; /* Read JEDEC ID command */
    buf[0].tx_buf = &cmd;
    buf[0].rx_buf = NULL;
    buf[0].len = 1;
    buf[1].tx_buf = NULL;
    buf[1].rx_buf = jedec_buf;
    buf[1].len = sizeof(jedec_buf);


    /* Read JEDEC ID, verify it matches what we expect */
    ret = spi_transfer(buf, 2);
    if (ret != 0) {
        return ret;
    }

    if (jedec_buf[0] != 0x20 || jedec_buf[1] != 0xBB || jedec_buf[2] != 0x20) {
        return -1; /* Invalid JEDEC ID */
    }

    return 0; /* Correct flash chip discovered */
}

int mt25qu512abb_deinit(void)
{
    return 0; /* No deinit required */
}

int mt25qu512abb_erase_chip(void)
{
    return -1; /* Chip erase not implemented */
}

int mt25qu512abb_erase_sector(uint32_t sector)
{
    return -1; /* Sector erase not implemented */
}

int mt25qu512abb_program(uint32_t addr, const uint8_t *data, uint32_t len)
{
    return -1; /* Programming not implemented */
}

int mt25qu512abb_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    return -1; /* Reading not implemented */
}
