module HeaterBoard {
    @ Blink led on the stm32 board
    active component LedBlinker {

        # ----------------------------------------------------------------------
        # Ports
        # ----------------------------------------------------------------------

        @ Rate group input - called periodically
        sync input port schedIn: Svc.Sched

        @ GPIO write output
        output port gpioWrite: Drv.GpioWrite

        # ----------------------------------------------------------------------
        # Parameters
        # ----------------------------------------------------------------------

        @ Blink interval in rate group ticks
        param BLINK_INTERVAL: U32 default 10

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        @ LED state changed
        event LED_STATE($state: Fw.On) severity activity low format "LED state changed to {}"

        # ----------------------------------------------------------------------
        # Telemetry
        # ----------------------------------------------------------------------

        @ Number of blinks
        telemetry BLINK_COUNT: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}