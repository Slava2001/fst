#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

struct Config {
    std::string name;
    std::string version;
    std::size_t max_responses;
    std::vector<std::string> files;

    static Config LoadFile(const char* path);
};

void from_json(const nlohmann::json& j, Config& c);

#endif  // #INCLUDE_CONFIG_H
