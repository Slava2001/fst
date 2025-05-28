#ifndef INCLUDE_ANSWERS_H
#define INCLUDE_ANSWERS_H

#include <vector>

#include "nlohmann/json.hpp"
#include "types.h"

struct RelevanceFile {
    DocId docid;
    float rank;
};
void to_json(nlohmann::json& j, const RelevanceFile& f);

struct Answer {
    bool result;
    std::vector<RelevanceFile> relevance;
};
void to_json(nlohmann::json& j, const Answer& a);

struct Answers {
    std::vector<Answer> answers;
};
void to_json(nlohmann::json& j, const Answers& a);

#endif  // INCLUDE_ANSWERS_H
