//
// Created by martkans on 24.10.18.
//

#include "ApplicationRunner.h"

void start() {
    CTableHandler* table_handler = new CTableHandler();
    CMenu* main_menu = CMenuBuilder::buildCTableMenu(table_handler);

    if(main_menu != NULL){
        main_menu->run();
        writeToFile("ala.txt",main_menu->saveMenu());
        delete main_menu;
    }

    delete table_handler;
}

void start(string file_name) {
    CMenu* main_menu = CMenuBuilder::buildMenuFromString(loadFromFile(file_name));
    if(main_menu != NULL){
        main_menu->run();
        writeToFile("ala.txt", main_menu->saveMenu());
        delete main_menu;
    }
}


