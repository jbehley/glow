#include "GlShaderCache.h"

#include <iostream>

namespace glow {

GlShaderCache& GlShaderCache::getInstance() {
  static std::unique_ptr<GlShaderCache> instance(new GlShaderCache());

  return *instance;
}

bool GlShaderCache::hasSource(const std::string& filename) {
  std::string b = basename(filename);

  return (sources_.find(b) != sources_.end());
}

std::string GlShaderCache::getSource(const std::string& filename) {
  std::string b = basename(filename);

  return sources_[b];
}

void GlShaderCache::insertSource(const std::string& filename, const std::string& source) {
  std::string b = basename(filename);
  if (sources_.find(b) != sources_.end()) {
    std::cerr << "Warning: Overwriting cached shader source for filename '" << filename << "'" << std::endl;
  }
  sources_[b] = source;
}

std::string GlShaderCache::basename(const std::string& filename) const {
  std::string::size_type n = filename.rfind("/");
  if (n == std::string::npos) return filename;

  return filename.substr(n);
}

GlShaderCache::GlShaderCache() {}
GlShaderCache::GlShaderCache(const GlShaderCache&){};

} /* namespace glow */
