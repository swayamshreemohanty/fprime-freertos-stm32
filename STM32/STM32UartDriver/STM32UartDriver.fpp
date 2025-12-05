module Drv {
  @ UART driver for STM32 providing byte stream interface
  passive component STM32UartDriver {

    # ----------------------------------------------------------------------
    # Import byte stream driver interface
    # ----------------------------------------------------------------------

    import Drv.ByteStreamDriver

    # ----------------------------------------------------------------------
    # Additional ports for buffer management
    # ----------------------------------------------------------------------

    @ Port for allocation of buffers to receive data
    output port allocate: Fw.BufferGet

    @ Port for deallocation of buffers from received data
    output port deallocate: Fw.BufferSend

    @ Port to poll for received data (called from rate group)
    sync input port poll: Svc.Sched

  }
}
