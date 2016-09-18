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

unsigned long int Ini_manager::get_number_of_entries()const {
    unsigned long int sum=0;
    for(auto itr=content.begin(); itr!=content.end(); itr++)
        sum+=(*itr)->get_length();
    return sum;
}
Ini_manager::~Ini_manager() {
    if (i_file.is_open())
        close_file();
}

void Ini_manager::open_file(std::string file_name) throw(std::invalid_argument){
    if(!i_file.is_open())
        close_file();
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
#ifdef DEBUG
        std::cout << "unable to load file" << std::endl;
#endif
        throw std::invalid_argument(file_name);
    }
}


void Ini_manager::save() throw(std::invalid_argument){
    save_as(file_name);
}

void Ini_manager::save_as(std::string new_file_name) throw(std::invalid_argument){
    if(i_file.is_open()) {
        o_file.open(new_file_name);
        if (o_file.is_open()) {     //making sure new file is writeable
            o_file << read();
            o_file.flush();
            o_file.close();
        } else {
#ifdef DEBUG
            std::cout << "error: file not writable" << std::endl;
#endif
            throw std::invalid_argument(new_file_name);
        }
    }else{
#ifdef DEBUG
        std::cout << "error: no file to save!" << std::endl;
#endif
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
#ifdef DEBUG
        std::cout << "error: no file to close" << std::endl;
#endif
    }
}

void Ini_manager::add_line(const Ini_entry &entry, std::string section) throw(std::invalid_argument){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->add_line(entry);
}

void Ini_manager::add_line(const Ini_entry &entry, int pos,
                           std::string section) throw(std::invalid_argument, std::out_of_range){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->add_line(entry, pos);
}

void Ini_manager::add_line(const std::string &entry, std::string section) throw(std::invalid_argument){
    Ini_entry tmp(entry);
    add_line(tmp, section);

}

void Ini_manager::add_line(const std::string &entry, int pos,
                           std::string section) throw(std::invalid_argument, std::out_of_range){
        Ini_entry tmp(entry);
        add_line(tmp, pos, section);
}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value,
                           std::string section) throw(std::invalid_argument){

    Ini_entry tmp(ty, name, value);
    add_line(tmp, section);

}

void Ini_manager::add_line(enum entry_type ty, std::string name, std::string value,
                           int pos, std::string section) throw(std::invalid_argument, std::out_of_range){
    Ini_entry tmp(ty, name, value);
    add_line(tmp, pos, section);
}

void Ini_manager::remove_line(int pos, std::string section) throw(std::invalid_argument, std::out_of_range){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->remove_line(pos);
}

void Ini_manager::remove_line(std::string name, std::string section) throw(std::invalid_argument){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->remove_line(name);
}



void Ini_manager::remove_any_line(int pos) throw(std::out_of_range){
    auto itr= search(pos);
    (*itr)->remove_line(pos);
}

void Ini_manager::remove_any_line(std::string name) throw(std::invalid_argument){
    auto itr= search(name);
    (*itr)->remove_line(name);
}


void Ini_manager::add_section(std::string name, int pos) throw(std::out_of_range){
    auto itr=content.cend();
    if(pos!=content.size() && pos != end_content){
        try {
            itr = section_search(pos + 1);     //the unsectioned section must be invisible to theese methods
        }catch(std::out_of_range){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }
    content.insert(itr, new Ini_section(name));
}

void Ini_manager::add_section(const Ini_section &section, int pos) throw(std::out_of_range){
    auto itr=content.cend();
    if(pos!=content.size() && pos != end_content){
        try {
            itr = section_search(pos + 1);
        }catch(std::out_of_range){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }
    content.insert(itr, new Ini_section(section));
}

Ini_section Ini_manager::get_section(int pos)const throw(std::out_of_range){
    auto itr=content.cend();
    if(pos!=content.size()){
        try {
            itr = section_search(pos + 1);
        }catch(std::out_of_range){
            throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()));
        }
    }
    return *(*itr);
}
Ini_section Ini_manager::get_section(std::string name)const throw(std::invalid_argument){
    auto itr=section_search(name);
    return *(*itr);
}

void Ini_manager::remove_section(std::string name) throw(std::invalid_argument){
    auto itr=section_search(name);
    delete (*itr);
    if(itr!=content.begin()) {  //when asked to remove the unsectioned, the section must be recreated
        content.erase(itr);
    }else{
        content.push_front(new Ini_section("unsectioned"));
    }
}

