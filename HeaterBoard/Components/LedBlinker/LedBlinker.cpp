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
    m_cycleCount(0),
    m_blinking(true)  // Start with blinking ENABLED
{}

LedBlinker::~LedBlinker() {}

// ----------------------------------------------------------------------
// Handler implementations
// ----------------------------------------------------------------------

void LedBlinker::schedIn_handler(
    const FwIndexType portNum,
    U32 context
) {
    // Only blink if blinking is enabled
    if (!m_blinking) {
        return;
    }

    m_cycleCount++;

    // Get blink interval parameter
    Fw::ParamValid valid;
    U32 interval = paramGet_BLINK_INTERVAL(valid);
    if (valid != Fw::ParamValid::VALID) {
        interval = 2; // Default to 2 ticks
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

void LedBlinker::BLINKING_ON_OFF_cmdHandler(
    FwOpcodeType opCode,
    U32 cmdSeq,
    Fw::On on_off
) {
    // Set blinking state
    m_blinking = (on_off == Fw::On::ON);
    
    // Reset cycle counter when state changes
    m_cycleCount = 0;
    
    // If turning off, ensure LED is also off
    if (!m_blinking && m_ledState) {
        m_ledState = false;
        this->gpioWrite_out(0, Fw::Logic::LOW);
    }
    
    // Send event
    this->log_ACTIVITY_HI_BLINKING_STATE_CHANGE(on_off);
    
    // Send command response
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace HeaterBoard
