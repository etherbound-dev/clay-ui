cmake_minimum_required(VERSION 3.22)
project(Project)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# add_link_options(-fsanitize=address)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assets)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Project main.c)
# target_compile_options(Project PRIVATE -Wall -Wextra -Wpedantic -Werror -fsanitize=address)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)

target_link_libraries(Project raylib)
target_link_libraries(Project m)
