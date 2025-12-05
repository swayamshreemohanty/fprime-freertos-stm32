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
