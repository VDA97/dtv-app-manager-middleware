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

# --- First Target 1: Unit Tests ---
add_executable(app_manager_test 
    ${LIB_SOURCES} 
    tests/TestMain.cpp
    tests/ApplicationTest.cpp
    tests/AppManagerTest.cpp
)

target_link_libraries(app_manager_test 
    PRIVATE 
        nlohmann_json::nlohmann_json
        GTest::gtest
        spdlog::spdlog
)

target_include_directories(app_manager_test PRIVATE include)

# --- Target 2: Application ---
add_executable(app_manager 
    ${LIB_SOURCES}
    apps/main.cpp
)

target_link_libraries(app_manager 
    PRIVATE 
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)
target_include_directories(app_manager PRIVATE include)