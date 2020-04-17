cmake_minimum_required (VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project(statslib)

option(USE_SYSTEM_EIGEN "Use system Eigen instead of a bundled submodule" OFF)
option(USE_OPENMP "Compile with OpenMP" OFF)

set(DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/deps")

# Eigen. Use a system package, if preferred.
if(USE_SYSTEM_EIGEN)
  find_package(Eigen3 REQUIRED)
  include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
else()
  include_directories(SYSTEM "${DEPS_DIR}/eigen")
  set(EIGEN3_INCLUDE_DIR "${DEPS_DIR}/eigen")
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DEPS_DIR}/eigen")
endif()

include_directories(SYSTEM "${DEPS_DIR}/gcem/include")
include_directories(SYSTEM "${DEPS_DIR}/stats/include")

add_subdirectory("${DEPS_DIR}/pybind11")
pybind11_add_module(statslib src/main.cpp src/dens.cpp src/rand.cpp)

# OpenMP support?
find_package(OpenMP)
if(OpenMP_FOUND AND USE_OPENMP)
    target_link_libraries(statslib PRIVATE OpenMP::OpenMP_CXX)
    #add_definitions(-DSTATS_USE_OPENMP)
endif()
