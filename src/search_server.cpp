#include "search_server.h"

#include <unordered_set>

#include "word_iter.h"
// #define LOG_LVL LogLevel::Debug
#include "logger.h"

SearchServer::SearchServer(const InvertedIndex &ii) : _ii(ii) {}

std::vector<std::vector<RelativeIndex>> SearchServer::Search(
    const std::vector<std::string> &queries_input, size_t max_responses) {
    log_enter();
    std::vector<std::vector<RelativeIndex>> result;
    for (const auto &query : queries_input) {
        result.push_back(SearchOne(query, max_responses));
    }
    return result;
}

std::vector<RelativeIndex> SearchServer::SearchOne(const std::string &request,
                                                   size_t max_responses) {
    log_enter();
    log_debug("Handle request: \"", request, "\"");
    std::unordered_set<std::string> words;
    std::istringstream request_stream(request);
    Words words_iter(request_stream);
    for (auto w : words_iter) {
        log_debug("Word: \"", w, "\"");
        words.insert(w);
    }

    if (words.empty()) {
        log_error("No words in request: \"", request, "\"");
        return {};
    }

    std::string word = *words.begin();
    size_t doc_cnt = _ii.GetWordCount(word).size();
    for (auto w : words) {
        size_t cnt = _ii.GetWordCount(w).size();
        log_debug("Word: \"", w, "\", doc cnt: ", cnt);
        if (doc_cnt > cnt) {
            doc_cnt = cnt;
            word = w;
        }
    }
    log_debug("The word with the least number of documents: \"", word, "\"");

    auto possible_docs = _ii.GetWordCount(word);
    std::vector<RelativeIndex> relative_docs;
    size_t max_rank = 0;
    for (const auto &entry : possible_docs) {
        DocId doc_id = entry.doc_id;
        log_debug("Check doc: \'", doc_id, "\'");
        auto words_in_doc = _ii.GetDocWords(doc_id);
        size_t rank = 0;

        bool found_all_words = true;
        for (const auto &w : words) {
            auto cnt = words_in_doc.find(w);
            if (cnt == words_in_doc.end()) {
                log_debug("Word \"", w, "\" not found");
                found_all_words = false;
                continue;
            }
            rank += cnt->second;
        }
        if (found_all_words) {
            log_debug("Relative document has been found: \'", doc_id, "\' absolute rank: ", rank);
            relative_docs.emplace_back(doc_id, (float)rank);
            if (max_rank < rank) {
                max_rank = rank;
            }
        }
    }

    for (auto &doc : relative_docs) {
        doc.rank /= (float)max_rank;
    }

    std::sort(relative_docs.begin(), relative_docs.end(),
              [](const auto &a, const auto &b) { return a.rank > b.rank; });

    relative_docs.resize(std::min(relative_docs.size(), max_responses),
                         /*Dummy value*/ RelativeIndex(0, 0.0f));
    return relative_docs;
}
