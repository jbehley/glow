#ifndef SRC_GLOW_UTIL_EGLOFFSCREENCONTEXT_H_
#define SRC_GLOW_UTIL_EGLOFFSCREENCONTEXT_H_

#include <EGL/egl.h>

namespace glow {

/** \brief offscreen context based on EGL.
 *
 *  \author behley
 */
class EglOffscreenContext {

  public:
    EglOffscreenContext();

    ~EglOffscreenContext();

  protected:
    EGLContext eglCtx;
    EGLDisplay eglDpy;
    EGLConfig eglCfg;
    EGLSurface eglSurf;
};

} /* namespace velo_sim */

#endif /* SRC_GLOW_UTIL_EGLOFFSCREENCONTEXT_H_ */
