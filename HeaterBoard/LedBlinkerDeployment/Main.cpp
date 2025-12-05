// ======================================================================
// \title  Main.cpp
// \brief main program for STM32 LED Blinker with FreeRTOS
//
// ======================================================================
// Used to access topology functions
#include <LedBlinkerDeployment/Top/LedBlinkerDeploymentTopology.hpp>
// STM32 HAL and FreeRTOS
#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
// Used for printf functions
#include <cstdio>

// External functions from STM32CubeMX generated code
extern "C" {
    void SystemClock_Config(void);
    void MX_GPIO_Init(void);
    void Error_Handler(void);
}

/**
 * \brief FreeRTOS task for FPrime rate group cycling
 *
 * This task cycles the rate groups at 10Hz (100ms period)
 */
void fprimeTask(void* pvParameters) {
    (void)pvParameters;
    
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // 10Hz rate group
    
    while (1) {
        // Cycle rate groups
        LedBlinkerDeployment::cycleTick();
        
        // Wait for next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/**
 * \brief execute the program
 *
 * This is the main entry point for the STM32 LED Blinker application
 *
 * @return: never returns (embedded system)
 */
int main(void) {
    // Reset of all peripherals, Initializes the Flash interface and the Systick
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize all configured peripherals
    MX_GPIO_Init();

    // Setup topology
    LedBlinkerDeployment::TopologyState inputs;
    LedBlinkerDeployment::setupTopology(inputs);

    // Configure GPIO for LED (assuming LED is on a specific pin)
    // This should match your CubeMX configuration
    // Example: Using GPIO pin for LED
    LedBlinkerDeployment::ledGpioDriver.open(GPIOB, GPIO_PIN_0, Drv::GpioDirection::OUT);

    // Create FPrime task
    xTaskCreate(fprimeTask, "FPrime", 2048, NULL, tskIDLE_PRIORITY + 2, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1) {
        Error_Handler();
    }
    
    return 0;
}

