cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME_STR variad)

project("${PROJECT_NAME_STR}")

# C++11
set(CMAKE_CXX_STANDARD 11)

# Clang - export compilation database.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.72.0 REQUIRED)

# Build Helper - configuration variables. Must set before configuring the
# CMake module.
set(BUILD_HELPER_USE_SRC_DIR "${CMAKE_SOURCE_DIR}/src/cpp")
set(BUILD_HELPER_USE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/cpp/variad/internal")
set(BUILD_HELPER_USE_PREFIX "${PROJECT_NAME_STR}")
# Build Helper - configure CMake module.
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/CMake/BuildHelper.cmake.in"
  "${CMAKE_CURRENT_LIST_DIR}/CMake/BuildHelper.cmake"
  @ONLY)
# Build Helper - add it the the CMake module path.
list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/CMake
)
# Build Helper - add module.
include(BuildHelper)

# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

add_subdirectory("src/cpp/${PROJECT_NAME_STR}")

