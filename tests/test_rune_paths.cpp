#include "base.hpp"

#include <filesystem>

#include "rune_paths.hpp"

int main() {
    auto home = rune::paths::home_dir();

    expect_true(home.has_value());
    expect_true(std::filesystem::exists(home.value()));

    return 0;
}
