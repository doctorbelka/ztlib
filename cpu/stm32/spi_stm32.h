#pragma once

#include "periph/spi.h"
#include "periph/serialdrv.h"

extern "C" {
#include "Core/Inc/spi.h"   // CubeMX (HAL SPI_HandleTypeDef)
}

class Gpio; // если у тебя есть GPIO abstraction

/// STM32 HAL implementation of Spi driver
class P_Spi : public Spi {
public:
    explicit P_Spi(SPI_HandleTypeDef* hspi);

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

protected:
    int32_t write_(const void* buf, uint32_t len) override;
    int32_t read_(void* buf, uint32_t len) override;

private:
    void csLow();
    void csHigh();

private:
    SPI_HandleTypeDef* hspi_;
    Gpio* cs_ = nullptr;
};
