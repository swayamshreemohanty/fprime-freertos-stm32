#ifndef DRV_STM32UARTDRIVER_HPP
#define DRV_STM32UARTDRIVER_HPP

#include <STM32/STM32UartDriver/STM32UartDriverComponentAc.hpp>
#include "stm32h7xx_hal.h"

namespace Drv {

class STM32UartDriver : public STM32UartDriverComponentBase {
public:
    // Constructor
    STM32UartDriver(const char* const compName);

    // Initialize component with UART handle
    void configure(UART_HandleTypeDef* huart);

    // Start receiving data
    void startReadThread();

    // Destructor
    ~STM32UartDriver();

private:
    // Handler implementations
    Drv::SendStatus send_handler(
        const FwIndexType portNum,
        Fw::Buffer &sendBuffer
    );

    Drv::PollStatus poll_handler(
        const FwIndexType portNum,
        Fw::Buffer &pollBuffer
    );

    // Member variables
    UART_HandleTypeDef* m_uart;
    
    // RX buffer for DMA/IT reception
    static constexpr U32 RX_BUFFER_SIZE = 256;
    U8 m_rxBuffer[RX_BUFFER_SIZE];
    U32 m_rxHead;
    U32 m_rxTail;
    
    // Circular buffer management
    U32 getBytesAvailable();
    U32 readFromBuffer(U8* dest, U32 size);
};

} // namespace Drv

#endif // DRV_STM32UARTDRIVER_HPP
