//
// Created by martkans on 29.10.18.
//

#include "Menu.h"

/*CMenuCommand*/

CMenuCommand::CMenuCommand(string name, string command, CCommand *command_object) {
    this->name = name;
    this->command = command;
    this->level = 0;
    this->command_object = command_object;
}

CMenuCommand::CMenuCommand(string name, string command) {
    this->name = name;
    this->command = command;
    this->level = 0;
    this->command_object = NULL;
}

CMenuCommand::~CMenuCommand() {
    delete command_object;
    cout << "usuwam CMenuCommand: " + command + "\n";
}

void CMenuCommand::run() {
    if (command_object == NULL){
        cout << "pusta komenda\n";
    } else {
        command_object->runCommand();
    }
}

void CMenuCommand::setLevel(int level) {
    this->level = level;
}

int CMenuCommand::getMaxLevel(int max) {
    if(this->level > max){
        max = this->level;
    }
    return max;
}

void CMenuCommand::buildLevel(string **tree_menu) {
    *(tree_menu[level]) += command + " ";
}


/*CMenu*/

CMenu::CMenu(string name, string command) {
    this->name = name;
    this->command = command;
    this->level = 0;
    error = new bool();
}

CMenu::~CMenu() {
    delete error;

    while (!menu_items.empty()){
        delete menu_items.at(0);
        menu_items.erase(menu_items.begin());
    }

    cout << "usuwam CMenu: " + name + "\n";
}

bool CMenu::addCMenuItem(CMenuItem *item) {
    if(checkIfUnique(item->name, item->command)){
        menu_items.push_back(item);
        return true;
    } else {
        return false;
    }
}

bool CMenu::deleteCMenuItem(string command_of_object_to_delete) {
    unsigned long pos = getPositionOfCMenuItem(command_of_object_to_delete, error);
    if(!*error){
        delete menu_items.at(pos);
        menu_items.erase(menu_items.begin() + pos);
        return true;
    }
    return false;
}

void CMenu::run() {
    string input;
    unsigned long pos;

    do{
        showMenu();

        cout << "\nWprowadz komende:\n";
        getline(cin, input);

        if(input != BACK_STRING){
            pos = getPositionOfCMenuItem(input, error);

            if(!*error){
                menu_items.at(pos)->run();
            } else {
                alert(BAD_VALUE_ALERT_MESSAGE);
            }
        } else {
            cout << "\ncofnij\n\n";
        }

    }while (input != BACK_STRING);
}

int CMenu::getMaxLevel(int max) {
    if(max < this->level){
        max = this->level;
    }

    for (int i = 0; i < menu_items.size(); ++i) {
        max = menu_items.at(i)->getMaxLevel(max);
    }

    return max;
}

void CMenu::setLevel(int level) {
    this->level = level;
    for (unsigned int i = 0; i < menu_items.size(); ++i) {
        menu_items.at(i)->setLevel(level+1);
    }
}

void CMenu::buildLevel(string **tree_menu) {
    *(tree_menu[level]) += command + " ";
    for (int i = 0; i < menu_items.size(); ++i) {
        menu_items.at(i)->buildLevel(tree_menu);
    }
}

void CMenu::showMenu() {
    cout    << "\n\n" << this->name << " (" << this->command << ")\n"
            << "------------------------\n";

    if(!menu_items.empty()){
        for (unsigned long i = 0; i < menu_items.size(); ++i) {
            cout << i+1 << ". " << menu_items.at(i)->name << " (" << menu_items.at(i)->command << ")\n";
        }
    }
}

bool CMenu::checkIfUnique(string new_name, string new_command) {
    for(unsigned long i = 0; i != menu_items.size(); ++i){
        if(menu_items.at(i)->name == new_name || menu_items.at(i)->command == new_command){
            return false;
        }
    }

    return true;
}

unsigned long CMenu::getPositionOfCMenuItem(string command, bool* error) {
    *error = false;
    for(unsigned long i = 0; i != menu_items.size(); ++i){
        if(menu_items.at(i)->command == command){
            return i;
        }
    }
    *error = true;
    return 0;
}