#include "sakura/Emulator.hpp"
#include "Disassembler.hpp"
#include "IO.hpp"
#include "Instructions.hpp"
#include "Instructions_Impl.hpp"
#include "Interrupt.hpp"
#include "Memory.hpp"
#include "Processor.hpp"
#include "ProgrammableSoundGenerator.hpp"
#include "VideoColorEncoder.hpp"
#include "VideoDisplayController.hpp"
#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

using namespace Sakura;

Emulator::Emulator()
    : m_processor(std::make_unique<HuC6280::Processor>()),
      m_disassembler(std::make_unique<HuC6280::Disassembler>(m_processor)){};

Emulator::~Emulator() = default;

void Emulator::emulate() {
  for (;;) {
    uint8_t opcode = m_processor->fetch_instruction();
    HuC6280::InstructionHandler<uint8_t> handler =
        HuC6280::INSTRUCTION_TABLE<uint8_t>[opcode];
    m_disassembler->disassemble(opcode);
    handler(m_processor, opcode);
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
