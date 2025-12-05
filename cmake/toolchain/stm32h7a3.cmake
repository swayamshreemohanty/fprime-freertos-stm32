####
# STM32H7A3 Toolchain for Nucleo-H7A3ZI-Q Board
####

set(CMAKE_SYSTEM_NAME "Generic")
set(FPRIME_PLATFORM "freertos")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)

# Path to ARM GCC toolchain
set(TOOLCHAIN_PREFIX "arm-none-eabi-")
find_program(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
find_program(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)

# CPU-specific compiler flags
set(CPU_FLAGS "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb")

# Common compiler flags
set(COMMON_FLAGS "${CPU_FLAGS} -DUSE_HAL_DRIVER -DSTM32H7A3XXQ -Wall -fdata-sections -ffunction-sections")

# C flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11" CACHE STRING "" FORCE)

# C++ flags
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11 -fno-exceptions -fno-rtti -include cinttypes" CACHE STRING "" FORCE)

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -specs=nano.specs -T${CMAKE_CURRENT_LIST_DIR}/../STM32H7_HAL/STM32H7A3XX_FLASH.ld -Wl,--gc-sections -Wl,-Map=output.map" CACHE STRING "" FORCE)

# Tell CMake not to try to link during the test compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Find root path
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
