#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
    spdlog::info("Starting DTV App Manager Unit Tests...");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}