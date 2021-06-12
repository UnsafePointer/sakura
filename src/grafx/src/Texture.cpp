#include <glad/glad.h>
#include <grafx/Texture.hpp>

using namespace Grafx;

Texture::Texture(int width, int height) : m_width(width), m_height(height) {
  glGenTextures(1, &m_object);
  glBindTexture(GL_TEXTURE_2D, m_object);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB5_A1, width, height);
}

Texture::~Texture() { glDeleteTextures(1, &m_object); }

auto Texture::dimensions() const -> std::pair<int, int> {
  return {m_width, m_height};
}

auto Texture::get_object() const -> GLuint { return m_object; }

void Texture::bind(unsigned int texture) const {
  glActiveTexture(texture);
  glBindTexture(GL_TEXTURE_2D, m_object);
}
