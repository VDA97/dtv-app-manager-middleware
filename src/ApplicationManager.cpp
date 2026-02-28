#include "ApplicationManager.hpp"
#include <algorithm>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::shared_ptr<BaseApp> ApplicationManager::find_app(int id) {
    auto it = std::find_if(m_app_list.begin(), m_app_list.end(),
                      [id](const std::shared_ptr<BaseApp>& app)
                      {
                          return app->getId() == id;
                      });
    return (it != m_app_list.end()) ? *it : nullptr;
}

void ApplicationManager::create_app_list(const std::string &app_list_str)
{
    try
    {
        auto j_list = json::parse(app_list_str);

        if (!j_list.is_array())
        {
            throw std::runtime_error("JSON is not an array");
        }

        for (const auto &item : j_list)
        {
            try
            {
                if (!item.contains("id") || !item.contains("name"))
                {
                    spdlog::warn("Skipping app: Missing mandatory fields.");
                    continue;
                }

                AppInfo info;
                info.id = item.at("id");
                info.name = item.at("name");
                info.full_path = item.value("path", "/default/path"); // default/path is just a fallbackValue
                info.control_code = static_cast<CONTROL_CODE>(item.at("controlCode"));
                info.engine = static_cast<ENGINE_TYPE>(item.at("engineType"));
                info.type = static_cast<APP_TYPE>(item.at("appType"));
                info.state = APP_STATE::STOPPED;

                create_or_update_app(info);
            }
            catch (const std::exception &e)
            {
                spdlog::error("[Error] Failed to process app item: {} ", e.what());
            }
        }
    }
    catch (json::parse_error &e)
    {
        spdlog::error("Error processing JSON: {}", e.what());
    }
    catch (const std::exception &e)
    {
        spdlog::error("General Exception: {}", e.what());
    }
}

void ApplicationManager::create_or_update_app(const AppInfo &new_info)
{
    auto existing_app = find_app(new_info.id);

    if (existing_app)
    {
        existing_app->update_app(new_info);
        spdlog::info("[Manager] App ID: {} updated !", new_info.id);
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
        spdlog::info("[Manager] New App ID: {} created and added !", new_info.id);
    }
}

bool ApplicationManager::remove_app(int id)
{
    auto it = std::find_if(m_app_list.begin(), m_app_list.end(),
                           [id](const std::shared_ptr<BaseApp> &app)
                           {
                               return app->getId() == id;
                           });

    if (it != m_app_list.end())
    {
        m_app_list.erase(it);
        return true;
    }

    return false;
}

size_t ApplicationManager::get_app_count() const 
{
    return m_app_list.size();
}
