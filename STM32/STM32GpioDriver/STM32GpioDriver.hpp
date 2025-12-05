#ifndef DRV_STM32GPIODRIVER_HPP
#define DRV_STM32GPIODRIVER_HPP

#include <STM32/STM32GpioDriver/STM32GpioDriverComponentAc.hpp>
#include "stm32h7xx_hal.h"

namespace Drv {

class STM32GpioDriver : public STM32GpioDriverComponentBase {
public:
    // Constructor
    STM32GpioDriver(const char* const compName);

    // Initialize component
    void init(const FwEnumStoreType instance = 0);

    // Open GPIO with specific port and pin
    bool open(GPIO_TypeDef* port, uint16_t pin);

    // Destructor
    ~STM32GpioDriver();

private:
    // Handler implementations
    Drv::GpioStatus gpioRead_handler(
        const FwIndexType portNum,
        Fw::Logic &state
    );

    Drv::GpioStatus gpioWrite_handler(
        const FwIndexType portNum,
        const Fw::Logic& state
    );

    // Member variables
    GPIO_TypeDef* m_gpio_port;
    uint16_t m_gpio_pin;
    uint32_t m_led_id;  // BSP LED ID (LED_GREEN, LED_YELLOW, LED_RED)
};

} // namespace Drv

#endif // DRV_STM32GPIODRIVER_HPP
