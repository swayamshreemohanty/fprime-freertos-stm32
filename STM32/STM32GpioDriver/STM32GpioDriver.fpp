module Drv {
  @ GPIO driver for STM32
  passive component STM32GpioDriver {

    # ----------------------------------------------------------------------
    # Input ports
    # ----------------------------------------------------------------------

    @ GPIO read port
    sync input port gpioRead: Drv.GpioRead

    @ GPIO write port
    sync input port gpioWrite: Drv.GpioWrite

  }
}
