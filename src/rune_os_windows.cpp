#include "rune_os.hpp"

#if RUNE_OS_WINDOWS

    #include <optional>
    #include <windows.h>

std::optional<OSVERSIONINFOEX> win_version_info() {
    OSVERSIONINFOEX version;
    ZeroMemory(&version, sizeof(OSVERSIONINFOEX));
    version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (GetVersionEx((OSVERSIONINFO*)&version)) {
        return version;
    }

    return {};
}

std::string rune::os::name() {
    auto win_version = win_version_info();
    if (win_version.has_value() && win_version->szCSDVersion[0] != '\0') {
        return win_version->szCSDVersion;
    }

    return RUNE_OS_NAME;
}

std::string rune::os::version() {
    auto win_version = win_version_info();
    if (win_version.has_value() && win_version->szCSDVersion[0] != '\0') {
        return std::to_string(win_version->dwMajorVersion) + "." + std::to_string(win_version->dwMinorVersion) + "." +
            std::to_string(win_version->dwBuildNumber);
    }

    return "???";
}

#endif
