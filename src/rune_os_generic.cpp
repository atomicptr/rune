#include "rune_os.hpp"

#if !RUNE_OS_LINUX && !RUNE_OS_WINDOWS
std::string rune::os::name() {
    return RUNE_OS_NAME;
}

std::string rune::os::version() {
    return "???";
}
#endif
