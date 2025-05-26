#include "inverted_index.h"

#include <algorithm>

Entry::Entry(DocIndex id, size_t cnt) : doc_id(id), count(cnt) {}

bool Entry::operator==(const Entry& other) const {
    return (doc_id == other.doc_id && count == other.count);
}

void InvertedIndex::UpdateDocumentBase(DocIndex doc, const std::map<std::string, size_t>& words) {
    for (auto& [word, count] : words) {
        auto& freqs = _freq_dictionary[word];
        auto entry = std::find_if(freqs.begin(), freqs.end(),
                                  [doc](const Entry& e) { return e.doc_id == doc; });
        if (entry != freqs.end()) {
            entry->count = count;
        } else {
            freqs.emplace_back(doc, count);
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    auto it = _freq_dictionary.find(word);
    if (it != _freq_dictionary.end()) {
        return it->second;
    }
    return {};
}
