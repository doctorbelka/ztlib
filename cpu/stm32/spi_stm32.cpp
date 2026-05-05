#include "cpu/stm32/spi_stm32.h"

//------------------------------------------------------------

P_Spi::P_Spi(SPI_HandleTypeDef* hspi)
    : hspi_(hspi)
{
}

//------------------------------------------------------------

bool P_Spi::setConfig(const void* drvConfig)
{
    // CubeMX уже полностью инициализирует SPI
    // здесь ничего не делаем (ВАЖНО)
    (void)drvConfig;
    return true;
}

//------------------------------------------------------------

bool P_Spi::open()
{
    if (!hspi_)
        return false;

    setOpened(true);
    return true;
}

//------------------------------------------------------------

void P_Spi::close()
{
    setOpened(false);
}

//------------------------------------------------------------

bool P_Spi::ioctl(uint32_t cmd, void* pValue)
{
    switch (cmd)
    {
        case kSetCs:
            cs_ = static_cast<Gpio*>(pValue);
            return true;

        default:
            return false;
    }
}

//------------------------------------------------------------

void P_Spi::csLow()
{
    if (cs_)
        cs_->reset();   // LOW
}

//------------------------------------------------------------

void P_Spi::csHigh()
{
    if (cs_)
        cs_->set();     // HIGH
}

//------------------------------------------------------------

int32_t P_Spi::write_(const void* buf, uint32_t len)
{
    if (!isOpen())
        return -1;

    csLow();

    auto status = HAL_SPI_Transmit(
        hspi_,
        (uint8_t*)buf,
        len,
        HAL_MAX_DELAY
    );

    csHigh();

    return (status == HAL_OK) ? (int32_t)len : -1;
}

//------------------------------------------------------------

int32_t P_Spi::read_(void* buf, uint32_t len)
{
    if (!isOpen())
        return -1;

    csLow();

    auto status = HAL_SPI_Receive(
        hspi_,
        (uint8_t*)buf,
        len,
        HAL_MAX_DELAY
    );

    csHigh();

    return (status == HAL_OK) ? (int32_t)len : -1;
}
