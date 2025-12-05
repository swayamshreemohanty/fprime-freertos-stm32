#####
# PlatformTypes.fpp:
#
# Define platform type aliases for FreeRTOS/STM32 32-bit ARM platform.
# These types are optimized for embedded 32-bit systems.
####

@ The unsigned type of larger sizes internal to the software,
@ e.g., memory buffer sizes, file sizes. Must be unsigned.
@ For 32-bit systems, use U32 instead of U64
type PlatformSizeType = U32

@ The signed type of larger sizes internal to the software, used
@ for signed offsets, e.g., file seek offsets. Must be signed.
@ For 32-bit systems, use I32 instead of I64
type PlatformSignedSizeType = I32

@ The type of smaller indices internal to the software, used
@ for array indices, e.g., port indices. Must be signed.
type PlatformIndexType = I16

@ The type of arguments to assert functions. Supplied by platform,
@ overridable by project.
type PlatformAssertArgType = I32

@ The type of task priorities used. Supplied by platform,
@ overridable by project.
type PlatformTaskPriorityType = U8

@ The type of task identifiers. Supplied by platform,
@ overridable by project.
type PlatformTaskIdType = I32

@ The type of queue priorities used. Supplied by platform,
@ overridable by project.
type PlatformQueuePriorityType = U8
