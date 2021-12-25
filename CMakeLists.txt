cmake_minimum_required(VERSION 3.17)

project(QTranslator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

option(BUILD_TESTS "When sets to ON, builds the unit tests" OFF)

set(MAIN src/main.cpp)

set(SOURCES
    src/qtranslator.cpp
    src/parser.cpp
    src/tools.cpp
)

set(TEST_SOURCES
    tests/src/qtranslator.cpp
)

if(BUILD_TESTS)
    set(BIN QTranslatorTests)
    include(import/GoogleTest.cmake)
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
        ${MAIN}
    )
    target_include_directories(${BIN} PRIVATE include)
endif()

if(UNIX)
    target_link_libraries(${BIN} PRIVATE pthread)
endif()