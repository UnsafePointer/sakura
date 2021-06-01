#ifndef GRAFX_TEXTURE_HPP
#define GRAFX_TEXTURE_HPP
#include <tuple>

namespace Grafx {
class Texture {
  unsigned int m_object;
  int m_width;
  int m_height;

public:
  Texture(int width, int height);
  ~Texture();

  [[nodiscard]] auto dimensions() const -> std::pair<int, int>;
  [[nodiscard]] auto get_object() const -> unsigned int;
  void bind(unsigned int texture) const;
};
}; // namespace Grafx
#endif
