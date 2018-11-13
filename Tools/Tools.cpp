//
// Created by martkans on 19.10.18.
//

#include "Tools.h"

string convertIntToString(int number){
    stringstream ss;
    ss << number;
    return ss.str();
}

int convertStringToInt(string input, bool* error){
    int number;

    istringstream is(input);
    is >> number;
    *error = false;
    for (unsigned long i = 0; i < input.length(); ++i) {
        if(!isInRange(input.at(i), ASCII_ZERO_VALUE, ASCII_NINE_VALUE)){
            *error = true;
        }
    }
    return number;
}

int* copyTable(int* source_table, int source_table_size, int target_table_size) {
    int* target_table = new int[target_table_size];

    for(int i = 0; i < target_table_size && i < source_table_size; ++i) {
        target_table[i] = source_table[i];
    }

    return target_table;
}

void eraseTable(int* table, int first_index, int last_index) {
    for (int i = first_index; i < last_index; ++i){
        table[i] = 0;
    }
}

bool isInRange(int number, int lower_limit, int upper_limit) {
    if(number >= lower_limit && number <= upper_limit){
        return true;
    } else {
        return false;
    }
}

int provideInt(int lower_limit, int upper_limit, bool* error) {
    string input_data;
    bool* conversion_error = new bool();
    int number;

    getline(cin, input_data);
    number = convertStringToInt(input_data, conversion_error);

    if(*conversion_error || !isInRange(number, lower_limit, upper_limit)){
        *error = true;
    } else{
        *error = false;
    }
    return number;
}

bool provideYesOrNo(bool *error) {
    string confirm;

    getline(cin, confirm);

    *error = false;
    if (confirm == "T" || confirm == "t"){
        return true;
    } else if (confirm != "N" && confirm != "n"){
        *error = true;
    }
    return false;
}

void alert(string message) {
    cout << "\nOperacja zakończona niepowodzeniem!\n"
         << message << "\n";
}

string convertCharToString(char sign) {
    string buffer = "";
    buffer += sign;
    return buffer;
}

string trim(string processed_string) {
    int i = 0;
    while (i < processed_string.length() && processed_string.at(i) == ' '){
        i++;
    }
    processed_string = processed_string.substr(i, processed_string.length() - i);

    i = processed_string.length() - 1;
    while (i >= 0 && processed_string.at(i) == ' '){
        i--;
    }
    processed_string = processed_string.substr(0, i + 1);

    return processed_string;
}

string removeApostrophes(string processed_string) {
    return processed_string.substr(1,processed_string.length() - 2);
}


string loadFromFile(string file_name) {
    ifstream i_file_stream(file_name.c_str());
    string menu;

    if (i_file_stream.is_open()) {
        getline(i_file_stream, menu);
    }

    i_file_stream.close();
    return menu;
}

bool writeToFile(string file_name, string menu_to_save) {
    ofstream o_file_stream(file_name.c_str());

    if (o_file_stream.is_open()) {
        o_file_stream << menu_to_save << "\n";
        o_file_stream.close();
        return true;
    }

    return false;
}
