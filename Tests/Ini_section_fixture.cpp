//
// Created by dfg on 27/07/16.
//


#include "../Ini_section.h"

#include <gtest/gtest.h>


class section_fixture_test : public ::testing::Test {
public:
    section_fixture_test():testing("under test"){

    }

protected:
    virtual void SetUp(){
        testing.add_line("!a comment");
        testing.add_line("CAT=TRUE");
        testing.add_line("DOG=7");
        testing.add_line("ANSWER=42");
        testing.add_line("NAME=\"MARVIN\"");
    }
    virtual void TearDown(){

    }

    Ini_section testing;
};

TEST_F(section_fixture_test, testing_read){
    std::string expected_line="DOG = 7";
    ASSERT_EQ(testing.read_line(2), expected_line);
    ASSERT_EQ(testing.read_line("DOG"), expected_line);
    ASSERT_THROW(testing.read_line(5), std::out_of_range);
    ASSERT_THROW(testing.read_line("not present"), std::invalid_argument);
    std::string expected="!a comment\n"
            "CAT = TRUE\n"
            "DOG = 7\n"
            "ANSWER = 42\n"
            "NAME = \"MARVIN\"\n";
    ASSERT_EQ(testing.read(), expected);
}

TEST_F(section_fixture_test, testing_remove) {
    testing.remove_line(0);
    ASSERT_THROW(testing.remove_line(4), std::out_of_range);
    testing.remove_line("DOG");
    ASSERT_THROW(testing.remove_line("DOG"), std::invalid_argument);
    ASSERT_THROW(testing.remove_line("not present"), std::invalid_argument);
    std::string expected="CAT = TRUE\n"
            "ANSWER = 42\n"
            "NAME = \"MARVIN\"\n";
    ASSERT_EQ(testing.get_length(), 3);
    ASSERT_EQ(testing.read(), expected);

}

TEST_F(section_fixture_test, testing_set) {
    ASSERT_THROW(testing.set_line(0, "FALSE"), std::invalid_argument);
    testing.set_line(1, "FALSE");
    testing.set_line("NAME", "\"NO NAME\"");
    ASSERT_THROW(testing.set_line("not present", "FALSE"), std::invalid_argument);
    ASSERT_THROW(testing.set_line(42, ""), std::out_of_range);
    testing.set_line_type(2, float_entry, "5.3");
    ASSERT_THROW(testing.set_line_type(2, float_entry, "5"), std::invalid_argument);
    testing.set_line_type("ANSWER", bool_entry, "TRUE");
    ASSERT_THROW(testing.set_line_type("ANSWER", bool_entry, "5.3"), std::invalid_argument);
    std::string expected="!a comment\n"
            "CAT = FALSE\n"
            "DOG = 5.3\n"
            "ANSWER = TRUE\n"
            "NAME = \"NO NAME\"\n";
    ASSERT_EQ(testing.read(), expected);
}

TEST_F(section_fixture_test, testing_exists){
    ASSERT_EQ(testing.exists("ANSWER"), true);
    ASSERT_EQ(testing.exists("not present"), false);

}

TEST_F(section_fixture_test, testing_copy_constructor){
    Ini_section copied(testing);
    testing.remove_line("DOG");
    testing.set_line(1, "FALSE");       //modifications to the original should not change copy
    copied.set_line_type("ANSWER", bool_entry, "TRUE");
    std::string expected="!a comment\n"
            "CAT = FALSE\n"
            "ANSWER = 42\n"
            "NAME = \"MARVIN\"\n";
    ASSERT_EQ(testing.read(), expected);  //and vice versa
    std::string copy_expected="!a comment\n"
            "CAT = TRUE\n"
            "DOG = 7\n"
            "ANSWER = TRUE\n"
            "NAME = \"MARVIN\"\n";
    ASSERT_EQ(copied.read(), copy_expected);
}

TEST_F(section_fixture_test, testing_identity_operator){
    Ini_section copy(testing);
    ASSERT_EQ(copy, testing);
    testing.remove_line(0);
    ASSERT_EQ(!(copy==testing), true);
    copy.remove_line(0);
    ASSERT_EQ(copy, testing);
}