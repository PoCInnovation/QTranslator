#include <gtest/gtest.h>
#include <array>
#include "qtranslator.hpp"

TEST(qtranslator, no_file)
{
    std::array<const char *, 2> args{"qtranslator", "null_file.io"};
    try {
        qtranslator app(2, args.data());
        EXPECT_EQ(true, false);
    } catch (...) {
        EXPECT_EQ(true, true);
    }
}

TEST(qtranslator, adder)
{
    std::array<const char *, 2> args{"qtranslator", "tests/data/adder.io"};
    try {
        qtranslator app(2, args.data());
        EXPECT_EQ(true, true);
    } catch (...) {
        EXPECT_EQ(true, false);
    }
}