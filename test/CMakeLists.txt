# following the gtest docs pretty much

###### GTest Setup ######
message("Fetching GTest.")
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
###### GTest Setup ######

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

# gtest requires c++14 but this shit doesnt work
target_compile_features(${TEST_BINARY} PUBLIC cxx_std_14)

include(GoogleTest)
gtest_discover_tests(${TEST_BINARY})
# add_test(${TEST_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_BINARY})
