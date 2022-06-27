cmake_minimum_required(VERSION 3.17)

project(QTranslator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/instructions)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(
    dylib
    GIT_REPOSITORY "https://github.com/martin-olivier/dylib"
    GIT_TAG        "v1.8.2"
)

FetchContent_MakeAvailable(dylib)
include_directories(${dylib_SOURCE_DIR}/include)

set(BIN QTranslator)

set(SOURCES
    src/main.cpp
    src/qtranslator.cpp
    src/parser.cpp
    src/tools.cpp
    src/Qasm/Circuit.cpp
    src/Qasm/QRegister.cpp
)

if(UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)
else()
    add_compile_options(/W4)
endif()

add_executable(${BIN} ${SOURCES})

target_include_directories(${BIN} PRIVATE
    include
    include/intructions
    include/Qasm
)

if(UNIX)
    target_link_libraries(${BIN} PRIVATE dl)
endif()

file(GLOB instructions CONFIGURE_DEPENDS "src/instructions/*.cpp")
foreach(instruction ${instructions})
    get_filename_component(mod_name ${instruction} NAME_WLE)
    add_library(${mod_name} SHARED ${instruction} src/Qasm/Circuit.cpp src/Qasm/QRegister.cpp)
    target_include_directories(${mod_name} PRIVATE include/intructions include/Qasm)
    set_target_properties(${mod_name} PROPERTIES PREFIX "")
endforeach()