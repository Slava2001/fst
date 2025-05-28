#include "request.h"

#include <fstream>
#include <stdexcept>

Request Request::LoadFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open request file: " + std::string(path));
    }
    return nlohmann::json::parse(file);
}

void from_json(const nlohmann::json& j, Request& c) {
    j.at("requests").get_to(c.requests);
}
