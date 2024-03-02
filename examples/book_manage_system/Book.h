//
// Created by dev on 17/1/2024.
//

#ifndef BOOKSMANAGESYSTEM_BOOK_H
#define BOOKSMANAGESYSTEM_BOOK_H

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

#define NULLID "0"

class Book {
private:
    string bookName;
    string bookAuthor;
    string bookISBN;
    string type;
    int bookStatus;
    string bookPress;

public:
    Book();
    ~Book();

    string getName()const;//获得书名
    string getbookAuthor()const;//获得作者
    string getbookISBN()const;//获得ISBN
    string gettype()const;//获得类型
    string getbookPress()const;//获得出版社
    int getbookStatue()const;//获取状态

    void setName(string a);//设定书名
    void setAuthor(string b);//设定作者
    void setISBN(string c);//设定ISBN码
    void settype(string d);//设定书项
    void setPress(string e);//设定出版社
    void setStatus(int f);//设定状态

    void readBookInformation();//读入书籍信息函数
    void printBookInformation();//输出书籍信息函数
    void changeStatus();//判断状态
};


#endif //BOOKSMANAGESYSTEM_BOOK_H
