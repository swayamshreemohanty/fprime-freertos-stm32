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
// Standard IO for printf
#include <stdio.h>

// Global variables for button state
COM_InitTypeDef BspCOMInit;
__IO uint32_t BspButtonState = 0;  // 0 = RELEASED, 1 = PRESSED

extern "C" {
    void SystemClock_Config(void);
    void Error_Handler(void);
    void MPU_Config(void);
    void MX_GPIO_Init(void);
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
    // MPU Configuration
    MPU_Config();
    
    // Initialize STM32 HAL
    HAL_Init();
    
    // Configure system clock
    SystemClock_Config();
    
    // Initialize GPIO clocks
    MX_GPIO_Init();
    
    // Initialize all LEDs
    BSP_LED_Init(LED_GREEN);
    BSP_LED_Init(LED_YELLOW);
    BSP_LED_Init(LED_RED);
    
    // Initialize USER push-button in interrupt mode
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
    
    // Initialize COM1 port for debug console (115200, 8N1, no flow control)
    BspCOMInit.BaudRate   = 115200;
    BspCOMInit.WordLength = COM_WORDLENGTH_8B;
    BspCOMInit.StopBits   = COM_STOPBITS_1;
    BspCOMInit.Parity     = COM_PARITY_NONE;
    BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
    if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE) {
        Error_Handler();
    }
    
    // Send welcome message
    printf("F' STM32 LED Blinker Starting...\r\n");
    
    // Turn on all LEDs initially
    BSP_LED_On(LED_GREEN);
    BSP_LED_On(LED_YELLOW);
    BSP_LED_On(LED_RED);
    
    // Initialize F Prime Os layer
    Os::init();
    
    // Object for communicating state to the topology (empty for this deployment)
    LedBlinkerDeployment::TopologyState state;
    
    // Setup topology
    LedBlinkerDeployment::setupTopology(state);
    
    printf("F' Topology initialized\r\n");
    
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

// MPU Configuration
extern "C" void MPU_Config(void) {
    MPU_Region_InitTypeDef MPU_InitStruct = {0};

    // Disable the MPU
    HAL_MPU_Disable();

    // Configure the MPU attributes for Region 0 (Full 4GB address space)
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0x0;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    
    // Enable the MPU
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

// GPIO Initialization
extern "C" void MX_GPIO_Init(void) {
    // Enable GPIO Ports Clock
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
}

// System Clock Configuration (from STM32CubeMX)
extern "C" void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // AXI clock gating
    RCC->CKGAENR = 0xE003FFFF;

    // Supply configuration update enable
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    // Initializes the RCC Oscillators according to the specified parameters
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = 64;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 8;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                  RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }
}

// BSP Push Button Callback - Called by interrupt handler
extern "C" void BSP_PB_Callback(Button_TypeDef Button) {
    if (Button == BUTTON_USER) {
        BspButtonState = 1;  // BUTTON_PRESSED
        
        // Toggle all LEDs
        BSP_LED_Toggle(LED_GREEN);
        BSP_LED_Toggle(LED_YELLOW);
        BSP_LED_Toggle(LED_RED);
        
        printf("Button pressed! LEDs toggled\r\n");
        
        // Reset button state
        BspButtonState = 0;  // BUTTON_RELEASED
    }
}

// Error Handler
extern "C" void Error_Handler(void) {
    __disable_irq();
    while (1) {
        // Blink LED to indicate error
        BSP_LED_Toggle(LED_RED);
        HAL_Delay(100);
    }
}
