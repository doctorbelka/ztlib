#pragma once

#include "Core/Inc/gpio.h"
#include "periph/gpio.h"

namespace stm32{
class Gpio : public ::Gpio {
public:
    Gpio(GPIO_TypeDef* port, uint16_t pin)
        : port_(port), pin_(pin) {}

    void set() override;
    void reset() override;
    void toggle();
    bool get() const override;

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close()override;

    bool ioctl(uint32_t cmd, void* pValue)override;

private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
};
}
