#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cipher_finder.h>

/* Проверяем, что вообще говоря это работает
 */
TEST_CASE("SimpleTest") {
    cipher::CipherFinder finder("test1.txt");

    auto first = finder.GetFirstKeyWord("Lpl");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 0);
}

/* Проверяется факт того. что функция может быть вызвана несколько раз,
 * и ничего не сломается
 */
TEST_CASE("MultipleTimes") {
    cipher::CipherFinder finder("test1.txt");

    auto first = finder.GetFirstKeyWord("Lpl");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 0);

    auto second = finder.GetFirstKeyWord("cdi");
    REQUIRE(second.has_value());
    REQUIRE(second.value() == 5);
}

/* Может получится так, что ответ будет чуть ли не
 * в самом конце текста. Проверка этого случая
 */
TEST_CASE("LastWord") {
    cipher::CipherFinder finder("test1.txt");
    auto first = finder.GetFirstKeyWord("dsm");
    REQUIRE(first.has_value());
    REQUIRE(first.value() == 66);
}

/* А вдруг мы не нашли такого шифра?)
 */
TEST_CASE("NotFound") {
    cipher::CipherFinder finder("test1.txt");
    auto first = finder.GetFirstKeyWord("abc");
    REQUIRE(!first.has_value());
}