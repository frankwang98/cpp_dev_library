//
// Created by dev on 17/1/2024.
//

#ifndef BOOKSMANAGESYSTEM_READER_H
#define BOOKSMANAGESYSTEM_READER_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Reader {
private:
    string name;
    string number;

public:
    Reader();
    ~Reader();

    void setName(string n);
    void setNumber(string nu);

    string getName()const;
    string getNumber()const;

    int getInfo();
    void searchBook();
    void borrowBook();
    void returnBook();
};


#endif //BOOKSMANAGESYSTEM_READER_H
