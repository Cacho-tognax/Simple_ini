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
    ASSERT_THROW(testing.read_line(99, "not present"), std::invalid_argument);
    ASSERT_THROW(testing.read_line(99), std::out_of_range);
    ASSERT_EQ(testing.read_line("DOG", ""), "DOG = 1");
    ASSERT_EQ(testing.read_line("Pi", "section head with entries"), "Pi = 3.14");
    ASSERT_THROW(testing.read_line("not present", "not present"), std::invalid_argument);
    ASSERT_THROW(testing.read_line("not present"), std::invalid_argument);
    ASSERT_EQ(testing.read_any_line(5), "Pi = 3.14");
    ASSERT_EQ(testing.read_any_line(3), "G = \"ok\"");
    ASSERT_THROW(testing.read_any_line(99), std::out_of_range);
    ASSERT_EQ(testing.read_any_line("an added entry"), "an added entry = 1");
    ASSERT_EQ(testing.read_any_line("CAT"), "CAT = TRUE");
    ASSERT_THROW(testing.read_any_line("not present"), std::invalid_argument);
}

TEST_F(Testing_manager, Get_entry_and_lenght_test){

    ASSERT_EQ(testing.get_line(2, ""), Ini_entry("F = 1.1"));
    ASSERT_EQ(testing.get_line(2), Ini_entry("F = 1.1"));
    ASSERT_EQ(testing.get_line(1, "section head with entries"), Ini_entry("Internet = \"cats\""));
    ASSERT_THROW(testing.get_line(99, "not present"), std::invalid_argument);
    ASSERT_THROW(testing.get_line(99), std::out_of_range);
    ASSERT_EQ(testing.get_line("DOG", ""), Ini_entry("DOG = 1"));
    ASSERT_EQ(testing.get_line("DOG"), Ini_entry("DOG = 1"));
    ASSERT_EQ(testing.get_line("Pi", "section head with entries"), Ini_entry("Pi = 3.14"));
    ASSERT_THROW(testing.get_line("not present", "not present"), std::invalid_argument);
    ASSERT_THROW(testing.get_line("not present"), std::invalid_argument);
    ASSERT_EQ(testing.get_any_line(5), Ini_entry("Pi = 3.14"));
    ASSERT_EQ(testing.get_any_line(3), Ini_entry("G = \"ok\""));
    ASSERT_THROW(testing.get_any_line(99), std::out_of_range);
    ASSERT_EQ(testing.get_any_line("an added entry"), Ini_entry("an added entry = 1"));
    ASSERT_EQ(testing.get_any_line("CAT"), Ini_entry("CAT = TRUE"));
    ASSERT_THROW(testing.get_any_line("not present"), std::invalid_argument);
    ASSERT_EQ(testing.get_length(), 3);
}

