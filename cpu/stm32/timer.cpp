#include "timer.h"

// Static instance tracking for interrupt routing
TimerStm32* TimerStm32::instances_[3] = {nullptr, nullptr, nullptr};

int TimerStm32::getTimerIndex(TIM_TypeDef* instance) {
    if (instance == TIM8) return 0;
    if (instance == TIM16) return 1;
    if (instance == TIM17) return 2;
    return -1;
}

TimerStm32::TimerStm32(TIM_HandleTypeDef* htim, Mode mode)
    : htim_(htim), mode_(mode)
{
    int idx = getTimerIndex(htim->Instance);
    if (idx >= 0) {
        instances_[idx] = this;
    }
}

void TimerStm32::start() {
    if (htim_ == nullptr) return;

    if (mode_ == Mode::OnePulse) {
        htim_->Instance->CR1 |= TIM_CR1_OPM;
        HAL_TIM_OnePulse_Start_IT(htim_, TIM_CHANNEL_1);
    } else {
        HAL_TIM_Base_Start_IT(htim_);
    }
}

void TimerStm32::stop() {
    if (htim_ == nullptr) return;

    if (mode_ == Mode::OnePulse) {
        HAL_TIM_OnePulse_Stop_IT(htim_, TIM_CHANNEL_1);
    } else {
        HAL_TIM_Base_Stop_IT(htim_);
    }
}

void TimerStm32::irqHandler(TIM_HandleTypeDef* htim) {
    int idx = getTimerIndex(htim->Instance);
    if (idx < 0 || instances_[idx] == nullptr) return;

    TimerStm32* timer = instances_[idx];
    if (timer->mode_ == Mode::OnePulse) {
        // HAL_TIM_OnePulse_Stop_IT(htim, TIM_CHANNEL_1);
    } else {
        if (htim->Instance == TIM16) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);
        } else if (htim->Instance == TIM17) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);
        }
    }
}


