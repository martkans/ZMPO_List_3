//
// Created by martkans on 10.11.18.
//

#include "CMenuBuilder.h"

CMenu *CMenuBuilder::buildMenu() {
    CTableHandler* table_handler = new CTableHandler();
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
    main_menu->run();
    cout << main_menu->saveMenu();

    delete table_handler;
    delete main_menu;
}

CMenu *CMenuBuilder::buildMenuFromString(string menu) {
    CMenu* main_menu;
    bool error = false;
    int error_index, pos_to_interpretation = 0;
    vector <int> elements_indexes;
    vector <string> menu_info = processString(menu, elements_indexes, error, error_index);


    if (error){
        alert(NOT_ALLOWED_VALUE_OUTSIDE_APOSTROPHES + menu.substr(error_index, menu.length() - error_index));
    } else {
        if (!menu_info.empty()){
            if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
                main_menu = createCMenuObject(menu_info, ++pos_to_interpretation, error);
                if(error){

                    if(pos_to_interpretation == menu_info.size()){
                        alert(ODD_NUMBER_OF_BRACKETS + menu + "\n");
                    } else {
                        alert(UNEXPECTED_VALUE +
                              menu.substr(elements_indexes.at(pos_to_interpretation), menu.length() - elements_indexes.at(pos_to_interpretation)) + "\n");
                    }

                    delete main_menu;
                    return NULL;
                }

                if(pos_to_interpretation < menu_info.size()){
                    warning(elements_indexes, pos_to_interpretation, menu);
                }

                main_menu->prepareMenu(ZERO_LEVEL, EMPTY_PATH, main_menu);
            } else {
                alert(NOT_ALLOWED_VALUE_OUTSIDE_APOSTROPHES +
                      menu.substr(elements_indexes.at(pos_to_interpretation), menu.length() - elements_indexes.at(pos_to_interpretation)) + "\n"
                      EXPECTED_VALUE + convertCharToString(LEFT_BRACKET));
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

            while (checkIfMissRigthBracket(menu_info, pos_to_interpretation, error) && menu_info.at(pos_to_interpretation) != convertCharToString(RIGHT_BRACKET) ){
                if(!error){
                    if(menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_BRACKET)){
                        menu->addCMenuItem(createCMenuObject(menu_info, ++pos_to_interpretation, error));
                    } else if (menu_info.at(pos_to_interpretation) == convertCharToString(LEFT_QUADRATIC_BRACKET)){
                        menu->addCMenuItem(createCMenuCommandObject(menu_info, ++pos_to_interpretation, error));
                    } else {
                        error = true;
                        return menu;
                    }
                } else {
                    return menu;
                }
            }
            pos_to_interpretation++;
        } else {
            pos_to_interpretation--;
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
        pos_to_interpretation--;
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

bool CMenuBuilder::checkIfMissRigthBracket(vector<string> menu_info, int &pos_to_interpretation, bool &error) {
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
