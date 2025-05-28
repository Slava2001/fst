#include "answers.h"

#include <cstring>
#include <fstream>
#include <stdexcept>

RelativeIndex::RelativeIndex(DocId docid_, float rank_) : docid(docid_), rank(rank_) {}

void to_json(nlohmann::json& j, const RelativeIndex& f) {
    j = nlohmann::json{{"docid", f.docid}, {"rank", f.rank}};
}

Answer::Answer(bool result_, std::vector<RelativeIndex> relevance_)
    : result(result_), relevance(std::move(relevance_)) {}

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

void Answers::SaveFile(const char* path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open answers file: " + std::string(path));
    }
    nlohmann::json j = *this;
    file << j.dump(4);
    file.close();
}
