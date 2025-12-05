// ======================================================================
// \title  LedBlinker.hpp
// \author swayamshreemohanty
// \brief  hpp file for LedBlinker component implementation class
// ======================================================================

#ifndef HeaterBoard_LedBlinker_HPP
#define HeaterBoard_LedBlinker_HPP

#include "HeaterBoard/Components/LedBlinker/LedBlinkerComponentAc.hpp"
#include <Fw/Types/BasicTypes.hpp>

namespace HeaterBoard {

class LedBlinker final : public LedBlinkerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct LedBlinker object
    LedBlinker(const char* const compName  //!< The component name
    );

    //! Destroy LedBlinker object
    ~LedBlinker();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations
    // ----------------------------------------------------------------------

    //! Handler for schedIn port
    void schedIn_handler(
        const FwIndexType portNum,  //!< The port number
        U32 context                 //!< The call order
    ) override;

    //! Handler for command BLINKING_ON_OFF
    void BLINKING_ON_OFF_cmdHandler(
        FwOpcodeType opCode,        //!< The opcode
        U32 cmdSeq,                 //!< The command sequence number
        Fw::On on_off               //!< Blinking state
    ) override;

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    U32 m_blinkCount;   //!< Number of blinks
    bool m_ledState;    //!< Current LED state
    U32 m_cycleCount;   //!< Cycle counter for blink interval
    bool m_blinking;    //!< Is blinking enabled
};

}  // namespace HeaterBoard

#endif
