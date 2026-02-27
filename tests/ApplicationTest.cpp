#include <gtest/gtest.h>
#include "Application.hpp"

class ApplicationTest : public ::testing::Test
{
protected:
    AppInfo default_info;

    void SetUp() override
    {
        default_info.id = 10;
        default_info.name = "Test App";
        default_info.full_path = "/usr/bin/test";
        default_info.control_code = CONTROL_CODE::AUTOSTART;
        default_info.engine = ENGINE_TYPE::HTML;
        default_info.type = APP_TYPE::TV2X;
        default_info.state = APP_STATE::STOPPED;
    }
};

TEST_F(ApplicationTest, InitializationAndGetters)
{
    AppTV2X app(default_info);

    EXPECT_EQ(app.getId(), 10);
    EXPECT_EQ(app.getName(), "Test App");
    EXPECT_EQ(app.getPath(), "/usr/bin/test");
    EXPECT_EQ(app.getControlCode(), CONTROL_CODE::AUTOSTART);
    EXPECT_EQ(app.getState(), APP_STATE::STOPPED);
}

TEST_F(ApplicationTest, StateTransition)
{
    AppTV2X app(default_info);

    app.set_state(APP_STATE::RUNNING);
    EXPECT_EQ(app.getState(), APP_STATE::RUNNING);
}

TEST_F(ApplicationTest, UpdateAppInfo)
{
    AppTV2X app(default_info);

    AppInfo new_info = default_info;
    new_info.name = "Updated Name";
    new_info.control_code = CONTROL_CODE::KILL;

    app.update_app(new_info);

    EXPECT_EQ(app.getName(), "Updated Name");
    EXPECT_EQ(app.getControlCode(), CONTROL_CODE::KILL);
}

TEST_F(ApplicationTest, TypeIntegrity)
{
    AppTV2X app2x(default_info);

    default_info.type = APP_TYPE::TV30;
    AppTV30 app30(default_info);

    EXPECT_EQ(app2x.getType(), APP_TYPE::TV2X);
    EXPECT_EQ(app30.getType(), APP_TYPE::TV30);
}