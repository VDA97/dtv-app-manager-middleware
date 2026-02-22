#include "ApplicationManager.hpp"
#include <iostream>
#include <string>

int main()
{
    ApplicationManager manager;

    // Cenário 1: Simulando uma string JSON vindo da API
    std::cout << "--- Step 1: Loading Apps from JSON string ---" << std::endl;
    std::string json_data = R"(
    [
        {
            "id": 1,
            "name": "Ncl App",
            "path": "/home/main.ncl",
            "controlCode": 1,
            "engineType": 9,
            "appType": 1
        },
        {
            "id": 2,
            "name": "HTML App",
            "path": "/home/index.html",
            "controlCode": 2,
            "engineType": 11,
            "appType": 2
        }
    ]
    )";

    manager.create_app_list(json_data);

    std::cout << "\n--- Step 2: Testing Update (Same ID, New Name) ---" << std::endl;
    std::string update_data = R"(
    [
        {
            "id": 1,
            "name": "Live TV PREMIUM",
            "path": "/sys/live",
            "controlCode": 1,
            "engineType": 9,
            "appType": 1
        }
    ]
    )";
    manager.create_app_list(update_data);

    std::cout << "\n--- Step 3: Removing App ID 2 ---" << std::endl;
    manager.remove_app(2);

    return 0;
}