/*******************************************************************************
 * @file    system.cpp
 * @author  4lagest (zakirodion@gmail.com)
 * @brief   STM32 global system class functions.
 ******************************************************************************/

#include "system.h"
#include "version.h"
#include "attr.h"

#include <sys/time.h>

extern uint32_t SystemCoreClock;

/**
 * @brief Sets system frequency with chosen frequency in Hz and source
 *
 * @param freq frequency in Hz
 * @param freqSrc frequency source
 * @return true if frequency updated otherwise false
 */
bool System::setFrequency(uint32_t freq, SysFreqSrc freqSrc)
{
    return true;
}

/**
 * @brief Returns current system frequency
 *
 * @return uint32_t frequency in Hz
 */
uint32_t System::frequency() const
{
    return SystemCoreClock;
}

/**
 * @brief Constructor platform initialization
 */
void System::platformInit()
{
}

/**
 * @brief Restarts CPU
 */
void System::restart()
{
}

/**
 * @brief Switchs CPU to sleep mode with selected wakeup modes
 */
void System::goToSleep() const
{
}

/***************************** END OF FILE ************************************/
