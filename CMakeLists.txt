cmake_minimum_required(VERSION 3.17)

project(QTranslator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(BIN QTranslator)

add_compile_options(-Wall -Wextra -Weffc++)

set(SOURCES
    src/main.cpp
    src/qtranslator.cpp
    src/parser.cpp
)

add_executable(${BIN} ${SOURCES})

target_include_directories(${BIN} PRIVATE include)

target_link_libraries(${BIN} PRIVATE pthread)