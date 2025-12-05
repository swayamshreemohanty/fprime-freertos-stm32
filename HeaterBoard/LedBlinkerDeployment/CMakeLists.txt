#####
# 'LedBlinkerDeployment' Deployment:
#
# This registers the 'LedBlinkerDeployment' deployment to the build system. 
# Custom components that have not been added at the project-level should be added to 
# the list below.
#
#####

###
# Topology and Components
###

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

# Add custom components to this specific deployment here
# add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MyComponent/")

register_fprime_deployment(
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
    DEPENDS
        ${FPRIME_CURRENT_MODULE}_Top
)

# Link STM32 HAL library when cross-compiling
if(CMAKE_CROSSCOMPILING AND TARGET stm32h7_hal)
    target_link_libraries(${FPRIME_CURRENT_MODULE} PRIVATE stm32h7_hal)
    target_include_directories(${FPRIME_CURRENT_MODULE} PRIVATE
        ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Core/Inc
        ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Drivers/STM32H7xx_HAL_Driver/Inc
        ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Middlewares/Third_Party/FreeRTOS/Source/include
        ${CMAKE_SOURCE_DIR}/STM32/STM32H7_HAL/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    )
endif()
