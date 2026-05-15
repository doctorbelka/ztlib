// #pragma once

// #include "periph/timer.h"
// #include "tim.h"

// namespace stm32 {
// enum class Mode {
//     OnePulse,
//     Toggle,
// };

// enum Channel {
//     Channel1 = TIM_CHANNEL_1,
//     Channel2 = TIM_CHANNEL_2,
//     Channel3 = TIM_CHANNEL_3,
//     Channel4 = TIM_CHANNEL_4,
//     Channel5 = TIM_CHANNEL_5,
//     Channel6 = TIM_CHANNEL_6,
//     ChannelAll = TIM_CHANNEL_ALL,
// };

// enum class ChannelType {
//     Normal,
//     Complementary
// };

// class Timer : public ::Timer {
// public:
//     Timer(TIM_HandleTypeDef* htim, Channel channel, Mode mode = Mode::Toggle);

//     bool setConfig(const void* drvConfig) override;
//     bool open() override;
//     void close() override;

//     bool ioctl(uint32_t cmd, void* pValue) override;

//     void start() override;
//     void stop() override;

//     uint32_t captured() const override;
//     void setCounter(uint32_t counter) override;
//     uint32_t counter() const override;

//     static void irqHandler(TIM_HandleTypeDef* htim);

//     TIM_HandleTypeDef* getHandler()
//     {
//         return htim_;
//     }

//     void startChannel(Channel channel, ChannelType type);
//     void stopChannel(Channel channel, ChannelType type);

// private:
//     TIM_HandleTypeDef* htim_;
//     Mode mode_;
//     Channel channel_;
//     static int getTimerIndex(TIM_TypeDef* instance);
// };

// }


#pragma once

#include "periph/timer.h"
#include "tim.h"

namespace stm32 {

enum class Mode {
    Base,
    OnePulse,
    Pwm,
};

enum class ChannelType {
    Normal,
    Complementary
};

enum Channel {
    Channel1 = TIM_CHANNEL_1,
    Channel2 = TIM_CHANNEL_2,
    Channel3 = TIM_CHANNEL_3,
    Channel4 = TIM_CHANNEL_4,
};

class Timer : public ::Timer {
public:
    Timer(TIM_HandleTypeDef* htim,
          Channel channel,
          ChannelType channelType = ChannelType::Normal,
          Mode mode = Mode::Base);

    bool setConfig(const void* drvConfig) override;

    bool open() override;
    void close() override;

    bool ioctl(uint32_t cmd, void* pValue) override;

    void start() override;
    void stop() override;

    uint32_t captured() const override;

    void setCounter(uint32_t counter) override;
    uint32_t counter() const override;

    void startChannel(Channel channel,
                      ChannelType type = ChannelType::Normal);

    void stopChannel(Channel channel,
                     ChannelType type = ChannelType::Normal);

    static void irqHandler(TIM_HandleTypeDef* htim);

    TIM_HandleTypeDef* getHandler()
    {
        return htim_;
    }

    static int getTimerIndex(TIM_TypeDef* instance);

private:
    TIM_HandleTypeDef* htim_;
    Channel channel_;
    ChannelType channelType_;
    Mode mode_;
};

} // namespace stm32
