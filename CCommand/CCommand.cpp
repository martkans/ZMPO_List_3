//
// Created by martkans on 19.10.18.
//

#include "CCommand.h"

/*CCommand*/

CCommand::~CCommand() {
    cout << "usuwam CCommand\n";
}

void CCommand::runCommand() {
    cout << "Komenda domyślna\n";
}

/*CCommandChangeObjectName*/

CCommandChangeObjectName::CCommandChangeObjectName(CTableHandler* table_handler){
    this->table_handler = table_handler;
}

CCommandChangeObjectName::~CCommandChangeObjectName() {
    cout << "usuwam CCommandChangeObjectName\n";
}

void CCommandChangeObjectName::runCommand() {
    bool* error = new bool();
    int position_of_object;
    string name;

    if(table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, którego chcesz zmienić nazwę (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if (*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            cout << "\nPodaj nową nazwę obiektu: ";
            getline(cin, name);

            table_handler->changeNameOfObject(position_of_object, name);
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandChangeTableSize*/

CCommandChangeTableSize::CCommandChangeTableSize(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandChangeTableSize::~CCommandChangeTableSize() {
    cout << "usuwam CCommandChangeTableSize\n";
}

void CCommandChangeTableSize::runCommand() {
    bool* error = new bool();
    int position_of_object;
    int table_length;

    if(table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, którego chcesz zmienić rozmiar (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if (*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            cout << "\nPodaj nowy rozmiar tablicy obiektu (1 - " << INT_MAX
                 << ")\n";

            table_length = provideInt(1, INT_MAX, error);

            if (*error){
                alert(BAD_VALUE_ALERT_MESSAGE);
            } else {
                table_handler->changeSizeOfObject(position_of_object, table_length);
            }
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandCloneObject*/

CCommandCloneObject::CCommandCloneObject(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandCloneObject::~CCommandCloneObject() {
    cout << "usuwam CCommandCloneObject\n";
}

void CCommandCloneObject::runCommand() {
    bool* error = new bool();
    int position_of_object;

    if(table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, który chcesz sklonować (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if(*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            table_handler->cloneObject(position_of_object);
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandCreateDefaultObjects*/
CCommandCreateDefaultObjects::CCommandCreateDefaultObjects(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandCreateDefaultObjects::~CCommandCreateDefaultObjects() {
    cout << "usuwam CCommandCreateDefaultObjects\n";
}

void CCommandCreateDefaultObjects::runCommand() {
    bool* error = new bool();
    int number_of_objects;

    cout << "\nIle chcesz utworzyć obiektów?\n";
    number_of_objects = provideInt(1, INT_MAX, error);

    if (*error){
        alert(BAD_VALUE_ALERT_MESSAGE);
    } else {
        for (int i = 0; i < number_of_objects; ++i) {
            cout << "\nObiekt nr " << i+1 << "\n";
            table_handler->createDefaultObject();
        }
    }
    delete error;
}

/*CCommandCreateSpecificObjects*/
CCommandCreateSpecificObjects::CCommandCreateSpecificObjects(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandCreateSpecificObjects::~CCommandCreateSpecificObjects() {
    cout << "usuwam CCommandCreateSpecificObjects\n";
}


void CCommandCreateSpecificObjects::runCommand() {
    bool* error = new bool();
    int number_of_objects;

    cout << "\nIle chcesz utworzyć obiektów?\n";
    number_of_objects = provideInt(1, INT_MAX, error);

    if (*error){
        alert(BAD_VALUE_ALERT_MESSAGE);
    } else {
        for (int i = 0; i < number_of_objects; ++i) {
            string name;
            int table_length;

            cout << "\nObiekt nr " << i+1 << "\n";
            cout << "\nPodaj nazwę obiektu: ";
            getline(cin, name);

            cout << "\nPodaj długość tablicy obiektu: ";
            table_length = provideInt(1, INT_MAX, error);

            if (*error){
                alert(BAD_VALUE_ALERT_MESSAGE);
                --i;
            } else {
                table_handler->createPersonalizedObject(table_length, name);
            }

        }
    }

    delete error;
}

/*CCommandDeleteAllObjects*/

CCommandDeleteAllObjects::CCommandDeleteAllObjects(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandDeleteAllObjects::~CCommandDeleteAllObjects() {
    cout << "usuwam CCommandDeleteAllObjects\n";
}

void CCommandDeleteAllObjects::runCommand() {
    bool answer;
    bool* error = new bool();

    if (table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nCzy na pewno chcesz usunąć wszystkie obiekty? (t/n)\n";
        answer = provideYesOrNo(error);

        if(*error){
            alert(CONFIRMATION_ERROR_ALERT_MESSAGE);
        } else{
            if (answer) {
                table_handler->deleteAllObjects();
            }
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandDeleteSpecificObject*/

CCommandDeleteSpecificObject::CCommandDeleteSpecificObject(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandDeleteSpecificObject::~CCommandDeleteSpecificObject() {
    cout << "usuwam CCommandDeleteSpecificObject\n";
}

void CCommandDeleteSpecificObject::runCommand() {
    bool* error = new bool();
    int position_of_object;

    if (table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, który chcesz usunąć (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);
        if (*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else if(!*error){
            table_handler->deleteSpecificObject(position_of_object);
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandSetTableCellValue*/

CCommandSetTableCellValue::CCommandSetTableCellValue(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandSetTableCellValue::~CCommandSetTableCellValue() {
    cout << "usuwam CCommandSetTableCellValue\n";
}

void CCommandSetTableCellValue::runCommand() {
    bool* error = new bool();
    int position_of_object, cell_number, cell_value;

    if (table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, którego wartość komórki chcesz zmienić (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if(*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            cout << "\nPodaj nr komórki, której chcesz zmienić (0 - " << table_handler->getTableLastIndex(position_of_object)
                 << ")\n";
            cell_number = provideInt(0, table_handler->getTableLastIndex(position_of_object), error);

            if(*error){
                alert(BAD_VALUE_ALERT_MESSAGE);
            } else {
                cout << "\nPodaj nową wartość komórki.\n";
                cell_value = provideInt(INT_MIN, INT_MAX, error);

                if(*error){
                    alert(BAD_VALUE_ALERT_MESSAGE);
                } else {
                    table_handler->setValueOfObjectCell(position_of_object, cell_number, cell_value);
                }
            }
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}

/*CCommandShowAllCTableObjects*/

CCommandShowAllCTableObjects::CCommandShowAllCTableObjects(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandShowAllCTableObjects::~CCommandShowAllCTableObjects() {
    cout << "usuwam CCommandShowAllCTableObjects\n";
}

void CCommandShowAllCTableObjects::runCommand() {
    if (table_handler->getVectorLastIndex() != EMPTY_VECTOR) {
        cout << "\n" << table_handler->getShortInfoAboutAllObjects() << "\n";
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }
}


/*CCommandShowObjectInfo*/

CCommandShowObjectInfo::CCommandShowObjectInfo(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandShowObjectInfo::~CCommandShowObjectInfo() {
    cout << "usuwam CCommandShowObjectInfo\n";
}

void CCommandShowObjectInfo::runCommand() {
    bool* error = new bool();
    int position_of_object;

    if (table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, o którym informacje chcesz otrzymać (0 - " << table_handler->getVectorLastIndex()
             << ")\n";
        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if(*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            cout << "\n" << table_handler->getInfoAboutObject(position_of_object) << "\n";
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}


/*CCommandShowTree*/

CCommandShowTree::CCommandShowTree(CMenu *main_menu) {
    this->main_menu = main_menu;
}

CCommandShowTree::~CCommandShowTree() {
    cout << "usuwam CCommandShowTree\n";
}

void CCommandShowTree::runCommand() {
    int number_of_levels = main_menu->getMaxLevel(0) + 1;
    string** tree_menu = new string*[number_of_levels];

    for (int i = 0; i < number_of_levels; ++i) {
        tree_menu[i] = new string;
    }

    main_menu->buildLevel(tree_menu);

    for (int i = 0; i < number_of_levels; ++i) {
        cout << *(tree_menu[i]) << "\n";
        delete tree_menu[i];
    }

    delete[] tree_menu;
}

/*CCommandTest*/

CCommandTest::CCommandTest(CTableHandler *table_handler) {
    this->table_handler = table_handler;
}

CCommandTest::~CCommandTest() {
    cout << "usuwam CCommandTest\n";
}

void CCommandTest::runCommand() {
    bool* error = new bool();
    int position_of_object;

    if(table_handler->getVectorLastIndex() != EMPTY_VECTOR){
        cout << "\nPodaj nr obiektu, którego rozmiar chcesz zmienić (0 - " << table_handler->getVectorLastIndex()
             << ")\n";

        position_of_object = provideInt(0, table_handler->getVectorLastIndex(), error);

        if(*error){
            alert(BAD_VALUE_ALERT_MESSAGE);
        } else {
            table_handler->testObject(*table_handler->getObject(position_of_object));
        }
    } else {
        alert(NO_OBJECTS_ALERT_MESSAGE);
    }

    delete error;
}