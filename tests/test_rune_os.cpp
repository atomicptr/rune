#include "base.hpp"

#include <cstdlib>

#include "rune_os.hpp"

int main() {
    auto os = getenv("TEST_OS");

    auto os_str = std::string {os == nullptr ? RUNE_OS_NAME : os};

    expect_equals(os_str, RUNE_OS_NAME);

    if (os_str == "Linux") {
        expect_true(rune::os::current() == rune::os::OperatingSystem::Linux);
        expect_true(rune::os::is_linux());
        expect_false(rune::os::is_windows());
        expect_true(rune::os::is_desktop());
        expect_true(rune::os::name().size() > 0);
        expect_true(rune::os::version().size() > 0);
    } else if (os_str == "macOS") {
        expect_true(rune::os::current() == rune::os::OperatingSystem::MacOS);
        expect_true(rune::os::is_macos());
        expect_false(rune::os::is_windows());
        expect_true(rune::os::is_desktop());
        expect_true(rune::os::name().size() > 0);
        expect_true(rune::os::version().size() > 0);
    } else if (os_str == "Windows") {
        expect_true(rune::os::current() == rune::os::OperatingSystem::Windows);
        expect_true(rune::os::is_windows());
        expect_false(rune::os::is_macos());
        expect_true(rune::os::is_desktop());
        expect_true(rune::os::name().size() > 0);
        expect_true(rune::os::version().size() > 0);
    }

    return 0;
}
