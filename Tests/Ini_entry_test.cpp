//
// Created by dfg on 13/07/16.
//

#include <gtest/gtest.h>
#include "../Ini_entry.h"

TEST(Ini_entry, Constructor_test) {
    Ini_entry tmp("!exclamation mark");
    ASSERT_EQ(tmp.getType(), comment);
    ASSERT_EQ(tmp.getName(), "exclamation mark");
    ASSERT_EQ(tmp.getValue(), "");
    Ini_entry tmp2("CAT=FALSE");
    ASSERT_EQ(tmp2.getType(), bool_entry);
    ASSERT_EQ(tmp2.getName(), "CAT");
    ASSERT_EQ(tmp2.getValue(), "FALSE");
    Ini_entry tmp3("DOG  =  7");
    ASSERT_EQ(tmp3.getType(), int_entry);
    ASSERT_EQ(tmp3.getName(), "DOG");
    ASSERT_EQ(tmp3.getValue(), "7");
    Ini_entry tmp4("Pi  =3.14");
    ASSERT_EQ(tmp4.getType(), float_entry);
    ASSERT_EQ(tmp4.getName(), "Pi");
    ASSERT_EQ(tmp4.getValue(), "3.14");
    Ini_entry tmp5("ANSWER=  \"42\"");
    ASSERT_EQ(tmp5.getType(), string_entry);
    ASSERT_EQ(tmp5.getName(), "ANSWER");
    ASSERT_EQ(tmp5.getValue(), "42");
    ASSERT_THROW(new Ini_entry("Not an entry"), Invalid_entry_exception);
    ASSERT_THROW(new Ini_entry("[section head]"), Invalid_entry_exception);
    ASSERT_THROW(new Ini_entry("Typo = \" no closing quotes"), Invalid_entry_exception);

}
