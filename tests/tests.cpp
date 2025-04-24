#include <gtest/gtest.h>
#include "../processing_server/ProcessingServer.h"

TEST(RemoveDuplicatesTest, BasicTest) {
    std::string input = "hello world hello again world";
    std::string expected = "hello world again";
    EXPECT_EQ(ProcessingServer::removeDuplicates(input), expected);
}

TEST(RemoveDuplicatesTest, EmptyInput) {
    EXPECT_EQ(ProcessingServer::removeDuplicates(""), "");
}

TEST(RemoveDuplicatesTest, NoDuplicates) {
    EXPECT_EQ(ProcessingServer::removeDuplicates("a b c"), "a b c");
}

TEST(RemoveDuplicatesTest, AllDuplicates) {
    EXPECT_EQ(ProcessingServer::removeDuplicates("x x x x x"), "x");
}

