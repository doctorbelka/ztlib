#include "stm32/spi.h"

namespace stm32 {

bool Spi::setConfig(const void* drvConfig)
{
    (void)drvConfig;
    return true;
}

bool Spi::open()
{
    setOpened(true);
    return true;
}

void Spi::close()
{
    setOpened(false);
}

bool Spi::ioctl(uint32_t cmd, void* pValue)
{
    if (cmd == kSetCs) {
        if (pValue != nullptr) {
            cs_ = static_cast<Gpio*>(pValue);
            return true;
        }
        return false;
    }
    return false;
}

int32_t Spi::write_(const void* buf, uint32_t len)
{
    if (!hspi_ || !buf || len == 0)
        return -1;

    if (cs_)
        cs_->reset();

    const int32_t reg = getReg();
    if (reg >= 0) {
        uint8_t regByte = static_cast<uint8_t>(reg);
        if (HAL_SPI_Transmit(hspi_, &regByte, 1, 1000) != HAL_OK) {
            if (cs_)
                cs_->set();
            return -1;
        }
    }

    int32_t result = HAL_SPI_Transmit(hspi_,
               static_cast<uint8_t*>(const_cast<void*>(buf)),
               len,
               1000)
        == HAL_OK ? static_cast<int32_t>(len) : -1;

    if (cs_)
        cs_->set();

    return result;
}

int32_t Spi::read_(void* buf, uint32_t len)
{
    if (!hspi_ || !buf || len == 0)
        return -1;

    if (cs_)
        cs_->reset();

    const int32_t reg = getReg();
    if (reg >= 0) {
        uint8_t regByte = static_cast<uint8_t>(reg);
        if (HAL_SPI_Transmit(hspi_, &regByte, 1, 1000) != HAL_OK) {
            if (cs_)
                cs_->set();
            return -1;
        }
    }

    int32_t result = HAL_SPI_Receive(hspi_,
               static_cast<uint8_t*>(buf),
               len,
               1000)
        == HAL_OK ? static_cast<int32_t>(len) : -1;

    if (cs_)
        cs_->set();

    return result;
}

} // namespace stm32
