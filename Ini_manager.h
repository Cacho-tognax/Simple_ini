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

const int end_content= -89;  //just a random number, recognized by search:
                             // it wil give the pointer content.end() without error messages

class Ini_manager {
public:
    Ini_manager();
    Ini_manager(std::string file_name);
    virtual ~Ini_manager();

    unsigned long int get_length()const;

    void open_file(std::string file_name);
    void save();
    void save_as(std::string new_file_name);   //after savig as the class will link to the new file
    void close_file();


    void add_line(const Ini_entry &entry, std::string section="");
    void add_line(const Ini_entry &entry, int pos, std::string section="");
    void add_line(const std::string &entry, std::string section="");
    void add_line(const std::string &entry, int pos, std::string section="");
    void add_line(enum entry_type ty, std::string name, std::string value, std::string section="");
    void add_line(enum entry_type ty, std::string name, std::string value, int pos, std::string section="");
    void remove_line(int pos, std::string section = "");
    void remove_line(std::string name, std::string section = "");
    void remove_any_line(int pos);
    void remove_any_line(std::string name);
    void add_section(std::string name, int pos=end_content);
    void add_section(const Ini_section &section, int pos=end_content);
    Ini_section get_section(int pos)const;
    Ini_section get_section(std::string name)const;
    void remove_section(std::string name);
    void remove_section(int pos=end_content);
    Ini_entry get_line(int pos, std::string section = "")const;
    Ini_entry get_line(std::string name, std::string section = "")const;
    Ini_entry get_any_line(int pos)const;
    Ini_entry get_any_line(std::string name)const;
    std::string read()const;
    std::string read_line(int pos, std::string section="")const;
    std::string read_line(std::string name, std::string section="")const;
    std::string read_any_line(int pos)const;
    std::string read_any_line(std::string name)const;
    void set_line(int pos, std::string value, std::string section="");
    void set_line(std::string name, std::string value, std::string section="");
    void set_any_line(int pos, std::string value);
    void set_any_line(std::string name, std::string value);


private:

    Ini_manager operator =(const Ini_manager &rhs){
        return Ini_manager("you shouldn't be seeing this");
    }
    Ini_manager operator =(const Ini_manager &&rhs){
        return Ini_manager("you shouldn't be seeing this");
    }
    Ini_manager(const Ini_manager & source){

    }

    std::list<Ini_section*>::const_iterator search(int &pos)const;       /* will return the section with that position and
                                                                    * modify pos to the relative position in the section
                                                                    */
    std::list<Ini_section*>::const_iterator search(std::string name)const; /* wrapping frequently used code in functions
                                                                      * both return an iterator to the last section
                                                                      * of the file if not found
                                                                      */

    std::list<Ini_section*>::const_iterator section_search(int pos)const;
    std::list<Ini_section*>::const_iterator section_search(std::string name)const;


    std::string file_name;
    std::ifstream i_file;
    std::ofstream o_file;
    std::list<Ini_section*> content;

};


#endif //SIMPLE_INI_INI_MANAGER_H
