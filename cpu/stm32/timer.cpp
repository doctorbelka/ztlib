// #include "timer.h"

// namespace stm32 {
// // Static instance tracking for interrupt routing
// static Timer* timerInstances_[18] = { nullptr };

// // int TimerStm32::getTimerIndex(TIM_TypeDef* instance) {
// //     if (instance == TIM8) return 0;
// //     if (instance == TIM16) return 1;
// //     if (instance == TIM17) return 2;
// //     return -1;
// // }

// static void setHandler(Timer* arg)
// {
//     auto inst = arg->getHandler()->Instance;

//     if (inst == TIM8) {
//         timerInstances_[8] = arg;
//     } else if (inst == TIM16) {
//         timerInstances_[16] = arg;
//     } else if (inst == TIM17) {
//         timerInstances_[17] = arg;
//     }
// }

// Timer::Timer(TIM_HandleTypeDef* htim, Channel channel,  Mode mode)
//     : htim_(htim)
//     , mode_(mode)
//     , channel_(channel)
// {
// }

// bool Timer::setConfig(const void* drvConfig){
//     (void)drvConfig;
//     return true;
// }

// bool Timer::open()
// {
//     if (isOpen() || htim_ == nullptr)
//         return false;
//     setHandler(this);
//     setOpened(true);
//     return true;
// }

// void Timer::close(){
//     if(isOpen()){
//         setOpened(false);
//     }
// }

// void Timer::start()
// {
//     if (!isOpen())
//         return;

//     if (mode_ == Mode::OnePulse) {
//         __HAL_TIM_SET_COUNTER(htim_, 0);
//         HAL_TIM_OnePulse_Start_IT(htim_, channel_);
//     } else {
//         HAL_TIM_PWM_Start_IT(htim_, channel_);
//     }
// }

// void Timer::stop()
// {
//     if (!isOpen() || htim_ == nullptr)
//         return;

//     if (mode_ == Mode::OnePulse) {
//         HAL_TIM_OnePulse_Stop_IT(htim_, channel_);
//     } else {
//         HAL_TIM_PWM_Stop_IT(htim_, channel_);
//     }
// }

// uint32_t Timer::captured() const{
//     return 0;
// }

// void Timer::setCounter(uint32_t counter){
//     __HAL_TIM_SET_COUNTER(htim_, counter);
// }

// uint32_t Timer::counter() const{
//     return __HAL_TIM_GET_COUNTER(htim_);
// }

// bool Timer::ioctl(uint32_t cmd, void* pValue)
// {
//     (void)cmd;
//     (void)pValue;
//     return false;
// }

// void Timer::startChannel(Channel channel, ChannelType type)
// {
//     if (type == ChannelType::Normal) {
//         HAL_TIM_PWM_Start(htim_, channel);
//     }
//     else {
//         HAL_TIMEx_PWMN_Start(htim_, channel);
//     }
// }

// void Timer::stopChannel(Channel channel, ChannelType type)
// {
//     if (type == ChannelType::Normal) {
//         HAL_TIM_PWM_Stop(htim_, channel);
//     }
//     else {
//         HAL_TIMEx_PWMN_Stop(htim_, channel);
//     }
// }

//   void Timer::irqHandler(TIM_HandleTypeDef* htim)
// {
//     if (htim == nullptr)
//         return;

//     Timer* timer = nullptr;

//     if (htim->Instance == TIM8) {
//         timer = timerInstances_[8];
//     }
//     else if (htim->Instance == TIM16) {
//         timer = timerInstances_[16];
//     }
//     else if (htim->Instance == TIM17) {
//         timer = timerInstances_[17];
//     }

//     if (timer == nullptr)
//         return;

//     if (timer->mode_ == Mode::OnePulse) {
//         timer->generalCb().call_if();
//     }
//     else {
//         timer->captureCb().call_if();
//     }
// }
// //     int idx = getTimerIndex(htim->Instance);
// //     if (idx < 0 || instances_[idx] == nullptr)
// //         return;

// //     Timer* timer = instances_[idx];
// //     if (timer->mode_ == Mode::OnePulse) {
// //         // HAL_TIM_OnePulse_Stop_IT(htim, TIM_CHANNEL_1);
// //     } else {
// //         if (htim->Instance == TIM16) {
// //             HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);
// //         } else if (htim->Instance == TIM17) {
// //             HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);
// //         }
// //     }
// // }

