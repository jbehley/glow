#include "GlTransformFeedback.h"
#include "glexception.h"

namespace glow {

GlTransformFeedback::GlTransformFeedback() : linked_(std::make_shared<bool>(false)) {
#if __GL_VERSION >= 400L
  glGenTransformFeedbacks(1, &id_);
  ptr_ = std::shared_ptr<GLuint>(new GLuint(id_), [](GLuint* ptr) {
    glDeleteTransformFeedbacks(1, ptr);
    delete ptr;
  });
#endif
}

void GlTransformFeedback::bind() {
  if (!linked_) throw GlTransformFeedbackError("Transform feedback not linked with any program!");
#if __GL_VERSION >= 400L
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, id_);  // if OpenGl4.0+
#endif

  // bind buffers.
  for (uint32_t i = 0; i < buffers_.size(); ++i) {
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, i, *(buffers_[i].second));
  }
  CheckGlError();
}

void GlTransformFeedback::begin(TransformFeedbackMode mode) {
  countquery_.begin();
  glBeginTransformFeedback(static_cast<GLenum>(mode));

  CheckGlError();
}

uint32_t GlTransformFeedback::end() {
  glEndTransformFeedback();

  glFinish();

  countquery_.end();

  return (uint32_t)countquery_;
}

#if __GL_VERSION >= 400L
void GlTransformFeedback::pause() {
  glPauseTransformFeedback();  // if OpenGl4.0+
}

void GlTransformFeedback::resume() {
  glResumeTransformFeedback();  // if OpenGl4.0+
}

void GlTransformFeedback::draw(GLenum mode) const {
  // OpenGL 4.0+
  glDrawTransformFeedback(mode, id_);
}
#endif

void GlTransformFeedback::release() {
#if __GL_VERSION >= 400L
  glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);  // if OpenGl4.0+
#endif
  // bind buffers.
  for (uint32_t i = 0; i < buffers_.size(); ++i) {
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, i, 0);
  }
}

void GlTransformFeedback::registerVaryings(GLuint program_id) {
  // here the magic happens. All attached varyings are bound to the given program.
  // Should it be possible to have a single transform feedback to bind on multiple programs?

  // 1. determine which buffer mode...
  GLenum bufferMode = (buffers_.size() == 1) ? GL_INTERLEAVED_ATTRIBS : GL_SEPARATE_ATTRIBS;
  bool addNextBuffer = false;
  std::string nextBuffer = "gl_NextBuffer";

  for (auto& p : buffers_) {
    if (p.first.size() > 1 && buffers_.size() > 1) {
#if __GL_VERSION >= 400L
      bufferMode = GL_INTERLEAVED_ATTRIBS;
      // TODO: Check: ONLY SUPPORTED IN OpenGL 4.0+
      addNextBuffer = true;
      break;
#else
      throw GlTransformFeedbackError(
          "Multiple interleaved buffers using gl_NextBuffer only supported beginning with GL version 4.0");
#endif
    }
  }

  // 2. set varyings.
  for (auto& p : buffers_) {
    uint32_t n = p.first.size() + static_cast<uint32_t>(addNextBuffer);

    const char* vars[n];
    for (uint32_t i = 0; i < p.first.size(); ++i) vars[i] = p.first[i].c_str();

    if (addNextBuffer) vars[n - 1] = nextBuffer.c_str();

    glTransformFeedbackVaryings(program_id, n, vars, bufferMode);
  }
}

} /* namespace rv */
