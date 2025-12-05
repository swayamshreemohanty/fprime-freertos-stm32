// ======================================================================
// \title  LedBlinker.hpp
// \author swayamshreemohanty
// \brief  hpp file for LedBlinker component implementation class
// ======================================================================

#ifndef HeaterBoard_LedBlinker_HPP
#define HeaterBoard_LedBlinker_HPP

#include "HeaterBoard/Components/LedBlinker/LedBlinkerComponentAc.hpp"

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
        const NATIVE_INT_TYPE portNum,  //!< The port number
        NATIVE_UINT_TYPE context        //!< The call order
    ) override;

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    U32 m_blinkCount;   //!< Number of blinks
    bool m_ledState;    //!< Current LED state
    U32 m_cycleCount;   //!< Cycle counter for blink interval
};

}  // namespace HeaterBoard

#endif
