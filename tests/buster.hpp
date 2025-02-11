/**
 * buster: A tiny, single file, header only assertion library for C++23
 *
 * Repository: https://github.com/atomicptr/buster
 * License:    BSD 0-Clause
 */
#pragma once

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace buster {
    namespace internal {
        inline void print_pass(std::string file, int line) {
            #ifndef BUSTER_NO_PASS_PRINT
            std::cout << "\t\033[32mPASS\033[0m\t" << file << ":" << line << std::endl;
            #endif
        }

        inline void print_fail(std::string file, int line, std::string reason) {
            std::cout << "\t\033[1;31mFAIL\033[0m\t" << file << ":" << line << "\t" << reason << std::endl;
            std::abort();
        }

        template<typename T, typename U>
        inline bool is_equal(T a, U b) {
            return a == b;
        }

        template<>
        inline bool is_equal(float a, float b) {
            return std::abs(a - b) < 0.000001f;
        }

        template<typename T, typename U>
        inline void test_equals(T expected, U actual, std::string file, int line) {
            if (is_equal(expected, actual)) {
                print_pass(file, line);
                return;
            }

            std::stringstream ss;
            ss << "Expected " << actual << " to be " << expected;
            print_fail(file, line, ss.str());
        }

        inline void test_true(bool value, std::string file, int line) {
            if (value) {
                print_pass(file, line);
                return;
            }
            print_fail(file, line, "Expected value to be true");
        }

        inline void test_false(bool value, std::string file, int line) {
            if (!value) {
                print_pass(file, line);
                return;
            }
            print_fail(file, line, "Expected value to be false");
        }
    }
}

#define expect_equals(expected, actual) buster::internal::test_equals((expected), (actual), __FILE__, __LINE__)

#define expect_true(value) buster::internal::test_true((value), __FILE__, __LINE__)

#define expect_false(value) buster::internal::test_false((value), __FILE__, __LINE__)
