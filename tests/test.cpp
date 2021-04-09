#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cipher_finder.h>

TEST_CASE("SimpleTest") {
    cipher::CipherFinder finder("test1.txt");

    auto first = finder.GetFirstKeyWord("Lpl");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 0);
}

TEST_CASE("MultipleTimes") {
    cipher::CipherFinder finder("test1.txt");

    auto first = finder.GetFirstKeyWord("Lpl");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 0);

    auto second = finder.GetFirstKeyWord("cdi");
    REQUIRE(second.has_value());
    REQUIRE(second.value() == 5);
}

TEST_CASE("LastWord") {
    cipher::CipherFinder finder("test1.txt");
    auto first = finder.GetFirstKeyWord("dsm");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 66);
}

TEST_CASE("NotFound") {
    cipher::CipherFinder finder("test1.txt");
    auto first = finder.GetFirstKeyWord("abc");
    REQUIRE(!first.has_value());
}