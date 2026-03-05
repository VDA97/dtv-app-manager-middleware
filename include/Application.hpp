#pragma once
#include <string>
#include <ostream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

enum class CONTROL_CODE : int
{
    AUTOSTART = 0x01,
    PRESENT = 0x02,
    KILL = 0x03
};
enum class ENGINE_TYPE : int
{
    NCL = 0x09,
    HTML = 0x11
};
enum class APP_TYPE : int
{
    TV2X = 0x01,
    TV30 = 0x02
};
enum class APP_STATE : int
{
    RUNNING = 0x01,
    STOPPED = 0x02
};

std::ostream &operator<<(std::ostream &os, CONTROL_CODE code);
std::ostream &operator<<(std::ostream &os, ENGINE_TYPE engine);
std::ostream &operator<<(std::ostream &os, APP_TYPE type);
std::ostream &operator<<(std::ostream &os, APP_STATE state);

struct AppInfo
{
    std::string full_path;
    std::string name;
    CONTROL_CODE control_code;
    ENGINE_TYPE engine;
    APP_TYPE type;
    APP_STATE state;
    int id;
};

class BaseApp
{
protected:
    AppInfo m_app_data;

public:
    BaseApp(const AppInfo &info);
    virtual ~BaseApp() = default;
    virtual void print_info() = 0;

    int getId() const;
    std::string getName() const;
    std::string getPath() const;
    APP_STATE getState() const;
    APP_TYPE getType() const;
    ENGINE_TYPE getEngine() const;
    CONTROL_CODE getControlCode() const;

    void set_state(APP_STATE new_state);
    void update_app(const AppInfo &new_info);
};

class AppTV2X : public BaseApp
{
public:
    using BaseApp::BaseApp;
    void print_info() override;
};

class AppTV30 : public BaseApp
{
public:
    using BaseApp::BaseApp;
    void print_info() override;
};
