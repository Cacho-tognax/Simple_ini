//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_SECTION_H
#define SIMPLE_INI_INI_SECTION_H

#include <list>
#include <string>
#include <iostream>

#include "Ini_entry.h"


class Ini_section {
public:
    Ini_section(std::string name);
    ~Ini_section();

    bool exists(int pos);                      //TODO farlo fungere!!!
    bool exists(std::string name);

    void add_line(Ini_entry & line);
    void add_line(enum entry_type ty, std::string name, std::string value);
    void add_line(std::string entry);                                    /* with no specified position it places it
                                                                          * at the end of the section
                                                                          */
    void add_line(Ini_entry & line, int pos);                            /* if pos out of bounds,
                                                                          *will ad at end of section
                                                                          */
    void add_line(enum entry_type ty, std::string name, std::string value, int pos);
    void add_line(std::string entry, int pos);
    void remove_line(int pos);
    void remove_line(std::string name);
    Ini_entry get_ine(int pos) ;
    Ini_entry get_ine(std::string name) ;
    std::string read_line(int pos) ;
    std::string read_line(std::string name) ;
    void set_line(int pos, std::string value);
    void set_line(std::string name, std::string value);

    int get_lenght();


private:

    std::list<Ini_entry*>::iterator search(int pos) ;
    std::list<Ini_entry*>::iterator search(std::string name) ;     /* wrapping frequently used code in functions
                                                                   * both return entries.end() if not found
                                                                   */
    std::string name;
    std::list<Ini_entry*> entries;

};


#endif //SIMPLE_INI_INI_SECTION_H
