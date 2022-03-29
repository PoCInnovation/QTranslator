cmake_minimum_required(VERSION 3.17)

project(QTranslator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(BIN QTranslator)

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

if(UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
else()
    add_compile_options(/W4)
endif()

add_executable(${BIN}
    ${SOURCES}
)

target_include_directories(${BIN} PRIVATE
    include
    include/intructions
    include/Qasm
)