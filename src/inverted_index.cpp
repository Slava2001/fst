#include "inverted_index.h"

#include <algorithm>
// #define LOG_LVL LogLevel::Debug
#include "logger.h"

Entry::Entry(DocId id, size_t cnt) : doc_id(id), count(cnt) {}

bool Entry::operator==(const Entry& other) const {
    return (doc_id == other.doc_id && count == other.count);
}

bool Entry::operator!=(const Entry& other) const { return !(*this == other); }

void InvertedIndex::UpdateDocumentBase(DocId doc, const std::map<std::string, size_t>& words) {
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
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    auto it = _freq_dictionary.find(word);
    if (it != _freq_dictionary.end()) {
        return it->second;
    }
    return {};
}
