#include <iostream>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"

// #define LOG_LVL LogLevel::Debug
#include "config.h"
#include "inverted_index.h"
#include "logger.h"
#include "word_iter.h"

int main(int /*unused*/, char ** /*unused*/) {
    Logger::init();
    log_enter();
    log_info("Starting the FST...");
    log_info("Loading config...");
    Config cfg = Config::LoadFile("../config.json");
    log_info("Config loaded: name: ", cfg.name, " ", cfg.version);
    for (const auto &f : cfg.files) {
        log_info("File: ", f);
    }

    return EXIT_SUCCESS;
}
