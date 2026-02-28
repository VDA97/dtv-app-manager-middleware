#include "Application.hpp"

std::ostream &operator<<(std::ostream &os, CONTROL_CODE code) { return os << static_cast<int>(code); }
std::ostream &operator<<(std::ostream &os, ENGINE_TYPE engine) { return os << static_cast<int>(engine); }
std::ostream &operator<<(std::ostream &os, APP_TYPE type) { return os << static_cast<int>(type); }
std::ostream &operator<<(std::ostream &os, APP_STATE state) { return os << static_cast<int>(state); }

BaseApp::BaseApp(const AppInfo &info) : m_app_data(info) {}
int BaseApp::getId() const { return m_app_data.id; }
std::string BaseApp::getName() const { return m_app_data.name; }
std::string BaseApp::getPath() const { return m_app_data.full_path; }
APP_STATE BaseApp::getState() const { return m_app_data.state; }
APP_TYPE BaseApp::getType() const { return m_app_data.type; }
ENGINE_TYPE BaseApp::getEngine() const { return m_app_data.engine; }
CONTROL_CODE BaseApp::getControlCode() const { return m_app_data.control_code; }
void BaseApp::set_state(APP_STATE new_state) { m_app_data.state = new_state; }
void BaseApp::update_app(const AppInfo &new_info) { m_app_data = new_info; }

void AppTV2X::print_info()
{
    spdlog::info("[TV 2.X App] Name: {} | Path: {} | Engine: {} | ID: {} | Control: {} | Type: {} | State: {}",
                 m_app_data.name,
                 m_app_data.full_path,
                 (m_app_data.engine == ENGINE_TYPE::NCL ? "NCL" : "HTML"),
                 m_app_data.id,
                 m_app_data.control_code,
                 m_app_data.type,
                 m_app_data.state);
}

void AppTV30::print_info()
{
    spdlog::info("[TV 3.X App] Name: {} | Path: {} | Engine: {} | ID: {} | Control: {} | Type: {} | State: {}",
                 m_app_data.name,
                 m_app_data.full_path,
                 (m_app_data.engine == ENGINE_TYPE::NCL ? "NCL" : "HTML"),
                 m_app_data.id,
                 m_app_data.control_code,
                 m_app_data.type,
                 m_app_data.state);
}