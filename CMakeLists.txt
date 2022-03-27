cmake_minimum_required(VERSION 3.17)

project(QTranslator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

option(BUILD_TESTS "When sets to ON, builds the unit tests" OFF)

if(BUILD_TESTS)
    find_package(googletest QUIET)
    include(FetchContent)
    FetchContent_Declare(
	    googletest
	    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/tools.cpp
    src/Qasm/Circuit.cpp
    src/qtranslator.cpp
    src/Qasm/QRegister.cpp
    src/instructions/Add.cpp
    src/instructions/Div.cpp
    src/instructions/Move.cpp
    src/instructions/Mul.cpp
    src/instructions/Sar.cpp
    src/instructions/Shl.cpp
    src/instructions/Shr.cpp
    src/instructions/Sub.cpp
)

set(TEST_SOURCES
    tests/src/qtranslator.cpp
    tests/src/tools.cpp
)

if(BUILD_TESTS)
    set(BIN QTranslatorTests)
else()
    set(BIN QTranslator)
endif()

if(UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
else()
    add_compile_options(/W4)
endif()

if(BUILD_TESTS)
    add_executable(${BIN}
        ${SOURCES}
        ${TEST_SOURCES}
    )
    target_include_directories(${BIN} PRIVATE include)
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(${BIN})
    target_link_libraries(${BIN} PRIVATE gtest_main)
else()
    add_executable(${BIN}
        ${SOURCES}
    )
    target_include_directories(${BIN} PRIVATE
        include
        include/intructions
        include/Qasm
        )
endif()

if(UNIX)
    target_link_libraries(${BIN} PRIVATE pthread)
endif()