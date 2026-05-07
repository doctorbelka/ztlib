#pragma once

#include "tim.h"

#ifdef __cplusplus

class TimerStm32 {
public:
    enum class Mode {
        OnePulse,
        Toggle,
    };

    TimerStm32(TIM_HandleTypeDef* htim, Mode mode = Mode::Toggle);

    void start();
    void stop();

    static void irqHandler(TIM_HandleTypeDef* htim);

private:
    TIM_HandleTypeDef* htim_;
    Mode mode_;

    static TimerStm32* instances_[3];
    static int getTimerIndex(TIM_TypeDef* instance);
};

#endif // __cplusplus


