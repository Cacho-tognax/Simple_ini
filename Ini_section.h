//
// Created by stefano lavori on 09/07/2016.
//

#ifndef SIMPLE_INI_INI_SECTION_H
#define SIMPLE_INI_INI_SECTION_H

#include <list>
#include <string>
#include <iostream>

#include "Ini_entry.h"

const int entries_end=-1;   //just a random number, recognized by search:
                             //it wil give the pointer entries.end() without error messages

class Ini_section {
public:
    Ini_section(std::string name);
    Ini_section(const Ini_section &source);
    virtual ~Ini_section();

    bool operator==(const Ini_section &lhs)const;

    bool exists(std::string name);

    void add_line(const Ini_entry & entry, int pos=entries_end) throw(std::out_of_range);
    void add_line(enum entry_type ty, std::string name,
                  std::string value, int pos=entries_end) throw(std::invalid_argument, std::out_of_range);
    void add_line(const std::string &line,
                  int pos=entries_end) throw(std::invalid_argument, std::out_of_range);
    void remove_line(int pos) throw(std::out_of_range);
    void remove_line(std::string name) throw(std::invalid_argument);
    Ini_entry get_line(int pos)const throw(std::out_of_range);
    Ini_entry get_line(std::string name)const throw(std::invalid_argument);
    std::string read()const;
    std::string read_line(int pos)const throw(std::out_of_range);
    std::string read_line(std::string name)const throw(std::invalid_argument);
    void set_line(int pos, std::string value) throw(std::invalid_argument, std::out_of_range);
    void set_line(std::string name, std::string value) throw(std::invalid_argument);
    void set_line_type(int pos, enum entry_type typ, std::string value) throw(std::invalid_argument, std::out_of_range);
    void set_line_type(std::string name, enum entry_type typ, std::string value) throw(std::invalid_argument);

    unsigned long int get_length()const;
    std::string get_name()const;


private:

    Ini_section operator =(const Ini_section &rhs){
        return Ini_section("you shouldn't be seeing this");
    }
    Ini_section operator =(const Ini_section &&rhs){
        return Ini_section("you shouldn't be seeing this");
    }

    std::list<Ini_entry*>::const_iterator search(int pos)const throw(std::out_of_range);
    std::list<Ini_entry*>::const_iterator search(std::string name)const throw(std::invalid_argument);     /* wrapping frequently used code in functions
                                                                   * both return entries.end() if not found
                                                                   */
    std::string name;
    std::list<Ini_entry*> entries;

};


#endif //SIMPLE_INI_INI_SECTION_H
