cmake_minimum_required(VERSION 3.10)

project(primitif C)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# libs
find_package(SDL2 REQUIRED)

# include directories
include_directories(${SDL2_INCLUDE_DIRS})

# links to all targets defined after this call
link_libraries(${SDL2_LIBRARIES})

# sources
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
   ${CMAKE_CURRENT_SOURCE_DIR}/src/util/util.c
)

# executables
add_executable(primitif ${SOURCE})
