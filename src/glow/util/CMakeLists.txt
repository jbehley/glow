add_library(glow_util STATIC)
add_library(glow::util ALIAS glow_util)
  
if(X11_FOUND)
  target_sources(glow_util PRIVATE 
    GlCamera.cpp 
    RoSeCamera.cpp
    FpsCamera.cpp
    RandomColorGenerator.cpp
    X11OffscreenContext.cpp)

  target_link_libraries(glow_util PUBLIC ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} Eigen3::Eigen)
else()
  target_sources(glow_util PRIVATE 
    GlCamera.cpp 
    RoSeCamera.cpp
    FpsCamera.cpp
    RandomColorGenerator.cpp)

  target_link_libraries(glow_util PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} Eigen3::Eigen)
endif()

target_include_directories(glow_util PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_options(glow_util PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(glow_util PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
target_compile_definitions(glow_util PUBLIC "${GL_DEFINITIONS}")
target_compile_features(glow_util PUBLIC cxx_std_11)