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
    instance rateGroup1
    instance rateGroupDriver
    instance systemResources
    instance osTime
    instance ledBlinker
    instance ledGpioDriver

  # ----------------------------------------------------------------------
  # Pattern graph specifiers
  # ----------------------------------------------------------------------

    time connections instance osTime

  # ----------------------------------------------------------------------
  # Telemetry packets (only used when TlmPacketizer is used)
  # ----------------------------------------------------------------------

    # include "LedBlinkerDeploymentPackets.fppi"

  # ----------------------------------------------------------------------
  # Direct graph specifiers
  # ----------------------------------------------------------------------

    connections RateGroups {
      # Rate group driver driven by osTime
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      
      # Rate group 1 connections
      rateGroup1.RateGroupMemberOut[0] -> systemResources.run
      rateGroup1.RateGroupMemberOut[1] -> ledBlinker.schedIn
    }

    connections LedBlinker {
      # LED Blinker to GPIO Driver
      ledBlinker.gpioWrite -> ledGpioDriver.gpioWrite
    }

  }

}
