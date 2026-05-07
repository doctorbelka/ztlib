#include "stm32/uart.h"

namespace stm32 {

P_Uart::P_Uart(IUartQueue& tx, IUartQueue& rx, UART_HandleTypeDef* huart)
    : txQueue_(tx), rxQueue_(rx), huart_(huart)
{
    open();
}

bool P_Uart::setConfig(const void* drvConfig)
{
    (void)drvConfig;
    return true;
}

bool P_Uart::open()
{
    if (isOpen())
        return false;

    setOpened(true);
    return true;
}

void P_Uart::close()
{
    if (isOpen()) {
        setOpened(false);
    }
}

bool P_Uart::ioctl(uint32_t cmd, void* pValue)
{
    (void)cmd;
    (void)pValue;
    return false;
}

void P_Uart::start()
{
    rxStarted_ = true;
    HAL_UART_Receive_IT(huart_, &rxByte_, 1);
}

int32_t P_Uart::write_(const void* buf, uint32_t len)
{
    if (!huart_ || !buf || len == 0)
        return -1;

    const uint8_t* data = static_cast<const uint8_t*>(buf);
    size_t written = 0;

    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    for (; written < len && !txQueue_.full(); written++)
    {
        txQueue_.push(data[written]);
    }

    if (!txBusy_ && !txQueue_.empty())
    {
        txBusy_ = true;
        startTx();
    }

    __set_PRIMASK(primask);

    return written;
}

int32_t P_Uart::read_(void* buf, uint32_t len)
{
    if (!buf || len == 0)
        return -1;

    uint8_t* data = static_cast<uint8_t*>(buf);
    size_t read = 0;

    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    for (; read < len && !rxQueue_.empty(); read++)
    {
        data[read] = rxQueue_.front();
        rxQueue_.pop();
    }

    __set_PRIMASK(primask);

    return read;
}

void P_Uart::startTx()
{
    if (txQueue_.empty())
        return;

    uint8_t b = txQueue_.front();
    txQueue_.pop();

    HAL_UART_Transmit_IT(huart_, &b, 1);
}

void P_Uart::irqHandler(P_Uart* uart, bool isRx)
{
    if (isRx) {
        // RX handler
        if (!uart->rxQueue_.full()) {
            uart->rxQueue_.push(uart->rxByte_);
        }
        HAL_UART_Receive_IT(uart->huart_, &uart->rxByte_, 1);
    } else {
        // TX handler
        if (uart->txQueue_.empty()) {
            uart->txBusy_ = false;
        } else {
            uart->startTx();
        }
    }
}

} // namespace stm32
