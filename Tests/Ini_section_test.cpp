//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_section.h"

TEST(Ini_section_test, Test_constructor) {
    Ini_section testing("Under_test");
    ASSERT_EQ(testing.get_lenght(), 0);
    ASSERT_EQ(testing.get_name(), "Under_test");
}
TEST(Ini_section_test, Test_add){
    Ini_section testing("Under_test");
    Ini_entry string("!string");
    testing.add_line("!string");
    Ini_entry definition(bool_entry, "Definition", "TRUE");
    testing.add_line(bool_entry, "Definition", "TRUE");
    Ini_entry entry("Answer=42");
    testing.add_line(entry, 1);

    ASSERT_EQ(testing.get_ine(0), string);
    ASSERT_EQ(testing.get_ine(1), entry);
    ASSERT_EQ(testing.get_ine(2), definition);
}

TEST(Ini_section_test, Test_read) {  //TODO actualy make

}