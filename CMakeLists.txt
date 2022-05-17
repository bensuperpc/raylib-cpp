cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    raylib-cpp
    VERSION 4.2.1
    DESCRIPTION "C++ Object Oriented Wrapper for raylib"
    HOMEPAGE_URL "https://github.com/RobLoach/raylib-cpp"
    LANGUAGES NONE
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(raylib-cpp_raylib-cpp INTERFACE)
add_library(raylib-cpp::raylib-cpp ALIAS raylib-cpp_raylib-cpp)

set_property(
    TARGET raylib-cpp_raylib-cpp PROPERTY
    EXPORT_NAME raylib-cpp
)

target_include_directories(
    raylib-cpp_raylib-cpp ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(raylib-cpp_raylib-cpp INTERFACE cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${raylib-cpp_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT raylib-cpp_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of raylib-cpp"
  )
endif()

include(cmake/dev-mode.cmake)
