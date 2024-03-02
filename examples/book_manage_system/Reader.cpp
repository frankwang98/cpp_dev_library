//
// Created by dev on 17/1/2024.
//

#include "Reader.h"

Reader::Reader() {

}

Reader::~Reader() {

}

int Reader::getInfo() {
    string filename = "../reader.txt";
    ifstream ifile(filename);
    if (!ifile.is_open()) {
        cout << "Can't open the file: " << filename << endl;
        return 0;
    }

    cout << "Please enter your name:" << endl;
    cin >> name;
    cout << "Please enter your number:" << endl;
    cin >> number;

    string tmp_name, tmp_number;

    while (ifile >> tmp_name >> tmp_number) {
        if (tmp_name == name && tmp_number == number) {
            cout << "Login successfully!" << endl;
            return 1;
        } else {
            cout << "name or number is not correct!" << endl;
            cout << "tips: " << tmp_name << " " << tmp_number << endl;
            return 0;
        }
    }

    ifile.close();
    
    return 0;
}

void Reader::searchBook() {

}

void Reader::borrowBook() {

}

void Reader::returnBook() {

}

void Reader::setName(string n) {

}

void Reader::setNumber(string nu) {

}

string Reader::getName() const {
    return std::__cxx11::string();
}

string Reader::getNumber() const {
    return std::__cxx11::string();
}


