#include <STM32/STM32UartDriver/STM32UartDriver.hpp>
#include "stm32h7xx_hal.h"
#include <Fw/Types/Assert.hpp>

namespace Drv {

STM32UartDriver::STM32UartDriver(const char* const compName) :
    STM32UartDriverComponentBase(compName),
    m_uart(nullptr),
    m_rxHead(0),
    m_rxTail(0)
{
}

void STM32UartDriver::configure(UART_HandleTypeDef* huart) {
    FW_ASSERT(huart != nullptr);
    m_uart = huart;
    
    // Start UART reception in interrupt mode (single byte at a time)
    HAL_UART_Receive_IT(m_uart, &m_rxBuffer[m_rxHead], 1);
}

void STM32UartDriver::startReadThread() {
    // Notify that we're ready to receive
    this->ready_out(0);
}

Drv::SendStatus STM32UartDriver::send_handler(
    const FwIndexType portNum,
    Fw::Buffer &sendBuffer
) {
    if (m_uart == nullptr) {
        return SendStatus::SEND_ERROR;
    }

    U8* data = sendBuffer.getData();
    U32 size = sendBuffer.getSize();

    // Send data via UART (blocking mode for simplicity)
    HAL_StatusTypeDef status = HAL_UART_Transmit(m_uart, data, size, 1000);

    // Deallocate the buffer after sending
    this->deallocate_out(0, sendBuffer);

    return (status == HAL_OK) ? SendStatus::SEND_OK : SendStatus::SEND_ERROR;
}

Drv::PollStatus STM32UartDriver::poll_handler(
    const FwIndexType portNum,
    Fw::Buffer &pollBuffer
) {
    U32 available = getBytesAvailable();
    
    if (available == 0) {
        return PollStatus::POLL_RETRY;
    }

    // Allocate buffer for received data
    Fw::Buffer recvBuffer = this->allocate_out(0, available);
    
    if (!recvBuffer.isValid()) {
        return PollStatus::POLL_ERROR;
    }

    // Read available data from circular buffer
    U32 bytesRead = readFromBuffer(recvBuffer.getData(), available);
    recvBuffer.setSize(bytesRead);

    // Send received data to upper layer
    this->recv_out(0, recvBuffer, RecvStatus::RECV_OK);

    return PollStatus::POLL_OK;
}

U32 STM32UartDriver::getBytesAvailable() {
    if (m_rxHead >= m_rxTail) {
        return m_rxHead - m_rxTail;
    } else {
        return (RX_BUFFER_SIZE - m_rxTail) + m_rxHead;
    }
}

U32 STM32UartDriver::readFromBuffer(U8* dest, U32 size) {
    U32 bytesRead = 0;
    
    while (bytesRead < size && m_rxTail != m_rxHead) {
        dest[bytesRead++] = m_rxBuffer[m_rxTail];
        m_rxTail = (m_rxTail + 1) % RX_BUFFER_SIZE;
    }
    
    return bytesRead;
}

STM32UartDriver::~STM32UartDriver() {
}

} // namespace Drv

// UART RX Complete Callback (to be called from HAL_UART_RxCpltCallback)
extern "C" void STM32_UART_RxCallback(UART_HandleTypeDef* huart, Drv::STM32UartDriver* driver) {
    // Move head forward
    driver->m_rxHead = (driver->m_rxHead + 1) % Drv::STM32UartDriver::RX_BUFFER_SIZE;
    
    // Start next reception
    HAL_UART_Receive_IT(huart, &driver->m_rxBuffer[driver->m_rxHead], 1);
}
