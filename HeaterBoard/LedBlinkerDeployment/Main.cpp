// ======================================================================
// \title  Main.cpp
// \brief main program for the F' STM32 LED Blinker application
//
// ======================================================================
// Used to access topology functions
#include <HeaterBoard/LedBlinkerDeployment/Top/LedBlinkerDeploymentTopology.hpp>
#include <HeaterBoard/LedBlinkerDeployment/Top/LedBlinkerDeploymentTopologyAc.hpp>
// STM32 HAL and BSP
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"
// OSAL initialization
#include <Os/Os.hpp>
// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

extern "C" {
    void SystemClock_Config(void);
    void Error_Handler(void);
}

/**
 * \brief Rate group task for LED blinker
 */
void rateGroupTask(void *pvParameters) {
    // Drive rate group at 1Hz
    U32 counter = 0;
    while (1) {
        // Cycle the rate group driver
        Os::RawTime cycleStart;
        cycleStart.now();
        LedBlinkerDeployment::rateGroupDriver.get_CycleIn_InputPort(0)->invoke(cycleStart);
        
        // Wait for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
        counter++;
    }
}

/**
 * \brief main entry point for STM32
 */
int main(void) {
    // Initialize STM32 HAL
    HAL_Init();
    
    // Configure system clock
    SystemClock_Config();
    
    // Initialize LED GPIO
    BSP_LED_Init(LED_GREEN);
    
    // Initialize F Prime Os layer
    Os::init();
    
    // Object for communicating state to the topology (empty for this deployment)
    LedBlinkerDeployment::TopologyState state;
    
    // Setup topology
    LedBlinkerDeployment::setupTopology(state);
    
    // Create rate group task
    xTaskCreate(rateGroupTask, "RateGroup", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, NULL);
    
    // Start FreeRTOS scheduler
    vTaskStartScheduler();
    
    // Should never reach here
    while (1) {
        Error_Handler();
    }
    
    return 0;
}

// System Clock Configuration (from STM32CubeMX)
extern "C" void SystemClock_Config(void) {
    // This function should be implemented based on your STM32 HAL project
    // For now, using default configuration
}

// Error Handler
extern "C" void Error_Handler(void) {
    __disable_irq();
    while (1) {
        // Blink LED to indicate error
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(100);
    }
}
