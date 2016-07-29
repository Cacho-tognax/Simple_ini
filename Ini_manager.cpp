//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_manager.h"

Ini_manager::Ini_manager(){

}

Ini_manager::Ini_manager(std::string file_name) {
    open_file(file_name);
}

unsigned long int Ini_manager::get_length()const{
    return static_cast<int>(content.size());
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
        if (o_file.is_open()) {     //making sure new file is writeable
            o_file.close();         //letting save to open it
            file_name=new_file_name;
            save();
        } else {
            std::cout << "error: file not writable" << std::endl;
        }
    }else{
        std::cout << "error: no file to save!" << std::endl;
    }

}

void Ini_manager::close_file() {
    if(i_file.is_open()) {
        for(auto itr=content.begin(); itr!=content.end(); itr ++){
            delete (*itr);  //the manager owns the sections
        }
        content.erase(content.begin(), content.end());
        i_file.close();
    }else{
        std::cout << "error: no file to close" << std::endl;
    }
}

void Ini_manager::add_line(const Ini_entry &entry, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()) {
        std::cout << "Error: no such section found" << std::endl;
    }else {
        (*itr)->add_line(entry);
    }
}

void Ini_manager::add_line(const Ini_entry &entry, int pos, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()) {
        std::cout << "Error: no such section found" << std::endl;
    }else {
        (*itr)->add_line(entry, pos);
    }
}

void Ini_manager::add_line(const std::string &entry, std::string section) {
    try {
        Ini_entry tmp(entry);
        add_line(tmp, section);
    }
    catch (Invalid_entry_exception){
        std::cout << "Invalid entry" << std::endl;
    }
}

void Ini_manager::add_line(const std::string &entry, int pos, std::string section) {
    try {
        Ini_entry tmp(entry);
        add_line(tmp, pos, section);
    }
    catch (Invalid_entry_exception){
        std::cout << "Invalid entry" << std::endl;
    }
}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value, std::string section) {
    try{
        Ini_entry tmp(ty, name, value);
        add_line(tmp, section);
    }catch (Invalid_entry_exception){
        std::cout << "Invalid entry" << std::endl;
    }
}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value, int pos, std::string section) {
    try{
        Ini_entry tmp(ty, name, value);
        add_line(tmp, pos, section);
    }catch (Invalid_entry_exception){
        std::cout << "Invalid entry" << std::endl;
    }
}

void Ini_manager::remove_line(int pos, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
    }else{
        (*itr)->remove_line(pos);
    }
}

void Ini_manager::remove_line(std::string name, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
    }else{
        (*itr)->remove_line(name);
    }
}



void Ini_manager::remove_any_line(int pos) {
    auto itr= search(pos);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
    }else{
        (*itr)->remove_line(pos);
    }
}

void Ini_manager::remove_any_line(std::string name) {
    auto itr= search(name);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
    }else{
        (*itr)->remove_line(name);
    }
}


void Ini_manager::add_section(std::string name, int pos) {
    auto itr=section_search(pos);
    content.insert(itr, new Ini_section(name));
}

void Ini_manager::add_section(const Ini_section &section, int pos){
    auto itr=section_search(pos+1);     //the unsectioned section must be invisible to this method
    content.insert(itr, new Ini_section(section));
}

Ini_section Ini_manager::get_section(int pos)const{
    auto itr=section_search(pos+1);    //as above
    if (itr!=content.end()){
        return *(*itr);
    }else {
        std::cout << "Warning:section not found, returning dummy" << std::endl;
        return Ini_section("section not found");
    }
}
Ini_section Ini_manager::get_section(std::string name)const{
    auto itr=section_search(name);
    if (itr!=content.end()){
        return *(*itr);
    }else {
        std::cout << "Warning:section not found, returning dummy" << std::endl;
        return Ini_section("section not found");
    }
}

