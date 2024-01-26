# GTest Setup ######
message(STATUS "Fetching GTest.")
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
)

FetchContent_MakeAvailable(googletest)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_build_tests OFF CACHE BOOL "" FORCE)

# build the test cases

add_executable(test_opengl
  main.cpp
  texture-test.cpp
  buffer-test.cpp
  framebuffer-test.cpp
  color-test.cpp
  #camera-test.cpp
)


target_link_libraries(test_opengl gtest_main glow glow_util pthread)

add_test(test_opengl test_opengl)
