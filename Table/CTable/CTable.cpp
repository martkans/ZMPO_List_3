//
// Created by martkans on 19.10.18.
//

#include "CTable.h"

CTable::CTable() {
    constructorHelper(DEFAULT_SIZE_OF_TABLE, DEFAULT_NAME_OF_OBJECT);
    cout << "\nbezp: '"<< name << "'\n";
}

CTable::CTable(int size_of_table, string new_name) {
    constructorHelper(size_of_table, new_name);
    cout << "\nparametr: '"<< name << "'\n";
}

CTable::CTable(CTable &object_to_copy) {
    constructorHelper(DEFAULT_SIZE_OF_TABLE, object_to_copy.name + "_copy");
    copyTableFromOtherObject(object_to_copy);
    cout << "\nkopiuj: '"<< name << "'\n";
}

CTable::~CTable() {
    delete[](table);
    cout << "\nusuwam: '" + name + "'";
}


void CTable::constructorHelper(int size, string name) {
    setName(name);
    table_size = size;
    table = new int[table_size];
    eraseTable(table, 0, table_size);
}


void CTable::setName(string new_name) {
    name = new_name;
}

string CTable::getName() {
    return name;
}

int CTable::getTableSize() {
    return table_size;
}

void CTable::changeSizeOfTable(int new_size) {
    int *temp_table = table;
    table = copyTable(temp_table, table_size, new_size);
    eraseTable(table, table_size, new_size);
    table_size = new_size;
    delete[](temp_table);
}

CTable *CTable::cloneObject() {
    return new CTable(*this);
}

int CTable::getValueOfTableCell(int cell_number) {
    return table[cell_number];
}

void CTable::setValueOfTableCell(int cell_number, int value) {
    table[cell_number] = value;
}


void CTable::copyTableFromOtherObject(CTable &object_to_copy) {
    delete[](table);
    table = copyTable(object_to_copy.table, object_to_copy.table_size, object_to_copy.table_size);
    table_size = object_to_copy.table_size;
}

string CTable::toString() {
    string object_info = "(" + name + " len: " + convertIntToString(table_size) + " values: ";
    for (int i = 0; i < table_size; ++i) {
        object_info += convertIntToString(table[i]);
        if(i == table_size-1){
            object_info += ")\n";
        } else {
            object_info +=", ";
        }
    }
    return object_info;
}
