//
// Created by stefano lavori on 10/07/2016.
//

#include"Ini_entry.h"




Ini_entry::Ini_entry(std::string entry) { //TODO implement

}

std::string Ini_entry::read() {

    std::string return_string;
    if (type==comment) {
        return_string = "!" + name;
    }else {                                        //if not a comment, must be an entry
        return_string == name + " = " + value;
    }
    return return_string;

}

enum type Ini_entry::identify(std::string entry) {
    auto itr = entry.begin();
    char tmp = (*itr);
    if (tmp == exclamation_mark) {
        return comment;
    } else if (tmp == open_square_pharentesis) {    //must find closing or it's an ignored typo
        for (; itr != entry.end(); itr++) {
            if ((*itr) == close_square_pharentesis)
                return section_head;
        }
        return to_ignore;
    } else {                         //attempting to understand entry type
        for (; (*itr) != equal_sign && itr != entry.end(); itr++);  //finding end of entry name
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
                if ((tmp < numbers_start || numbers_end < tmp) && tmp!=dot)
                    return to_ignore;       // non-number found
                if (tmp == dot) {
                    itr++;
                    for (; itr != entry.end(); itr++) {
                        tmp=(*itr);
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
                        return bool_entry;            //anything after wil be ignored and won't appear after a save
                    }
                }
            }
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
                            return bool_entry;            //as above
                        }
                    }
                }
            }
        }

    }
    return to_ignore;
}


