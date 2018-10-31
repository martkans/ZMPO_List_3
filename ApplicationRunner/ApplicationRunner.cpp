//
// Created by martkans on 24.10.18.
//

#include "ApplicationRunner.h"

void start() {

    CTableHandler* table_handler = new CTableHandler();
    CMenuCommand* change_object_name_mc = new CMenuCommand("Zmień nazwę obiektu CTable", "change object name", new CCommandChangeObjectName(table_handler));
    CMenuCommand* change_table_size_mc = new CMenuCommand("Zmień rozmiar tablicy obiektu CTable", "change size", new CCommandChangeTableSize(table_handler));
    CMenuCommand* clone_table_mc = new CMenuCommand("Klonuj obiekt CTable", "clone", new CCommandCloneObject(table_handler));
    CMenuCommand* create_specific_objects_mc = new CMenuCommand("Utwórz spersonalizowane obiekty CTable", "create", new CCommandCreateSpecificObjects(table_handler));
    CMenuCommand* create_default_objects_mc = new CMenuCommand("Utwórz domyślne obiekty CTable", "create default", new CCommandCreateDefaultObjects(table_handler));
    CMenuCommand* delete_all_objects_mc = new CMenuCommand("Usuń wszystkie obiekty CTable", "delete", new CCommandDeleteAllObjects(table_handler));
    CMenuCommand* delete_specific_object_mc = new CMenuCommand("Usuń określony obiekt CTable", "delete specific", new CCommandDeleteSpecificObject(table_handler));
    CMenuCommand* set_table_cell_value_mc = new CMenuCommand("Ustaw wartość określonej komórki CTable", "set", new CCommandSetTableCellValue(table_handler));
    CMenuCommand* show_all_ctable_objects_mc = new CMenuCommand("Pokaż wszystkie obiekty CTable", "show all", new CCommandShowAllCTableObjects(table_handler));
    CMenuCommand* show_object_info_mc = new CMenuCommand("Pokaż info o specyficznym obiekcie CTable", "show", new CCommandShowObjectInfo(table_handler));
    CMenuCommand* test_mc = new CMenuCommand("Test", "test", new CCommandTest(table_handler));


    CMenu* ctable_create_menu = new CMenu("Utwórz obiekty" , "create menu");
    ctable_create_menu->addCMenuItem(create_default_objects_mc);
    ctable_create_menu->addCMenuItem(create_specific_objects_mc);
    ctable_create_menu->addCMenuItem(clone_table_mc);
    ctable_create_menu->addCMenuItem(new CMenuCommand("Klonuj obiekt CTable", "cloe", new CCommandCloneObject(table_handler)));

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


    CMenuCommand* default_mc = new CMenuCommand("Domyślne polecenie", "defcom", new CCommand());
    CMenuCommand* without_command_mc = new CMenuCommand("Menu command bez polecenia", "without");

    CMenu* main_menu = new CMenu("Menu główne", "main");
    main_menu->addCMenuItem(ctable_create_menu);
    main_menu->addCMenuItem(ctable_menu);
    main_menu->addCMenuItem(default_mc);
    main_menu->addCMenuItem(without_command_mc);
    main_menu->addCMenuItem(new CMenuCommand("Wypisz drzewo menu", "tree", new CCommandShowTree(main_menu)));

    main_menu->setLevel(0);
    main_menu->run();

    delete table_handler;
    delete main_menu;

}
