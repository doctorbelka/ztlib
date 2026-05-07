#include "stm32/gpio.h"

namespace stm32{
    void Gpio::set() {
        HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_SET);
    }

    void Gpio::reset() {
        HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
    }

    void Gpio::toggle() {
        HAL_GPIO_TogglePin(port_, pin_);
    }

    bool Gpio::get() const {
        return HAL_GPIO_ReadPin(port_, pin_) == GPIO_PIN_SET;
    }



    bool Gpio::setConfig(const void* drvConfig)
    {
        (void)drvConfig;
        return true;
    }

    bool Gpio::open()
    {
        setOpened(true);
        return true;
    }

    void Gpio::close()
    {
        setOpened(false);
    }

    bool Gpio::ioctl(uint32_t cmd, void* pValue)
    {
        (void)cmd;
        (void)pValue;
        return false;
    }
}
