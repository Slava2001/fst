#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

enum class LogLevel { Debug, Info, Warn, Error, Fatal };
std::ostream &operator<<(std::ostream &os, const LogLevel &lvl);

#ifndef LOG_LVL
#define LOG_LVL LogLevel::Info
#endif
static const LogLevel __LOG_LVL = LOG_LVL;

// #define LOGGER_NO_COLOR_LVL
#ifdef LOGGER_NO_COLOR_LVL
#define LOG_COLOR_GRAY ""
#define LOG_COLOR_RED ""
#define LOG_BG_COLOR_RED ""
#define LOG_COLOR_GREEN ""
#define LOG_COLOR_YELLOW ""
#define LOG_COLOR_BLUE ""
#define LOG_COLOR_CLEAR ""
#else
#define LOG_COLOR_GRAY "\033[90m"
#define LOG_COLOR_RED "\033[31m"
#define LOG_BG_COLOR_RED "\033[41m"
#define LOG_COLOR_GREEN "\033[32m"
#define LOG_COLOR_YELLOW "\033[33m"
#define LOG_COLOR_BLUE "\033[36m"
#define LOG_COLOR_CLEAR "\033[0m"
#endif

#if defined(__GNUC__) || defined(__clang__)
#define __FUNC_NAME__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define __FUNC_NAME__ __FUNCSIG__
#else
#define __FUNC_NAME__ __func__
#endif

#define log_lvl(lvl, ...) \
    Logger::log(__LOG_LVL, lvl, __FILE__, __LINE__, __FUNC_NAME__, ##__VA_ARGS__)
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
