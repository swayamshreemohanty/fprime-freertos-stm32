module LedBlinkerDeployment {

  # ----------------------------------------------------------------------
  # Base ID Convention
  # ----------------------------------------------------------------------
  #
  # All Base IDs follow the 8-digit hex format: 0xDSSCCxxx
  #
  # Where:
  #   D   = Deployment digit (1 for this deployment)
  #   SS  = Subtopology digits (00 for main topology, 01-05 for subtopologies)
  #   CC  = Component digits (00, 01, 02, etc.)
  #   xxx = Reserved for internal component items (events, commands, telemetry)
  #

  # ----------------------------------------------------------------------
  # Defaults (Reduced for STM32 memory constraints)
  # ----------------------------------------------------------------------

  module Default {
    constant QUEUE_SIZE = 5
    constant STACK_SIZE = 4 * 1024  # 4KB instead of 64KB
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance rateGroup1: Svc.ActiveRateGroup base id 0x10001000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 43

  instance ledBlinker: HeaterBoard.LedBlinker base id 0x10005000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 39

  instance cmdDisp: Svc.CommandDispatcher base id 0x10006000 \
    queue size 10 \
    stack size Default.STACK_SIZE \
    priority 41

  instance eventLogger: Svc.EventManager base id 0x10007000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 42

  instance tlmSend: Svc.TlmChan base id 0x10008000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 44


  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  instance ledGpioDriver: Drv.STM32GpioDriver base id 0x10010000

  instance osTime: Svc.OsTime base id 0x10011000

  instance rateGroupDriver: Svc.RateGroupDriver base id 0x10012000

  instance systemResources: Svc.SystemResources base id 0x10013000

}
