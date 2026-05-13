#pragma once

#include "periph/adc.h"

#include "adc.h"

namespace stm32 {

class Adc : public ::Adc {
public:
    explicit Adc(ADC_HandleTypeDef* hadc);

    bool setConfig(const void* drvConfig) override;

    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

    void start() override;
    void stop() override;

    bool isReady() override;
    uint16_t value() override;

private:
    ADC_HandleTypeDef* hadc_;
};

} // namespace stm32
