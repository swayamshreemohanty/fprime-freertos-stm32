####
# STM32 UART Driver
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/STM32UartDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/STM32UartDriver.cpp"
)

register_fprime_module()

# Include STM32 HAL headers
target_include_directories(${FPRIME_CURRENT_MODULE} PUBLIC
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Core/Inc
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/STM32H7xx_HAL_Driver/Inc
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/BSP/STM32H7xx_Nucleo
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/CMSIS/Device/ST/STM32H7xx/Include
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/CMSIS/Include
)

# Link against STM32 HAL
target_link_libraries(${FPRIME_CURRENT_MODULE} PUBLIC stm32h7_hal)
