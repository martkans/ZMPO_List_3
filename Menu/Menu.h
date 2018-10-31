//
// Created by martkans on 29.10.18.
//
#define BACK_STRING                 "back"
#define BAD_VALUE_ALERT_MESSAGE     "Podano błędną wartość.\n"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef LISTA3_CMENUITEM_H
#define LISTA3_CMENUITEM_H

class CMenuItem {
public:
    friend class CMenu;
    virtual ~CMenuItem(){};

protected:
    string name;
    string command;
    int level;

    virtual void run() = 0;

    virtual int getMaxLevel(int max) = 0;
    virtual void setLevel(int level) = 0;
    virtual void buildLevel(string** tree_menu) = 0;
};


#endif //LISTA3_CMENUITEM_H

#ifndef LISTA3_CMENU_H
#define LISTA3_CMENU_H

class CMenu : public CMenuItem{
public:
    CMenu(string name, string command);
    ~CMenu();

    void run();

    bool addCMenuItem(CMenuItem* item);
    bool deleteCMenuItem(string command_of_object_to_delete);

    int getMaxLevel(int max);
    void setLevel(int level);
    void buildLevel(string** tree_menu);

private:
    bool* error;
    vector <CMenuItem*> menu_items;

    void showMenu();
    bool checkIfUnique(string new_name, string new_command);
    unsigned long getPositionOfCMenuItem(string command, bool* error);
};

#endif //LISTA3_CMENU_H

#ifndef LISTA3_CMENUCOMMAND_H
#define LISTA3_CMENUCOMMAND_H

#include "../CCommand/CCommand.h"

class CMenuCommand : public CMenuItem{
public:
    CMenuCommand(string name, string command, CCommand* command_object);
    CMenuCommand(string name, string command);

    ~CMenuCommand();
    void run();

    int getMaxLevel(int max);
    void setLevel(int level);
    void buildLevel(string** tree_menu);

private:
    CCommand* command_object;

};


#endif //LISTA3_CMENUCOMMAND_H