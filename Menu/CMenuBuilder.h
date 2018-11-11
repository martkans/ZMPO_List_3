//
// Created by martkans on 10.11.18.
//

#ifndef LISTA3_CMENUBUILDER_H
#define LISTA3_CMENUBUILDER_H

#define LEFT_BRACKET            '('
#define RIGHT_BRACKET           ')'
#define LEFT_QUADRATIC_BRACKET  '['
#define RIGHT_QUADRATIC_BRACKET ']'
#define SEMICOLON               ';'
#define COMMA                   ','
#define APOSTROPHE              '\''

#define POSITION_MENU_NAME      0
#define POSITION_MENU_COMMAND   1

#define POSITION_MENU_COMMAND_NAME                  0
#define POSITION_MENU_COMMAND_COMMAND               1
#define POSITION_MENU_COMMAND_HELP                  2
#define POSITION_MENU_COMMAND_CLOSE_BRACKET         3

#define ZERO_LEVEL  0
#define EMPTY_PATH  ""

#define DEFAULT_MENU_NAME               "defmenu"
#define DEFAULT_MENU_COMMAND            "defmenucomm"
#define DEFAULT_MENU_COMMAND_NAME       "defcommand"
#define DEFAULT_MENU_COMMAND_COMMAND    "defcommandcomm"
#define DEFAULT_MENU_COMMAND_HELP       "defhelp"

#define NOT_ALLOWED_VALUE_OUTSIDE_APOSTROPHES   "Niedozwolona wartość po za apostrofami: "
#define EXPECTED_VALUE                          "Oczekiwana wartość: "
#define UNEXPECTED_VALUE                        "Nieoczekiwana wartość: "

#include <string>
#include <vector>
#include "Menu.h"

using namespace std;

class CMenuBuilder {
    public:
        static CMenu* buildMenuFromString(string menu);

    private:
        static CMenu* createCMenuObject(vector <string> menu_info, int &pos_to_interpretation, bool &error);
        static CMenuCommand* createCMenuCommandObject(vector <string> menu_info, int &pos_to_interpretation, bool &error);

        static vector <string> processString(string inscription, vector<int> &indexes_vector, bool &error, int &error_index);
        static bool validate(string item, int suggested_role_of_item);
        static bool isSemicolon(string item);
};


#endif //LISTA3_CMENUBUILDER_H
