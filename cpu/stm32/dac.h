/*******************************************************************************
 * @file    dac.h
 * @brief   STM32 DAC driver wrapper
 ******************************************************************************/

#pragma once

#include <cstdint>
#include "Core/Inc/dac.h"   // STM32 HAL DAC handle
#include "periph/dac.h"

namespace stm32 {

/// @brief STM32 DAC channel abstraction
class Dac final : public ::Dac {
public:
   /**
    * @brief Construct a new Dac object
    *
    * @param hdac
    * @param channel DAC_CHANNEL_1
    *                DAC_CHANNEL_2
    */
    Dac(DAC_HandleTypeDef* hdac, uint32_t channel);

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

    void start() override;
    void stop() override;

    void setValue(uint16_t value) override;
    uint16_t value() override;

    bool isReady() override;

private:
    DAC_HandleTypeDef* hdac_;
    uint32_t channel_;

    uint16_t value_ = 0;
    bool started_ = false;
};

} // namespace stm32
