#include <gtest/gtest.h>
#include <sstream>

#include "word_iter.h"

TEST(WordIterTest, Begin) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);
    EXPECT_EQ(*words_iter.begin(), "hello");
}

TEST(WordIterTest, End) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);
    EXPECT_EQ(*words_iter.end(), "");
}

TEST(WordIterTest, Empty) {
    std::istringstream stream("");
    Words words_iter(stream);
    EXPECT_EQ(words_iter.begin(), words_iter.end());
}

TEST(WordIterTest, OneWord) {
    std::istringstream stream("hello");
    Words words_iter(stream);
    auto it = words_iter.begin();
    EXPECT_EQ(*it, "hello");
    EXPECT_EQ(++it, words_iter.end());
}

TEST(WordIterTest, PreIncrement) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);
    EXPECT_EQ(*(++words_iter.begin()), "world");
}

TEST(WordIterTest, PostIncrement) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);
    EXPECT_EQ(*(words_iter.begin()++), "hello");
}

TEST(WordIterTest, RangeBasedForLoop) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);

    std::vector<std::string> result(words_iter.begin(), words_iter.end());
    std::vector<std::string> expect = {"hello", "world"};
    EXPECT_EQ(result, expect);
}

TEST(WordIterTest, ComplexStream) {
    std::istringstream stream(
        "hello, world! hello snake_case, hello camelCase, hello PascalCase, hello kebab-case, "
        "hello UPPER_CASE");
    Words words_iter(stream);
    std::vector<std::string> result(words_iter.begin(), words_iter.end());
    std::vector<std::string> expect = {"hello", "world",     "hello", "snake",      "case",
                                       "hello", "camelCase", "hello", "PascalCase", "hello",
                                       "kebab", "case",      "hello", "UPPER",      "CASE"};
    EXPECT_EQ(result, expect);
}

TEST(WordIterTest, DereferenceOperator) {
    std::istringstream stream("hello, world");
    Words words_iter(stream);
    EXPECT_EQ(*words_iter.begin(), "hello");
}

TEST(WordIterTest, ArrowOperator) {
    std::istringstream stream("hello!!!");
    Words words_iter(stream);
    EXPECT_EQ(words_iter.begin()->length(), 5);
}

TEST(WordIterTest, BadStream) {
    std::istream bad_stream = std::istream(nullptr);
    Words words_iter(bad_stream);
    EXPECT_THROW(words_iter.begin(), std::ios_base::failure);
}
