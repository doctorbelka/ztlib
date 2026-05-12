#include "dac.h"

namespace stm32 {

Dac::Dac(DAC_HandleTypeDef* hdac,
         uint32_t channel)
    : hdac_(hdac)
    , channel_(channel)
{
}

bool Dac::setConfig(const void* drvConfig)
{
    (void)drvConfig;
    return true;
}

bool Dac::open()
{
    if (isOpen() || hdac_ == nullptr)
        return false;

    setOpened(true);
    return true;
}

void Dac::close()
{
    if (!isOpen())
        return;

    stop();
    setOpened(false);
}

void Dac::start()
{
    if (!isOpen() || hdac_ == nullptr)
        return;

    HAL_DAC_Start(hdac_, channel_);
    started_ = true;
}

void Dac::stop()
{
    if (!isOpen() || hdac_ == nullptr)
        return;

    HAL_DAC_Stop(hdac_, channel_);
    started_ = false;
}

void Dac::setValue(uint16_t value)
{
    value_ = value;

    if (!isOpen() || hdac_ == nullptr)
        return;

    HAL_DAC_SetValue(hdac_,
                     channel_,
                     DAC_ALIGN_12B_R,
                     value_);
}

uint16_t Dac::value()
{
    return value_;
}

bool Dac::isReady()
{
    return started_;
}

bool Dac::ioctl(uint32_t cmd, void* pValue)
{
    (void)cmd;
    (void)pValue;
    return false;
}

} // namespace stm32
