// ======================================================================
// \title  LedBlinker.cpp
// \author swayamshreemohanty
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================

#include "HeaterBoard/Components/LedBlinker/LedBlinker.hpp"

namespace HeaterBoard {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LedBlinker ::LedBlinker(const char* const compName) : LedBlinkerComponentBase(compName) {}

LedBlinker ::~LedBlinker() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void LedBlinker ::TODO_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace HeaterBoard
