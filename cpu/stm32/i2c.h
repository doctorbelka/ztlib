#pragma once

#include "Core/Inc/i2c.h"
#include <cstdint>
#include <cstddef>

class I2c {
public:
    explicit I2c(I2C_HandleTypeDef* hi2c)
        : hi2c_(hi2c) {}

    bool write(uint16_t devAddr,
               const uint8_t* data,
               size_t len,
               uint32_t timeout = 1000)
    {
        return HAL_I2C_Master_Transmit(
                   hi2c_,
                   devAddr << 1,
                   (uint8_t*)data,
                   len,
                   timeout) == HAL_OK;
    }

    bool read(uint16_t devAddr,
              uint8_t* data,
              size_t len,
              uint32_t timeout = 1000)
    {
        return HAL_I2C_Master_Receive(
                   hi2c_,
                   devAddr << 1,
                   data,
                   len,
                   timeout) == HAL_OK;
    }


    bool writeReg(uint16_t devAddr,
                  uint8_t reg,
                  const uint8_t* data,
                  size_t len,
                  uint32_t timeout = 1000)
    {
        uint8_t buf[1 + len];
        buf[0] = reg;

        for (size_t i = 0; i < len; i++)
            buf[i + 1] = data[i];

        return write(devAddr, buf, len + 1, timeout);
    }

    bool readReg(uint16_t devAddr,
                 uint8_t reg,
                 uint8_t* data,
                 size_t len,
                 uint32_t timeout = 1000)
    {
        // write register address
        if (!write(devAddr, &reg, 1, timeout))
            return false;

        // read data
        return read(devAddr, data, len, timeout);
    }

private:
    I2C_HandleTypeDef* hi2c_;
};
