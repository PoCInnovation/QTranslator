#include <gtest/gtest.h>
#include "tools.hpp"

TEST(string_to_vector, basic_test)
{
    auto arr = tools::string_to_vector("\n\none\n\ntwo\ntree\n\n", '\n');
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], "one");
    EXPECT_EQ(arr[1], "two");
    EXPECT_EQ(arr[2], "tree");
}

TEST(string_to_vector, push_separator)
{
    auto arr = tools::string_to_vector("\n\none\n\ntwo\ntree\n\n", '\n', true);

    EXPECT_EQ(arr.size(), 8);
    EXPECT_EQ(arr[0], "");
    EXPECT_EQ(arr[1], "");
    EXPECT_EQ(arr[2], "one");
    EXPECT_EQ(arr[3], "");
    EXPECT_EQ(arr[4], "two");
    EXPECT_EQ(arr[5], "tree");
    EXPECT_EQ(arr[6], "");
    EXPECT_EQ(arr[7], "");
}

TEST(string_to_vector, push_separator_advanced)
{
    auto arr = tools::string_to_vector("a\n\none\n\ntwo\ntree\n\nz", '\n', true);

    EXPECT_EQ(arr.size(), 8);
    EXPECT_EQ(arr[0], "a");
    EXPECT_EQ(arr[1], "");
    EXPECT_EQ(arr[2], "one");
    EXPECT_EQ(arr[3], "");
    EXPECT_EQ(arr[4], "two");
    EXPECT_EQ(arr[5], "tree");
    EXPECT_EQ(arr[6], "");
    EXPECT_EQ(arr[7], "z");
}

TEST(string_to_vector, empty_string)
{
    auto arr = tools::string_to_vector("", '\n');
    EXPECT_EQ(arr.empty(), true);
}

TEST(get_file_content, test_file)
{
    auto arr = tools::string_to_vector(tools::get_file_content("tests/data/adder.io"), '\n', true);

    EXPECT_EQ(arr.size(), 12);
    EXPECT_EQ(arr[0], "# adder example of our custom language !");
    EXPECT_EQ(arr[1], "");
    EXPECT_EQ(arr[2], "                # variables");
    EXPECT_EQ(arr[3], "int i 3");
    EXPECT_EQ(arr[4], "int j 10");
    EXPECT_EQ(arr[5], "char c 42");
    EXPECT_EQ(arr[6], "");
    EXPECT_EQ(arr[7], "                # operations");
    EXPECT_EQ(arr[8], "");
    EXPECT_EQ(arr[9], "add i 5");
    EXPECT_EQ(arr[10], "sub i 5");
    EXPECT_EQ(arr[11], "# add i j");
}

TEST(get_file_content, bad_file)
{
    try {
        auto file = tools::get_file_content("tests/data/null.io");
        EXPECT_EQ(true, false);
    } catch (...) {
        EXPECT_EQ(true, true);
    }
}