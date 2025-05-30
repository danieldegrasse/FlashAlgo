/*
 * Copyright (c) 2025, Tenstorrent AI ULC
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SPI_HAL_H
#define SPI_HAL_H

#include <stdint.h>

/*
 * This file contains the HAL interface for SPI peripherals.
 * It includes initialization, deinit and data transfer functions.
 */

struct spi_buf {
    /* Pointer to transmit buffer. If NULL 0xFF will be clocked. */
    uint8_t *tx_buf;
    /* Pointer to receive buffer. If NULL data will be discarded. */
    uint8_t *rx_buf;
    /* Length of the buffer in bytes. */
    uint32_t len;
};

struct spi_hal_fns {
    int (*init)(void);
    int (*deinit)(void);
    int (*transfer)(struct spi_buf *bufs, uint8_t cnt);
};

#endif /* SPI_HAL_H */
