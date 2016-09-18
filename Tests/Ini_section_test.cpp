//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_section.h"

TEST(Ini_section_test, Test_constructor) {
    Ini_section testing("Under_test");
    ASSERT_EQ(testing.get_length(), 0);
    ASSERT_EQ(testing.get_name(), "Under_test");
}
TEST(Ini_section_test, Test_add_and_get){
    Ini_section testing("Under_test");
    Ini_entry string("!string");
    testing.add_line("!string");
    Ini_entry definition(bool_entry, "Definition", "TRUE");
    testing.add_line(bool_entry, "Definition", "TRUE");
    Ini_entry entry("Answer=42");
    testing.add_line(entry, 1);
    Ini_entry unordered_entry("0=5");
    testing.add_line(unordered_entry);
    Ini_entry ordered_definition(bool_entry, "1", "TRUE");
    testing.add_line(bool_entry, "1", "TRUE", 4);
    Ini_entry ordered_string("4=5");
    testing.add_line("4=5", 4);
    ASSERT_THROW(testing.add_line(bool_entry, "invalid", ""), std::invalid_argument);
    ASSERT_THROW(testing.add_line("invalid"), std::invalid_argument);

    Ini_entry dummy(comment, "Error: line does not exists", "");

    ASSERT_EQ(testing.get_line(0), string);
    ASSERT_EQ(testing.get_line(1), entry);
    ASSERT_EQ(testing.get_line(2), definition);
    ASSERT_EQ(testing.get_line(3), unordered_entry);
    ASSERT_EQ(testing.get_line(4), ordered_string);
    ASSERT_EQ(testing.get_line(5), ordered_definition);
    ASSERT_THROW(testing.get_line(6), std::out_of_range);

    ASSERT_EQ(testing.get_line("string"), string);
    ASSERT_EQ(testing.get_line("Definition"), definition);
    ASSERT_EQ(testing.get_line("Answer"), entry);
    ASSERT_EQ(testing.get_line("0"), unordered_entry);
    ASSERT_EQ(testing.get_line("1"), ordered_definition);
    ASSERT_EQ(testing.get_line("4"), ordered_string);
    ASSERT_THROW(testing.get_line("not exisiting"), std::invalid_argument);

}