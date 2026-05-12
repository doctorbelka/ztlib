/*******************************************************************************
 * @file    i2c.h
 * @author  4lagest (zakirodion@gmail.com)
 * @brief   Header file of STM32 I2C bus driver.
 ******************************************************************************/

#pragma once

#include "Core/Inc/i2c.h"
#include "periph/i2c.h"

namespace stm32 {

struct I2cConfig {
    I2C_HandleTypeDef* hi2c;
    uint16_t devAddr;
    uint32_t timeout;
};

class I2c : public ::I2c {
public:
    I2c() = default;

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

private:
    int32_t write_(const void* buf, uint32_t len) override;
    int32_t read_(void* buf, uint32_t len) override;

    I2cConfig config_;
};

} // namespace stm32

/***************************** END OF FILE ************************************/
