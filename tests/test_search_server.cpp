#include <gtest/gtest.h>

#include "logger.h"
#include "search_server.h"

TEST(SearchServer, SearchOne) {
    Logger::init();
    InvertedIndex ii;
    ii.UpdateDocumentBase(0, {{"hello", 10}, {"WORLD", 20}});
    ii.UpdateDocumentBase(1, {{"hello", 15}, {"world", 25}});
    ii.UpdateDocumentBase(2, {{"HELLO", 20}, {"world", 30}});
    ii.UpdateDocumentBase(3, {{"HELLO", 20}, {"world", 30}});
    ii.UpdateDocumentBase(4, {{"HELLO", 20}, {"world", 30}});
    SearchServer server(ii);
    auto _resp = server.SearchOne("hello, world", 5);
}
