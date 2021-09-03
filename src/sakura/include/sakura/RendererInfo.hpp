#ifndef SAKURA_RENDERERINFO_HPP
#define SAKURA_RENDERERINFO_HPP

#include "sakura/Constants.hpp"
#include <memory>

namespace Sakura {
namespace HuC6270 {
class Controller;
} // namespace HuC6270
namespace HuC6260 {
class Controller;
} // namespace HuC6260

class RendererInfo {
private:
  std::unique_ptr<HuC6270::Controller> &m_video_display_controller;
  std::unique_ptr<HuC6260::Controller> &m_video_color_encoder_controller;

public:
  RendererInfo(
      std::unique_ptr<HuC6270::Controller> &video_display_controller,
      std::unique_ptr<HuC6260::Controller> &video_color_encoder_controller);
  ~RendererInfo() = default;

  auto get_color_table_data() -> std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>;
  auto get_background_attribute_table_data()
      -> std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH>;
  auto get_character_generator_data()
      -> std::array<float, CHARACTER_GENERATOR_DATA_LENGTH>;
};
} // namespace Sakura

#endif
