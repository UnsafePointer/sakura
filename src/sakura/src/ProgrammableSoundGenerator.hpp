#ifndef SAKURA_PROGRAMMABLE_SOUND_GENERATOR_HPP
#define SAKURA_PROGRAMMABLE_SOUND_GENERATOR_HPP

#include <cstdint>

namespace Sakura::HuC6280::ProgrammableSoundGenerator {

union MainAmplitudeLevelAdjustment {
  struct {
    uint8_t lmal : 4;
    uint8_t rmal : 4;
  };
  uint8_t value;

  MainAmplitudeLevelAdjustment() : value() {}
};

union LowFrequencyOscillatorControl {
  struct {
    uint8_t lf_ctl : 2;
    uint8_t unused : 5;
    uint8_t lf_trg : 1;
  };

  uint8_t value;

  LowFrequencyOscillatorControl() : value() {}
};

union ChannelSelect {
  struct {
    uint8_t ch_sel : 3;
    uint8_t unused : 5;
  };

  uint8_t value;

  ChannelSelect() : value() {}
};

class Controller {
private:
  MainAmplitudeLevelAdjustment m_main_amplitude_level_adjustment;
  uint8_t m_low_frequency_oscillator_frequency;
  LowFrequencyOscillatorControl m_low_frequency_oscillator_control;
  ChannelSelect m_channel_select;

public:
  Controller() = default;
  ~Controller() = default;

  [[nodiscard]] auto load(uint16_t offset) const -> uint8_t;
  void store(uint16_t offset, uint8_t value);
};
}; // namespace Sakura::HuC6280::ProgrammableSoundGenerator

#endif
