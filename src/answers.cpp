#include "answers.h"

#include <cstring>

void to_json(nlohmann::json& j, const RelevanceFile& f) {
    j = nlohmann::json{{"docid", f.docid}, {"rank", f.rank}};
}

void to_json(nlohmann::json& j, const Answer& a) {
    j = nlohmann::json{{"result", a.result}};
    if (a.result) {
        j["relevance"] = nlohmann::json(a.relevance);
    }
}

void to_json(nlohmann::json& j, const Answers& a) {
    for (size_t i = 0; i < a.answers.size(); ++i) {
        char buf[32];
        sprintf(buf, "request%03zu", i);
        j["answers"][buf] = a.answers[i];
    }
}
