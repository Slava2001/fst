#include <gtest/gtest.h>

#include "logger.h"
#include "request.h"
#include "search_server.h"
#include "word_iter.h"

TEST(SearchServer, SearchOne) {
    InvertedIndex ii;
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"WORLD", 20}});
    ii.UpdateDocumentBase(1, {{"hello", 15}, {"world", 25}});
    ii.UpdateDocumentBase(2, {{"HELLO", 20}, {"world", 30}});
    ii.UpdateDocumentBase(3, {{"HELLO", 20}, {"world", 30}});
    ii.UpdateDocumentBase(4, {{"HELLO", 20}, {"world", 30}});
    SearchServer server(ii);
    auto _resp = server.SearchOne("hello, world", 5);
}

std::vector<std::map<std::string, size_t>> strs_to_docs(const std::vector<std::string>& strs) {
    std::vector<std::map<std::string, size_t>> result;
    for (const auto& str : strs) {
        std::istringstream stream(str);
        Words words(stream);
        std::map<std::string, size_t> doc;
        for (const auto& word : words) {
            ++doc[word];
        }
        result.push_back(doc);
    }
    return result;
}

void assert_results_eq(const std::vector<std::vector<RelativeIndex>>& result,
                       const std::vector<std::vector<RelativeIndex>>& expected) {
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i].size(), expected[i].size());
        for (size_t j = 0; j < result[i].size(); ++j) {
            ASSERT_EQ(result[i][j].docid, expected[i][j].docid);
            ASSERT_FLOAT_EQ(result[i][j].rank, expected[i][j].rank);
        }
    }
}

TEST(SearchServer, TestSimple) {
    const std::vector<std::string> docs = {
        "milk milk milk milk water water water", "milk water water",
        "milk milk milk milk milk water water water water water", "americano cappuccino"};

    const std::vector<std::string> request = {"milk water", "sugar"};
    const std::vector<std::vector<RelativeIndex>> expected = {{{2, 1.0f}, {0, 0.7f}, {1, 0.3f}},
                                                              {}};
    InvertedIndex idx;
    auto converted_docs = strs_to_docs(docs);
    for (size_t i = 0; i < converted_docs.size(); ++i) {
        idx.UpdateDocumentBase(i, converted_docs[i]);
    }
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.Search(request, 5);
    assert_results_eq(result, expected);
}

TEST(SearchServer, TestTop5) {
    const std::vector<std::string> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow is the capital of russia third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland",
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<RelativeIndex>> expected = {{{7, 1}, {14, 1}}};
    InvertedIndex idx;
    auto converted_docs = strs_to_docs(docs);
    for (size_t i = 0; i < converted_docs.size(); ++i) {
        idx.UpdateDocumentBase(i, converted_docs[i]);
    }
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.Search(request, 5);
    assert_results_eq(result, expected);
}
