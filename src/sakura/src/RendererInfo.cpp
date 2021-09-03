#include "sakura/RendererInfo.hpp"
#include "VideoColorEncoder.hpp"
#include "VideoDisplayController.hpp"

using namespace Sakura;

RendererInfo::RendererInfo(
    std::unique_ptr<HuC6270::Controller> &video_display_controller,
    std::unique_ptr<HuC6260::Controller> &video_color_encoder_controller)
    : m_video_display_controller(video_display_controller),
      m_video_color_encoder_controller(video_color_encoder_controller){};

auto RendererInfo::get_color_table_data()
    -> std::array<float, COLOR_TABLE_RAM_DATA_LENGTH> {
  return m_video_color_encoder_controller->get_color_table_data();
}

auto RendererInfo::get_background_attribute_table_data()
    -> std::array<float, BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH> {
  return m_video_display_controller->get_background_attribute_table_data();
}
auto RendererInfo::get_character_generator_data()
    -> std::array<float, CHARACTER_GENERATOR_DATA_LENGTH> {
  return m_video_display_controller->get_character_generator_data();
}
