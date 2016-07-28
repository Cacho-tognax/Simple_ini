//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_section.h"

Ini_section::Ini_section(std::string name): name(name) {

}

Ini_section::~Ini_section() {
    for(auto itr=entries.begin(); itr!=entries.end(); itr ++){
        delete (*itr);  //the section owns the entries
    }
    entries.erase(entries.begin(), entries.end());

}


std::list<Ini_entry*>::iterator Ini_section::search(int pos) {
    if (pos<0){
        std::cout << "Error: negative index, if adding it will be placed at the end" << std::endl;
        return entries.end();
    }
    auto itr=entries.begin();
    for(; pos>0&&itr!=entries.end(); itr ++, pos--);  /* finding iterator to required position,
                                                       * using pos as local variable
                                                       */
    return itr;
}

std::list<Ini_entry*>::iterator Ini_section::search(std::string name) {
    auto itr=entries.begin();                                          /* can't initialize inside for:
                                                                        * i need it later to be used only once
                                                                        */
    for (; itr!=entries.end(); itr++){
        if((*itr)->get_name()==name)
            return itr;
    }
    return itr;

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

Ini_entry Ini_section::get_line(int pos) {
    auto itr=entries.begin();                         //can't initialize in for: i need it later to be used only once
    for(; pos>0&&itr!=entries.end(); itr ++, pos--);  /* finding iterator to required position,
                                                       * using pos as local variable
                                                       */
    if (itr==entries.end()){
        std::cout << "warning: line requested does not exists, returning dummy" << std::endl;
        return Ini_entry(comment, "Error: line does not exists", "");
    }else {                                           //else not necessary, but makes code more readable
        return (*(*itr));
    }
}

Ini_entry Ini_section::get_line(std::string name) {
    auto itr=search(name);
    if (itr==entries.end()){
        std::cout << "warning: line requested does not exists, returning dummy" << std::endl;
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
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
        return "entry does not exists";
    }
    return (*itr)->read();
}

std::string Ini_section::read_line(std::string name) {
    auto itr=search(name);
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
        return "entry does not exists";
    }
    return (*itr)->read();
}

void Ini_section::set_line(int pos, std::string value) {
    auto itr=search(pos);
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
    }else {
        (*itr)->set_value(value);
    }

}

void Ini_section::set_line(std::string name, std::string value) {
    auto itr=search(name);
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
    }else {
        (*itr)->set_value(value);
    }
}

void Ini_section::set_line_type(int pos, enum entry_type typ, std::string value) {
    auto itr=search(pos);
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
    }else {
        (*itr)->change_type(typ, value);
    }
}

void Ini_section::set_line_type(std::string name, enum entry_type typ, std::string value){
    auto itr=search(name);
    if(itr==entries.end()){
        std::cout << "Warning: requested line does not exists" << std::endl;
    }else {
        (*itr)->change_type(typ, value);
    }
}

unsigned long int Ini_section::get_length() {
    return entries.size();
}

std::string Ini_section::get_name() {
    return name;
}



