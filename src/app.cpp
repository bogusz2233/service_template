#include "app.h"

#include "config.h"
#include "spdlog/spdlog.h"

#include <atomic>
#include <chrono>
#include <thread>

namespace {
std::atomic<bool> running = true;
}

namespace app {

void ApplicationMain() {
    const config::Config &app_config = config::AppConfig();

    while (running) {
        SPDLOG_INFO("Hello world");
        std::this_thread::sleep_for(std::chrono::milliseconds(app_config.interval));
    }
}

void Running(bool state) {
    running = state;
}

} // namespace app
