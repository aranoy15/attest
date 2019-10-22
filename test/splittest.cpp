#include <gtest/gtest.h>
#include <utils.h>
#include <iostream>

TEST(attestsource, splittest)
{
    std::string test = "Test message for split";
    auto split_test = utils::split(test, ' ');

    std::cout << "Message: " << test << std::endl;
    std::cout << "Count split: " << split_test.size() << std::endl;

    ASSERT_TRUE(split_test.size() == 4);
}