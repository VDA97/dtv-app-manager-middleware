#include "ApplicationManager.hpp"
#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::shared_ptr<BaseApp> ApplicationManager::find_app(int id) {
    auto it = std::find_if(m_app_list.begin(), m_app_list.end(),
                      [id](const std::shared_ptr<BaseApp> app)
                      {
                          return app->get_app_data().id == id;
                      });
    return (it != m_app_list.end()) ? *it : nullptr;
}

void ApplicationManager::create_app_list(const std::string &app_list_str)
{
    try
    {
        auto j_list = json::parse(app_list_str);

        for (const auto &item : j_list)
        {
            AppInfo info;
            info.id = item["id"];
            info.name = item["name"];
            info.full_path = item["path"];
            info.control_code = static_cast<CONTROL_CODE>(item["controlCode"]);
            info.engine = static_cast<ENGINE_TYPE>(item["engineType"]);
            info.type = static_cast<APP_TYPE>(item["appType"]);
            info.state = APP_STATE::STOPPED;

            create_or_update_app(info);
        }
    }
    catch (json::parse_error &e)
    {
        std::cerr << "Error processing JSON: " << e.what() << std::endl;
    }
}

void ApplicationManager::create_or_update_app(const AppInfo &new_info)
{
    auto existing_app = find_app(new_info.id);

    if (existing_app)
    {
        existing_app->update_app(new_info);
        std::cout << "[Manager] App ID " << new_info.id << " updated !" << std::endl;
    }
    else
    {
        if (new_info.type == APP_TYPE::TV2X)
        {
            m_app_list.push_back(std::make_shared<AppTV2X>(new_info));
        }
        else
        {
            m_app_list.push_back(std::make_shared<AppTV30>(new_info));
        }
        std::cout << "[Manager] New App ID " << new_info.id << " created and added !" << std::endl;
    }
}


void ApplicationManager::remove_app(int id)
{
    auto it = std::remove_if(m_app_list.begin(), m_app_list.end(),
                                [id](const std::shared_ptr<BaseApp> &app)
                                {
                                    return app->get_app_data().id == id;
                                });

    if (it != m_app_list.end())
    {
        m_app_list.erase(it, m_app_list.end());
        std::cout << "[Manager] App ID " << id << " removed!" << std::endl;
    }
    else
    {
        std::cerr << "[Error] Attempt to remove " << id << ", a non-existent app!" << std::endl;
    }
}
