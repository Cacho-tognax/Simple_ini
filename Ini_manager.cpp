//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_manager.h"

Ini_manager::Ini_manager(std::string file_name) {
    file.open (file_name);
    if(file.good()) {
        std::string tmp;
        Ini_section *current = new Ini_section("unsectioned");
        while (getline(file, tmp)) {
            if (Ini_entry::identify(tmp) != to_ignore) {
                if (Ini_entry::identify(tmp) == section_head) {
                    content.push_back(current);
                    tmp.erase(tmp.begin());
                    tmp.erase(--tmp.end());            //removing [ and ], will be added later on save
                    current = new Ini_section(tmp);
                } else {
                    current->add_line(tmp);
                }
            }
        }
        content.push_back(current);
        std::cout << "file loaded" << std::endl;
    } else{
        std::cout << "error loading file" << std::endl;
    }

}

Ini_manager::~Ini_manager() {
    for(auto itr=content.begin(); itr!=content.end(); itr ++){
        delete (*itr);  //the manager owns the sections
    }

}

std::list<Ini_entry *>::iterator Ini_manager::search(int pos) {

}

std::list<Ini_entry *>::iterator Ini_manager::search(std::string name) {

}

std::list<Ini_section *>::iterator Ini_manager::section_search(int pos) {
    return std::_List_iterator<Ini_section *>();
}

std::list<Ini_section *>::iterator Ini_manager::section_search(std::string name) {
    return std::_List_iterator<Ini_section *>();
}

void Ini_manager::add_line(std::string &line) {

}

void Ini_manager::add_line(std::string &line, int pos) {

}

void Ini_manager::add_line(std::string section, std::string &line) {

}

void Ini_manager::add_line(std::string section, std::string &line, int pos) {

}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value) {

}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value, int pos) {

}

void Ini_manager::add_line(std::string section, enum entry_type ty, std::string name, std::string value) {

}

void Ini_manager::add_line(std::string section, enum entry_type ty, std::string name, std::string value, int pos) {

}

void Ini_manager::remove_line(std::string section, int pos) {

}

void Ini_manager::remove_line(std::string section, std::string name) {

}

void Ini_manager::add_section(std::string name) {

}

void Ini_manager::add_section(std::string name, int pos) {

}

void Ini_manager::remove_section(std::string name) {

}

void Ini_manager::remove_section(int pos) {

}

Ini_entry Ini_manager::get_ine(std::string section, int pos) {

}

Ini_entry Ini_manager::get_ine(std::string section, std::string name) {

}

std::string Ini_manager::read(){
    std::string tmp="";
    auto itr=content.begin();
    tmp+=(*itr)->read();         //first section has no section header
    itr++;
    for(; itr!=content.end(); itr++){
        tmp+="["+(*itr)->get_name()+"]\n";
        tmp+=(*itr)->read();
    }
    return tmp;
}

std::string Ini_manager::read_line(std::string section, int pos) {

}

std::string Ini_manager::read_line(std::string section, std::string name) {

}

void Ini_manager::set_line(std::string section, int pos, std::string value) {

}

void Ini_manager::set_line(std::string section, std::string name, std::string value) {

}
