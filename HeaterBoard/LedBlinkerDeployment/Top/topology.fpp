module LedBlinkerDeployment {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

  enum Ports_RateGroups {
    rateGroup1
  }

  topology LedBlinkerDeployment {

  # ----------------------------------------------------------------------
  # Instances used in the topology
  # ----------------------------------------------------------------------
    
  # ----------------------------------------------------------------------
  # Instances used in the topology
  # ----------------------------------------------------------------------
    instance rateGroupDriver
    instance rateGroup1
    instance ledGpioDriver
    instance ledBlinker

  # ----------------------------------------------------------------------
  # Pattern graph specifiers
  # ----------------------------------------------------------------------

    connections RateGroups {
      # Rate group driver to rate groups
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      
      # Components called by rate group 1
      rateGroup1.RateGroupMemberOut[0] -> ledBlinker.schedIn
    }

    connections LedBlinkerDeployment {
      # LED blinker to GPIO driver
      ledBlinker.gpioWrite -> ledGpioDriver.gpioWrite
      
      # Time connections for LED blinker
      ledBlinker.timeCaller -> rateGroupDriver.timeGetOut
      
      # Parameter connections for LED blinker
      ledBlinker.prmGetOut -> rateGroupDriver.prmGetOut
      ledBlinker.prmSetOut -> rateGroupDriver.prmSetOut
    }

  }

}
