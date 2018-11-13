//
// Created by martkans on 24.10.18.
//

#include "ApplicationRunner.h"

void start() {
    CMenuBuilder::buildMenu();
}

void start(string menu) {
    CMenu* main_menu = CMenuBuilder::buildMenuFromString(menu);
    if(main_menu != NULL){
        main_menu->run();
    }
    delete main_menu;
}


