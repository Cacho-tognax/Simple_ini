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
const int end_content= -1;  //just a random number, recognized by search:
                             // it wil give the pointer content.end() without error messages

class Ini_manager {
public:
    Ini_manager();
    Ini_manager(std::string file_name);
    virtual ~Ini_manager();

    unsigned long int get_length()const;
    unsigned long int get_number_of_entries()const;

    void open_file(std::string file_name) throw(std::invalid_argument);
    void save() throw(std::invalid_argument);
    void save_as(std::string new_file_name) throw(std::invalid_argument);   /* after saving as the class will link to
                                                                             * the new file
                                                                             */
    void close_file();


    void add_line(const Ini_entry &entry, std::string section="") throw(std::invalid_argument);
    void add_line(const Ini_entry &entry, int pos,
                  std::string section="") throw(std::invalid_argument, std::out_of_range);
    void add_line(const std::string &entry, std::string section="") throw(std::invalid_argument);
    void add_line(const std::string &entry, int pos,
                  std::string section="") throw(std::invalid_argument, std::out_of_range);
    void add_line(enum entry_type ty, std::string name, std::string value,
                  std::string section="") throw(std::invalid_argument);
    void add_line(enum entry_type ty, std::string name, std::string value,
                  int pos, std::string section="") throw(std::invalid_argument, std::out_of_range);
    void remove_line(int pos, std::string section = "") throw(std::invalid_argument, std::out_of_range);
    void remove_line(std::string name, std::string section = "") throw(std::invalid_argument);
    void remove_any_line(int pos) throw(std::out_of_range);
    void remove_any_line(std::string name) throw(std::invalid_argument);
    void add_section(std::string name, int pos=end_content) throw(std::out_of_range);
    void add_section(const Ini_section &section, int pos=end_content) throw(std::out_of_range);
    Ini_section get_section(int pos)const throw(std::out_of_range);
    Ini_section get_section(std::string name)const throw(std::invalid_argument);
    void remove_section(std::string name) throw(std::invalid_argument);
    void remove_section(int pos) throw(std::out_of_range);
    Ini_entry get_line(int pos, std::string section = "")const throw(std::invalid_argument, std::out_of_range);
    Ini_entry get_line(std::string name, std::string section = "")const throw(std::invalid_argument);
    Ini_entry get_any_line(int pos)const throw(std::out_of_range);
    Ini_entry get_any_line(std::string name)const throw(std::invalid_argument);
    std::string read()const;
    std::string read_line(int pos, std::string section="")const throw(std::invalid_argument, std::out_of_range);
    std::string read_line(std::string name, std::string section="")const throw(std::invalid_argument);
    std::string read_any_line(int pos)const throw(std::out_of_range);
    std::string read_any_line(std::string name)const throw(std::invalid_argument);
    void set_line(int pos, std::string value, std::string section="") throw(std::invalid_argument, std::out_of_range);
    void set_line(std::string name, std::string value, std::string section="") throw(std::invalid_argument);
    void set_any_line(int pos, std::string value) throw(std::invalid_argument, std::out_of_range);
    void set_any_line(std::string name, std::string value) throw(std::invalid_argument);


private:

    Ini_manager operator =(const Ini_manager &rhs){
        return Ini_manager("you shouldn't be seeing this");
    }
    Ini_manager operator =(const Ini_manager &&rhs){
        return Ini_manager("you shouldn't be seeing this");
    }
    Ini_manager(const Ini_manager & source){

    }

    std::list<Ini_section*>::const_iterator search(int &pos)const throw(std::out_of_range); /* will
                                                                    * return the section with that position and
                                                                    * modify pos to the relative position in the section
                                                                    */
    std::list<Ini_section*>::const_iterator search(std::string name)const throw(std::invalid_argument); /* wrapping
                                                                      * frequently used code in functions
                                                                      */

    std::list<Ini_section*>::const_iterator section_search(int pos)const throw(std::out_of_range);
    std::list<Ini_section*>::const_iterator section_search(std::string name)const throw(std::invalid_argument);


    std::string file_name;
    std::ifstream i_file;
    std::ofstream o_file;
    std::list<Ini_section*> content;

};


#endif //SIMPLE_INI_INI_MANAGER_H
