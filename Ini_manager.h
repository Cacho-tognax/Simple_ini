//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_MANAGER_H
#define SIMPLE_INI_INI_MANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <list>

#include "Ini_section.h"

class Ini_manager {
    Ini_manager(std::string file_name);
    ~Ini_manager();
    void add_line(std::string section, std::string & line);
    void add_line(std::string section, std::string & line, int pos);
    void remove_line(std::string section, int pos);
    void remove_line(std::string section, std::string name);
    void add_section(std::string name);
    void add_section(std::string name, int pos);
    void remove_section(std::string name);
    void remove_section(int pos);
    Ini_entry get_ine(std::string section, int pos);
    Ini_entry get_ine(std::string section, std::string name);
    std::string read_line(std::string section, int pos);
    std::string read_line(std::string section, std::string name);
    void set_line(std::string section, int pos, std::string value);
    void set_line(std::string section, std::string name, std::string value);


private:
    enum type identify(std::string);
    Ini_entry convert(std::string);
    std::fstream file;
    std::list<Ini_section*> content;

};


#endif //SIMPLE_INI_INI_MANAGER_H
