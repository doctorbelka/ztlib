/*******************************************************************************
 * @file    dac.h
 * @brief   DAC peripheral driver interface (STM32 style)
 ******************************************************************************/

#pragma once

#include "basedrv.h"
#include "etl/delegate.h"

/// @brief DAC operating mode
enum class DacMode {
    Normal,
    NoiseWave,
    TriangleWave,
};

/// @brief DAC peripheral driver interface
class Dac : public BaseDrv {
public:
    /**
     * @brief Basic DAC commands
     */
    enum IoctlCmd {
        kSetResolution,   // Sets output resolution (12/8 bit)
        kSetMode,         // Sets DAC mode (normal/wave)
        kSetValue,        // Sets output value
        kSetTrigger,      // Sets trigger source
        kSetUpdateCb,     // Sets update callback
    };

    /**
     * @brief Starts DAC output
     */
    virtual void start() = 0;

    /**
     * @brief Stops DAC output
     */
    virtual void stop() = 0;

    /**
     * @brief Sets output value
     *
     * @param value DAC digital value
     */
    virtual void setValue(uint16_t value) = 0;

    /**
     * @brief Returns last set value
     */
    virtual uint16_t value() = 0;

    /**
     * @brief Checks if DAC is active
     */
    virtual bool isReady() = 0;

    /**
     * @brief Callback for DAC update event (DMA / trigger / update)
     */
    using UpdateDelegate = etl::delegate<void(Dac*, uint16_t)>;

    /**
     * @brief Sets callback for DAC update event
     */
    void setUpdateDelegate(const UpdateDelegate& cb)
    {
        updateCb_ = cb;
    }

protected:
    /**
     * @brief Returns update callback reference
     */
    UpdateDelegate& updateCb()
    {
        return updateCb_;
    }

private:
    UpdateDelegate updateCb_;
};
