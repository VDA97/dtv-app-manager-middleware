#include "Application.hpp"

std::ostream &operator<<(std::ostream &os, CONTROL_CODE code) { return os << static_cast<int>(code); }
std::ostream &operator<<(std::ostream &os, ENGINE_TYPE engine) { return os << static_cast<int>(engine); }
std::ostream &operator<<(std::ostream &os, APP_TYPE type) { return os << static_cast<int>(type); }
std::ostream &operator<<(std::ostream &os, APP_STATE state) { return os << static_cast<int>(state); }

BaseApp::BaseApp(const AppInfo &info) : m_app_data(info) {}
const AppInfo &BaseApp::get_app_data() const { return m_app_data; }
void BaseApp::set_state(APP_STATE new_state) { m_app_data.state = new_state; }
void BaseApp::update_app(const AppInfo &new_info) { m_app_data = new_info; }

void AppTV2X::print_info()
{
    std::cout << "[TV 2.X App] Name: " << m_app_data.name
              << " | Path: " << m_app_data.full_path
              << " | Engine: " << (m_app_data.engine == ENGINE_TYPE::NCL ? "NCL" : "HTML")
              << " | id: " << m_app_data.id
              << " | Control Code : " << m_app_data.control_code
              << " | Type : " << m_app_data.type
              << " | state :" << m_app_data.state
              << std::endl;
}

void AppTV30::print_info()
{
    std::cout << "[TV 3.X App] Name: " << m_app_data.name
              << " | Path: " << m_app_data.full_path
              << " | Engine: " << (m_app_data.engine == ENGINE_TYPE::NCL ? "NCL" : "HTML")
              << " | id: " << m_app_data.id
              << " | Control Code : " << m_app_data.control_code
              << " | Type : " << m_app_data.type
              << " | state :" << m_app_data.state
              << std::endl;
}