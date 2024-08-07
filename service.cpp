#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "config.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

#include <app.h>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <windows.h>

/// @brief Global variable to control application lifecycle
std::atomic<bool> running = true;

SERVICE_STATUS service_status{};
SERVICE_STATUS_HANDLE g_StatusHandle = nullptr;

// Function to handle the service control requests
void WINAPI ServiceCtrlHandler(DWORD dwControl) {
    // Handle the control requests here

    switch (dwControl) {
        case SERVICE_CONTROL_STOP:
            service_status.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(g_StatusHandle, &service_status);
            app::Running(false);

            break;

        case SERVICE_CONTROL_PAUSE:
            // Handle pause request
            break;

        case SERVICE_CONTROL_CONTINUE:
            // Handle continue request
            break;

        case SERVICE_CONTROL_SHUTDOWN:
            // Handle system shutdown request
            break;

        default:
            // Handle other control requests
            break;
    }
}

void WINAPI ServiceMain(DWORD, LPTSTR *) {
    g_StatusHandle = RegisterServiceCtrlHandler(config::ApplicationName, ServiceCtrlHandler);

    if (g_StatusHandle == nullptr) {
        // Handle the error
        return;
    }

    service_status.dwServiceType      = SERVICE_WIN32_OWN_PROCESS;
    service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    service_status.dwCurrentState     = SERVICE_START_PENDING;

    SetServiceStatus(g_StatusHandle, &service_status);

    service_status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_StatusHandle, &service_status);

    SPDLOG_INFO("Service started");

    app::ApplicationMain();

    service_status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_StatusHandle, &service_status);

    SPDLOG_INFO("Service stopped");
}

// Entry point for the service
int main(int argc, const char **argv) {
    std::string directory = config::AppDirectory();
    auto rotating_sink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(directory + "\\log.txt", 1024 * 1024 * 5, 3);
    spdlog::default_logger()->sinks().push_back(rotating_sink);

    config::ParseArguments(argc, argv);
    const config::Config &app_config = config::AppConfig();

    std::string service_name = config::ApplicationName;
    if (app_config.run_as_service) {
        SERVICE_TABLE_ENTRY service_table[] = {
            {service_name.data(), ServiceMain},
            {nullptr,             nullptr    },
        };

        if (!StartServiceCtrlDispatcher(service_table)) {
            return GetLastError();
        }
    } else {
        app::ApplicationMain();
    }

    return 0;
}