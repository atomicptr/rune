#pragma once

#include "rune_defs.hpp"

#include <string>
#include <optional>

#if RUNE_OS_LINUX
#include <fstream>
#elif RUNE_OS_WINDOWS
#include <windows.h>
#endif

namespace rune::os {
    namespace internal {
        #if RUNE_OS_LINUX
        std::optional<std::string> linux_os_release_find(const std::string key) {
            auto f = std::ifstream{"/etc/os-release"};

            if (!f.is_open()) {
                return {};
            }

            auto line = std::string{};

            while (std::getline(f, line)) {
                if (line.find(key + "=") != std::string::npos) {
                    f.close();

                    auto str = line.substr(line.find("=") + 1);

                    if (str.size() == 0) {
                        return {};
                    }

                    if (str[0] == '"' && str[str.size() - 1] == '"' && str.size() > 2) {
                        return str.substr(1, str.size() - 2);
                    }

                    return str;
                }
            }

            f.close();
            return {};
        }

        std::optional<std::string> linux_kernel_version() {
            auto f = std::ifstream{"/proc/version"};

            if (!f.is_open()) {
                return {};
            }

            auto line = std::string{};
            std::getline(f, line, ' '); // Linux
            std::getline(f, line, ' '); // version
            std::getline(f, line, ' '); // x.y.z

            f.close();
            return line;
        }
        #elif RUNE_OS_WINDOWS
        std::optional<OSVERSIONINFOEX> win_version_info() {
            OSVERSIONINFOEX version;
            ZeroMemory(&version, sizeof(OSVERSIONINFOEX));
            version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

            if (GetVersionEx((OSVERSIONINFO*)&version)) {
                return version;
            }

            return {};
        }
        #endif
    }
    
    enum class OperatingSystem {
        Unknown,
        Linux,
        MacOS,
        Windows,
        Android,
        IOS,
    };
    
    inline std::string name() {
        // linux has lots of distributions so we wanna know exactly which one is being used here
        #if RUNE_OS_LINUX
        auto pretty_name = internal::linux_os_release_find("PRETTY_NAME");
        if (pretty_name.has_value()) {
            return pretty_name.value();
        }
        #elif RUNE_OS_WINDOWS
        auto win_version = win_version_info();
        if (win_version.has_value() && win_version->szCSDVersion[0] != '\0') {
            return win_version->szCSDVersion;
        }
        #endif
        
        return RUNE_OS_NAME;
    }

    inline std::string version() {
        // on linux we probably want to know the kernel version
        #if RUNE_OS_LINUX
        auto version = internal::linux_kernel_version();
        if (version.has_value()) {
            return version.value();
        }
        #elif RUNE_OS_WINDOWS
        auto win_version = win_version_info();
        if (win_version.has_value() && win_version->szCSDVersion[0] != '\0') {
            return std::to_string(win_version->dwMajorVersion) + "." + std::to_string(win_version->dwMinorVersion) + "." + std::to_string(win_version->dwBuildNumber);
        }
        #endif
        
        return "???";
    }

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
