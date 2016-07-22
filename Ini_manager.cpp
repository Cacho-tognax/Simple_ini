//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_manager.h"

Ini_manager::Ini_manager(){

}

Ini_manager::Ini_manager(std::string file_name) {
    open_file(file_name);
}

Ini_manager::~Ini_manager() {
    close_file();
}

void Ini_manager::open_file(std::string file_name) {
    if(!i_file.is_open()) {
        i_file.open(file_name);
        if (i_file.is_open()) {
            this->file_name=file_name;
            std::string tmp;
            Ini_section *current = new Ini_section("unsectioned");
            while (getline(i_file, tmp)) {
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
        } else {
            std::cout << "error loading file" << std::endl;
        }
    }else{
        std::cout << "please close current file first" << std::endl;
    }
}


void Ini_manager::save() {
    if(i_file.is_open()) {
        i_file.close();          //to have it opened by only 1 fstream object
        o_file.open(file_name);
        if (o_file.is_open()) {
            o_file << read();
            o_file.flush();
            o_file.close();
        } else {
            std::cout << "error: file not writable" << std::endl;
        }
        i_file.open(file_name);
    }else{
        std::cout << "error: no file to save!" << std::endl;
    }
}

void Ini_manager::save_as(std::string new_file_name){
    if(i_file.is_open()) {
        o_file.open(new_file_name);
        if (o_file.is_open()) {
            o_file << read();
            o_file.flush();
            o_file.close();
            i_file.close();
            file_name=new_file_name;
            i_file.open(new_file_name);
        } else {
            std::cout << "error: file not writable" << std::endl;
        }
    }else{
        std::cout << "error: no file to save!" << std::endl;
    }

}

void Ini_manager::close_file() {
    if(i_file.is_open()) {
        content.erase(content.begin(), content.end());
        i_file.close();
    }else{
        std::cout << "error: no file to close" << std::endl;
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
    if(i_file.is_open()) {
        std::string tmp = "";
        auto itr = content.begin();
        tmp += (*itr)->read();         //first section has no section header
        itr++;
        for (; itr != content.end(); itr++) {
            tmp += "[" + (*itr)->get_name() + "]\n";
            tmp += (*itr)->read();
        }
        return tmp;
    }else{
        std::cout << "error:no file to read!" << std::endl;
        return "";
    }
}

std::string Ini_manager::read_line(std::string section, int pos) {

}

std::string Ini_manager::read_line(std::string section, std::string name) {

}

void Ini_manager::set_line(std::string section, int pos, std::string value) {

}

void Ini_manager::set_line(std::string section, std::string name, std::string value) {

}

