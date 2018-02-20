# build the test cases
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_opengl
  main.cpp
  texture-test.cpp
  buffer-test.cpp
  framebuffer-test.cpp
  color-test.cpp
  #camera-test.cpp
)


target_link_libraries(test_opengl ${GTEST_MAIN_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glow glow_util)

add_test(test_opengl test_opengl)
