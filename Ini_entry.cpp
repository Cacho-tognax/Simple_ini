//
// Created by stefano lavori on 10/07/2016.
//

#include"Ini_entry.h"

Ini_entry::Ini_entry(enum entry_type ty, std::string name, std::string value) throw(std::invalid_argument):
        type(ty), name(name), value(value){
    if (type==comment){
        this->value="";
    } else{
        if (type==string_entry) {  // removing the ""
            if(this->value.size()<3){      //to avoid segmentation faults
                std::string tmp= name + " = " + value;
#ifdef DEBUG
                std::cout << "value too short, no room for the double quotation marks" << std::endl;
#endif
                throw std::invalid_argument(tmp);
            }
            this->value.erase(this->value.begin());
            this->value.erase(--this->value.end());
        }

        std::string tmp= name + " = " + value;
        if(identify(tmp)!=type){
#ifdef DEBUG
            std::cout << "value is not of type or invalid name(only spaces or with an=)" << std::endl;
#endif
            throw std::invalid_argument(tmp);
        }
    }

}


Ini_entry::Ini_entry(std::string entry) throw(std::invalid_argument){
    set(entry);
}

void Ini_entry::set(std::string entry) throw(std::invalid_argument){
    std::vector<std::string> parts;
    type=identify(entry, parts);
    if (type==to_ignore||type==section_head){
#ifdef DEBUG
        std::cout << "such string is not an entry" << std::endl;
#endif
        throw std::invalid_argument(entry);
    }
    name=parts[0];
    if (type!=comment){  // if not a comment value must be added to
        if(type!=string_entry) {
            value = parts[1];
        } else{
            std::string tmp = parts[1];
            tmp.erase(tmp.begin());
            tmp.erase(--tmp.end());   //removing the ""
            value = tmp;
        }
    }
}

void Ini_entry::set(enum entry_type ty, std::string name, std::string value) throw(std::invalid_argument){
    if (type==comment){
        this->type=ty;
        this->name=name;
        this->value="";
    } else{
        std::string tmp= name + " = " + value;
        if(identify(tmp)!=ty){
#ifdef DEBUG
            std::cout << "new value is not of new type" << std::endl;
#endif
            throw std::invalid_argument(tmp);
        }else{
            this->type=ty;
            this->name=name;
            this->value=value;
        }
    }

}

std::string Ini_entry::read() const{

    std::string return_string;
    if (type==comment) {
        return_string = "!" + name;
    }else if(type==string_entry) {
        return_string = name + " = \"" + value + "\"";
    }else {
        return_string = name + " = " + value;
    }
    return return_string;

}

enum entry_type Ini_entry::identify(std::string entry, std::vector<std::string>& parts) {


    if (entry.size()==0)
        return to_ignore;
    char tmp = entry[0];
    if (tmp == '!') {
        parts.push_back(entry.substr(1, entry.size()-1));
        return comment;
    } else if (tmp == '[') {    //must find closing or it's an ignored typo
        std::string::size_type the_char=entry.find_first_of("]", 1);
        if(the_char == entry.size()-1) {
            parts.push_back(entry.substr(1, entry.size() - 2));
            return section_head;
        }
        else
            return to_ignore;
    } else {                         //attempting to understand entry type
        std::string::size_type the_char = entry.find_first_of("=", 0);
        std::string tmp_string = entry.substr(0, the_char);
        if(tmp_string.find_first_not_of(" ", 0)==std::string::npos)  //no non space found
            return to_ignore; //no actual name
        remove_spaces_to_the_right(tmp_string);  //enclosed to a mehid since it's used twice
        parts.push_back(tmp_string);
        the_char = entry.find_first_not_of(" ", the_char+1);
        if(the_char==std::string::npos)
            return to_ignore;
        tmp_string=entry.substr(the_char);      //this is the value
        remove_spaces_to_the_right(tmp_string);
        parts.push_back(tmp_string);            //even if it is invalid
        if(tmp_string.find_first_of("1234567890")!=std::string::npos && tmp_string.find_first_not_of("1234567890-.")==
                                                                                std::string::npos) {
            if (tmp_string[0] == '-')
                the_char = tmp_string.find_first_not_of("1234567890", 1);
            else
                the_char = tmp_string.find_first_not_of("1234567890");
            if (the_char == std::string::npos)
                return int_entry;
            if (tmp_string[the_char] == '.') {
                the_char = tmp_string.find_first_not_of("1234567890", the_char+1);
                if (the_char == std::string::npos)
                    return float_entry;
            }
            return to_ignore;
        }
        if(tmp_string == "TRUE" || tmp_string == "FALSE")
            return bool_entry;
        if (tmp_string[0] == '"') {    //must find closing or it's an ignored typo
            the_char = tmp_string.find_first_of("\"", 1);
            if(the_char == tmp_string.size() - 1)     //the closing quotation mark must be the last char in the string
                return string_entry;
            }
        return to_ignore;   //was none of the above
    }
}

void Ini_entry::remove_spaces_to_the_right(std::string &tmp_string) {
    std::string::size_type the_char2 = tmp_string.find_last_of(" ", std::string::npos);
    while(the_char2==tmp_string.size()-1){    //while we have a space at the end
            tmp_string.erase(the_char2);
            the_char2 = tmp_string.find_last_of(" ", std::string::npos);
        }
}

enum entry_type Ini_entry::identify(std::string entry) {  //calls the previous one discarding the tokens
    std::vector<std::string> parts;
    return identify(entry, parts);
}

bool Ini_entry::operator ==(const Ini_entry rhs) const{
    if(type!= rhs.get_type())
        return false;
    if(name!= rhs.get_name())
        return false;
    return !(value != rhs.get_value());  //just to make clion happy
}

void Ini_entry::change_type(const entry_type &typ, const std::string &valu) throw(std::invalid_argument){
    if(type==comment){
#ifdef DEBUG
        std::cout << "can't change comment entry type" << std::endl;
#endif
        throw std::invalid_argument(this->read() + " = "+ valu);
    }
    std::string tmp = name + " = " + valu;
    if(identify(tmp)==typ) {
        type = typ;
        value = valu;
    } else{
#ifdef DEBUG
        std::cout << "new value type and new type are not equal" << std::endl;
#endif
        throw std::invalid_argument(tmp);
    }
}

void Ini_entry::set_value(std::string valu) throw(std::invalid_argument){
    if(type!=comment) {
        std::string tmp = name + " = " + valu;
        if (identify(tmp) == type) {
            if (type==string_entry) {  // removing the ""
                valu.erase(valu.begin());
                valu.erase(--valu.end());
            }
            value = valu;
        } else {
#ifdef DEBUG
            std::cout << "new value type and current type are not equal" << std::endl;
#endif
            throw std::invalid_argument(tmp);
        }
    }else{
#ifdef DEBUG
        std::cout << "can't change comment value!" << std::endl;
#endif
        throw std::invalid_argument(this->read() + " = "+ valu);
    }
}
