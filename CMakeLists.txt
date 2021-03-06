#########################################################################

# CMAKE MINIMAL VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT PROPERTIES
project ("RISC-V Interpreter" LANGUAGES CXX)

#########################################################################

add_compile_options(
    -Wall
    -Wpedantic

    -Wno-int-to-pointer-cast
    -Wno-variadic-macros
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-sign-compare
    -Wno-misleading-indentation
    -Wno-shift-count-overflow
    -Wno-old-style-cast

    -Wcast-align
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
)

#########################################################################

# EXECUTABLE FILE PROPERTIES
set(FILE_NAME "RISC-V-Interpreter")

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

#########################################################################

# LINKING WITH LIBELF
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lelf")

# ASSEMBLY OPTIONS
set_target_properties(${FILE_NAME} PROPERTIES
    CXX_STANDARD          14
    CXX_STANDARD_REQUIRED ON
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

#########################################################################
