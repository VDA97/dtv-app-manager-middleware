cmake_minimum_required(VERSION 3.10)
project(DTVAppManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

include_directories(include)

set(SOURCES 
    src/main.cpp 
    src/ApplicationManager.cpp
    src/Application.cpp
)

add_executable(app_manager_test ${SOURCES})

target_link_libraries(app_manager_test PRIVATE nlohmann_json::nlohmann_json)