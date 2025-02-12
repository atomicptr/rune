/**
 * rune: A collection of C++23 header files for handling various cross platform related tasks
 *
 * Repository: https://github.com/atomicptr/rune
 * License:    MIT
 */
#pragma once

#include <cstdlib>
#include <filesystem>
#include <optional>

#include "rune_defs.hpp"

#if RUNE_OS_LINUX || RUNE_OS_MACOS
    #include <pwd.h>
    #include <unistd.h>
#endif

namespace rune::paths {
    namespace internal {
        inline std::optional<std::filesystem::path>
        extend_dir(std::optional<std::filesystem::path> base_dir, const std::string path) {
            if (!base_dir.has_value()) {
                return {};
            }

            auto res = base_dir.value() / path;

            if (!std::filesystem::exists(res)) {
                std::filesystem::create_directories(res);
            }

            return res;
        }
    }

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

    inline std::optional<std::filesystem::path> config_base_dir() {
        // if the XDG dir is set we just use that regardless ;)
        auto dir = std::getenv("XDG_CONFIG_HOME");
        if (dir) {
            return {dir};
        }

        auto home = home_dir();

#if RUNE_OS_LINUX
        if (home.has_value()) {
            return home.value() / ".config";
        }
#elif RUNE_OS_MACOS
        if (home.has_value()) {
            return home.value() / "Library" / "Preferences";
        }
#elif RUNE_OS_WINDOWS
        auto windir = std::getenv("LOCALAPPDATA");
        if (windir) {
            return {windir};
        }
#endif

        return {};
    }

    inline std::optional<std::filesystem::path> config_dir(const std::string app_identifier) {
        return internal::extend_dir(config_base_dir(), app_identifier);
    }

    inline std::optional<std::filesystem::path> cache_base_dir() {
        // if the XDG dir is set we just use that regardless ;)
        auto dir = std::getenv("XDG_CACHE_HOME");
        if (dir) {
            return {dir};
        }

        auto home = home_dir();

#if RUNE_OS_LINUX
        if (home.has_value()) {
            return home.value() / ".cache";
        }
#elif RUNE_OS_MACOS
        if (home.has_value()) {
            return home.value() / "Library" / "Caches";
        }
#elif RUNE_OS_WINDOWS
        // windows doesn't seem to have a good alternative here so we just use temp
        return std::filesystem::temp_directory_path();
#endif

        return {};
    }

    inline std::optional<std::filesystem::path> cache_dir(const std::string app_identifier) {
        return internal::extend_dir(cache_base_dir(), app_identifier);
    }

    inline std::optional<std::filesystem::path> data_base_dir() {
        // if the XDG dir is set we just use that regardless ;)
        auto dir = std::getenv("XDG_DATA_HOME");
        if (dir) {
            return {dir};
        }

        auto home = home_dir();

#if RUNE_OS_LINUX
        if (home.has_value()) {
            return home.value() / ".local" / "share";
        }
#elif RUNE_OS_MACOS
        if (home.has_value()) {
            return home.value() / "Library";
        }
#elif RUNE_OS_WINDOWS
        auto windir = std::getenv("LOCALAPPDATA");
        if (windir) {
            return {windir};
        }
#endif

        return {};
    }

    inline std::optional<std::filesystem::path> data_dir(const std::string app_identifier) {
        return internal::extend_dir(data_base_dir(), app_identifier);
    }
}
