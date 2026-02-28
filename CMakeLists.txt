cmake_minimum_required(VERSION 3.10)
project(DTVAppManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

set(LIB_SOURCES 
    src/ApplicationManager.cpp
    src/Application.cpp
)

add_executable(app_manager_test 
    ${LIB_SOURCES} 
    tests/ApplicationTest.cpp
    tests/AppManagerTest.cpp
)

target_link_libraries(app_manager_test 
    PRIVATE 
        nlohmann_json::nlohmann_json
        GTest::gtest
        GTest::gtest_main
        spdlog::spdlog
)

target_include_directories(app_manager_test PRIVATE include)