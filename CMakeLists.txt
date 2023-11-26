cmake_minimum_required(VERSION 3.10)

project(primitif C)

# export compile commands for clangd database
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# libs
if (WIN32)
    set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}\\libs\\SDL2\\build\\RelWithDebInfo\\SDL2.lib")
    set(SDL2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}\\libs\\SDL2\\include")
else ()
    find_package(SDL2 REQUIRED)
endif ()

message("ASDASD ${SDL2_INCLUDE_DIRS}")
message("KDLSKDLSKD ${SDL2_LIBRARIES}")

link_libraries(${SDL2_LIBRARIES})
include_directories(${SDL2_INCLUDE_DIRS})

# sources
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
   ${CMAKE_CURRENT_SOURCE_DIR}/src/electron.c
   ${CMAKE_CURRENT_SOURCE_DIR}/src/util/util.c
   ${CMAKE_CURRENT_SOURCE_DIR}/src/util/circle.c
)

# executables
add_executable(primitif ${SOURCE})