// }             // ДОДЕЛАТЬ ПРЕРЫВАНИЕ






// /******************************************************************************
//  * @file    timer.cpp
//  * @brief   STM32 timer driver
//  ******************************************************************************/

// #include "timer.h"

// namespace stm32 {


// static Timer* timerInstances_[3] = { nullptr };


// static void setHandler(Timer* timer)
// {
//     int idx = Timer::getTimerIndex(timer->getHandler()->Instance);

//     if (idx >= 0) {
//         timerInstances_[idx] = timer;
//     }
// }


// int Timer::getTimerIndex(TIM_TypeDef* instance)
// {
//     if (instance == TIM8)
//         return 0;

//     if (instance == TIM16)
//         return 1;

//     if (instance == TIM17)
//         return 2;

//     return -1;
// }

// Timer::Timer(TIM_HandleTypeDef* htim,
//              Channel channel,
//              Mode mode)
//     : htim_(htim)
//     , channel_(channel)
//     , mode_(mode)
// {
// }

// bool Timer::setConfig(const void* drvConfig)
// {
//     (void)drvConfig;
//     return true;
// }

// bool Timer::open()
// {
//     if (isOpen() || htim_ == nullptr)
//         return false;

//     setHandler(this);

//     setOpened(true);

//     return true;
// }

// void Timer::close()
// {
//     if (!isOpen())
//         return;

//     stop();

//     setOpened(false);
// }

// void Timer::start()
// {
//     if (!isOpen() || htim_ == nullptr)
//         return;

//     __HAL_TIM_SET_COUNTER(htim_, 0);

//     switch (mode_) {

//     case Mode::Base:
//         HAL_TIM_Base_Start_IT(htim_);
//         break;

//     default:
//         break;
//     }
// }

// void Timer::stop()
// {
//     // if (!isOpen() || htim_ == nullptr)
//     //     return;

//     // HAL_TIM_Base_Stop_IT(htim_);
//         if (!isOpen() || htim_ == nullptr)
//         return;

//     switch (mode_) {

//     case Mode::Base:
//         HAL_TIM_Base_Stop_IT(htim_);
//         break;

//     default:
//         break;
//     }
// }

// void Timer::startChannel(Channel channel,
//                          ChannelType type)
// {
//     // if (!isOpen() || htim_ == nullptr)
//     //     return;

//     // if (type == ChannelType::Normal) {

//     //     HAL_TIM_PWM_Start(htim_, channel);
//     // }
//     // else {

//     //     HAL_TIMEx_PWMN_Start(htim_, channel);
//     // }

//     if (!isOpen() || htim_ == nullptr)
//         return;

//     __HAL_TIM_SET_COUNTER(htim_, 0);

//     if (type == ChannelType::Normal) {

//         HAL_TIM_PWM_Start(htim_, channel);

//     } else {

//         HAL_TIMEx_PWMN_Start(htim_, channel);
//     }
//     }


// void Timer::stopChannel(Channel channel,
//                         ChannelType type)
// {
//     // if (!isOpen() || htim_ == nullptr)
//     //     return;

//     // if (type == ChannelType::Normal) {

//     //     HAL_TIM_PWM_Stop(htim_, channel);
//     // }
//     // else {

//     //     HAL_TIMEx_PWMN_Stop(htim_, channel);
//     // }
//         if (!isOpen() || htim_ == nullptr)
//         return;

//     switch (mode_) {

//     case Mode::Pwm:
//     case Mode::OnePulse:

//         if (type == ChannelType::Normal) {

//             HAL_TIM_PWM_Stop(htim_, channel);

//         } else {

//             HAL_TIMEx_PWMN_Stop(htim_, channel);
//         }

//         break;

//     default:
//         break;
//     }
// }

// uint32_t Timer::captured() const
// {
//     return 0;
// }

// void Timer::setCounter(uint32_t counter)
// {
//     __HAL_TIM_SET_COUNTER(htim_, counter);
// }

// uint32_t Timer::counter() const
// {
//     return __HAL_TIM_GET_COUNTER(htim_);
// }

