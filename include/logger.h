#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <ctime>
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

enum class LogLevel { Debug, Info, Warn, Error, Fatal };
std::ostream &operator<<(std::ostream &os, const LogLevel &lvl);

#ifndef LOG_LVL
#define LOG_LVL LogLevel::Info
#endif
static const LogLevel __LOG_LVL = LOG_LVL;

#ifdef LOGGER_NO_COLOR_LVL
#define LOG_COLOR_GRAY ""
#define LOG_COLOR_REG ""
#define LOG_BG_COLOR_REG ""
#define LOG_BG_GREEN ""
#define LOG_COLOR_YELLOW ""
#define LOG_COLOR_BLUE ""
#define LOG_COLOR_CLEAR ""
#else
#define LOG_COLOR_GRAY "\033[30m"
#define LOG_COLOR_REG "\033[31m"
#define LOG_BG_COLOR_REG "\033[41m"
#define LOG_BG_GREEN "\033[32m"
#define LOG_COLOR_YELLOW "\033[33m"
#define LOG_COLOR_BLUE "\033[36m"
#define LOG_COLOR_CLEAR "\033[0m"
#endif

#define log_lvl(lvl, ...) \
    Logger::log(__LOG_LVL, lvl, __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define log_debug(...) log_lvl(LogLevel::Debug, ##__VA_ARGS__)
#define log_info(...) log_lvl(LogLevel::Info, ##__VA_ARGS__)
#define log_warn(...) log_lvl(LogLevel::Warn, ##__VA_ARGS__)
#define log_error(...) log_lvl(LogLevel::Error, ##__VA_ARGS__)
#define log_fatal(...) log_lvl(LogLevel::Fatal, ##__VA_ARGS__)

#define log_enter() log_debug("Enter")

/// @brief Singleton logger class for logging messages with different log levels.
class Logger {
   public:
    /// @brief  Initializes the logger instance. Should be called only once.
    static void init();

    /// Logs a message with the specified log level, file, line, and function.
    template <typename... Args>
    static void log(LogLevel min_log_lvl, LogLevel log_lvl, const char *file, size_t line,
                    const char *func, const Args &...args) {
        if (!_inst) {
            return;  // Logger not initialized
        }

        if (log_lvl < min_log_lvl) {
            return;
        }

        std::stringstream msg;
        msg << "[" << time(0) << "] " << log_lvl << " " << LOG_COLOR_GRAY "" << file << ":" << line
            << " " << func << ":" LOG_COLOR_CLEAR " ";
        (msg << ... << args) << std::endl;
        std::cerr << msg.str();
    }

   private:
    static std::unique_ptr<Logger> _inst;
};

#endif  // INCLUDE_LOGGER_H
