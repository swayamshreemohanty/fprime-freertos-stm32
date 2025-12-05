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
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command TODO
    //!
    //! TODO
    void TODO_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq            //!< The command sequence number
                         ) override;
};

}  // namespace HeaterBoard

#endif
