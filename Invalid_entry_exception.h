//
// Created by stefano lavori on 10/07/2016.
//

#ifndef SIMPLE_INI_INVALID_ENTRY_EXEPTION_H
#define SIMPLE_INI_INVALID_ENTRY_EXEPTION_H

#include <exception>
#include <string>

class Invalid_entry_exception : public std::exception {
public:
    Invalid_entry_exception(std::string req): requested(req){

    }
    std::string requested;

};


#endif //SIMPLE_INI_INVALID_ENTRY_EXEPTION_H
