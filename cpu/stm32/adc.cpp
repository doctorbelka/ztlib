/******************************************************************************
 * @file    adc.cpp
 * @brief   STM32 ADC driver
 ******************************************************************************/

#include "adc.h"

namespace stm32 {

Adc::Adc(ADC_HandleTypeDef* hadc)
    : hadc_(hadc)
{
}

bool Adc::setConfig(const void* drvConfig)
{
    (void)drvConfig;

    return true;
}

bool Adc::open()
{
    if (isOpen() || hadc_ == nullptr)
        return false;

    setOpened(true);

    return true;
}

void Adc::close()
{
    if (!isOpen())
        return;

    stop();

    setOpened(false);
}

void Adc::start()
{
    if (!isOpen() || hadc_ == nullptr)
        return;

    HAL_ADC_Start(hadc_);
}

void Adc::stop()
{
    if (!isOpen() || hadc_ == nullptr)
        return;

    HAL_ADC_Stop(hadc_);
}

bool Adc::isReady()
{
    if (!isOpen() || hadc_ == nullptr)
        return false;

    return HAL_ADC_PollForConversion(hadc_, 10) == HAL_OK;
}

uint16_t Adc::value()
{
    if (!isOpen() || hadc_ == nullptr)
        return 0;

    return HAL_ADC_GetValue(hadc_);
}

bool Adc::ioctl(uint32_t cmd, void* pValue)
{
    (void)cmd;
    (void)pValue;

    return false;
}

} // namespace stm32
