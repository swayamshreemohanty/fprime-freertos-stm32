// ======================================================================
// \title  LedBlinker.cpp
// \author swayamshreemohanty
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================

#include "HeaterBoard/Components/LedBlinker/LedBlinker.hpp"
#include <Fw/Types/BasicTypes.hpp>

namespace HeaterBoard {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LedBlinker::LedBlinker(const char* const compName) : 
    LedBlinkerComponentBase(compName),
    m_blinkCount(0),
    m_ledState(false),
    m_cycleCount(0)
{}

LedBlinker::~LedBlinker() {}

// ----------------------------------------------------------------------
// Handler implementations
// ----------------------------------------------------------------------

void LedBlinker::schedIn_handler(
    const NATIVE_INT_TYPE portNum,
    NATIVE_UINT_TYPE context
) {
    m_cycleCount++;

    // Get blink interval parameter
    Fw::ParamValid valid;
    U32 interval = paramGet_BLINK_INTERVAL(valid);
    if (valid != Fw::ParamValid::VALID) {
        interval = 10; // Default to 10 ticks (1 second at 10Hz rate group)
    }

    // Toggle LED at specified interval
    if (m_cycleCount >= interval) {
        m_cycleCount = 0;
        m_ledState = !m_ledState;

        // Write to GPIO
        Fw::Logic logicState = m_ledState ? Fw::Logic::HIGH : Fw::Logic::LOW;
        this->gpioWrite_out(0, logicState);

        // Send telemetry
        m_blinkCount++;
        this->tlmWrite_BLINK_COUNT(m_blinkCount);

        // Send event
        Fw::On onState = m_ledState ? Fw::On::ON : Fw::On::OFF;
        this->log_ACTIVITY_LO_LED_STATE(onState);
    }
}

}  // namespace HeaterBoard
