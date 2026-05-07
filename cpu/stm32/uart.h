#pragma once

#include "Core/Inc/usart.h"
#include "periph/uart.h"
#include "etl/queue.h"
#include <cstdint>
#include <cstddef>

namespace stm32 {

class P_Uart : public ::Uart {
public:
    using IUartQueue = etl::iqueue<uint8_t, etl::memory_model::MEMORY_MODEL_MEDIUM>;

    P_Uart(IUartQueue& tx, IUartQueue& rx, UART_HandleTypeDef* huart);

    bool setConfig(const void* drvConfig) override;
    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

    void start();

    static void irqHandler(P_Uart* uart, bool isRx);

private:
    int32_t write_(const void* buf, uint32_t len) override;
    int32_t read_(void* buf, uint32_t len) override;

    void startTx();

    UART_HandleTypeDef* huart_;
    IUartQueue& txQueue_;
    IUartQueue& rxQueue_;

    volatile bool txBusy_ = false;
    volatile bool rxStarted_ = false;
    uint8_t rxByte_ = 0;
};

template <size_t SIZE>
class Uart final : public P_Uart {
public:
    using UartQueue = etl::queue<uint8_t, SIZE, etl::memory_model::MEMORY_MODEL_MEDIUM>;

    explicit Uart(UART_HandleTypeDef* huart)
        : P_Uart(txQueue_, rxQueue_, huart)
    {
    }

private:
    UartQueue txQueue_;
    UartQueue rxQueue_;
};

} // namespace stm32
