#include <iostream>
#include <sstream>
#include <string>

#include "BS_thread_pool.hpp"
#include "nlohmann/json.hpp"

// #define LOG_LVL LogLevel::Debug
#include "config.h"
#include "inverted_index.h"
#include "logger.h"
#include "request.h"
#include "search_server.h"
#include "word_iter.h"

InvertedIndex create_index(std::vector<std::string> files);

int main(int /*unused*/, char** /*unused*/) {
    Logger::init();
    log_enter();
    log_info("Starting the FST...");
    log_info("Loading config...");
    Config cfg = Config::LoadFile("./config.json");
    log_info("Config loaded: name: ", cfg.name, " v", cfg.version);

    log_info("Creating inverted index for ", cfg.files.size(), " files...");
    InvertedIndex ii = create_index(cfg.files);
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

std::map<std::string, size_t> handle_file(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        log_fatal("Failed to open file: ", path);
        throw std::runtime_error("File not found");
    }
    Words words(file);
    std::map<std::string, size_t> word_count;
    for (const auto& word : words) {
        ++word_count[word];
    }
    return word_count;
}

InvertedIndex create_index(std::vector<std::string> files) {
    BS::thread_pool pool;
    log_info("Using ", pool.get_thread_count(), " threads for processing files...");
    std::vector<std::future<std::map<std::string, size_t>>> futures;
    for (const auto& file : files) {
        futures.push_back(pool.submit_task([&] { return handle_file(file.c_str()); }));
    }
    InvertedIndex ii;
    for (size_t i = 0; i < futures.size(); ++i) {
        ii.UpdateDocumentBase(i, futures[i].get());
    }
    return ii;
}
