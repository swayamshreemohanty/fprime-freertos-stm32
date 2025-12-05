# =======================================================================
# FPP file for FreeRTOS/STM32 Platform Configuration
# =======================================================================

@ Platform-specific size type for 32-bit ARM Cortex-M7
type PlatformSizeType = U32

@ Platform-specific signed size type
type PlatformSignedSizeType = I32

@ Platform-specific integer type
type PlatformIntType = I32

@ Platform-specific unsigned integer type
type PlatformUIntType = U32

@ Platform-specific pointer cast type
type PlatformPointerCastType = U32

@ Maximum size of a handle for Os::Console (smaller for embedded)
constant FW_CONSOLE_HANDLE_MAX_SIZE = 16

@ Maximum size of a handle for Os::Task (FreeRTOS task handle)
constant FW_TASK_HANDLE_MAX_SIZE = 32

@ Maximum size of a handle for Os::File
constant FW_FILE_HANDLE_MAX_SIZE = 8

@ Maximum size of a handle for Os::Mutex (FreeRTOS mutex)
constant FW_MUTEX_HANDLE_MAX_SIZE = 32

@ Maximum size of a handle for Os::Queue (FreeRTOS queue)
constant FW_QUEUE_HANDLE_MAX_SIZE = 128

@ Maximum size of a handle for Os::Directory
constant FW_DIRECTORY_HANDLE_MAX_SIZE = 8

@ Maximum size of a handle for Os::FileSystem
constant FW_FILESYSTEM_HANDLE_MAX_SIZE = 8

@ Maximum size of a handle for Os::RawTime
constant FW_RAW_TIME_HANDLE_MAX_SIZE = 32

@ Maximum allowed serialization size for Os::RawTime objects
constant FW_RAW_TIME_SERIALIZATION_MAX_SIZE = 8

@ Maximum size of a handle for Os::ConditionVariable
constant FW_CONDITION_VARIABLE_HANDLE_MAX_SIZE = 32

@ Maximum size of a handle for Os::Cpu
constant FW_CPU_HANDLE_MAX_SIZE = 8

@ Maximum size of a handle for Os::Memory
constant FW_MEMORY_HANDLE_MAX_SIZE = 8

@ Alignment of handle storage (ARM Cortex-M7 is 32-bit aligned)
constant FW_HANDLE_ALIGNMENT = 4

@ Chunk size for working with files in the OSAL layer (smaller for embedded)
constant FW_FILE_CHUNK_SIZE = 256
