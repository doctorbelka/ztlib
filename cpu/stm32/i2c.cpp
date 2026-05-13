/*******************************************************************************
 * @file    i2c.cpp
 * @author  4lagest (zakirodion@gmail.com)
 * @brief   STM32 I2C bus driver.
 ******************************************************************************/

#include "stm32/i2c.h"

namespace stm32 {

bool I2c::setConfig(const void* drvConfig)
{
    if (isOpen())
        return false;

    const I2cConfig* config = static_cast<const I2cConfig*>(drvConfig);
    if (config == nullptr || config->hi2c == nullptr) {
        return false;
    }
    config_ = *config;
    return true;
}

bool I2c::open()
{
    if (isOpen() || config_.hi2c == nullptr) {
        return false;
    }

    // if (HAL_I2C_DeInit(config_.hi2c) != HAL_OK || HAL_I2C_Init(config_.hi2c) != HAL_OK
    //     || HAL_I2CEx_ConfigAnalogFilter(config_.hi2c, I2C_ANALOGFILTER_ENABLE) != HAL_OK
    //     || HAL_I2CEx_ConfigDigitalFilter(config_.hi2c, 0) != HAL_OK) {
    //     return false;
    // }

    setOpened(true);
    return true;
}

void I2c::close()
{
    if (!isOpen()) {
        return;
    }

    // if (HAL_I2C_DeInit(config_.hi2c) == HAL_OK) {
        setOpened(false);
    // }
}

bool I2c::ioctl(uint32_t cmd, void* pValue)
{
    if (!isOpen()) {
        return false;
    }

    switch (cmd) {
    case kSetAddress:
        if (pValue != nullptr) {
            setAddr(*static_cast<int32_t*>(pValue));
            return true;
        }
        break;
    default:
        break;
    }

    return false;
}

int32_t I2c::write_(const void* buf, uint32_t len)
{
    if (!isOpen()) {
        return -1;
    }

    int32_t addr = getAddr() >= 0 ? (getAddr() << 1) : -1;
    if (HAL_I2C_Master_Transmit(config_.hi2c, addr, static_cast<uint8_t*>(const_cast<void*>(buf)), len, config_.timeout) != HAL_OK) {
        return -1;
    }

    return len;
}

int32_t I2c::read_(void* buf, uint32_t len)
{
    if (!isOpen()) {
        return -1;
    }

    int32_t addr = getAddr() >= 0 ? (getAddr() << 1) : -1;
    if (HAL_I2C_Master_Receive(config_.hi2c, addr, static_cast<uint8_t*>(buf), len, config_.timeout) != HAL_OK) {
        return -1;
    }

    return len;
}

} // namespace stm32

/***************************** END OF FILE ************************************/
