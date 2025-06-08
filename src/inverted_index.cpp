#include "inverted_index.h"

#include <algorithm>
#include <thread>
#include "BS_thread_pool.hpp"

// #define LOG_LVL LogLevel::Debug
#include "logger.h"
#include "word_iter.h"

Entry::Entry(DocId id, size_t cnt) : doc_id(id), count(cnt) {}

bool Entry::operator==(const Entry& other) const {
    return (doc_id == other.doc_id && count == other.count);
}

bool Entry::operator!=(const Entry& other) const { return !(*this == other); }

/**
 * @brief Read file and count words.
 * @param path Path to the file to read.
 * @return A map where keys are unique words and values are their counts in the file.
 */
std::map<std::string, size_t> handle_file(const char* path) {
    log_info("Indexing \"", path, "\" in thread: ", std::this_thread::get_id());
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

InvertedIndex InvertedIndex::FromFiles(const std::vector<std::string>& files) {
    log_enter();
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

void InvertedIndex::UpdateDocumentBase(DocId doc, std::map<std::string, size_t> words) {
    log_enter();
    log_debug("Update base for doc id: ", doc);
    for (auto& [word, count] : words) {
        auto& freqs = _freq_dictionary[word];
        auto entry = std::find_if(freqs.begin(), freqs.end(),
                                  [doc](const Entry& e) { return e.doc_id == doc; });
        log_debug("word: \"", word, "\", cnt: ", count);
        if (entry != freqs.end()) {
            entry->count = count;
        } else {
            freqs.emplace_back(doc, count);
        }
    }
    if (!_docs.insert_or_assign(doc, std::move(words)).second) {
        log_warn("Document '", doc, "' overriden!");
    };
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    auto it = _freq_dictionary.find(word);
    if (it != _freq_dictionary.end()) {
        return it->second;
    }
    return {};
}

std::map<std::string, size_t> InvertedIndex::GetDocWords(DocId id) const {
    auto it = _docs.find(id);
    if (it != _docs.end()) {
        return it->second;
    }
    return {};
}
