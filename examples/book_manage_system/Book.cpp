//
// Created by dev on 17/1/2024.
//

#include "Book.h"

Book::Book() {
    bookName = "book_demo";
    bookISBN = NULLID;
}

Book::~Book() {

}

string Book::getName() const {
    return bookName;
}

string Book::getbookAuthor() const {
    return bookAuthor;
}

string Book::getbookISBN() const {
    return bookISBN;
}

string Book::gettype() const {
    return type;
}

string Book::getbookPress() const {
    return bookPress;
}

int Book::getbookStatue() const {
    return bookStatus;
}

void Book::setName(string a) {
    bookName = a;
}

void Book::setAuthor(string b) {
    bookAuthor = b;
}

void Book::setISBN(string c) {
    bookISBN = c;
}

void Book::settype(string d) {
    type = d;
}

void Book::setPress(string e) {
    bookPress = e;
}

void Book::setStatus(int f) {
    bookStatus = f;
}

void Book::readBookInformation() {
    cout<<"book's name: "<<endl;//读入书名
    cin>>bookName;

    cout<<"author: "<<endl;//读入作者名
    cin>>bookAuthor;

    cout<<"ISBN: "<<endl;//读入ISBN码
    cin>>bookISBN;

    cout<<"type: "<<endl;//读入类别
    cin>>type;

    cout<<"press: "<<endl;//读入出版社
    cin>>bookPress;

    cout<<"status: "<<endl;//读入状态
    cin>>bookStatus;
}

void Book::printBookInformation() {
    cout<<"name："<<bookName<<endl;//输出书名
    cout<<"author："<<bookAuthor<<endl;//输出作者
    cout<<"ISBN："<<bookISBN<<endl;//输出ISBN码
    cout<<"type："<<type<<endl;//输出类别
    cout<<"press："<<bookPress<<endl;//输出出版社
    changeStatus();//调用状态改变函数
}

void Book::changeStatus() {
    if(bookStatus==0)
    {
        cout<<"alive"<<endl;//输出状态
    }
    else
    {
        cout<<"borrowed"<<endl;//输出状态
    }
}
