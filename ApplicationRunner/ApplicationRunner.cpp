//
// Created by martkans on 24.10.18.
//

#include "ApplicationRunner.h"

void start() {

    CTableHandler* table_handler = new CTableHandler();
    CMenuCommand* change_object_name_mc = new CMenuCommand("Zmień nazwę obiektu CTable", "change object name", TEST_HELP, new CCommandChangeObjectName(table_handler));
    CMenuCommand* change_table_size_mc = new CMenuCommand("Zmień rozmiar tablicy obiektu CTable", "change size", TEST_HELP, new CCommandChangeTableSize(table_handler));
    CMenuCommand* clone_table_mc = new CMenuCommand("Klonuj obiekt CTable", "clone", TEST_HELP, new CCommandCloneObject(table_handler));
    CMenuCommand* create_specific_objects_mc = new CMenuCommand("Utwórz spersonalizowane obiekty CTable", "create", TEST_HELP, new CCommandCreateSpecificObjects(table_handler));
    CMenuCommand* create_default_objects_mc = new CMenuCommand("Utwórz domyślne obiekty CTable", "create default", TEST_HELP, new CCommandCreateDefaultObjects(table_handler));
    CMenuCommand* delete_all_objects_mc = new CMenuCommand("Usuń wszystkie obiekty CTable", "delete", TEST_HELP, new CCommandDeleteAllObjects(table_handler));
    CMenuCommand* delete_specific_object_mc = new CMenuCommand("Usuń określony obiekt CTable", "delete specific", TEST_HELP, new CCommandDeleteSpecificObject(table_handler));
    CMenuCommand* set_table_cell_value_mc = new CMenuCommand("Ustaw wartość określonej komórki CTable", "set", TEST_HELP, new CCommandSetTableCellValue(table_handler));
    CMenuCommand* show_all_ctable_objects_mc = new CMenuCommand("Pokaż wszystkie obiekty CTable", "show all", TEST_HELP, new CCommandShowAllCTableObjects(table_handler));
    CMenuCommand* show_object_info_mc = new CMenuCommand("Pokaż info o specyficznym obiekcie CTable", "show", TEST_HELP, new CCommandShowObjectInfo(table_handler));
    CMenuCommand* test_mc = new CMenuCommand("Test", "test", TEST_HELP, new CCommandTest(table_handler));


    CMenu* ctable_create_menu = new CMenu("Utwórz obiekty" , "create menu");
    ctable_create_menu->addCMenuItem(create_default_objects_mc);
    ctable_create_menu->addCMenuItem(create_specific_objects_mc);
    ctable_create_menu->addCMenuItem(clone_table_mc);
    ctable_create_menu->addCMenuItem(new CMenuCommand("Klonuj obiekt CTable", "cloe", TEST_HELP, new CCommandCloneObject(table_handler)));

    CMenu* ctable_menu = new CMenu("CTable menu", "ctable");
//    ctable_menu->addCMenuItem(ctable_create_menu);
    ctable_menu->addCMenuItem(change_object_name_mc);
    ctable_menu->addCMenuItem(change_table_size_mc);
    ctable_menu->addCMenuItem(delete_all_objects_mc);
    ctable_menu->addCMenuItem(delete_specific_object_mc);
    ctable_menu->addCMenuItem(set_table_cell_value_mc);
    ctable_menu->addCMenuItem(show_all_ctable_objects_mc);
    ctable_menu->addCMenuItem(show_object_info_mc);
    ctable_menu->addCMenuItem(test_mc);
    ctable_menu->addCMenuItem(new CMenuCommand("a", "defcom",TEST_HELP ,new CCommand()));


    CMenuCommand* default_mc = new CMenuCommand("Domyślne polecenie", "defcom", TEST_HELP, new CCommand());
    CMenuCommand* without_command_mc = new CMenuCommand("Menu command bez polecenia", "without", TEST_HELP);

    CMenu* main_menu = new CMenu("Menu główne", "main");
    main_menu->addCMenuItem(ctable_create_menu);
    main_menu->addCMenuItem(ctable_menu);
    main_menu->addCMenuItem(default_mc);
    main_menu->addCMenuItem(without_command_mc);
    main_menu->addCMenuItem(new CMenuCommand("Wypisz drzewo menu", "tree", TEST_HELP, new CCommandShowTree(main_menu)));

    main_menu->prepareMenu(ZERO_LEVEL, EMPTY_PATH, main_menu);
    main_menu->run();

    delete table_handler;
    delete main_menu;

}
