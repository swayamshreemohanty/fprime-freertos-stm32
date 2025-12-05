####
# Platform FPP types module
#
# This module provides platform-specific type definitions through FPP for FreeRTOS/STM32.
# It contains PlatformTypes.fpp which defines types like PlatformSizeType, 
# PlatformIndexType, etc. optimized for the 32-bit ARM embedded platform.
####

register_fprime_config(
        FreeRTOSPlatformTypes
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/PlatformTypes.fpp"
    HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/PlatformTypes.h"
    CHOOSES_IMPLEMENTATIONS
        Os_File_Stub
        Os_Console_Stub
        Os_Task_FreeRTOS
        Os_Mutex_FreeRTOS
        Os_Generic_PriorityQueue
        Os_RawTime_Stub
        Fw_StringFormat_snprintf
        Os_Cpu_Stub
        Os_Memory_Stub
    INTERFACE # No compilable outputs produced
    BASE_CONFIG
)

