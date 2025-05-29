#include <iostream>
#include <sstream>
#include <string>

// #define LOG_LVL LogLevel::Debug
#include "config.h"
#include "inverted_index.h"
#include "logger.h"
#include "request.h"
#include "search_server.h"

int main(int /*unused*/, char** /*unused*/) {
    Logger::init();
    log_enter();
    log_info("Starting the FST...");
    log_info("Loading config...");
    Config cfg = Config::LoadFile("./config.json");
    log_info("Config loaded: name: ", cfg.name, " v", cfg.version);

    log_info("Creating inverted index for ", cfg.files.size(), " files...");
    InvertedIndex ii = InvertedIndex::FromFiles(cfg.files);
    log_info("Inverted index created successfully.");

    SearchServer server(ii);
    log_info("Search server initialized.");

    Request request = Request::LoadFile("./request.json");
    log_info("Request file loaded: ", request.requests.size(), " queries.");
    std::vector<std::vector<RelativeIndex>> responses =
        server.Search(request.requests, cfg.max_responses);
    log_info("Search completed.");

    Answers answers;
    for (const auto& response : responses) {
        answers.answers.emplace_back(!response.empty(), std::move(response));
    }

    log_info("Saving answers to file...");
    answers.SaveFile("./answers.json");
    log_info("Answers saved successfully.");
    return EXIT_SUCCESS;
}

