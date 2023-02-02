cmake_minimum_required(VERSION 3.20)

project(glow_main)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(X11)

set(GCC_COMPILE_DEBUG_OPTIONS "-g2;-DDEBUG")
set(GCC_COMPILE_RELEASE_OPTIONS "-Wall;-O3;-DNDEBUG")

option(ENABLE_NVIDIA_EXT "Enable Nvidia GL capabilites." OFF)
set(OPENGL_VERSION 330 CACHE STRING "Available OpenGL version")

if(ENABLE_NVIDIA_EXT)
  message("Enabling Nvidia OpenGL extensions.")
  set(GL_DEFINITIONS "-DQUERY_MEMORY_NV")
endif()

set(GL_DEFINITIONS "-D__GL_VERSION=${OPENGL_VERSION} ${GL_DEFINITIONS}")
message(STATUS "Using OpenGL version ${OPENGL_VERSION} with compile definitions: ${GL_DEFINITIONS}")

add_subdirectory(src/glow)
target_compile_options(glow PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(glow PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
target_compile_definitions(glow PUBLIC "${GL_DEFINITIONS}")

add_subdirectory(src/glow_util)
target_compile_options(glow_util PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(glow_util PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
target_compile_definitions(glow_util PUBLIC "${GL_DEFINITIONS}")

# TODO: Install options for CMake only.

# Grep running processes for hints of gui. We only want to enable tests if they
# can run. OpenGL tests depend on running X server and cannot be run without it.
# execute_process(COMMAND service --status-all
#                 COMMAND grep -P \\+.*\(gdm3|lightdm\)
#                 OUTPUT_VARIABLE XSERVER_FOUND)
# message(STATUS "Found X server related running processes: \n${XSERVER_FOUND}")

# if(XSERVER_FOUND OR FORCE_BUILD_TEST)
#   message(STATUS "Building tests")
#   enable_testing()
#   # TODO: add testcases.
#   add_subdirectory(test)
# endif()



