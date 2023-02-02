set(TEST_BINARY ${PROJECT_NAME}_test)
add_executable(${TEST_BINARY}
  main.cpp
  texture-test.cpp
  buffer-test.cpp
  framebuffer-test.cpp
  color-test.cpp
  #camera-test.cpp
)

target_link_libraries(${TEST_BINARY} 
  PUBLIC 
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    glow 
    glow_util
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_BINARY})
# add_test(${TEST_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_BINARY})
