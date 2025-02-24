#include "rune_os.hpp"

#if RUNE_OS_LINUX

    #include <fstream>
    #include <optional>

std::optional<std::string> os_release_find(const std::string key) {
    auto f = std::ifstream {"/etc/os-release"};

    if (!f.is_open()) {
        return {};
    }

    auto line = std::string {};

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

std::optional<std::string> kernel_version() {
    auto f = std::ifstream {"/proc/version"};

    if (!f.is_open()) {
        return {};
    }

    auto line = std::string {};
    std::getline(f, line, ' '); // Linux
    std::getline(f, line, ' '); // version
    std::getline(f, line, ' '); // x.y.z

    f.close();
    return line;
}

std::string rune::os::name() {
    // linux has lots of distributions so we wanna know exactly which one is being used here
    auto pretty_name = os_release_find("PRETTY_NAME");
    if (pretty_name.has_value()) {
        return pretty_name.value();
    }

    return RUNE_OS_NAME;
}

std::string rune::os::version() {
    // on linux we probably want to know the kernel version
    auto version = kernel_version();
    if (version.has_value()) {
        return version.value();
    }

    return "???";
}

#endif
