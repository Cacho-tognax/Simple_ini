//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_section.h"

Ini_section::Ini_section(std::string name): name(name) {

}

Ini_section::~Ini_section() {
    entries.erase(entries.begin(), entries.end());

}


std::list<Ini_entry*>::iterator Ini_section::search(int pos) {
    auto itr=entries.begin();
    for(; pos>0&&itr!=entries.end(); itr ++, pos--);  /* finding iterator to required position,
                                                       * using pos as local variable
                                                       */
    return itr;
}

std::list<Ini_entry*>::iterator Ini_section::search(std::string name) { /* can't use remove since
                                                                        * i have to search the element by name
                                                                        */
    auto itr=entries.begin();                                          /* can't initialize inside for:
                                                                        * i need it later to be used only once
                                                                        */
    for (; (*itr)->getName()!=name&&itr!=entries.end(); itr++);
    return itr;

}

bool Ini_section::exists(int pos){
    return (search(pos)!=entries.end());
}

bool Ini_section::exists(std::string name){
    return (search(name)!=entries.end());
}

void Ini_section::add_line(Ini_entry & line) {
    Ini_entry* ptr=new Ini_entry(line);
    entries.push_back(ptr);

}

void Ini_section::add_line(enum entry_type ty, std::string name, std::string value){
    Ini_entry* ptr=new Ini_entry(ty, name, value);
    entries.push_back(ptr);
}

void Ini_section::add_line(std::string entry){
    Ini_entry* ptr=new Ini_entry(entry);
    entries.push_back(ptr);
}

void Ini_section::add_line(Ini_entry & line, int pos) {
    Ini_entry* ptr=new Ini_entry(line);
    auto itr=search(pos);
    entries.insert(itr, ptr);

}

void Ini_section::add_line(enum entry_type ty, std::string name, std::string value, int pos){
    Ini_entry* ptr=new Ini_entry(ty, name, value);
    auto itr=search(pos);
    entries.insert(itr, ptr);
}

void Ini_section::add_line(std::string entry, int pos){
    Ini_entry* ptr=new Ini_entry(entry);
    auto itr=search(pos);
    entries.insert(itr, ptr);
}

void Ini_section::remove_line(int pos) {
    auto itr=search(pos);
    if (itr==entries.end()){
        std::cout << "warning: line requested to remove does not exists" << std::endl;
    } else{
        entries.erase(itr);
    }
}

void Ini_section::remove_line(std::string name) {
    auto itr=search(name);
    if (itr==entries.end()){
        std::cout << "warning: line requested to remove does not exists" << std::endl;
    } else{
        entries.erase(itr);
    }
}

Ini_entry Ini_section::get_ine(int pos) {
    auto itr=entries.begin();                         //can't initialize in for: i need it later to be used only once
    for(; pos>0&&itr!=entries.end(); itr ++, pos--);  /* finding iterator to required position,
                                                       * using pos as local variable
                                                       */
    if (itr==entries.end()){
        std::cout << "warning: line requested to remove does not exists, returning dummy" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else {                                           //else not necessary, but makes code more readable
        return (*(*itr));
    }
}

Ini_entry Ini_section::get_ine(std::string name) {
    auto itr=search(name);
    if (itr==entries.end()){
        std::cout << "warning: line requested to remove does not exists, returning dummy" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else {                                           //else not necessary, but makes code more readable
        return (*(*itr));
    }
}

std::string Ini_section::read(){
    std::string tmp="";
    for (auto itr=entries.begin(); itr!=entries.end(); itr ++) {
        tmp += (*itr)->read()+"\n";
    }
    return tmp;
}

std::string Ini_section::read_line(int pos) {
    auto itr=search(pos);
    return (*itr)->read();
}

std::string Ini_section::read_line(std::string name) {
    auto itr=search(name);
    return (*itr)->read();
}

void Ini_section::set_line(int pos, std::string value) {
    auto itr=search(pos);
    (*itr)->setValue(value);

}

void Ini_section::set_line(std::string name, std::string value) {
    auto itr=search(name);
    (*itr)->setValue(value);

}

int Ini_section::get_lenght() {
    return entries.size();
}

std::string Ini_section::get_name() {
    return name;
}


