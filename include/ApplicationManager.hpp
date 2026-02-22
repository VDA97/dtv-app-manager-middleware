#include "Application.hpp"
#include <memory>
#include <vector>
#include <string>


class ApplicationManager
{
public:
    void create_app_list(const std::string &app_list);
    void remove_app(int id);
private:
    std::shared_ptr<BaseApp> find_app(int id);
    void create_or_update_app(const AppInfo &new_info);
    std::vector<std::shared_ptr<BaseApp>> m_app_list;
};