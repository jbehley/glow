cmake_minimum_required(VERSION 3.16)

project(glow VERSION 1.0 
             DESCRIPTION "glow -- a high-level wrapper for OpenGL"
             LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(Eigen3 REQUIRED)
find_package(X11)

set(GCC_COMPILE_DEBUG_OPTIONS "-g2;-DDEBUG")
set(GCC_COMPILE_RELEASE_OPTIONS "-Wall;-O3;-DNDEBUG")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(ENABLE_NVIDIA_EXT "Enable Nvidia GL capabilites." OFF)
set(OPENGL_VERSION 330 CACHE STRING "Available OpenGL version")

if(ENABLE_NVIDIA_EXT)
  message(STATUS "Enabling Nvidia OpenGL extensions.")
  add_definitions(-DQUERY_MEMORY_NV)
endif()

add_definitions(-D__GL_VERSION=${OPENGL_VERSION})
message(STATUS "Using OpenGL version ${OPENGL_VERSION}.")

add_subdirectory(src)

# modify the module path so that the custom macros can be loaded downstream.
# Kinda hacky
if(NOT PROJECT_IS_TOP_LEVEL)
  set(CMAKE_MODULE_PATH
      "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake"
      PARENT_SCOPE)
endif()

# Prevent building tests for FetchContent build: https://www.foonathan.net/2022/06/cmake-fetchcontent/
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(GLOW_BUILD_TESTS      "whether or not tests should be built" ON)
    
  # Grep running processes for hints of gui. We only want to enable tests if they
  # can run. OpenGL tests depend on running X server and cannot be run without it.
  execute_process(
    COMMAND service --status-all
    COMMAND grep -P \\+.*\(gdm3|lightdm\)
    OUTPUT_VARIABLE XSERVER_FOUND)
  message(STATUS "Found X server related running processes: \n${XSERVER_FOUND}")
  
  if(XSERVER_FOUND OR GLOW_BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory(test)
  endif()

endif()