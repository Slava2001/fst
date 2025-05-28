#include <gtest/gtest.h>

#include <sstream>

#define TEST_FRIENDS friend class InvertedIndex_UpdateDocumentBase_Test;
#include "inverted_index.h"

TEST(Entry, Constructor) {
    Entry e(0, 10);
    ASSERT_EQ(e.doc_id, 0);
    ASSERT_EQ(e.count, 10);
}

TEST(Entry, EqualOperator) {
    ASSERT_EQ(Entry(0, 10), Entry(0, 10));
    ASSERT_NE(Entry(0, 10), Entry(1, 10));
    ASSERT_NE(Entry(0, 10), Entry(0, 11));
}

TEST(InvertedIndex, UpdateDocumentBase) {
    InvertedIndex ii;
    ASSERT_TRUE(ii._freq_dictionary.empty());
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"world", 20}});
    ASSERT_FALSE(ii._freq_dictionary.empty());
    ASSERT_EQ(ii._freq_dictionary["hello"].size(), 1);
    ASSERT_EQ(ii._freq_dictionary["hello"][0].doc_id, 0);
    ASSERT_EQ(ii._freq_dictionary["hello"][0].count, 10);
    ASSERT_EQ(ii._freq_dictionary["world"].size(), 1);
    ASSERT_EQ(ii._freq_dictionary["world"][0].doc_id, 0);
    ASSERT_EQ(ii._freq_dictionary["world"][0].count, 20);
}

TEST(InvertedIndex, GetWordCount) {
    InvertedIndex ii;
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"world", 20}});
    ASSERT_EQ(ii.GetWordCount("hello").size(), 1);
    ASSERT_EQ(ii.GetWordCount("hello")[0], Entry(0, 10));
    ASSERT_EQ(ii.GetWordCount("world").size(), 1);
    ASSERT_EQ(ii.GetWordCount("world")[0], Entry(0, 20));
}

TEST(InvertedIndex, GetDocWords) {
    InvertedIndex ii;
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"world", 20}});
    ASSERT_EQ(ii.GetDocWords(0).size(), 2);
    ASSERT_EQ(ii.GetDocWords(0).at("hello"), 10);
    ASSERT_EQ(ii.GetDocWords(0).at("world"), 20);
}

TEST(InvertedIndex, Override) {
    InvertedIndex ii;
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"world", 20}});
    ii.UpdateDocumentBase(0, {{"hello", 1}, {"world", 2}});
    ASSERT_EQ(ii.GetDocWords(0).size(), 2);
    ASSERT_EQ(ii.GetDocWords(0).at("hello"), 1);
    ASSERT_EQ(ii.GetDocWords(0).at("world"), 2);
}
