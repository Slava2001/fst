#include "config.h"

#include <fstream>

Config Config::LoadFile(const char* path) {
    std::ifstream file(path);
    return nlohmann::json::parse(file);
}

void from_json(const nlohmann::json& j, Config& c) {
    auto cfg = j.at("config");
    cfg.at("name").get_to(c.name);
    cfg.at("version").get_to(c.version);
    cfg.at("max_responses").get_to(c.max_responses);
    j.at("files").get_to(c.files);
}
