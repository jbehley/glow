add_library(glow STATIC)
add_library(glow::glow ALIAS glow)

target_sources(glow PRIVATE 
  glexception.cpp
  GlProgram.cpp
  GlShader.cpp
  GlVertexArray.cpp
  GlUniform.cpp
  glutil.cpp
  GlTexture.cpp
  GlTextureRectangle.cpp
  GlFramebuffer.cpp
  GlRenderbuffer.cpp
  GlTransformFeedback.cpp
  GlQuery.cpp
  GlSampler.cpp
  GlState.cpp
  GlColor.cpp
  GlShaderCache.cpp
  GlCapabilities.cpp
  GlTextureBuffer.cpp)

target_include_directories(glow PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(glow PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${Boost_LIBRARIES} Eigen3::Eigen)

target_compile_options(glow PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(glow PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
target_compile_definitions(glow PUBLIC "${GL_DEFINITIONS}")
target_compile_features(glow PUBLIC cxx_std_11)