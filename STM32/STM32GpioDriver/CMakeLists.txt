####
# STM32 GPIO Driver
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/STM32GpioDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/STM32GpioDriver.cpp"
)

register_fprime_module()

# Include STM32 HAL headers
target_include_directories(${FPRIME_CURRENT_MODULE} PUBLIC
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Core/Inc
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/STM32H7xx_HAL_Driver/Inc
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/CMSIS/Device/ST/STM32H7xx/Include
  ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/CMSIS/Include
)
