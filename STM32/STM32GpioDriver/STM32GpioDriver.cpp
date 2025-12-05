#include <STM32/STM32GpioDriver/STM32GpioDriver.hpp>
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"  // BSP for LED control

namespace Drv {

STM32GpioDriver::STM32GpioDriver(const char* const compName) :
    STM32GpioDriverComponentBase(compName),
    m_gpio_port(nullptr),
    m_gpio_pin(0),
    m_led_id(LED_GREEN)  // Default to green LED
{
}

void STM32GpioDriver::init(const NATIVE_INT_TYPE instance) {
    STM32GpioDriverComponentBase::init(instance);
}

bool STM32GpioDriver::open(GPIO_TypeDef* port, uint16_t pin, GpioDirection direction) {
    m_gpio_port = port;
    m_gpio_pin = pin;

    // Map GPIO pin to LED ID for Nucleo board
    // You can extend this for other pins
    if (port == GPIOB && pin == GPIO_PIN_0) {
        m_led_id = LED_GREEN;
    } else if (port == GPIOB && pin == GPIO_PIN_14) {
        m_led_id = LED_YELLOW;
    } else if (port == GPIOE && pin == GPIO_PIN_1) {
        m_led_id = LED_RED;
    }

    // Initialize the LED
    BSP_LED_Init(m_led_id);

    return true;
}

Drv::GpioStatus STM32GpioDriver::gpioRead_handler(
    const NATIVE_INT_TYPE portNum,
    Fw::Logic &state
) {
    // Read LED state (on/off)
    uint32_t led_state = BSP_LED_GetState(m_led_id);
    state = (led_state == 1) ? Fw::Logic::HIGH : Fw::Logic::LOW;

    return Drv::GpioStatus::OP_OK;
}

Drv::GpioStatus STM32GpioDriver::gpioWrite_handler(
    const NATIVE_INT_TYPE portNum,
    const Fw::Logic& state
) {
    // Control LED using BSP functions
    if (state == Fw::Logic::HIGH) {
        BSP_LED_On(m_led_id);
    } else {
        BSP_LED_Off(m_led_id);
    }

    return Drv::GpioStatus::OP_OK;
}

STM32GpioDriver::~STM32GpioDriver() {
}

} // namespace Drv
