####
# This sets up the build system for the 'HeaterBoard' project, including
# components and deployments from project.cmake. In addition, it imports the core F Prime components.
####

cmake_minimum_required(VERSION 3.24.2)
project(HeaterBoard C CXX ASM)

###
# F' Core Setup
# This includes all of the F prime core components, and imports the make-system.
###
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime/cmake/FPrime.cmake")

# Include STM32 HAL when cross-compiling
if(CMAKE_CROSSCOMPILING AND FPRIME_PLATFORM STREQUAL "freertos")
  include("${CMAKE_CURRENT_LIST_DIR}/STM32/STM32H7_HAL/CMakeLists_fprime.txt")
endif()

# NOTE: register custom targets between these two lines
fprime_setup_included_code()

# Include FreeRTOS OS layer for F Prime
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime-freertos/library.cmake")

# Add STM32 drivers first (needed by deployments)
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/STM32/STM32GpioDriver")
# TODO: Add STM32UartDriver once communication topology is complete
# add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/STM32/STM32UartDriver")

# This includes project-wide objects
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/HeaterBoard")
