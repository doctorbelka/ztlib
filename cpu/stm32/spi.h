#pragma once

#include "Core/Inc/spi.h"
#include "periph/gpio.h"
#include "periph/spi.h"
#include <cstddef>
#include <cstdint>

namespace stm32 {

class Spi : public ::Spi {
public:
    explicit Spi(SPI_HandleTypeDef* hspi)
        : hspi_(hspi)
    {
        open();
    }

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close() override;
    bool ioctl(uint32_t cmd, void* pValue) override;

    // bool write(const void* data, size_t len, uint32_t timeout = 1000)
    // {
    //     return HAL_SPI_Transmit(hspi_,
    //                static_cast<uint8_t*>(const_cast<void*>(data)),
    //                len,
    //                timeout)
    //         == HAL_OK;
    // }

    // bool read(void* data, size_t len, uint32_t timeout = 1000)
    // {
    //     return HAL_SPI_Receive(hspi_,
    //                static_cast<uint8_t*>(data),
    //                len,
    //                timeout)
    //         == HAL_OK;
    // }

    // bool transfer(const void* tx,
    //     void* rx,
    //     size_t len,
    //     uint32_t timeout = 1000)
    // {
    //     return HAL_SPI_TransmitReceive(hspi_,
    //                static_cast<uint8_t*>(const_cast<void*>(tx)),
    //                static_cast<uint8_t*>(rx),
    //                len,
    //                timeout)
    //         == HAL_OK;
    // }

private:
    int32_t write_(const void* buf, uint32_t len) override;
    int32_t read_(void* buf, uint32_t len) override;

    SPI_HandleTypeDef* hspi_;
    Gpio* cs_ = nullptr;
};

} // namespace stm32
