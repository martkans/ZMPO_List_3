//
// Created by martkans on 10.11.18.
//

#include "CMenuBuilder.h"

CMenu *CMenuBuilder::buildCTableMenu(CTableHandler* table_handler) {
    CMenuCommand* change_object_name_mc = new CMenuCommand("Zmień nazwę obiektu CTable", "change object name", "Zmienia nazwę",
            new CCommandChangeObjectName(table_handler));
    CMenuCommand* change_table_size_mc = new CMenuCommand("Zmień rozmiar tablicy obiektu CTable", "change size",
            "Zmienia rozmiar tablicy", new CCommandChangeTableSize(table_handler));
    CMenuCommand* clone_table_mc = new CMenuCommand("Klonuj obiekt CTable", "clone", "Klonuje obiekt",
            new CCommandCloneObject(table_handler));
    CMenuCommand* create_specific_objects_mc = new CMenuCommand("Utwórz spersonalizowane obiekty CTable", "create",
            "Tworzy personalizowane obiekty CTable", new CCommandCreateSpecificObjects(table_handler));
    CMenuCommand* create_default_objects_mc = new CMenuCommand("Utwórz domyślne obiekty CTable", "create default",
            "Tworzy domyślny obiekt", new CCommandCreateDefaultObjects(table_handler));
    CMenuCommand* delete_all_objects_mc = new CMenuCommand("Usuń wszystkie obiekty CTable", "delete", "Kasuje wszystkie obiekty",
            new CCommandDeleteAllObjects(table_handler));
    CMenuCommand* delete_specific_object_mc = new CMenuCommand("Usuń określony obiekt CTable", "delete specific",
            "Usuwa określony obiekt", new CCommandDeleteSpecificObject(table_handler));
    CMenuCommand* set_table_cell_value_mc = new CMenuCommand("Ustaw wartość określonej komórki CTable", "set",
            "Ustawia wartość wybranej komórki", new CCommandSetTableCellValue(table_handler));
    CMenuCommand* show_all_ctable_objects_mc = new CMenuCommand("Pokaż wszystkie obiekty CTable", "show all",
            "Pokazuje informacje o wszystkich obiektach", new CCommandShowAllCTableObjects(table_handler));
    CMenuCommand* show_object_info_mc = new CMenuCommand("Pokaż info o specyficznym obiekcie CTable", "show",
            "Pokazuje informacje o konkretnym obiekcie", new CCommandShowObjectInfo(table_handler));
    CMenuCommand* test_mc = new CMenuCommand("Test", "test", "Test z listy 1", new CCommandTest(table_handler));


    CMenu* ctable_create_menu = new CMenu("Utwórz obiekty" , "create menu");
    ctable_create_menu->addCMenuItem(create_default_objects_mc);
    ctable_create_menu->addCMenuItem(create_specific_objects_mc);
    ctable_create_menu->addCMenuItem(clone_table_mc);

    CMenu* ctable_menu = new CMenu("CTable menu", "ctable");
    ctable_menu->addCMenuItem(change_object_name_mc);
    ctable_menu->addCMenuItem(change_table_size_mc);
    ctable_menu->addCMenuItem(delete_all_objects_mc);
    ctable_menu->addCMenuItem(delete_specific_object_mc);
    ctable_menu->addCMenuItem(set_table_cell_value_mc);
    ctable_menu->addCMenuItem(show_all_ctable_objects_mc);
    ctable_menu->addCMenuItem(show_object_info_mc);
    ctable_menu->addCMenuItem(test_mc);
    ctable_menu->addCMenuItem(new CMenuCommand("Domyślne polecenie", "defcom","Domyślna komenda" ,new CCommand()));


    CMenuCommand* default_mc = new CMenuCommand("Domyślne polecenie", "defcom", "Domyślna komenda", new CCommand());
    CMenuCommand* without_command_mc = new CMenuCommand("Menu command bez polecenia", "without", "Menu Command bez polecenia");

    CMenu* main_menu = new CMenu("Menu główne", "main");
    main_menu->addCMenuItem(ctable_create_menu);
    main_menu->addCMenuItem(ctable_menu);
    main_menu->addCMenuItem(default_mc);
    main_menu->addCMenuItem(without_command_mc);
    main_menu->addCMenuItem(new CMenuCommand("Wypisz drzewo menu", "tree", "Wypisuje drzewo menu", new CCommandShowTree(main_menu)));

    main_menu->prepareMenu(ZERO_LEVEL, EMPTY_PATH, main_menu);

    return main_menu;

}

