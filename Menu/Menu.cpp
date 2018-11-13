//
// Created by martkans on 29.10.18.
//

#include "Menu.h"

/*CMenuCommand*/

CMenuCommand::CMenuCommand(string name, string command, string help_message, CCommand *command_object) {
    this->name = name;
    this->command = command;
    this->help_message = help_message;
    this->path = command;
    this->level = 0;
    this->main_menu = this;
    this->command_object = command_object;
}

CMenuCommand::CMenuCommand(string name, string command, string help_message) {
    this->name = name;
    this->command = command;
    this->help_message = help_message;
    this->path = command;
    this->level = 0;
    this->main_menu = this;
    this->command_object = NULL;
}

CMenuCommand::~CMenuCommand() {
    delete command_object;
    cout << "usuwam CMenuCommand: " + command + "\n";
}

void CMenuCommand::setHelp(string help) {
    this->help_message = help;
}

string CMenuCommand::getHelp() {
    return help_message;
}

void CMenuCommand::run() {
    if (command_object == NULL){
        cout << "pusta komenda\n";
    } else {
        command_object->runCommand();
    }
}

void CMenuCommand::prepareMenu(int level, string path, CMenuItem* main_menu) {
    this->level = level;
    this->path = path + " -> " + this->command;
    this->main_menu = main_menu;
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

string CMenuCommand::searchCommand(string command) {
    if(command == this->command){
        return path + "\n";
    }
    return "";
}

string CMenuCommand::saveMenu() {
    return "[\'" + this->name + "\',\'" + this->command + "\',\'" + this->help_message + "\']";
}

/*CMenu*/

CMenu::CMenu(string name, string command) {
    this->name = name;
    this->command = command;
    this->path = command;
    this->level = 0;
    this->main_menu = this;
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
            if(compareTo(input, HELP)) {
                pos = getPositionOfCMenuItem(input, error);
                if (!*error) {
                    cout << menu_items.at(pos)->getHelp() << "\n";
                }
            } else if (compareTo(input, SEARCH)) {
                string search_result = main_menu->searchCommand(input);
                if(search_result == ""){
                    *error = true;
                } else {
                    *error = false;
                    cout << search_result;
                }
            } else {
                pos = getPositionOfCMenuItem(input, error);
                if(!*error){
                    menu_items.at(pos)->run();
                }
            }
            if(*error){
                alert(BAD_VALUE_ALERT_MESSAGE);
            }
        } else {
            cout << "\ncofnij\n";
        }

    }while (input != BACK_STRING);
}

bool CMenu::compareTo(string &input, string expected_value) {
    if (input.compare(0,expected_value.length(),expected_value) == 0){
        input = input.substr(expected_value.length(), input.length());
        return true;
    }
    return false;
}

string CMenu::getHelp() {
    return HELP_ALERT_MESSAGE;
}

string CMenu::searchCommand(string command) {
    string path;
    if(command == this->command){
        path = this->path + "\n";
    }

    for (int i = 0; i < menu_items.size(); ++i) {
        path += menu_items.at(i)->searchCommand(command);
    }
    return path;
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

void CMenu::prepareMenu(int level, string path, CMenuItem* main_menu) {
    this->level = level;
    this->path = path + " -> " + this->command;
    this->main_menu = main_menu;
    for (unsigned int i = 0; i < menu_items.size(); ++i) {
        menu_items.at(i)->prepareMenu(level+1, this->path, main_menu);
    }
}

void CMenu::buildLevel(string **tree_menu) {
    *(tree_menu[level]) += command + " ";
    for (int i = 0; i < menu_items.size(); ++i) {
        menu_items.at(i)->buildLevel(tree_menu);
    }
}

void CMenu::showMenu() {
    cout    << "\n" << this->name << " (" << this->command << ")\n"
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

string CMenu::saveMenu() {
    string menu = "(\'" + this->name + "\',\'" + this->command + "\';";
    for (int i = 0; i < this->menu_items.size(); ++i) {
        if (i != 0){
            menu += ",";
        }
        menu += this->menu_items.at(i)->saveMenu();
    }

    return menu + ")";
}
