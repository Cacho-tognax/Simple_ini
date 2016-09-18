//
// Created by stefano lavori on 09/07/2016.
//

#include "Ini_section.h"

Ini_section::Ini_section(std::string name): name(name) {

}

Ini_section::Ini_section(const Ini_section &source): name(source.get_name()){
    int source_size= static_cast<int>(source.get_length());
    for(int i=0; i<source_size; i++){
        add_line(source.get_line(i));
    }
}
Ini_section::~Ini_section() {
    for(auto itr=entries.begin(); itr!=entries.end(); itr ++){
        delete (*itr);  //the section owns the entries
    }
    entries.erase(entries.begin(), entries.end());

}

bool Ini_section::operator==(const Ini_section &lhs)const{
    if(name!=lhs.get_name())
        return false;
    if(get_length()!=lhs.get_length())
        return false;
    int length= static_cast<int>(get_length());
    for(int i=0; i<length; i++){
        if(!(get_line(i)==lhs.get_line(i)))
            return false;
    }
    return true;
}


bool Ini_section::exists(std::string name){
    try{
        search(name);
    }catch (std::invalid_argument& exception){
        return false;
    }
    return true;
}

void Ini_section::add_line(const Ini_entry & entry, int pos) throw(std::out_of_range) {
    Ini_entry* ptr=new Ini_entry(entry);
    if(pos==get_length())
        entries.push_back(ptr);
    else {
        try {
            auto itr = search(pos);
            entries.insert(itr, ptr);
        }catch (std::out_of_range& exception){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }

}

void Ini_section::add_line(enum entry_type ty, std::string name, std::string value,
                           int pos) throw(std::invalid_argument, std::out_of_range){
    Ini_entry *ptr = new Ini_entry(ty, name, value);
    if(pos==get_length())
        entries.push_back(ptr);
    else {
        try {
            auto itr = search(pos);
            entries.insert(itr, ptr);
        }catch (std::out_of_range& exception){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }
}

void Ini_section::add_line(const std::string &line, int pos) throw(std::invalid_argument, std::out_of_range){
    Ini_entry *ptr = new Ini_entry(line);
    if(pos==get_length())
        entries.push_back(ptr);
    else {
        try {
            auto itr = search(pos);
            entries.insert(itr, ptr);
        }catch (std::out_of_range& exception){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }
}

void Ini_section::remove_line(int pos) throw(std::out_of_range){
    auto itr=search(pos);
    delete (*itr);
    entries.erase(itr);
}

void Ini_section::remove_line(std::string name) throw(std::invalid_argument){
    auto itr=search(name);
        delete (*itr);
        entries.erase(itr);
}

Ini_entry Ini_section::get_line(int pos)const throw(std::out_of_range){
    auto itr = search(pos);
    return *(*(itr));
}

Ini_entry Ini_section::get_line(std::string name)const throw(std::invalid_argument){
    auto itr=search(name);
    return (*(*itr));
}

std::string Ini_section::read()const{
    std::string tmp="";
    for (auto itr=entries.begin(); itr!=entries.end(); itr ++) {
        tmp += (*itr)->read()+"\n";
    }
    return tmp;
}

std::string Ini_section::read_line(int pos)const throw(std::out_of_range){
    auto itr=search(pos);
    return (*itr)->read();
}

std::string Ini_section::read_line(std::string name)const throw(std::invalid_argument){
    auto itr=search(name);
    return (*itr)->read();
}

void Ini_section::set_line(int pos, std::string value) throw(std::invalid_argument, std::out_of_range){
    auto itr=search(pos);
    (*itr)->set_value(value);
}

void Ini_section::set_line(std::string name, std::string value) throw(std::invalid_argument){
    auto itr=search(name);
    (*itr)->set_value(value);
}

void Ini_section::set_line_type(int pos, enum entry_type typ,
                                std::string value) throw(std::invalid_argument, std::out_of_range){
    auto itr=search(pos);
    (*itr)->change_type(typ, value);
}

void Ini_section::set_line_type(std::string name, enum entry_type typ, std::string value) throw(std::invalid_argument){
    auto itr=search(name);
    (*itr)->change_type(typ, value);
}

unsigned long int Ini_section::get_length()const{
    return entries.size();
}

std::string Ini_section::get_name()const{
    return name;
}



std::list<Ini_entry*>::const_iterator Ini_section::search(int pos)const throw(std::out_of_range){
    if (pos<0){
        if(pos==entries_end)
            return entries.end();
#ifdef DEBUG
        std::cout << "Error: negative index" << std::endl;
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()-1));
    }
    if(pos>=this->get_length()) {
#ifdef DEBUG
        std::cout << "Error: index greater or equal to section size" << std::endl;
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()-1));
    }
    auto itr=entries.begin();
    for(; pos>0&&itr!=entries.end(); itr ++, pos--);
    return itr;
}

std::list<Ini_entry*>::const_iterator Ini_section::search(std::string name)const throw(std::invalid_argument){
    for (auto itr=entries.begin(); itr!=entries.end(); itr++){
        if((*itr)->get_name()==name)
            return itr;
    }
#ifdef DEBUG
    std::cout << "Error: no key with this name found in the section" << std::endl;
#endif
    throw std::invalid_argument(name);

}