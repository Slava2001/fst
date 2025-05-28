#ifndef INCLUDE_ANSWERS_H
#define INCLUDE_ANSWERS_H

#include <vector>

#include "nlohmann/json.hpp"
#include "types.h"

struct RelativeIndex {
    DocId docid;
    float rank;

    RelativeIndex(DocId docid, float rank);
};
void to_json(nlohmann::json& j, const RelativeIndex& f);

struct Answer {
    bool result;
    std::vector<RelativeIndex> relevance;

    Answer(bool result, std::vector<RelativeIndex> relevance);
};
void to_json(nlohmann::json& j, const Answer& a);

struct Answers {
    std::vector<Answer> answers;

    void SaveFile(const char* path) const;
};
void to_json(nlohmann::json& j, const Answers& a);

#endif  // INCLUDE_ANSWERS_H
