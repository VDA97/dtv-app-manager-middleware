#include "Application.hpp"
#include <memory>
#include <vector>
#include <string>

class ApplicationManager
{
public:
    void create_app_list(const std::string &app_list);
    bool remove_app(int id);
    std::shared_ptr<BaseApp> find_app(int id);
    size_t get_app_count() const;

private:
    void create_or_update_app(const AppInfo &new_info);
    std::vector<std::shared_ptr<BaseApp>> m_app_list;
};