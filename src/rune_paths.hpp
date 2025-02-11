#pragma once

#include <optional>
#include <filesystem>

#include "rune_defs.hpp"

#if RUNE_OS_LINUX || RUNE_OS_MACOS
    #include <pwd.h>
    #include <unistd.h>
#endif

namespace rune::paths {
    inline std::optional<std::filesystem::path> home_dir() {
        #if RUNE_OS_LINUX || RUNE_OS_MACOS
        auto home = std::getenv("HOME");

        if (!home) {
            auto pwd = getpwuid(getuid());
            if (!pwd) {
                return {};
            }
            return {pwd->pw_dir};
        }

        return {home};
        #elif RUNE_OS_WINDOWS
        auto home = std::getenv("USERPROFILE");

        if (!home) {
            return {};
        }

        return {home};
        #endif

        return {};
    }
}