CMenu *CMenuBuilder::buildMenuFromString(string menu) {
    CMenu* main_menu = NULL;
    bool error = false;
    int pos_to_interpretation = 0;
    vector <int> elements_indexes;
    vector <string> menu_info = processString(menu, elements_indexes);


    if (!menu_info.empty()){
        if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
            main_menu = createCMenuObject(menu, menu_info, elements_indexes, ++pos_to_interpretation, error);
            if(error){
                if(pos_to_interpretation == menu_info.size()){
                    alert(ODD_NUMBER_OF_BRACKETS + menu + "\n");
                }

                delete main_menu;
                return NULL;
            }

            if(pos_to_interpretation < menu_info.size()){
                warning(elements_indexes, pos_to_interpretation, menu);
            }

            main_menu->prepareMenu(ZERO_LEVEL, EMPTY_PATH, main_menu);
        } else {
            expectedValueAlert(convertCharToString(LEFT_BRACKET), menu, elements_indexes, pos_to_interpretation);
        }
    }

    return main_menu;
}

CMenu *CMenuBuilder::createCMenuObject(string &menu, vector <string> &menu_info, vector <int> &elements_indexes, int &pos_to_interpretation, bool &error) {
    CMenu* sub_menu = new CMenu(DEFAULT_MENU_NAME, DEFAULT_MENU_COMMAND);
    int temp_pos = pos_to_interpretation;

    if(!error){
        if(validate(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation)) &&
           isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), COMMA) &&
           validate(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation)) &&
           isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), SEMICOLON)){

            bool isExpectedFirstChild = true;

            sub_menu->name = removeApostrophes(menu_info.at(temp_pos + POSITION_MENU_NAME));
            sub_menu->command = removeApostrophes(menu_info.at(temp_pos + POSITION_MENU_COMMAND));

            while (checkIfIsntMissRigthBracket(menu_info, pos_to_interpretation, error) && menu_info.at(pos_to_interpretation) != convertCharToString(RIGHT_BRACKET) ){
                if(!error){
                    if(isExpectedFirstChild || isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), COMMA)){
                        if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
                            isExpectedFirstChild = false;
                            sub_menu->addCMenuItem(createCMenuObject(menu, menu_info, elements_indexes,++pos_to_interpretation, error));
                        } else if (menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_QUADRATIC_BRACKET)){
                            isExpectedFirstChild = false;
                            sub_menu->addCMenuItem(createCMenuCommandObject(menu, menu_info, elements_indexes,++pos_to_interpretation, error));
                        } else {
                            if (isExpectedFirstChild){
                                expectedValueAlert(convertCharToString(LEFT_BRACKET) + " " + convertCharToString(LEFT_QUADRATIC_BRACKET) + " " + convertCharToString(RIGHT_BRACKET),
                                                   menu, elements_indexes, pos_to_interpretation);
                            } else {
                                expectedValueAlert(convertCharToString(LEFT_BRACKET) + "  " + convertCharToString(LEFT_QUADRATIC_BRACKET), menu, elements_indexes, pos_to_interpretation);
                            }

                            error = true;
                            return sub_menu;
                        }
                    } else {
                        error = true;
                        pos_to_interpretation--;
                        expectedValueAlert(convertCharToString(COMMA) + " " + convertCharToString(RIGHT_BRACKET),
                                           menu, elements_indexes, pos_to_interpretation);
                        return sub_menu;
                    }
                } else {
                    return sub_menu;
                }
            }
            pos_to_interpretation++;
        } else {
            pos_to_interpretation--;

            switch (pos_to_interpretation - temp_pos){
                case POSITION_MENU_NAME:
                    expectedValueAlert("'<nazwa menu>'", menu, elements_indexes, pos_to_interpretation);
                    break;
                case POSITION_MENU_COMMAND:
                    expectedValueAlert("'<polecenie menu>'", menu, elements_indexes, pos_to_interpretation);
                    break;
                case POSITION_SEMICOLON:
                    expectedValueAlert(convertCharToString(SEMICOLON), menu, elements_indexes, pos_to_interpretation);
                    break;
                default:
                    expectedValueAlert(convertCharToString(COMMA), menu, elements_indexes, pos_to_interpretation);
            }
            error = true;
        }
    }

    return sub_menu;
}

