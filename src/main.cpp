#include <iostream>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"

#define LOG_LVL LogLevel::Debug
#include "inverted_index.h"
#include "logger.h"
#include "word_iter.h"

int main(int /*unused*/, char ** /*unused*/) {
    Logger::init();
    log_enter();
    log_info("Starting the FST...");

    std::string text =
        "hello, world! hello snake_case, hello camelCase, hello PascalCase, hello kebab-case, "
        "hello UPPER_CASE";
    std::istringstream str(text);
    Words words_iter(str);
    std::map<std::string, size_t> words;
    for (const auto &word : words_iter) {
        words[word]++;
    }

    log_info("Words in the document:");
    for (const auto &word : words_iter) {
        log_info("Word: ", word, ", Count: ", words[word]);
    }

    InvertedIndex index;
    index.UpdateDocumentBase(0, words);

    log_info("Inverted index created. Now querying for 'hello':");
    auto result = index.GetWordCount("hello");
    if (result.empty()) {
        log_info("No occurrences of 'hello' found.");
    } else {
        log_info("Occurrences of 'hello':");
        for (const auto &entry : result) {
            log_info("Document ID: ", entry.doc_id, ", Count: ", entry.count);
        }
    }

    return EXIT_SUCCESS;
}
