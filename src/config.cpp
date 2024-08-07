#include "config.h"

#include "CLI/CLI.hpp"
#include "spdlog/spdlog.h"

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <memory>

namespace {
config::Config app_config;
}

namespace config {

std::string AppDirectory() {
    std::string path(MAX_PATH, '\0');
    GetModuleFileNameA(NULL, path.data(), MAX_PATH);

    std::string::size_type pos = path.find_last_of("\\/");
    return path.substr(0, pos);
}

void ParseArguments(int argc, const char **argv) {
    CLI::App app{ApplicationName};

    app.add_flag("--service", app_config.run_as_service, "Run as service");
    app.add_option("--interval", app_config.interval, "Interval in miliseconds")->default_val(1000);

    const std::string default_config_file = AppDirectory() + "\\config.ini";
    app.set_config("--config")->default_val(default_config_file);

    try {
        if (std::filesystem::exists(default_config_file)) {
            std::ifstream ifs(default_config_file);
            app.parse_from_stream(ifs);
        }
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        SPDLOG_ERROR("{}: {}", typeid(e).name(), e.what());
        exit(app.exit(e));
    } catch (const std::exception &e) {
        SPDLOG_ERROR("{}: {}", typeid(e).name(), e.what());
        exit(-1);
    }
}

const Config &AppConfig() {
    return app_config;
}

} // namespace config
