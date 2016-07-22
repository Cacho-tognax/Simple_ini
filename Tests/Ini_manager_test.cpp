//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_manager.h"

TEST(Testing_manager, Constructor_test) {
    Ini_manager testing("Test.ini");
    std::string testini=
            "CAT = TRUE\n"
                    "DOG = 1\n"
                    "F = 1.1\n"
                    "G = \"ok\"\n"
                    "!unsectioned comment\n"
                    "[section head with entries]\n"
                    "Pi = 3.14\n"
                    "Internet = \"cats\"\n"
                    "[added section]\n"
                    "an added entry = 1\n";
    ASSERT_EQ(testing.read(), testini);
}
