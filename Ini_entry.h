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

    bool operator ==(const Ini_entry rhs) const;


    const entry_type &get_type() const {
        return type;
    }
    void change_type(const entry_type &typ, const std::string &valu) throw(std::invalid_argument);
    const std::string &get_name() const {
        return name;
    }
    void set_name(const std::string &nam) {
        name = nam;
    }
    const std::string &get_value() const {
        return value;
    }
    void set_value(std::string valu) throw(std::invalid_argument);


private:
    enum entry_type type;
    std::string name;
    std::string value;    // if type is comment or section_head, this will be an empty string

    static void remove_spaces_to_the_right(std::string &tmp_string);
};


#endif //SIMPLE_INI_INI_ENTRY_H
