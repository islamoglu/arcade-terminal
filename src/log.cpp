#include "log.hpp"
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> LogManager::logger_instance = nullptr;

void LogManager::init_logger(const std::string &filename)
{
    logger_instance = spdlog::basic_logger_mt("logger", filename, true);
    logger_instance->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    logger_instance->set_level(LogLevel::debug);
}

LogLevel LogManager::get_log_level()
{
    return logger_instance->level();
}