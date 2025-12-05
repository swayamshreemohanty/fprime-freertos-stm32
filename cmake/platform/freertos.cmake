####
# FreeRTOS Platform Configuration
####

# Define OS type
add_definitions(-DTGT_OS_TYPE_FREERTOS)

# Disable POSIX
set(FPRIME_USE_POSIX OFF CACHE BOOL "Use POSIX" FORCE)

# Use FPrime Types for FreeRTOS
include_directories(SYSTEM "${FPRIME_FRAMEWORK_PATH}/Fw/Types/Linux")

# No baremetal scheduler (we're using FreeRTOS tasks)
set(FPRIME_USE_BAREMETAL_SCHEDULER OFF CACHE BOOL "Use baremetal scheduler" FORCE)

# Define platform size types for 32-bit ARM Cortex-M7
# These map to standard C99 types available after we added stdint.h
add_compile_definitions(
    PLATFORM_INT_TYPE=int32_t
    PLATFORM_UINT_TYPE=uint32_t  
    PLATFORM_POINTER_CAST_TYPE=uintptr_t
    FW_AMPCS_COMPATIBLE=0
)

# Use smaller types for embedded system
set(FW_SIZE_TYPE "U32" CACHE STRING "Size type for embedded")
set(FW_SIGNED_SIZE_TYPE "I32" CACHE STRING "Signed size type for embedded")

