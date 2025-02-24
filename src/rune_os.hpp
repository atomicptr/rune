/**
 * rune: A collection of C++23 header files for handling various cross platform related tasks
 *
 * Repository: https://github.com/atomicptr/rune
 * License:    MIT
 */
#pragma once

#include "rune_defs.hpp"

#include <string>

namespace rune::os {
    enum class OperatingSystem {
        Unknown,
        Linux,
        MacOS,
        Windows,
        Android,
        IOS,
    };

    std::string name();
    std::string version();

    constexpr inline OperatingSystem current() {
#if RUNE_OS_LINUX
        return OperatingSystem::Linux;
#elif RUNE_OS_MACOS
        return OperatingSystem::MacOS;
#elif RUNE_OS_WINDOWS
        return OperatingSystem::Windows;
#elif RUNE_OS_ANDROID
        return OperatingSystem::Android;
#elif RUNE_OS_IOS
        return OperatingSystem::IOS;
#else
        return OperatingSystem::Unknown;
#endif
    }

    constexpr inline bool is_desktop() {
#if RUNE_OS_PLATFORM_DESKTOP
        return true;
#else
        return false;
#endif
    }

    constexpr inline bool is_mobile() {
#if RUNE_OS_PLATFORM_MOBILE
        return true;
#else
        return false;
#endif
    }

    constexpr inline bool is_linux() {
        return current() == OperatingSystem::Linux;
    }

    constexpr inline bool is_macos() {
        return current() == OperatingSystem::MacOS;
    }

    constexpr inline bool is_windows() {
        return current() == OperatingSystem::Windows;
    }

    constexpr inline bool is_android() {
        return current() == OperatingSystem::Android;
    }

    constexpr inline bool is_ios() {
        return current() == OperatingSystem::IOS;
    }
}
