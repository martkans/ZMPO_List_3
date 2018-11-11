//
// Created by martkans on 10.11.18.
//

#include "CMenuBuilder.h"

CMenu *CMenuBuilder::buildMenuFromString(string menu) {
    CMenu* main_menu;
    bool error = false;
    int error_index, pos_to_interpretation = 0;
    vector <int> elements_indexes;
    vector <string> menu_info = processString(menu, elements_indexes, error, error_index);

    /*for (int i = 0; i < menu_info.size(); ++i) {
        cout << elements_indexes[i] << " " << menu_info.at(i) << "\n";
    }*/

    if (error){
        alert(NOT_ALLOWED_VALUE_OUTSIDE_APOSTROPHES + menu.substr(error_index - menu.length()));
    } else {
        if (!menu_info.empty()){
            if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
                main_menu = createCMenuObject(menu_info, ++pos_to_interpretation, error);
                if(error){
                    alert(UNEXPECTED_VALUE + menu.at(elements_indexes.at(pos_to_interpretation)));
                    delete main_menu;
                    return NULL;
                }
                main_menu->prepareMenu(ZERO_LEVEL, EMPTY_PATH, main_menu);
            } else {
                alert(NOT_ALLOWED_VALUE_OUTSIDE_APOSTROPHES + menu.at(elements_indexes.at(pos_to_interpretation)));
                alert(EXPECTED_VALUE + LEFT_BRACKET);
            }
        }
    }
    return main_menu;
}

CMenu *CMenuBuilder::createCMenuObject(vector<string> menu_info, int &pos_to_interpretation, bool &error) {
    CMenu* menu = new CMenu(DEFAULT_MENU_NAME, DEFAULT_MENU_COMMAND);
    int temp_pos = pos_to_interpretation;

    if(!error){
        if(validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_NAME) &&
           validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_COMMAND) &&
           isSemicolon(menu_info.at(pos_to_interpretation++))){

            menu->name = removeApostrophes(menu_info.at(temp_pos + POSITION_MENU_NAME));
            menu->command = removeApostrophes(menu_info.at(temp_pos + POSITION_MENU_COMMAND));

            while (menu_info.at(pos_to_interpretation) != convertCharToString(RIGHT_BRACKET)){
                if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
                    menu->addCMenuItem(createCMenuObject(menu_info, ++pos_to_interpretation, error));
                } else if (menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_QUADRATIC_BRACKET)){
                    menu->addCMenuItem(createCMenuCommandObject(menu_info, ++pos_to_interpretation, error));
                } else {
                    error = true;
                    return menu;
                }
            }
        } else {
            error = true;
        }
    }

    return menu;
}

CMenuCommand *CMenuBuilder::createCMenuCommandObject(vector<string> menu_info, int &pos_to_interpretation, bool &error) {
    CMenuCommand* menu_command = new CMenuCommand(DEFAULT_MENU_COMMAND_NAME, DEFAULT_MENU_COMMAND_COMMAND, DEFAULT_MENU_COMMAND_HELP);
    int temp_pos = pos_to_interpretation;

    if (validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_COMMAND_NAME) &&
        validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_COMMAND_COMMAND) &&
        validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_COMMAND_HELP) &&
        validate(menu_info.at(pos_to_interpretation++), POSITION_MENU_COMMAND_CLOSE_BRACKET)){

        menu_command->name = removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_NAME));
        menu_command->command =removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_COMMAND));
        menu_command->help_message = removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_HELP));

    } else  {
        error = true;
    }
    return menu_command;
}


vector<string> CMenuBuilder::processString(string inscription, vector<int> &indexes_vector, bool &error, int &error_index) {
    bool is_between_apostrophes = false;
    error = false;
    vector <string> info;
    string buffer;

    for (int i = 0; i < inscription.length(); ++i) {
        char sign = inscription.at(i);

        if (is_between_apostrophes){
            if (sign == APOSTROPHE){
                buffer += sign;
                info.push_back(buffer);
                buffer = "";
                is_between_apostrophes = false;
            } else {
                buffer += sign;
            }
        } else {
            if(sign == LEFT_BRACKET || sign == LEFT_QUADRATIC_BRACKET || sign == RIGHT_BRACKET || sign == RIGHT_QUADRATIC_BRACKET
               ||  sign == SEMICOLON){
                buffer = sign;
                info.push_back(buffer);
                buffer = "";
                indexes_vector.push_back(i);
            } else if(sign == APOSTROPHE){
                buffer += sign;
                is_between_apostrophes = true;
                indexes_vector.push_back(i);
            } else if(sign != COMMA){
                error = true;
                error_index = i;
                return info;
            }
        }
    }

    return info;
}


bool CMenuBuilder::validate(string item, int suggested_role_of_item) {
    if(suggested_role_of_item == POSITION_MENU_COMMAND_CLOSE_BRACKET){
        if (item.size() == 1){
            if(item.at(0) == RIGHT_QUADRATIC_BRACKET){
                return true;
            }
        }
    } else {
        if(item.at(0) == APOSTROPHE && item.at(item.size()-1) == APOSTROPHE){
            return true;
        }
    }

    return false;
}

bool CMenuBuilder::isSemicolon(string item) {
    if(item == convertCharToString(SEMICOLON))
        return true;
    else return false;
}
