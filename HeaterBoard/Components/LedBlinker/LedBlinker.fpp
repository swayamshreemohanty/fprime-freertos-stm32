module HeaterBoard {
    @ Blink led on the stm32 board
    active component LedBlinker {

        # ----------------------------------------------------------------------
        # Ports
        # ----------------------------------------------------------------------

        @ Rate group input - called periodically
        async input port schedIn: Svc.Sched

        @ GPIO write output
        output port gpioWrite: Drv.GpioWrite

        # ----------------------------------------------------------------------
        # Parameters
        # ----------------------------------------------------------------------

        @ Blink interval in rate group ticks
        param BLINK_INTERVAL: U32 default 2

        # ----------------------------------------------------------------------
        # Commands
        # ----------------------------------------------------------------------

        @ Start or stop LED blinking
        async command BLINKING_ON_OFF(
            on_off: Fw.On @< Indicates whether to start or stop blinking
        )

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        @ LED blinking state changed
        event BLINKING_STATE_CHANGE(blinkState: Fw.On) \
          severity activity high \
          format "LED blinking state set to {}"

        @ LED state changed
        event LED_STATE(ledState: Fw.On) \
          severity activity low \
          format "LED state changed to {}"

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

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending command registration messages
        command reg port cmdRegOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}