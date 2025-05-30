#ifndef INCLUDE_SEARCH_SERVER_H
#define INCLUDE_SEARCH_SERVER_H

#include "answers.h"
#include "inverted_index.h"

/**
 * @brief This class is responsible for searching documents based on queries using an inverted index.
 */
class SearchServer {
   public:
    /**
     * @brief Constructs a SearchServer with the given inverted index.
     * @param ii The inverted index to use for searching.
     */
    SearchServer(const InvertedIndex& ii);

    /**
     * @brief Searches for documents based on the provided queries.
     * @param queries_input A vector of query strings to search for.
     * @param max_responses The maximum number of responses to return for each query.
     * @return A vector of vectors containing RelativeIndex objects, each representing a document ID
     * and its relevance rank for each query.
     */
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queries_input,
                                                   size_t max_responses);
    /**
     * @brief Searches for documents based on a single query.
     * @param request The query string to search for.
     * @param max_responses The maximum number of responses to return.
     * @return A vector of RelativeIndex objects, each representing a document ID and its relevance
     * rank for the query.
     */
    std::vector<RelativeIndex> SearchOne(const std::string& request, size_t max_responses);

   private:
    const InvertedIndex& _ii;
};

#endif  // INCLUDE_SEARCH_SERVER_H
