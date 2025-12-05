/**
 * PlatformTypes.h:
 *
 * Platform-specific type definitions header for FreeRTOS/STM32 32-bit ARM.
 * This file is required by F Prime's type system and must be included via Platform/PlatformTypes.h
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <inttypes.h>

// For 32-bit ARM platforms, pointer size is always 4 bytes
typedef uint32_t PlatformPointerCastType;
#define PRI_PlatformPointerCastType PRIx32

#ifdef  __cplusplus
}
#endif

#endif // PLATFORM_TYPES_H_
