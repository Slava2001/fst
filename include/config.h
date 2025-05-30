#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

/**
 * @brief This structure holds the configuration for the application.
 */
struct Config {
    std::string name;
    std::string version;
    std::size_t max_responses;
    std::vector<std::string> files;

    /**
     * @brief Loads the configuration from a JSON file.
     * @param path The path to the JSON file.
     * @return A Config object populated with the data from the file.
     */
    static Config LoadFile(const char* path);
};

/**
 * @brief Parses a JSON to Config object.
 * @param j The JSON object to parse.
 * @param c The Config object to populate.
 */
void from_json(const nlohmann::json& j, Config& c);

#endif  // #INCLUDE_CONFIG_H
