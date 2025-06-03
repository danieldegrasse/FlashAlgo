/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file implements the programming routines for various SPI EEPROMs.
 */

#include <stddef.h>
#include <string.h>

#include "spi_hal.h"

/* Configuration for EEPROM */
struct spi_nor_config {
    uint8_t read_cmd; /* Read command */
    uint8_t pp_cmd; /* Page program command */
    uint8_t sector_erase_cmd; /* Sector erase command */
    uint8_t chip_erase_cmd; /* Chip erase command */
};

struct spi_nor_chip {
    uint32_t jedec_id; /* JEDEC ID of the chip */
    const struct spi_nor_config config;
};

/*
 * The data section doesn't work with PIC code for Cortex-M0+,
 * so we probe the EEPROM at runtime to find the correct configuration,
 * and allocate everything on the stack.
 */
static int eeprom_probe(struct spi_nor_config *cfg)
{
    struct spi_buf buf[2];
    uint32_t jedec_id = 0;
    int ret;
    uint8_t cmd = 0x9F; /* Read JEDEC ID command */
    buf[0].tx_buf = &cmd;
    buf[0].rx_buf = NULL;
    buf[0].len = 1;
    buf[1].tx_buf = NULL;
    buf[1].rx_buf = (uint8_t *)&jedec_id;
    buf[1].len = 3;
    struct spi_nor_chip eeproms[] = {
        {
            .jedec_id = 0x20BB20, /* JEDEC ID for MT25QU512ABB */
            .config = {
                .read_cmd = 0x13,
                .pp_cmd = 0x12,
                .sector_erase_cmd = 0x21,
                .chip_erase_cmd = 0xC7,
            },
        },
        { .jedec_id = 0, .config = {0} } /* Terminator */
    };
    struct spi_nor_chip *chip;

    /* Read JEDEC ID, match to eeprom */
    ret = spi_transfer(buf, 2);
    if (ret != 0) {
        return ret;
    }

    for (chip = &eeproms[0]; chip->jedec_id != 0; chip++) {
        if (jedec_id == chip->jedec_id) {
            memcpy(cfg, &chip->config, sizeof(struct spi_nor_config));
            return 0;
        }
    }
    return -1; /* No matching chip found */
}

static void fill_addr(uint8_t *addr_buf, uint32_t addr)
{
    addr_buf[0] = (addr >> 24) & 0xFF; /* MSB */
    addr_buf[1] = (addr >> 16) & 0xFF;
    addr_buf[2] = (addr >> 8) & 0xFF;
    addr_buf[3] = addr & 0xFF; /* LSB */
}

int eeprom_init(void)
{
    struct spi_nor_config cfg;

    return eeprom_probe(&cfg);
}

int eeprom_deinit(void)
{
    return 0; /* No deinit required */
}

int eeprom_erase_chip(void)
{
    return -1; /* Chip erase not implemented */
}

int eeprom_erase_sector(uint32_t sector)
{
    return -1; /* Sector erase not implemented */
}

int eeprom_program(uint32_t addr, const uint8_t *data, uint32_t len)
{
    return -1; /* Programming not implemented */
}

int eeprom_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    struct spi_nor_config cfg;
    struct spi_buf buf[2];
    uint8_t cmd_buf[5];

    volatile int i = 0;
    while (i == 0) {
        /* Wait for debugger */
    }

    if (eeprom_probe(&cfg) != 0) {
        return -1; /* EEPROM probe failed */
    }

    if (data == NULL || len == 0) {
        return -1; /* Invalid parameters */
    }

    /* Populate command buffer */
    cmd_buf[0] = cfg.read_cmd; /* Read command */
    fill_addr(&cmd_buf[1], addr); /* Address in big-endian format */

    buf[0].tx_buf = cmd_buf;
    buf[0].rx_buf = NULL;
    buf[0].len = 5; /* 1 byte command + 4 bytes address */
    buf[1].tx_buf = NULL;
    buf[1].rx_buf = data;
    buf[1].len = len;
    return spi_transfer(buf, 2);
}
