cmake_minimum_required(VERSION 3.20)
project(EXO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_library(exir_core STATIC
  exir/src/graph.cpp
  exir/src/verifier.cpp
)

target_include_directories(exir_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/exir/include
)

add_library(exo_core STATIC
  exo/src/compiler.cpp
)

target_include_directories(exo_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/exo/include
)

target_link_libraries(exo_core PUBLIC
  exir_core
)

add_executable(exo_sanity
  examples/sanity.cpp
)

target_link_libraries(exo_sanity PRIVATE
  exo_core
)
