#include <gtest/gtest.h>
#include "ApplicationManager.hpp"

TEST(AppManagerTestSuite, CreateAndLoadAppsFromJson)
{
    ApplicationManager manager;

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

    auto app = manager.find_app(1);

    ASSERT_NE(app, nullptr);          
    EXPECT_EQ(app->getName(), "Ncl App"); 
    EXPECT_EQ(app->getId(), 1);           
}

TEST(AppManagerTestSuite, UpdateExistingApp)
{
    ApplicationManager manager;

    manager.create_app_list(R"([{"id":1,"name":"Old","path":"/","controlCode":1,"engineType":9,"appType":1}])");

    std::string update_data = R"([{"id":1,"name":"Live TV PREMIUM","path":"/sys/live","controlCode":1,"engineType":9,"appType":1}])";
    manager.create_app_list(update_data);

    auto app = manager.find_app(1);
    ASSERT_NE(app, nullptr);
    EXPECT_EQ(app->getName(), "Live TV PREMIUM");
}

TEST(AppManagerTestSuite, RemoveAppById)
{
    ApplicationManager manager;
    manager.create_app_list(R"([{"id":2,"name":"To Remove","path":"/","controlCode":1,"engineType":9,"appType":1}])");

    manager.remove_app(2);

    auto app = manager.find_app(2);
    EXPECT_EQ(app, nullptr);
}

TEST(AppManagerTestSuite, HandleMalformedJson)
{
    ApplicationManager manager;

    std::string bad_json = R"({ "id": 1, "name": "Broken" )";

    EXPECT_NO_THROW(manager.create_app_list(bad_json));

    EXPECT_EQ(manager.get_app_count(), 0);
}

TEST(AppManagerTestSuite, RemoveNonExistentId)
{
    ApplicationManager manager;
    manager.create_app_list(R"([{"id":1,"name":"App1","path":"/","controlCode":1,"engineType":9,"appType":1}])");

    // Try to remove false id
    bool result = manager.remove_app(999);

    EXPECT_FALSE(result);                  
    EXPECT_EQ(manager.get_app_count(), 1);
}

