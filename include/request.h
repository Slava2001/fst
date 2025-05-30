#ifndef INCLUDE_REQUEST_H
#define INCLUDE_REQUEST_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

/**
 * @brief This structure represents a requests.
 */
struct Request {
    std::vector<std::string> requests;

    /**
     * @brief Loads a request from a JSON file.
     * @param path The path to the JSON file.
     * @return A Request object populated with the requests from the file.
     */
    static Request LoadFile(const char* path);
};

/**
 * @brief Parses a JSON to Request object.
 * @param j The JSON object to parse.
 * @param c The Config object to populate.
 */
void from_json(const nlohmann::json& j, Request& c);

#endif  // INCLUDE_REQUEST_H
