cmake_minimum_required(VERSION 3.20)

project(glow_main)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(X11)

# find_package(catkin)

# if(catkin_FOUND)
#   catkin_package(
#     INCLUDE_DIRS src/
#     LIBRARIES glow glow_util
#     CFG_EXTRAS GlowShaderCompilation.cmake GenCppFile.cmake
#   )
# endif()

# include_directories(${catkin_INCLUDE_DIRS} src/)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS "-std=c++11 -g2 -DDEBUG ${CMAKE_CXX_FLAGS}")
else()
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3 -DNDEBUG ${CMAKE_CXX_FLAGS}")
endif()

message(STATUS "Using CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

option(ENABLE_NVIDIA_EXT "Enable Nvidia GL capabilites." OFF)
set(OPENGL_VERSION 330 CACHE STRING "Available OpenGL version")

if(ENABLE_NVIDIA_EXT)
  message("Enabling Nvidia OpenGL extensions.")
  add_definitions(-DQUERY_MEMORY_NV)
endif()

add_definitions(-D__GL_VERSION=${OPENGL_VERSION})
message(STATUS "Using OpenGL version ${OPENGL_VERSION}.")

add_subdirectory(src/glow)

add_subdirectory(src/glow_util)



############ Testing ##################
## old

# if(NOT GTEST_FOUND)

#   IF(IS_DIRECTORY "/usr/src/gtest/")
#     MESSAGE(STATUS "Found google test sources in /usr/src/gtest/")

#     ADD_SUBDIRECTORY(/usr/src/gtest/ gtest)

#     # mimick the behaviour of find_package(GTest)
#     SET(GTEST_FOUND TRUE)
#     SET(GTEST_BOTH_LIBRARIES gtest gtest_main)
#     SET(GTEST_LIBRARIES gtest)
#     SET(GTEST_MAIN_LIBRARIES gtest_main)
#   ELSE()
#     find_package(GTest)
#   ENDIF()
# endif()
## redone
# enable_testing()
# add_subdirectory(test)
# TODO: Install options for CMake only.

# Grep running processes for hints of gui. We only want to enable tests if they
# can run. OpenGL tests depend on running X server and cannot be run without it.
execute_process(COMMAND service --status-all
                COMMAND grep -P \\+.*\(gdm3|lightdm\)
                OUTPUT_VARIABLE XSERVER_FOUND)
message(STATUS "Found X server related running processes: \n${XSERVER_FOUND}")

# if(GTEST_FOUND AND (XSERVER_FOUND OR FORCE_BUILD_TEST))
#   message(STATUS "Building tests")
#   enable_testing()
#   # TODO: add testcases.
#   add_subdirectory(test)


# endif()



