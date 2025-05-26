#include "logger.h"

std::unique_ptr<Logger> Logger::_inst = nullptr;

void Logger::init() {
    if (_inst != nullptr) {
        throw std::runtime_error("Logger is already initialized.");
    }
    _inst = std::make_unique<Logger>();
}

std::ostream &operator<<(std::ostream &os, const LogLevel &lvl) {
    switch (lvl) {
        case LogLevel::Debug:
            os << LOG_COLOR_GREEN << "DEBUG";
            break;
        case LogLevel::Info:
            os << LOG_COLOR_BLUE << "INFO";
            break;
        case LogLevel::Warn:
            os << LOG_COLOR_YELLOW << "WARN";
            break;
        case LogLevel::Error:
            os << LOG_COLOR_RED << "ERROR";
            break;
        case LogLevel::Fatal:
            os << LOG_BG_COLOR_RED << "FATAL";
            break;
    };
    return (os << LOG_COLOR_CLEAR);
}
