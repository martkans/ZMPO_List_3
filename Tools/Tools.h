//
// Created by martkans on 19.10.18.
//

#ifndef LISTA3_TOOLS_H
#define LISTA3_TOOLS_H

#define ASCII_ZERO_VALUE 47
#define ASCII_NINE_VALUE 58

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string convertIntToString(int number);
int convertStringToInt(string input, bool* error);

int* copyTable(int* source_table, int source_table_size, int target_table_size);
void eraseTable(int* table,int first_index, int last_index);

bool isInRange(int number, int lower_limit, int upper_limit);


int provideInt(int lower_limit, int upper_limit, bool* error);

bool provideYesOrNo(bool* error);

void alert(string message);

#endif //LISTA3_TOOLS_H
