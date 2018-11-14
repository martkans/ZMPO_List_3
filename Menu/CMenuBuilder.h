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
#define POSITION_MENU_COMMAND   2
#define POSITION_SEMICOLON      3

#define POSITION_MENU_COMMAND_NAME                  0
#define POSITION_MENU_COMMAND_COMMAND               2
#define POSITION_MENU_COMMAND_HELP                  4
#define POSITION_MENU_COMMAND_CLOSE_BRACKET         5

#define ZERO_LEVEL  0
#define EMPTY_PATH  ""

#define DEFAULT_MENU_NAME               "defmenu"
#define DEFAULT_MENU_COMMAND            "defmenucomm"
#define DEFAULT_MENU_COMMAND_NAME       "defcommand"
#define DEFAULT_MENU_COMMAND_COMMAND    "defcommandcomm"
#define DEFAULT_MENU_COMMAND_HELP       "defhelp"

#define EXPECTED_VALUE                          "Oczekiwana wartość: "
#define UNEXPECTED_VALUE                        "Nieoczekiwana wartość: "
#define ODD_NUMBER_OF_BRACKETS                  "Sprawdź parzystość nawiasów okrągłych. \n"

#include <string>
#include <vector>
#include "Menu.h"

using namespace std;

class CMenuBuilder {
    public:
        static CMenu* buildMenuFromString(string menu);
        static CMenu* buildCTableMenu(CTableHandler* table_handler);

    private:
        static CMenu* createCMenuObject(string &menu, vector <string> &menu_info, vector <int> &elements_indexes, int &pos_to_interpretation, bool &error);
        static CMenuCommand* createCMenuCommandObject(string &menu, vector <string> &menu_info, vector <int> &elements_indexes, int &pos_to_interpretation, bool &error);

        static vector <string> processString(string inscription, vector<int> &indexes_vector);
        static bool validate(string item);
        static bool isExpectedSign(string item, char expected_sign);
        static bool checkIfIsntMissRigthBracket(vector <string> &menu_info, int &pos_to_interpretation, bool &error);
        static void warning(vector<int> elements_indexes, int pos_to_interpretation, string menu);
        static void expectedValueAlert(string expected_value, string &menu, vector <int> &elements_indexes, int &pos_to_interpretation);
};


#endif //LISTA3_CMENUBUILDER_H
