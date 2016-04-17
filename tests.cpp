#include <stdexcept>

#include "gtest/gtest.h"

#include "process.hpp"
#include "utilities.hpp"

TEST(GetLineFromFile, SimpleTest)
{
    auto cmd = get_line_from_file("/proc/2264/cmdline");
    cmd = replace_null(cmd);
    EXPECT_EQ(cmd, "/bin/bash");
}

TEST(GetLineFromFile, MissingFile)
{
    ASSERT_THROW(get_line_from_file("/proc/2264/frfrr"), std::invalid_argument);
}

TEST(GetLineFromFile, ZeroFile)
{
    auto s = get_line_from_file("foo");
    EXPECT_EQ(s.size(), 0);
}

TEST(GetLineStartingWith, NoStringFound)
{
    EXPECT_THROW(get_line_starting_with("/proc/2264/stat", "Uid"),
            std::runtime_error);
}

TEST(GetLineStartingWith, MissingFile)
{
    EXPECT_THROW(get_line_starting_with("fjrjr", "frfr"),
            std::invalid_argument);
}

TEST(GetLineStartingWith, FindsString)
{
    auto s = get_line_starting_with("/proc/2264/status", "Uid");
    EXPECT_NE(s.size(), 0);
    EXPECT_FALSE(s.empty());
}

TEST(ProcessStruct, NewProcessIsEmpty)
{
    Process p;
    EXPECT_TRUE(p.cmdline.empty());
    EXPECT_TRUE(p.wchan.empty());
}

TEST(ProcessStruct, SetValues)
{
    Process p;
    p.cmdline = "fluhbluh";
    EXPECT_EQ(p.cmdline, "fluhbluh");
}

TEST(ProcessStruct, CreateProcessFromPath)
{
    auto process = create_process_data("/proc/2264");
    EXPECT_FALSE(process.cmdline.empty());
}

TEST(ProcessStruct, ProcessJsonNonEmpty)
{
    auto process = create_process_data("/proc/2264");
    auto json = get_process_json(process);
    EXPECT_FALSE(json.empty());
}

TEST(MiscTests, CheckPID)
{
    std::string s {"/proc/2222"};
    auto pid = s.substr(s.rfind('/') + 1);
    int n = std::atoi(pid.c_str());
    EXPECT_NE(n, 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
