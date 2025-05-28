#ifndef INCLUDE_SEARCH_SERVER_H
#define INCLUDE_SEARCH_SERVER_H

#include "answers.h"
#include "inverted_index.h"

class SearchServer {
   public:
    SearchServer(const InvertedIndex& ii);
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queries_input,
                                                   size_t max_responses);
    std::vector<RelativeIndex> SearchOne(const std::string& request, size_t max_responses);
   private:
    const InvertedIndex& _ii;
};

#endif  // INCLUDE_SEARCH_SERVER_H
