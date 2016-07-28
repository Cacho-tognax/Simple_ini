//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_manager.h"


class Testing_manager : public ::testing::Test {
protected:
    virtual void SetUp(){
        testing.open_file("Test.ini");
    }
    virtual void TearDown(){
        testing.close_file();
    }

    Ini_manager testing;
};

TEST_F(Testing_manager, Open_test) {
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

TEST_F(Testing_manager, Save_test){
    testing.save_as("Saving test file.ini");
    testing.close_file();
    testing.open_file("Saving test file.ini");
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