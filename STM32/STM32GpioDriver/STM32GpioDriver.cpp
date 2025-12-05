#include <Drv/STM32GpioDriver/STM32GpioDriver.hpp>
#include "stm32h7xx_hal.h"

namespace Drv {

STM32GpioDriver::STM32GpioDriver(const char* const compName) :
    STM32GpioDriverComponentBase(compName),
    m_gpio_port(nullptr),
    m_gpio_pin(0)
{
}

void STM32GpioDriver::init(const NATIVE_INT_TYPE instance) {
    STM32GpioDriverComponentBase::init(instance);
}

bool STM32GpioDriver::open(GPIO_TypeDef* port, uint16_t pin, GpioDirection direction) {
    m_gpio_port = port;
    m_gpio_pin = pin;

    // GPIO is already initialized by STM32CubeMX MX_GPIO_Init()
    // You can add runtime configuration here if needed

    return true;
}

Drv::GpioStatus STM32GpioDriver::gpioRead_handler(
    const NATIVE_INT_TYPE portNum,
    Fw::Logic &state
) {
    if (m_gpio_port == nullptr) {
        return Drv::GpioStatus::OP_ERROR;
    }

    GPIO_PinState pinState = HAL_GPIO_ReadPin(m_gpio_port, m_gpio_pin);
    state = (pinState == GPIO_PIN_SET) ? Fw::Logic::HIGH : Fw::Logic::LOW;

    return Drv::GpioStatus::OP_OK;
}

Drv::GpioStatus STM32GpioDriver::gpioWrite_handler(
    const NATIVE_INT_TYPE portNum,
    const Fw::Logic& state
) {
    if (m_gpio_port == nullptr) {
        return Drv::GpioStatus::OP_ERROR;
    }

    GPIO_PinState pinState = (state == Fw::Logic::HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(m_gpio_port, m_gpio_pin, pinState);

    return Drv::GpioStatus::OP_OK;
}

STM32GpioDriver::~STM32GpioDriver() {
}

} // namespace Drv