TEST_F(Testing_manager, Set_test){
    testing.set_line(0, "FALSE");
    testing.set_line(1, "3", "");
    ASSERT_THROW(testing.set_line(2, "3"), std::invalid_argument);
    ASSERT_THROW(testing.set_line(99, "not present"), std::out_of_range);
    testing.set_line("G", "\"not ok\"");
    ASSERT_THROW(testing.set_line("unsectioned comment", "not possible to set", ""), std::invalid_argument);
    ASSERT_THROW(testing.set_line("not present", "7"), std::invalid_argument);
    testing.set_any_line(7, "41");
    ASSERT_THROW(testing.set_any_line(6, "not a string"), std::invalid_argument);
    ASSERT_THROW(testing.set_any_line(99, "not present"), std::out_of_range);
    testing.set_any_line("Pi", "3.141");
    ASSERT_THROW(testing.set_any_line("CAT", "not a bool"), std::invalid_argument);
    ASSERT_THROW(testing.set_any_line("not present", "cam't"), std::invalid_argument);
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

TEST_F(Testing_manager, Save_test){
    testing.set_line(0, "FALSE");
    testing.save_as("Saving test file.ini");
    testing.close_file();
    testing.open_file("Saving test file.ini");
    testing.add_line("another added entry = 2 ", "added section");
    testing.save();
    testing.close_file();
    testing.open_file("Saving test file.ini");
    std::string testini=
            "CAT = FALSE\n"
                    "DOG = 1\n"
                    "F = 1.1\n"
                    "G = \"ok\"\n"
                    "!unsectioned comment\n"
                    "[section head with entries]\n"
                    "Pi = 3.14\n"
                    "Internet = \"cats\"\n"
                    "[added section]\n"
                    "an added entry = 1\n"
                    "another added entry = 2\n";
    ASSERT_EQ(testing.read(), testini);
}

TEST_F(Testing_manager, Remove_section_test){
    testing.remove_section(0);
    testing.remove_section("added section");
    ASSERT_THROW(testing.remove_section(42), std::out_of_range);
    ASSERT_THROW(testing.remove_section(" a non present section"), std::invalid_argument);
    std::string testini=
            "[section head with entries]\n"
                    "Pi = 3.14\n"
                    "Internet = \"cats\"\n";
    ASSERT_EQ(testing.read(), testini);
}

TEST_F(Testing_manager, Add_section_test){
    Ini_section new_section("new section");
    new_section.add_line("!a comment will do");
    testing.add_section("defined here");
    testing.add_section(new_section, 1);
    ASSERT_THROW(testing.add_section("defied here again", 42), std::out_of_range);
    ASSERT_THROW(testing.add_section(new_section, 42), std::out_of_range);
    std::string testini=
            "CAT = TRUE\n"
                    "DOG = 1\n"
                    "F = 1.1\n"
                    "G = \"ok\"\n"
                    "!unsectioned comment\n"
                    "[section head with entries]\n"
                    "Pi = 3.14\n"
                    "Internet = \"cats\"\n"
                    "[new section]\n"
                    "!a comment will do\n"
                    "[added section]\n"
                    "an added entry = 1\n"
                    "[defined here]\n";
    ASSERT_EQ(testing.read(), testini);
}

TEST_F(Testing_manager, Get_section_test){
    Ini_section first("section head with entries");
    first.add_line("Pi = 3.14");
    first.add_line("Internet = \"cats\"");
    Ini_section second("added section");
    second.add_line("an added entry = 1");
    ASSERT_EQ(first, testing.get_section(0));
    ASSERT_EQ(second, testing.get_section(1));
    ASSERT_EQ(first, testing.get_section("section head with entries"));
    ASSERT_EQ(second, testing.get_section("added section"));
    ASSERT_THROW(testing.get_section(7), std::out_of_range);
    ASSERT_THROW(testing.get_section("not actualy here"), std::invalid_argument);
}

TEST_F(Testing_manager, Remove_entry_test){
    testing.remove_line(4, "");
    ASSERT_THROW(testing.remove_line(9), std::out_of_range);
    ASSERT_THROW(testing.remove_line(9, "asd"), std::invalid_argument);
    testing.remove_line(0, "added section");
    testing.remove_line("Pi", "section head with entries");
    ASSERT_THROW(testing.remove_line("Pi", "asd"), std::invalid_argument);
    ASSERT_THROW(testing.remove_line("Pi"), std::invalid_argument);
    testing.remove_any_line(4);
    testing.remove_any_line("F");
    ASSERT_THROW(testing.remove_any_line(99), std::out_of_range);
    ASSERT_THROW(testing.remove_any_line("not present"), std::invalid_argument);
    std::string testini=
            "CAT = TRUE\n"
                    "DOG = 1\n"
                    "G = \"ok\"\n"
                    "[section head with entries]\n"
                    "[added section]\n";
    ASSERT_EQ(testing.read(), testini);
}

TEST_F(Testing_manager, Add_entry_test){
    testing.add_line("!here's one");
    testing.add_line("at the beginning = TRUE", 0);
    testing.add_line("now in a section = 1", "added section");
    ASSERT_THROW(testing.add_line("invalid"), std::invalid_argument);
    ASSERT_THROW(testing.add_line("invalid", 0), std::invalid_argument);
    ASSERT_THROW(testing.add_line("!won't be added", 99), std::out_of_range);
    testing.add_line(comment, "plot twist", "", 1, "section head with entries");
    testing.add_line(string_entry, "last", "\"one\"");
    ASSERT_THROW(testing.add_line(int_entry, "invalid", "cat"), std::invalid_argument);
    ASSERT_THROW(testing.add_line(int_entry, "invalid", "cat", 2), std::invalid_argument);
    ASSERT_THROW(testing.add_line(comment, "not ok", "", 99), std::out_of_range);
    std::string testini=
            "at the beginning = TRUE\n"
            "CAT = TRUE\n"
                    "DOG = 1\n"
                    "F = 1.1\n"
                    "G = \"ok\"\n"
                    "!unsectioned comment\n"
                    "!here's one\n"
                    "last = \"one\"\n"
                    "[section head with entries]\n"
                    "Pi = 3.14\n"
                    "!plot twist\n"
                    "Internet = \"cats\"\n"
                    "[added section]\n"
                    "an added entry = 1\n"
                    "now in a section = 1\n";
    ASSERT_EQ(testing.read(), testini);
}