#ifndef INCLUDE_REQUEST_H
#define INCLUDE_REQUEST_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Request {
    std::vector<std::string> requests;

    static Request LoadFile(const char* path);
};
void from_json(const nlohmann::json& j, Request& c);

#endif // INCLUDE_REQUEST_H
