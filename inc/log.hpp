#pragma once

#include <spdlog/spdlog.h>

typedef spdlog::level::level_enum LogLevel;

class LogManager
{
public:
    static void init_logger(const std::string &filename);
    static LogLevel get_log_level();
    template <typename... Args>
    static void log(LogLevel level, spdlog::format_string_t<Args...> fmt, Args &&...args)
    {
        logger_instance->log(level, fmt, std::forward<Args>(args)...);
    }

private:
    static std::shared_ptr<spdlog::logger> logger_instance;
};

#define LOG(level, fmt, ...)                            \
    {                                                   \
        if (LogManager::get_log_level() <= level)       \
            LogManager::log(level, fmt, ##__VA_ARGS__); \
    }

#define ERROR(fmt, ...) LOG(LogLevel::err, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) LOG(LogLevel::warn, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) LOG(LogLevel::info, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) LOG(LogLevel::debug, fmt, ##__VA_ARGS__)
#define TRACE(fmt, ...) LOG(LogLevel::trace, fmt, ##__VA_ARGS__)
