//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_ENTRY_H
#define SIMPLE_INI_INI_ENTRY_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "Invalid_entry_exception.h"


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
                if(this->value.size()<3){      //to avoid segmentation faults
                    std::string tmp= name + " = " + value;
                    throw Invalid_entry_exception(tmp);
                }
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
    static enum entry_type identify(std::string entry, std::vector<std::string>& parts);
    static enum entry_type identify(std::string entry);

    bool operator ==(const Ini_entry rhs) const{
        if(name!= rhs.get_name())
            return false;
        if(value!= rhs.get_value())
            return false;
        if(type!= rhs.get_type())
            return false;  //todo ordine megio
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
            std::cout << "can't change comment value!" << std::endl;  //todo cambialo in eccezioni
        }
    }


private:
    enum entry_type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

};


#endif //SIMPLE_INI_INI_ENTRY_H
