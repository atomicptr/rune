#pragma once

// utils
#define __RUNE_STRINGIFY(x) #x
#define __RUNE_TOSTRING(x) __RUNE_STRINGIFY(x)
#define __RUNE_PRAGMA(x) _Pragma(#x)
#ifdef _MSC_VER
    #define __RUNE_WARN(msg) __RUNE_PRAGMA(message("Warning: " #msg))
#else
    #define __RUNE_WARN(msg) __RUNE_PRAGMA(GCC warning #msg)
#endif

// os defines
#if defined(__ANDROID__)
    #define RUNE_OS_ANDROID 1
    #define RUNE_OS_NAME "Android"
    #define RUNE_OS_PLATFORM_MOBILE 1
#elif defined(__linux__)
    #define RUNE_OS_LINUX 1
    #define RUNE_OS_NAME "Linux"
    #define RUNE_OS_PLATFORM_DESKTOP 1
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR
        #define RUNE_OS_IOS 1
        #define RUNE_OS_NAME "iOS Simulator"
        #define RUNE_OS_PLATFORM_MOBILE 1
    #elif TARGET_OS_IPHONE
        #define RUNE_OS_IOS 1
        #define RUNE_OS_NAME "iOS"
        #define RUNE_OS_PLATFORM_MOBILE 1
    #elif TARGET_OS_MAC
        #define RUNE_OS_MACOS 1
        #define RUNE_OS_NAME "macOS"
        #define RUNE_OS_PLATFORM_DESKTOP 1
    #else
        #error "rune: Unknown Apple platform"
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__)
    #define RUNE_OS_WINDOWS 1
    #define RUNE_OS_NAME "Windows"
    #define RUNE_OS_PLATFORM_DESKTOP 1
#else
    #define RUNE_OS_UNKNOWN 1
    #define RUNE_OS_NAME "Unknown"
    __RUNE_WARN("rune: Unknown OS")
#endif

// compiler defines
#if defined(__MINGW32__) || defined(__MINGW64__)
    #define RUNE_COMPILER_MINGW 1
    #define RUNE_COMPILER_NAME "mingw"

    // necessary for getting versions
    #include <stdlib.h>
    #define RUNE_COMPILER_VERSION __RUNE_TOSTRING(__MINGW32_MAJOR_VERSION) "." __RUNE_TOSTRING(__MINGW32_MINOR_VERSION)
    #define RUNE_COMPILER_VERSION_MAJOR __MINGW32_MAJOR_VERSION
    #define RUNE_COMPILER_VERSION_MINOR __MINGW32_MINOR_VERSION
    #define RUNE_COMPILER_VERSION_PATCH 0
#elif (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)
    #define RUNE_COMPILER_GCC 1
    #define RUNE_COMPILER_NAME "gcc"
    #define RUNE_COMPILER_VERSION \
        __RUNE_TOSTRING(__GNUC__) "." __RUNE_TOSTRING(__GNUC_MINOR__) "." __RUNE_TOSTRING(__GNUC_PATCHLEVEL__)
    #define RUNE_COMPILER_VERSION_MAJOR __GNUC__
    #define RUNE_COMPILER_VERSION_MINOR __GNUC_MINOR__
    #define RUNE_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#elif defined(__clang__)
    #define RUNE_COMPILER_CLANG 1
    #define RUNE_COMPILER_NAME "clang"
    #define RUNE_COMPILER_VERSION \
        __RUNE_TOSTRING(__clang_major__) "." __RUNE_TOSTRING(__clang_minor__) "." __RUNE_TOSTRING(__clang_patchlevel__)
    #define RUNE_COMPILER_VERSION_MAJOR __clang_major__
    #define RUNE_COMPILER_VERSION_MINOR __clang_minor__
    #define RUNE_COMPILER_VERSION_PATCH __clang_patchlevel__
#elif defined(_MSC_VER)
    #define RUNE_COMPILER_MSVC 1
    #define RUNE_COMPILER_NAME "MSVC"
    #define RUNE_COMPILER_VERSION __RUNE_TOSTRING(_MSC_FULL_VER)
    #define RUNE_COMPILER_VERSION_MAJOR _MSC_VER
    #define RUNE_COMPILER_VERSION_MINOR 0
    #define RUNE_COMPILER_VERSION_PATCH 0
#else
    #define RUNE_COMPILER_UNKNOWN 1
    #define RUNE_COMPILER_NAME "unknown"
    #define RUNE_COMPILER_VERSION "0.0.0"
    #define RUNE_COMPILER_VERSION_MAJOR 0
    #define RUNE_COMPILER_VERSION_MINOR 0
    #define RUNE_COMPILER_VERSION_PATCH 0
    __RUNE_WARN("rune: Unknown compiler detected. This compiler is not supported and some things might not work")
#endif
