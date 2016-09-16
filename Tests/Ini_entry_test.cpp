//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_entry.h"

TEST(Ini_entry, Constructor_test) {
    Ini_entry tmp("!exclamation mark");
    ASSERT_EQ(tmp.get_type(), comment);
    ASSERT_EQ(tmp.get_name(), "exclamation mark");
    ASSERT_EQ(tmp.get_value(), "");
    Ini_entry tmp2(bool_entry, "CAT", "FALSE");
    ASSERT_EQ(tmp2.get_type(), bool_entry);
    ASSERT_EQ(tmp2.get_name(), "CAT");
    ASSERT_EQ(tmp2.get_value(), "FALSE");
    Ini_entry tmp3("DOG  =  7");
    ASSERT_EQ(tmp3.get_type(), int_entry);
    ASSERT_EQ(tmp3.get_name(), "DOG");
    ASSERT_EQ(tmp3.get_value(), "7");
    Ini_entry tmp4("Pi  =3.14");
    ASSERT_EQ(tmp4.get_type(), float_entry);
    ASSERT_EQ(tmp4.get_name(), "Pi");
    ASSERT_EQ(tmp4.get_value(), "3.14");
    Ini_entry tmp5("ANSWER=  \"42\"");
    ASSERT_EQ(tmp5.get_type(), string_entry);
    ASSERT_EQ(tmp5.get_name(), "ANSWER");
    ASSERT_EQ(tmp5.get_value(), "42");
    ASSERT_THROW(new Ini_entry("Not an entry"), std::invalid_argument);
    ASSERT_THROW(new Ini_entry("[section head]"), std::invalid_argument);
    ASSERT_THROW(new Ini_entry("Typo = \" no closing quotes"), std::invalid_argument);
    ASSERT_THROW(tmp5.set("Not an entry"), std::invalid_argument);
    ASSERT_THROW(tmp5.set(bool_entry, "Name", "wrong value"), std::invalid_argument);

}

TEST(In_entry, methds_test) {
    Ini_entry tmp("false=TRUE");
    tmp.set_name("a new name");
    ASSERT_EQ(tmp.get_type(), bool_entry);
    ASSERT_EQ(tmp.get_name(), "a new name");
    ASSERT_EQ(tmp.get_value(), "TRUE");
    ASSERT_THROW(tmp.set_value("this should be ignored"), std::invalid_argument);
    ASSERT_EQ(tmp.get_value(), "TRUE");
    tmp.set_value("FALSE");
    ASSERT_EQ(tmp.get_value(), "FALSE");
    ASSERT_THROW(tmp.change_type(int_entry, "again this should be ignored"), std::invalid_argument);
    ASSERT_EQ(tmp.get_value(), "FALSE");
    tmp.change_type(int_entry, "7");
    ASSERT_EQ(tmp.get_type(), int_entry);
    ASSERT_EQ(tmp.get_value(), "7");
}

TEST(In_entry, Identity_operator_test) {
    Ini_entry tmp("false=TRUE");
    Ini_entry copy(tmp);
    ASSERT_EQ(tmp, copy);
    tmp.change_type(int_entry, "7");
    ASSERT_EQ(!(tmp==copy), true);
    copy.change_type(int_entry, "7");
    ASSERT_EQ(tmp, copy);
}