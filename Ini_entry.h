//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_ENTRY_H
#define SIMPLE_INI_INI_ENTRY_H

#include <string>
#include <iostream>

#include "Invalid_entry_exception.h"

const char space=32;
const char exclamation_mark=33;
const char double_quotation_mark=34;
const char minus_sign=45;
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
const char open_square_parenthesis=91;
const char close_square_parenthesis=93;


enum entry_type { comment, section_head, bool_entry, int_entry,
               float_entry, string_entry, to_ignore};                                 /* section heads are actually
                                                                                       * managed in a different way than
                                                                                       * the other entries, see
                                                                                       * Ini_manager constructor
                                                                                       */

class Ini_entry {
public:
    Ini_entry(enum entry_type ty, std::string name, std::string value) throw(Invalid_entry_exception):
                                                                                type(ty), name(name), value(value) {
        if (type==comment){
            this->value="";
        } else{
            if (type==string_entry) {  // removing the ""
                this->value.erase(this->value.begin());
                this->value.erase(--this->value.end());
            }

            std::string tmp= name + " = " + value;
            if(identify(tmp)!=type){
                throw Invalid_entry_exception(tmp);
            }
        }

    }
    Ini_entry(std::string entry) throw(Invalid_entry_exception);

    void set(std::string entry) throw(Invalid_entry_exception);

    void set(enum entry_type ty, std::string name, std::string value) throw(Invalid_entry_exception);

    std::string read() const;
    static enum entry_type identify(std::string entry);

    bool operator ==(const Ini_entry rhs) const{
        if(name!= rhs.get_name())
            return false;
        if(value!= rhs.get_value())
            return false;
        if(type!= rhs.get_type())
            return false;
        return true;
    }


    const entry_type &get_type() const {
        return type;
    }

    void change_type(const entry_type &typ, const std::string &valu) {
        if(type==comment){
            std::cout << "can't change comment entry type" << std::endl;
        }
        std::string tmp = name + " = " + valu;
        if(identify(tmp)==typ) {
            type = typ;
            value = valu;
        } else{
            std::cout << "new value type and new type are not equal" << std::endl;
        }
    }

    const std::string &get_name() const {
        return name;
    }

    void set_name(const std::string &nam) {
        name = nam;
    }

    const std::string &get_value() const {
        return value;
    }

    void set_value(std::string valu) {
        if(type!=comment) {
            std::string tmp = name + " = " + valu;
            if (identify(tmp) == type) {
                if (type==string_entry) {  // removing the ""
                    valu.erase(valu.begin());
                    valu.erase(--valu.end());
                }
                value = valu;
            } else {
                std::cout << "new value type and current type are not equal" << std::endl;
            }
        }else{
            std::cout << "can't change comment value!" << std::endl;
        }
    }


private:
    enum entry_type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

};


#endif //SIMPLE_INI_INI_ENTRY_H
