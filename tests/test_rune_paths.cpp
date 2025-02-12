#include "base.hpp"

#include <filesystem>

#include "rune_paths.hpp"

int main() {
    auto dirs = {
        rune::paths::home_dir(),
        rune::paths::cache_base_dir(),
        rune::paths::cache_dir("rune_test"),
        rune::paths::config_base_dir(),
        rune::paths::config_dir("rune_test"),
        rune::paths::data_base_dir(),
        rune::paths::data_dir("rune_test"),
    };

    for (auto dir : dirs) {
        expect_true(dir.has_value());
        expect_true(std::filesystem::exists(dir.value()));
    }

    return 0;
}
