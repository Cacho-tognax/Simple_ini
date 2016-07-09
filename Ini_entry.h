//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_ENTRY_H
#define SIMPLE_INI_INI_ENTRY_H

#include <string>

enum type { comment, section_head, bool_enry, int_enry, float_entry, string_entry};

class Ini_entry {
public:
    Ini_entry(enum type ty, std::string name, std::string value):type(ty), name(name), value(value) {

    }



    const type &getType() const {
        return type;
    }

    void setType(const type &typ) {
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
    enum type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

};


#endif //SIMPLE_INI_INI_ENTRY_H