CMenuCommand *CMenuBuilder::createCMenuCommandObject(string &menu, vector <string> &menu_info, vector <int> &elements_indexes, int &pos_to_interpretation, bool &error) {
    CMenuCommand* menu_command = new CMenuCommand(DEFAULT_MENU_COMMAND_NAME, DEFAULT_MENU_COMMAND_COMMAND, DEFAULT_MENU_COMMAND_HELP);
    int temp_pos = pos_to_interpretation;

    if (validate(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation)) &&
        isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), COMMA) &&
        validate(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation)) &&
        isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), COMMA) &&
        validate(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation)) &&
        isExpectedSign(getNextVectorItemIfExist(menu, menu_info, elements_indexes, pos_to_interpretation), RIGHT_QUADRATIC_BRACKET)){

        menu_command->name = removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_NAME));
        menu_command->command =removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_COMMAND));
        menu_command->help_message = removeApostrophes(menu_info.at(temp_pos+POSITION_MENU_COMMAND_HELP));

    } else  {
        pos_to_interpretation--;


        switch (pos_to_interpretation - temp_pos){
            case POSITION_MENU_COMMAND_NAME:
                expectedValueAlert("'<nazwa komendy>'", menu, elements_indexes, pos_to_interpretation);
                break;
            case POSITION_MENU_COMMAND_COMMAND:
                expectedValueAlert("'<polecenie komendy>'", menu, elements_indexes, pos_to_interpretation);
                break;
            case POSITION_MENU_COMMAND_HELP:
                expectedValueAlert("'<pomoc komendy>'", menu, elements_indexes, pos_to_interpretation);
                break;
            case POSITION_MENU_COMMAND_CLOSE_BRACKET:
                expectedValueAlert(convertCharToString(RIGHT_QUADRATIC_BRACKET), menu, elements_indexes, pos_to_interpretation);
                break;
            default:
                expectedValueAlert(convertCharToString(COMMA), menu, elements_indexes, pos_to_interpretation);
        }

        error = true;
    }
    return menu_command;
}


vector<string> CMenuBuilder::processString(string inscription, vector<int> &indexes_vector) {
    bool is_between_apostrophes = false, is_word_outside_apostrophes = false;
    vector <string> info;
    string buffer;

    for (int i = 0; i < inscription.length(); ++i) {
        char sign = inscription.at(i);

        if (is_between_apostrophes) {
            if (sign == APOSTROPHE) {
                buffer += sign;
                info.push_back(buffer);
                buffer = "";
                is_between_apostrophes = false;
            } else {
                buffer += sign;
            }
        } else if(is_word_outside_apostrophes) {
            if(sign == LEFT_BRACKET || sign == LEFT_QUADRATIC_BRACKET || sign == RIGHT_BRACKET || sign == RIGHT_QUADRATIC_BRACKET
               ||  sign == SEMICOLON || sign == COMMA || sign == APOSTROPHE){
                info.push_back(buffer);
                buffer = "";
                is_word_outside_apostrophes = false;

                if(sign == APOSTROPHE){
                    buffer += sign;
                    is_between_apostrophes = true;
                } else {
                    info.push_back(convertCharToString(sign));
                    indexes_vector.push_back(i);
                }

            } else {
                buffer += sign;
            }
        } else {
            if(sign == LEFT_BRACKET || sign == LEFT_QUADRATIC_BRACKET || sign == RIGHT_BRACKET || sign == RIGHT_QUADRATIC_BRACKET
               ||  sign == SEMICOLON || sign == COMMA){
                info.push_back(convertCharToString(sign));
                buffer = "";
            } else if(sign == APOSTROPHE){
                buffer = sign;
                is_between_apostrophes = true;
            } else {
                is_word_outside_apostrophes = true;
                buffer = sign;
            }
            indexes_vector.push_back(i);
        }
    }

    return info;
}


bool CMenuBuilder::validate(string item) {
    if(item.length() > 1 && item.at(0) == APOSTROPHE && item.at(item.size()-1) == APOSTROPHE){
        return true;
    }
    return false;
}

bool CMenuBuilder::isExpectedSign(string item, char expected_sign) {
    if(item == convertCharToString(expected_sign))
        return true;
    else return false;
}

bool CMenuBuilder::checkIfIsntMissRigthBracket(vector<string> &menu_info, int &pos_to_interpretation, bool &error) {
    if(pos_to_interpretation >= menu_info.size()){
        pos_to_interpretation--;
        error = true;
        return false;
    }
    return true;
}

void CMenuBuilder::warning(vector<int> elements_indexes, int pos_to_interpretation, string menu) {
    cout << "Menu zostało zainicjalizowane lecz pozostała część napisu do interpretacji: " +
            menu.substr(elements_indexes.at(pos_to_interpretation), menu.length() - elements_indexes.at(pos_to_interpretation)) + "\n";
}

void CMenuBuilder::expectedValueAlert(string expected_value, string &menu, vector <int> &elements_indexes, int &pos_to_interpretation) {
    alert(UNEXPECTED_VALUE +
          menu.substr(elements_indexes.at(pos_to_interpretation), menu.length() - elements_indexes.at(pos_to_interpretation)) + "\n");
    cout << EXPECTED_VALUE << expected_value + "\n";
}

string CMenuBuilder::getNextVectorItemIfExist(string &menu, vector<string> &menu_info, vector<int> &elements_indexes, int &pos_to_interpretation) {
    if(pos_to_interpretation < menu_info.size()){
        return menu_info.at(pos_to_interpretation++);
    } else {
        pos_to_interpretation++;
        elements_indexes.push_back(menu.size());
        menu_info.push_back("");
        return "";
    }
}
