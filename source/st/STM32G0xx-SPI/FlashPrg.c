/*
 * Copyright (c) 2025 Tenstorrent AI ULC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>

#include "FlashOS.h"

#include "hal/stm32g0xx_ll_spi.h"
#include "hal/stm32g0xx_ll_gpio.h"
#include "hal/stm32g0xx_ll_bus.h"


uint32_t Init(uint32_t adr, uint32_t clk, uint32_t fnc)
{
    LL_SPI_InitTypeDef SPI_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};


    /* Init clocks for SPI1 and GPIO ports */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);


    return 1;
}

uint32_t UnInit(uint32_t fnc)
{
    return 1;
}

uint32_t BlankCheck(uint32_t adr, uint32_t sz, uint8_t pat)
{
    return 1;
}

uint32_t EraseChip(void)
{
    return 1;
}

uint32_t EraseSector(uint32_t adr)
{
    return 1;
}

uint32_t ProgramPage(uint32_t adr, uint32_t sz, uint32_t *buf)
{
    return 1;
}

uint32_t Verify(uint32_t adr, uint32_t sz, uint32_t *buf)
{
    return 1;
}
