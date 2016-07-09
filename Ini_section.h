//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_SECTION_H
#define SIMPLE_INI_INI_SECTION_H

#include <list>
#include <string>

#include "Ini_entry.h"


class Ini_section {
public:
    Ini_section(std::string name);
    ~Ini_section();
    void add_line(Ini_entry & line);
    void add_line(Ini_entry & line, int pos);
    void remove_line(int pos);
    void remove_line(std::string name);
    Ini_entry get_ine(int pos);
    Ini_entry get_ine(std::string name);
    std::string read_line(int pos);
    std::string read_line(std::string name);
    void set_line(int pos);
    void set_line(std::string name);


private:
    std::string name;
    std::list<Ini_entry*> entries;

};


#endif //SIMPLE_INI_INI_SECTION_H