// bool Timer::ioctl(uint32_t cmd, void* pValue)
// {
//     (void)cmd;
//     (void)pValue;

//     return false;
// }

// void Timer::irqHandler(TIM_HandleTypeDef* htim)
// {
//     if (htim == nullptr)
//         return;

//     int idx = getTimerIndex(htim->Instance);

//     if (idx < 0)
//         return;

//     Timer* timer = timerInstances_[idx];

//     if (timer == nullptr)
//         return;

//     // TIM update IRQ / OnePulse finished
//     timer->generalCb().call_if();
// }

// } // namespace stm32



/******************************************************************************
 * @file    timer.cpp
 * @brief   STM32 timer driver
 ******************************************************************************/

#include "timer.h"

namespace stm32 {

static Timer* timerInstances_[3] = { nullptr };

static void setHandler(Timer* timer)
{
    int idx = Timer::getTimerIndex(timer->getHandler()->Instance);

    if (idx >= 0) {
        timerInstances_[idx] = timer;
    }
}

int Timer::getTimerIndex(TIM_TypeDef* instance)
{
    if (instance == TIM8)
        return 0;

    if (instance == TIM16)
        return 1;

    if (instance == TIM17)
        return 2;

    return -1;
}

Timer::Timer(TIM_HandleTypeDef* htim,
             Channel channel,
             ChannelType channelType,
             Mode mode)
    : htim_(htim)
    , channel_(channel)
    , channelType_(channelType)
    , mode_(mode)
{
}

bool Timer::setConfig(const void* drvConfig)
{
    (void)drvConfig;
    return true;
}

bool Timer::open()
{
    if (isOpen() || htim_ == nullptr)
        return false;

    setHandler(this);

    setOpened(true);

    return true;
}

void Timer::close()
{
    if (!isOpen())
        return;

    stop();
    stopChannel(channel_);

    setOpened(false);
}

void Timer::start()
{
    if (!isOpen() || htim_ == nullptr)
        return;

    __HAL_TIM_SET_COUNTER(htim_, 0);

    switch (mode_) {

    case Mode::Base:

        HAL_TIM_Base_Start_IT(htim_);
        break;

    case Mode::Pwm:

            startChannel(channel_);
        break;

    case Mode::OnePulse:

        startChannel(channel_);
        break;

    default:
        break;
    }
}

void Timer::stop()
{
    if (!isOpen() || htim_ == nullptr)
        return;

    switch (mode_) {

    case Mode::Base:

        HAL_TIM_Base_Stop_IT(htim_);
        break;

    case Mode::Pwm:

        stopChannel(channel_);
        break;

    case Mode::OnePulse:

        stopChannel(channel_);
        break;

    default:
        break;
    }
}

void Timer::startChannel(Channel channel,
                         ChannelType type)
{
    if (!isOpen() || htim_ == nullptr)
        return;

    __HAL_TIM_SET_COUNTER(htim_, 0);

    if (type == ChannelType::Normal) {

        HAL_TIM_PWM_Start(htim_, channel);

    } else {

        HAL_TIMEx_PWMN_Start(htim_, channel);
    }
}

void Timer::stopChannel(Channel channel,
                        ChannelType type)
{
    if (!isOpen() || htim_ == nullptr)
        return;

    if (type == ChannelType::Normal) {

        HAL_TIM_PWM_Stop(htim_, channel);

    } else {

        HAL_TIMEx_PWMN_Stop(htim_, channel);
    }
}

uint32_t Timer::captured() const
{
    return 0;
}

void Timer::setCounter(uint32_t counter)
{
    __HAL_TIM_SET_COUNTER(htim_, counter);
}

uint32_t Timer::counter() const
{
    return __HAL_TIM_GET_COUNTER(htim_);
}


bool Timer::ioctl(uint32_t cmd, void* pValue)
{
    (void)cmd;
    (void)pValue;

    return false;
}

void Timer::irqHandler(TIM_HandleTypeDef* htim)
{
    if (htim == nullptr)
        return;

    int idx = getTimerIndex(htim->Instance);

    if (idx < 0)
        return;

    Timer* timer = timerInstances_[idx];

    if (timer == nullptr)
        return;

    timer->generalCb().call_if();
}

} // namespace stm32
