#ifndef INCLUDE_ANSWERS_H
#define INCLUDE_ANSWERS_H

#include <vector>

#include "nlohmann/json.hpp"
#include "types.h"

/**
 * @brief This structure is used to store the document ID and its relevance rank.
 */
struct RelativeIndex {
    DocId docid;
    float rank;

    /**
     * @brief Constructs a RelativeIndex with the given document ID and rank.
     * @param docid The document ID.
     * @param rank The relevance rank of the document.
     */
    RelativeIndex(DocId docid, float rank);
};

/**
 * @brief Converts a RelativeIndex to a JSON object.
 * @param j The JSON object to which the RelativeIndex will be converted.
 * @param f The RelativeIndex to convert.
 */
void to_json(nlohmann::json& j, const RelativeIndex& f);

/**
 * @brief This structure represents an answer to a query, including whether the query was successful
 * and the relevance of documents if it was.
 */
struct Answer {
    bool result;
    std::vector<RelativeIndex> relevance;

    /**
     * @brief Constructs an Answer with the given result and relevance.
     * @param result The result of the query (true if successful, false otherwise).
     * @param relevance A vector of RelativeIndex representing the relevance of documents.
     */
    Answer(bool result, std::vector<RelativeIndex> relevance);
};

/**
 * @brief Converts an Answer to a JSON object.
 * @param j The JSON object to which the Answer will be converted.
 * @param a The Answer to convert.
 */
void to_json(nlohmann::json& j, const Answer& a);

/**
 * @brief This structure holds a collection of answers to queries.
 */
struct Answers {
    std::vector<Answer> answers;

    /**
     * @brief Saves the answers to a file in JSON format.
     * @param path The file path where the answers will be saved.
     */
    void SaveFile(const char* path) const;
};

/**
 * @brief Converts the Answers structure to a JSON object.
 * @param j The JSON object to which the Answers will be converted.
 * @param a The Answers structure to convert.
 */
void to_json(nlohmann::json& j, const Answers& a);

#endif  // INCLUDE_ANSWERS_H
