//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_ENTRY_H
#define SIMPLE_INI_INI_ENTRY_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>


enum entry_type { comment, section_head, bool_entry, int_entry,
               float_entry, string_entry, to_ignore};                                 /* section heads are actually
                                                                                       * managed in a different way than
                                                                                       * the other entries, see
                                                                                       * Ini_manager constructor
                                                                                       */

class Ini_entry {
public:
    Ini_entry(enum entry_type ty, std::string name, std::string value) throw(std::invalid_argument);

    Ini_entry(std::string entry) throw(std::invalid_argument);

    void set(std::string entry) throw(std::invalid_argument);

    void set(enum entry_type ty, std::string name, std::string value) throw(std::invalid_argument);

    std::string read() const;
    static enum entry_type identify(std::string entry, std::vector<std::string>& parts);
    static enum entry_type identify(std::string entry);

    bool operator ==(const Ini_entry rhs) const{
        if(type!= rhs.get_type())
            return false;
        if(name!= rhs.get_name())
            return false;
        return !(value != rhs.get_value());  //just to make clion happy
    }


    const entry_type &get_type() const {
        return type;
    }

    void change_type(const entry_type &typ, const std::string &valu) throw(std::invalid_argument){
        if(type==comment){
#ifdef DEBUG
            std::cout << "can't change comment entry type" << std::endl;
#endif
            throw std::invalid_argument(this->read() + " = "+ valu);
        }
        std::string tmp = name + " = " + valu;
        if(identify(tmp)==typ) {
            type = typ;
            value = valu;
        } else{
#ifdef DEBUG
            std::cout << "new value type and new type are not equal" << std::endl;
#endif
            throw std::invalid_argument(tmp);
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

    void set_value(std::string valu) throw(std::invalid_argument){
        if(type!=comment) {
            std::string tmp = name + " = " + valu;
            if (identify(tmp) == type) {
                if (type==string_entry) {  // removing the ""
                    valu.erase(valu.begin());
                    valu.erase(--valu.end());
                }
                value = valu;
            } else {
#ifdef DEBUG
                std::cout << "new value type and current type are not equal" << std::endl;
#endif
                throw std::invalid_argument(tmp);
            }
        }else{
#ifdef DEBUG
            std::cout << "can't change comment value!" << std::endl;
#endif
            throw std::invalid_argument(this->read() + " = "+ valu);
        }
    }


private:
    enum entry_type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

    static void remove_spaces_to_the_right(std::string &tmp_string);
};


#endif //SIMPLE_INI_INI_ENTRY_H