void Ini_manager::remove_section(std::string name) {
    auto itr=section_search(name);
    if(itr==content.end()) {
        std::cout << "Error: no such section found" << std::endl;
    }else{
        delete (*itr);
        if(itr!=content.begin()) {  //when asked to remove the unsectioned, the section must be recreated
            content.erase(itr);
        }else{
            content.push_front(new Ini_section("unsectioned"));
        }
    }
}

void Ini_manager::remove_section(int pos) {
    auto itr=section_search(pos);
    if(itr==content.end()) {
        std::cout << "Error: no such section found" << std::endl;
    }else{
        delete (*itr);
        if(itr!=content.begin()) {  //as above
            content.erase(itr);
        }else{
            content.front()=(new Ini_section("unsectioned"));
        }
    }
}

Ini_entry Ini_manager::get_line(int pos, std::string section)const{
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else{
        return (*itr)->get_line(pos);
    }
}

Ini_entry Ini_manager::get_line(std::string name, std::string section)const{
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else{
        return (*itr)->get_line(name);
    }
}


Ini_entry Ini_manager::get_any_line(int pos)const{
    auto itr= search(pos);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else{
        return (*itr)->get_line(pos);
    }
}

Ini_entry Ini_manager::get_any_line(std::string name)const{
    auto itr= search(name);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else{
        return (*itr)->get_line(name);
    }
}



std::string Ini_manager::read()const{
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

std::string Ini_manager::read_line(int pos, std::string section)const{
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
        return "section not found";
    }else{
        return (*itr)->read_line(pos);
    }
}

std::string Ini_manager::read_line(std::string name, std::string section)const{
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
        return "section not found";
    }else{
        return (*itr)->read_line(name);
    }
}


std::string Ini_manager::read_any_line(int pos)const{
    auto itr= search(pos);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
        return "not found";
    }else{
        return (*itr)->read_line(pos);
    }
}

std::string Ini_manager::read_any_line(std::string name)const{
    auto itr= search(name);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
        return "not found";
    }else{
        return (*itr)->read_line(name);
    }
}


void Ini_manager::set_line(int pos, std::string value, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
    }else{
        (*itr)->set_line(pos, value);
    }
}

void Ini_manager::set_line(std::string name, std::string value, std::string section) {
    auto itr=section_search(section);
    if (section=="")
        itr=content.begin();
    if(itr==content.end()){
        std::cout << "Error: no such section found" << std::endl;
    }else{
        (*itr)->set_line(name, value);
    }
}

void Ini_manager::set_any_line(int pos, std::string value) {
    auto itr= search(pos);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
    }else{
        (*itr)->set_line(pos, value);
    }
}

void Ini_manager::set_any_line(std::string name, std::string value) {
    auto itr= search(name);
    if(itr==content.end()){
        std::cout << "no such line exists in any section" << std::endl;
    }else{
        (*itr)->set_line(name, value);
    }
}


std::list<Ini_section *>::const_iterator Ini_manager::search(int &pos)const{
    if(pos<0){
        std::cout << "error: negative index" << std::endl;
        return content.end();
    }
    auto itr =content.begin();
    while(itr!=content.end()){
        if((*itr)->get_length()>pos){
            return itr;
        }else{
            pos-=(*itr)->get_length();
            itr++;
        }
    }
    return itr;
}

std::list<Ini_section *>::const_iterator Ini_manager::search(std::string name)const{

    for(auto itr =content.begin();itr!=content.end();itr++){
        if((*itr)->exists(name))
            return itr;
    }
    return content.end();
}

std::list<Ini_section *>::const_iterator Ini_manager::section_search(int pos)const{
    if(pos<0){
        if(pos==end_content){
            return content.end();
        }
        std::cout << "error: negative index" << std::endl;
        return content.end();
    }
    if(pos>=content.size()){
        return content.end();
    }
    auto itr = content.begin();
    for(; pos>0; pos--)                     //getting the iterator to the section
        itr++;
    return itr;
}

std::list<Ini_section *>::const_iterator Ini_manager::section_search(std::string name)const{
    for(auto itr = content.begin();itr!=content.end(); itr++) {
        if ((*itr)->get_name()==name)
            return itr;
    }
    return content.end();
}
