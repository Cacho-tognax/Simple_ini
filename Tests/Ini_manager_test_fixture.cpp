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

TEST_F(Testing_manager, Open_and_read_test) {
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
    ASSERT_EQ(testing.read_line(2, ""), "F = 1.1");
    ASSERT_EQ(testing.read_line(1, "section head with entries"), "Internet = \"cats\"");
    ASSERT_EQ(testing.read_line(99, "not present"), "section not found");
    ASSERT_EQ(testing.read_line("DOG", ""), "DOG = 1");
    ASSERT_EQ(testing.read_line("Pi", "section head with entries"), "Pi = 3.14");
    ASSERT_EQ(testing.read_line("not present", "not present"), "section not found");
    ASSERT_EQ(testing.read_any_line(5), "Pi = 3.14");
    ASSERT_EQ(testing.read_any_line(3), "G = \"ok\"");
    ASSERT_EQ(testing.read_any_line(99), "not found");
    ASSERT_EQ(testing.read_any_line("an added entry"), "an added entry = 1");
    ASSERT_EQ(testing.read_any_line("CAT"), "CAT = TRUE");
    ASSERT_EQ(testing.read_any_line("not present"), "not found");
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

TEST_F(Testing_manager, Get_test){

    ASSERT_EQ(testing.get_line(2, ""), Ini_entry("F = 1.1"));
    ASSERT_EQ(testing.get_line(2), Ini_entry("F = 1.1"));
    ASSERT_EQ(testing.get_line(1, "section head with entries"), Ini_entry("Internet = \"cats\""));
    ASSERT_EQ(testing.get_line(99, "not present"), Ini_entry(comment, "Error: line does not exists", ""));
    ASSERT_EQ(testing.get_line("DOG", ""), Ini_entry("DOG = 1"));
    ASSERT_EQ(testing.get_line("DOG"), Ini_entry("DOG = 1"));
    ASSERT_EQ(testing.get_line("Pi", "section head with entries"), Ini_entry("Pi = 3.14"));
    ASSERT_EQ(testing.get_line("not present", "not present"), Ini_entry(comment, "Error: line does not exists", ""));
    ASSERT_EQ(testing.get_any_line(5), Ini_entry("Pi = 3.14"));
    ASSERT_EQ(testing.get_any_line(3), Ini_entry("G = \"ok\""));
    ASSERT_EQ(testing.get_any_line(99), Ini_entry(comment, "Error: line does not exists", ""));
    ASSERT_EQ(testing.get_any_line("an added entry"), Ini_entry("an added entry = 1"));
    ASSERT_EQ(testing.get_any_line("CAT"), Ini_entry("CAT = TRUE"));
    ASSERT_EQ(testing.get_any_line("not present"), Ini_entry(comment, "Error: line does not exists", ""));
}

TEST_F(Testing_manager, Set_test){
    testing.set_line(0, "FALSE");
    testing.set_line(1, "3", "");
    testing.set_line(2, "3");
    testing.set_line(99, "not present");
    testing.set_line("G", "\"not ok\"");
    testing.set_line("unsectioned comment", "not possible to set", "");
    testing.set_line("not present", "7");
    testing.set_any_line(7, "41");
    testing.set_any_line(6, "not a string");
    testing.set_any_line(99, "not present");
    testing.set_any_line("Pi", "3.141");
    testing.set_any_line("CAT", "not a bool");
    testing.set_any_line("not present", "cam't");
    testing.set_any_line("F", "3.2");
    std::string testini=
            "CAT = FALSE\n"
                    "DOG = 3\n"
                    "F = 3.2\n"
                    "G = \"not ok\"\n"
                    "!unsectioned comment\n"
                    "[section head with entries]\n"
                    "Pi = 3.141\n"
                    "Internet = \"cats\"\n"
                    "[added section]\n"
                    "an added entry = 41\n";
    ASSERT_EQ(testing.read(), testini);
}

TEST_F(Testing_manager, Remove_section_test){

}