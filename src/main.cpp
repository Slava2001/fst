#include <iostream>

#define LOG_LVL LogLevel::Debug
#include "logger.h"
#include "nlohmann/json.hpp"

int main(int /*unused*/, char** /*unused*/) {
    log_enter();
    log_info("Starting the FST...");

    return EXIT_SUCCESS;
}
