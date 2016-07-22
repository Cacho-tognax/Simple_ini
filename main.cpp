//
// Created by stefano lavori on 08/07/2016.
//

#include <string>
#include <iostream>

#include "Ini_manager.h"


int main(){
    Ini_manager boh("Saving test file.ini");
    boh.close_file();
    boh.open_file("Test.ini");
    boh.read();
    return 0;
}