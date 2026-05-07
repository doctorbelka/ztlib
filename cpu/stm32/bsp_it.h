#include "stm32/uart.h"
#include "timer.h"

extern stm32::Uart<4096> uart4;
extern TimerStm32 timer16;
extern TimerStm32 timer17;
extern TimerStm32 timer8;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART4)
        stm32::P_Uart::irqHandler(&uart4, true);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART4)
        stm32::P_Uart::irqHandler(&uart4, false);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM8)
    {
        TimerStm32::irqHandler(htim);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM16 ||
        htim->Instance == TIM17)
    {
        TimerStm32::irqHandler(htim);
    }
}
