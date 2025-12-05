module Drv {
  @ UART driver for STM32 providing byte stream interface
  passive component STM32UartDriver {

    # ----------------------------------------------------------------------
    # Ports for byte stream driver model
    # ----------------------------------------------------------------------

    @ Port for sending data
    sync input port send: Drv.ByteStreamSend

    @ Port for receiving ready notification  
    output port ready: Drv.ByteStreamReady

    @ Port for receiving data callbacks
    output port recv: Drv.ByteStreamRecv

    @ Port for allocation of buffers to receive data
    output port allocate: Fw.BufferGet

    @ Port for deallocation of buffers from received data
    output port deallocate: Fw.BufferSend

    @ Port to poll for received data
    sync input port poll: Drv.ByteStreamPoll

  }
}