void Ini_manager::remove_section(int pos) throw(std::out_of_range){
    auto itr=section_search(pos);
    delete (*itr);
    if(itr!=content.begin()) {  //as above
        content.erase(itr);
    }else{
        content.front()=(new Ini_section("unsectioned"));
    }
}

Ini_entry Ini_manager::get_line(int pos, std::string section)const throw(std::invalid_argument, std::out_of_range){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    return (*itr)->get_line(pos);
}

Ini_entry Ini_manager::get_line(std::string name, std::string section)const throw(std::invalid_argument){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    return (*itr)->get_line(name);
}


Ini_entry Ini_manager::get_any_line(int pos)const throw(std::out_of_range){
    auto itr= search(pos);
    return (*itr)->get_line(pos);
}

Ini_entry Ini_manager::get_any_line(std::string name)const throw(std::invalid_argument){
    auto itr= search(name);
    return (*itr)->get_line(name);
}



std::string Ini_manager::read()const{
    std::string tmp = "";
    auto itr = content.begin();
    tmp += (*itr)->read();         //first section has no section header
    itr++;
    for (; itr != content.end(); itr++) {
        tmp += "[" + (*itr)->get_name() + "]\n";
        tmp += (*itr)->read();
    }
    return tmp;
}

std::string Ini_manager::read_line(int pos, std::string section)const throw(std::invalid_argument, std::out_of_range){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    return (*itr)->read_line(pos);
}

std::string Ini_manager::read_line(std::string name, std::string section)const throw(std::invalid_argument){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    return (*itr)->read_line(name);
}


std::string Ini_manager::read_any_line(int pos)const throw(std::out_of_range){
    auto itr= search(pos);
    return (*itr)->read_line(pos);
}

std::string Ini_manager::read_any_line(std::string name)const throw(std::invalid_argument){
    auto itr= search(name);
    return (*itr)->read_line(name);
}


void Ini_manager::set_line(int pos, std::string value,
                           std::string section) throw(std::invalid_argument, std::out_of_range){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->set_line(pos, value);
}

void Ini_manager::set_line(std::string name, std::string value, std::string section) throw(std::invalid_argument){
    auto itr=content.cbegin();
    if (section!="")
        itr=section_search(section);
    (*itr)->set_line(name, value);
}

void Ini_manager::set_any_line(int pos, std::string value) throw(std::invalid_argument, std::out_of_range){
    auto itr= search(pos);
    (*itr)->set_line(pos, value);
}

void Ini_manager::set_any_line(std::string name, std::string value) throw(std::invalid_argument){
    auto itr= search(name);
    (*itr)->set_line(name, value);
}


std::list<Ini_section *>::const_iterator Ini_manager::search(int &pos)const throw(std::out_of_range){
    unsigned long int number_of_entries=get_number_of_entries();
    if(pos<0){
#ifdef DEBUG
        std::cout << "Error: negative index" << std::endl;
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(number_of_entries-1));
    }
    if(pos>=number_of_entries){
#ifdef DEBUG
        std::cout << "Error: pos greater than manger size";
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(number_of_entries-1));
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

std::list<Ini_section *>::const_iterator Ini_manager::search(std::string name)const throw (std::invalid_argument){
    for(auto itr =content.begin();itr!=content.end();itr++){
        if((*itr)->exists(name))
            return itr;
    }
#ifdef DEBUG
    std::cout << "Error: no section with such name found";
#endif
    throw (std::invalid_argument(name));
}

std::list<Ini_section *>::const_iterator Ini_manager::section_search(int pos)const  throw(std::out_of_range){
    if(pos<0){
        if(pos==end_content){
            return content.end();
        }
#ifdef DEBUG
        std::cout << "Error: negative index" << std::endl;
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()-1));
    }
    if(pos>=content.size()){
#ifdef DEBUG
        std::cout << "Error: pos greater or equal to manger size";
#endif
        throw std::out_of_range(std::to_string(pos) + " 0 " + std::to_string(this->get_length()-1));
    }
    auto itr = content.begin();
    for(; pos>0; pos--)                     //getting the iterator to the section
        itr++;
    return itr;
}

std::list<Ini_section *>::const_iterator Ini_manager::section_search(std::string name)const throw(std::invalid_argument){
    for(auto itr = content.begin();itr!=content.end(); itr++) {
        if ((*itr)->get_name()==name)
            return itr;
    }
#ifdef DEBUG
    std::cout << "Error: no such name found in any section";
#endif
    throw (std::invalid_argument(name));
}
