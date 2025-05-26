#include <iostream>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"

#define LOG_LVL LogLevel::Debug
#include "logger.h"
#include "word_iter.h"

int main(int /*unused*/, char** /*unused*/) {
    Logger::init();
    log_enter();
    log_info("Starting the FST...");

    std::string text = "hello, world! snake_case, camelCase, PascalCase, kebab-case, UPPER_CASE";
    std::istringstream str(text);
    Words words(str);
    for (auto word = words.begin(); word != words.end(); ++word) {
        log_info("Word: ", *word);
    }

    return EXIT_SUCCESS;
}
