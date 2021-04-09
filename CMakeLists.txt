cmake_minimum_required(VERSION 3.17)
project(SecretCipher)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(SecretCipher main.cpp src/cipher_finder.cpp)
add_executable(SecretTest tests/test.cpp src/cipher_finder.cpp)

target_link_libraries(SecretTest Catch2::Catch2)