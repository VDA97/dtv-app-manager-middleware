#include "ApplicationManager.hpp"
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

int main()
{
    // 1. Configure Log Pattern
    // [%H:%M:%S.%e] -> Timestamp | [%^%l%$] -> Log Level with colors | %v -> Message
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
    spdlog::info("Starting DTV App Manager Middleware...");

    ApplicationManager manager;

    // 2. Simulate JSON reading (In a real scenario, this would come from a .json file)
    std::string mock_json = R"([
        {"id": 1, "name": "App Test 1", "path": "/apps/test1", "controlCode": 1, "engineType": 2, "appType": 1},
        {"id": 2, "name": "App Test 2", "path": "/apps/test2", "controlCode": 2, "engineType": 2, "appType": 2},
        {"id": 3, "name": "Invalid App", "engineType": 1} 
    ])";

    spdlog::info("Loading application list...");
    manager.create_app_list(mock_json);

    spdlog::info("Total apps loaded: {}", manager.get_app_count());

    // 3. Simulate search and update operation
    auto app = manager.find_app(1);
    if (app)
    {
        spdlog::info("App found: {} | Current State: {}", app->getName(), app->getState());

        app->set_state(APP_STATE::RUNNING);

        spdlog::info("New state for app {}: {}", app->getName(), app->getState());
    }

    spdlog::info("Middleware shut down successfully.");
    return 0;
}