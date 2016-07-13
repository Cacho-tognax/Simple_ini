//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_manager.h"

TEST(Testing_manager, Constructor_test) {
    Ini_manager testing("Test.ini");
    std::string testini="CAT = TRUE\n"
            "!unsectioned comment\n"
            "[section head]\n"
            "Pi = 3.14\n"
            "Internet = \"cats\""
            "\n";
    ASSERT_EQ(testing.read(), testini);
}
