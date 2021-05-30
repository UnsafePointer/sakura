#include "sakura/Emulator.hpp"
#include "Disassembler.hpp"
#include "IO.hpp"
#include "Instructions.hpp"
#include "Instructions_Impl.hpp"
#include "Interrupt.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include "ProgrammableSoundGenerator.hpp"
#include "Timer.hpp"
#include "VideoColorEncoder.hpp"
#include "VideoDisplayController.hpp"
#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <utility>

using namespace Sakura;

Emulator::Emulator()
    : m_interrupt_controller(
          std::make_unique<HuC6280::Interrupt::Controller>()),
      m_video_color_encoder_controller(std::make_unique<HuC6260::Controller>()),
      m_video_display_controller(std::make_unique<HuC6270::Controller>(
          m_interrupt_controller, m_video_color_encoder_controller)),
      m_mapping_controller(std::make_unique<HuC6280::Mapping::Controller>(
          m_interrupt_controller, m_video_color_encoder_controller,
          m_video_display_controller)),
      m_processor(std::make_unique<HuC6280::Processor>(m_mapping_controller,
                                                       m_interrupt_controller)),
      m_disassembler(std::make_unique<HuC6280::Disassembler>(m_processor)){};

Emulator::~Emulator() = default;

void Emulator::emulate() {
  for (;;) {
    if (m_should_pause) {
      m_should_pause = false;
      break;
    }
    uint8_t opcode = m_processor->fetch_instruction();
    HuC6280::InstructionHandler<uint8_t> handler =
        HuC6280::INSTRUCTION_TABLE<uint8_t>[opcode];
    m_disassembler->disassemble(opcode);
    uint8_t cycles = handler(m_processor, opcode);
    m_mapping_controller->step(cycles);
    m_processor->check_interrupts();
  }
}

void Emulator::register_loggers(const LogConfig &log_config) {
  auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "sakura.log", 1024 * 1024 * 250, 10, true);
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto disassembler_logger = std::make_shared<spdlog::logger>(
      DISASSEMBLER_LOGGER_NAME,
      spdlog::sinks_init_list({console_sink, file_sink}));
  disassembler_logger->set_level(
      spdlog::level::from_str(log_config.disassembler));
  spdlog::register_logger(disassembler_logger);

  auto interrupt_controller_logger = std::make_shared<spdlog::logger>(
      Interrupt::LOGGER_NAME,
      spdlog::sinks_init_list({console_sink, file_sink}));
  interrupt_controller_logger->set_level(
      spdlog::level::from_str(log_config.interrupt_controller));
  spdlog::register_logger(interrupt_controller_logger);

  auto io_logger = std::make_shared<spdlog::logger>(
      IO::LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  io_logger->set_level(spdlog::level::from_str(log_config.io));
  spdlog::register_logger(io_logger);

  auto mapping_controller_logger = std::make_shared<spdlog::logger>(
      Mapping::LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  mapping_controller_logger->set_level(
      spdlog::level::from_str(log_config.mapping_controller));
  spdlog::register_logger(mapping_controller_logger);

  auto processor_logger = std::make_shared<spdlog::logger>(
      LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  processor_logger->set_level(spdlog::level::from_str(log_config.processor));
  spdlog::register_logger(processor_logger);

  auto programmable_sound_generator_logger = std::make_shared<spdlog::logger>(
      ProgrammableSoundGenerator::LOGGER_NAME,
      spdlog::sinks_init_list({console_sink, file_sink}));
  programmable_sound_generator_logger->set_level(
      spdlog::level::from_str(log_config.programmable_sound_generator));
  spdlog::register_logger(programmable_sound_generator_logger);

  auto timer_logger = std::make_shared<spdlog::logger>(
      Timer::LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  timer_logger->set_level(spdlog::level::from_str(log_config.timer));
  spdlog::register_logger(timer_logger);

  auto video_color_encoder_logger = std::make_shared<spdlog::logger>(
      HuC6260::LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  video_color_encoder_logger->set_level(
      spdlog::level::from_str(log_config.video_color_encoder));
  spdlog::register_logger(video_color_encoder_logger);

  auto video_display_controller_logger = std::make_shared<spdlog::logger>(
      HuC6270::LOGGER_NAME, spdlog::sinks_init_list({console_sink, file_sink}));
  video_display_controller_logger->set_level(
      spdlog::level::from_str(log_config.video_display_controller));
  spdlog::register_logger(video_display_controller_logger);
}

void Emulator::initialize(const std::filesystem::path &rom,
                          const LogConfig &log_config) {
  Emulator::register_loggers(log_config);
  m_processor->initialize(rom);
}

void Emulator::set_vsync_callback(
    std::function<void(std::array<float, COLOR_TABLE_RAM_DATA_LENGTH>)>
        vsync_callback) {
  m_video_display_controller->set_vsync_callback(std::move(vsync_callback));
}

void Emulator::set_should_pause() { m_should_pause = true; }
