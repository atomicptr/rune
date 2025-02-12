/**
 * rune: A collection of C++23 header files for handling various cross platform related tasks
 *
 * Repository: https://github.com/atomicptr/rune
 * License:    MIT
 */
#pragma once

#include "rune_defs.hpp"

namespace rune::compiler {
    enum class Compiler {
        Unknown,
        GCC,
        Clang,
        MSVC,
    };

    constexpr inline const char* name() {
        return RUNE_COMPILER_NAME;
    }

    constexpr inline const char* version() {
        return RUNE_COMPILER_VERSION;
    }

    constexpr inline unsigned int major_version() {
        return RUNE_COMPILER_VERSION_MAJOR;
    }

    constexpr inline Compiler current() {
#if RUNE_COMPILER_GCC
        return Compiler::GCC;
#elif RUNE_COMPILER_CLANGi
        return Compiler::Clang;
#elif RUNE_COMPILER_MSVC
        return Compiler::MSVC;
#else
        return Compiler::Unknown;
#endif
    }
}
