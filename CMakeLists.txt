#########################################################################

# CMAKE MINIMAL VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT PROPERTIES
project ("RISC Interpreter" LANGUAGES CXX)

#########################################################################

# EXECUTABLE FILE PROPERTIES
set(FILE_NAME "interpr")

set(HEADERS
        include/config.h
)

set(SOURCES
        src/main.cpp
        src/phys_page.cpp
        src/virtual_mem.cpp
        src/hart.cpp
        src/instruction.cpp
        src/executor.cpp
)

# EXECUTABLE FILE
add_executable(${FILE_NAME} ${SOURCES})
target_include_directories(${FILE_NAME} PRIVATE include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lelf")

#########################################################################

# ASSEMBLY OPTIONS
set_target_properties(${FILE_NAME} PROPERTIES
    CXX_STANDARD          14
    CXX_STANDARD_REQUIRED ON
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

#########################################################################