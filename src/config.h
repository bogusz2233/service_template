#pragma once

#include <cstdint>
#include <string>

namespace config {

/// @brief Application version
inline constexpr struct VersionT {
    uint8_t major = VERSION_MAJOR;
    uint8_t minor = VERSION_MINOR;
    uint8_t patch = VERSION_PATCH;
} Version;

/// @brief Application name
inline constexpr char ApplicationName[] = "service_template";

struct Config {
    int interval;
    bool run_as_service; ///< Run as service
};

/// @brief Get the application directory
std::string AppDirectory();

/// @brief Parse the command line arguments
void ParseArguments(int argc, const char **argv);

/// @brief Get the application configuration
const Config &AppConfig();

} // namespace config
