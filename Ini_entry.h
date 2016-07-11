//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_ENTRY_H
#define SIMPLE_INI_INI_ENTRY_H

#include <string>

#include "Invalid_entry_exception.h"

const char space=32;
const char exclamation_mark=33;
const char double_quotation_mark=34;
const char dot=46;
const char numbers_start=48;
const char numbers_end=57;
const char equal_sign=61;
const char A_letter=65;
const char E_letter=69;
const char F_letter=70;
const char L_letter=76;
const char R_letter=82;
const char S_letter=83;
const char T_letter=84;
const char U_letter=85;
const char open_square_pharentesis=91;
const char close_square_pharentesis=93;


enum entry_type { comment, section_head, bool_entry, int_entry,
               float_entry, string_entry, to_ignore};                                 /* section heads are actually
                                                                                       * managed in a different way than
                                                                                       * the other entries, see
                                                                                       * Ini_manager constructor
                                                                                       */

class Ini_entry {
public:
    Ini_entry(enum entry_type ty, std::string name, std::string value): type(ty), name(name), value(value) {
        if (type==comment){
            this->value="";
        }

    }
    Ini_entry(std::string entry) throw(Invalid_entry_exception);

    std::string read();
    static enum entry_type identify(std::string entry);


    const entry_type &getType() const {
        return type;
    }

    void setType(const entry_type &typ) {
        type = typ;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &nam) {
        name = nam;
    }

    const std::string &getValue() const {
        return value;
    }

    void setValue(const std::string &valu) {
       value = valu;
    }


private:
    enum entry_type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

};


#endif //SIMPLE_INI_INI_ENTRY_H
