//
// Created by dev on 17/1/2024.
//

#ifndef BOOKSMANAGESYSTEM_MANAGER_H
#define BOOKSMANAGESYSTEM_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Book.h"

using namespace std;

class Manager {
private:
    string username;
    string password;

public:
    Manager();
    ~Manager();

    int getManage();
//    void reviseInfo();

    void addBook();
    void deleteBook();
    void reviseBook();

    void addReader();
    void deleteReader();
};


#endif //BOOKSMANAGESYSTEM_MANAGER_H
