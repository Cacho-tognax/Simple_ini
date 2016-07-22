//
// Created by stefano lavori on 10/07/2016.
//

#include"Ini_entry.h"




Ini_entry::Ini_entry(std::string entry) throw(Invalid_entry_exception){
    type=identify(entry);
    if (type==to_ignore||type==section_head){
        throw Invalid_entry_exception(entry);
    }
    std::string tmp="";
    auto itr=entry.begin();
    if (type==comment){
        itr++;
        for(; itr!=entry.end(); itr++)
            tmp+=(*itr);
        name=tmp;
        value="";
    } else {
        for (; (*itr) != equal_sign; itr++)
            tmp += (*itr);
        for (auto enditr = --tmp.end(); (*enditr)==space; enditr--) //removing spaces
            tmp.erase(enditr);
        name=tmp;
        tmp="";
        itr++;
        for(; (*itr)==space||(*itr)==equal_sign; itr++); //finding the end of the spaces
        if (type==string_entry){
            itr++;                                     //removing the ""
            for(; itr!=entry.end()&&(*itr)!=double_quotation_mark; itr++){
                tmp+=(*itr);
            }
        } else {
            for(; itr!=entry.end(); itr++){
                tmp+=(*itr);
            }
        }
        value=tmp;
    }

}

std::string Ini_entry::read() {

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

enum entry_type Ini_entry::identify(std::string entry) {
    auto itr = entry.begin();
    if (itr == entry.end())
        return to_ignore;
    char tmp = (*itr);
    if (tmp == exclamation_mark) {
        return comment;
    } else if (tmp == open_square_parenthesis) {    //must find closing or it's an ignored typo
        for (; itr != entry.end(); itr++) {
            if ((*itr) == close_square_parenthesis) {
                itr++;
                if (itr == entry.end())
                    return section_head;
            }
        }
        return to_ignore;
    } else {                         //attempting to understand entry type
        bool has_name=false;
        for (; (*itr) != equal_sign && itr != entry.end(); itr++) {   //finding end of entry name
            if ((*itr)!=space)
                has_name=true;
        }
        if(!has_name)
            return to_ignore;                         //name made only of spaces
        if (itr == entry.end())
            return to_ignore;          //invalid line, won't appear after saving
        itr++;
        if (itr == entry.end())
            return to_ignore;          //as above
        for (; (*itr) == space && itr != entry.end(); itr++);
        if (itr == entry.end())
            return to_ignore;
        tmp = (*itr);
        if (numbers_start <= tmp && tmp <= numbers_end) {     /* it's either an int or a float,
                                                                   * attempting to identify, if a non number is found
                                                                   * the line will be ignored
                                                                   */
            for (; itr != entry.end(); itr++) {
                tmp = (*itr);
                if ((tmp < numbers_start || tmp > numbers_end) && tmp != dot)
                    return to_ignore;       // non-number found
                if (tmp == dot) {
                    itr++;
                    for (; itr != entry.end(); itr++) {
                        tmp = (*itr);
                        if (tmp < numbers_start || numbers_end < tmp)
                            return to_ignore;
                    }
                    return float_entry;
                }
            }
            return int_entry;
        } else if (tmp == T_letter) {                        //it's bool or a typo?
            itr++;
            if (itr == entry.end())
                return to_ignore;                      //better safe than sorry!
            if (*itr == R_letter) {
                itr++;
                if (itr == entry.end())
                    return to_ignore;
                if (*itr == U_letter) {
                    itr++;
                    if (itr == entry.end())
                        return to_ignore;
                    if (*itr == E_letter) {
                        itr++;
                        if (itr == entry.end())
                            return bool_entry;
                        return to_ignore;
                    }
                }
            }
            return to_ignore;
        } else if (tmp == F_letter) {                        //same for false
            itr++;
            if (itr == entry.end())
                return to_ignore;
            if (*itr == A_letter) {
                itr++;
                if (itr == entry.end())
                    return to_ignore;
                if (*itr == L_letter) {
                    itr++;
                    if (itr == entry.end())
                        return to_ignore;
                    if (*itr == S_letter) {
                        itr++;
                        if (itr == entry.end())
                            return to_ignore;
                        if (*itr == E_letter) {
                            itr++;
                            if (itr == entry.end())
                                return bool_entry;
                            return to_ignore;
                        }
                    }
                }
            }
            return to_ignore;
        } else if (tmp == double_quotation_mark) {    //must find closing or it's an ignored typo
            for (; itr != entry.end(); itr++) {
                if ((*itr) == double_quotation_mark) {
                    itr++;
                    if (itr == entry.end())
                        return string_entry;
                }
            }
            return to_ignore;
        } else {
            return to_ignore;

        }
    }
}


