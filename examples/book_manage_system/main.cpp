#include <iostream>
#include "Manager.h"
#include "Reader.h"
#include "Book.h"

using namespace std;

//管理员相关函数
void addbook()//进入添加书籍
{
    Manager manage1;//实例化对象
    for (int temp=1;temp;)//循环添加书籍
    {
        manage1.addBook();//调用manage类中的add（）函数
        cout<<"add?(y / n)"<<endl;//判断是否循环
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void deletebook()//进入删除书籍
{
    Manager manage6;//实例化对象
    for (int temp=1;temp;)//循环删除书籍
    {
        manage6.deleteBook();//调用manage类中的deleteBook()函数
        cout<<"delete?(y / n)"<<endl;//判断是否循环
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void changebook()//修改书籍信息
{
    Manager manage2;//实例化对象
    for (int temp=1;temp;)//循环修改书籍
    {
        manage2.reviseBook();//调用manage类中revise（）函数
        cout<<"modify?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void addReader()//增加读者函数
{
    Manager manage3;//实例化对象
    for (int temp=1;temp;)//循环增加
    {
        manage3.addReader();//调用manage类中addReader（）函数
        cout<<"add?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') {
            temp=1;
        }
        else if(a=='n') {
            temp=0;
        }
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void deleteReader()//删除读者函数
{
    Manager manage7;//实例化对象
    for (int temp=1;temp;)//循环删除
    {
        manage7.deleteReader();//调用manage类中deleteReader（）函数
        cout<<"delete?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void getManage()
{
    Manager manage4;//实例化对象
    for(int temp=1;temp;)//循环登陆
    {
        int b;//接受getManage()的返回值
        b=manage4.getManage();//调用manage类中的getManage()函数
        if(b==1)//登陆成功
        {
            while(true)
            {
                system("cls");//清除屏幕内容
                cout<<"***************************"<<endl;
                cout<<"1.add reader"<<endl;
                cout<<"2.delete reader"<<endl;
                cout<<"3.add book"<<endl;
                cout<<"4.delete book"<<endl;
                cout<<"5.modify book"<<endl;
                cout<<"6.exit"<<endl;
                int t;
                cin>>t;
                switch(t)
                {
                    case 1:addReader();break;//调用addReader()函数
                    case 2:deleteReader();break;//调用deleteReader()函数
                    case 3:addbook();break;//调用addbook()函数
                    case 4:deletebook();break;//调用deletebook()函数
                    case 5:changebook();break;//调用changebook()函数
                    case 6:
                        cout<<"Thank you"<<endl;//退出
                        system("pause");
                        exit(0);

                    default:
                        cout<<"failed"<<endl;//输入错误
                }
            }
        }

        else//登录失败判断是否再次登陆
        {
            cout<<"go on login? (Y / N)"<<endl;//循环判断
            char a;//定义变量
            cin>>a;
            if(a=='Y') temp=1;
            else if(a=='N') temp=0;
            else
            {
                cout<<"failed"<<endl; temp=1;//输入错误提示
            }
        }
    }
}

//读者相关函数
void search()//查询函数
{
    Reader reader3;//实例化对象
    for (int temp=1;temp;)//循环查询
    {
        reader3.searchBook();//调用reader类中的search()函数
        cout<<"search?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed!"<<endl; temp=1;//输入错误提示
        }
    }
}

void borrowBook()//借书函数
{
    Reader reader4;//实例化对象
    for (int temp=1;temp;)//循环借书
    {
        reader4.borrowBook();//调用reader类中的borrowBook()函数
        cout<<"borrow?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed!"<<endl; temp=1;//输入错误提示
        }
    }
}

void returnBook()//还书函数
{
    Reader reader5;//实例化对象
    for (int temp=1;temp;)//循环还书
    {
        reader5.returnBook();//调用reader类中的returnBook()函数
        cout<<"return?(y / n)"<<endl;//循环判断
        char a;//定义变量
        cin>>a;
        if(a=='y') temp=1;
        else if(a=='n') temp=0;
        else
        {
            cout<<"failed"<<endl; temp=1;//输入错误提示
        }
    }
}

void getStudent()//登录函数
{
    Reader reader5;//实例化对象
    for (int temp=1;temp;)//循环登陆
    {
        int a;//接受getInformation()的返回值
        a=reader5.getInfo();//调用reader类中的getInformation()函数
        if(a==1)//登陆成功
        {
            while(true)
            {
                system("cls");//清除屏幕内容
                cout<<"***************************"<<endl;
                cout<<"1.search"<<endl;
                cout<<"2.borrow"<<endl;
                cout<<"3.return"<<endl;
                cout<<"4.exit"<<endl;
                int t;
                cin>>t;
                switch(t)
                {
                    case 1:search();break;//调用search()函数
                    case 2:borrowBook();break;//调用borrowBook()函数
                    case 3:returnBook();break;//调用returnBook()函数
                    case 4:
                        cout<<"Thank you"<<endl;//退出
                        system("pause");
                        exit(0);
                    default:
                        cout<<"failed！"<<endl;//输入错误
                }
            }
        }
        else
        {
            cout<<"go on?(y / n)"<<endl;//循环判断
            char a;
            cin>>a;
            if(a=='y') temp=1;
            else if(a=='n') temp=0;
            else
            {
                cout<<"failed!"<<endl; temp=1;//输入错误提示
            }
        }
    }
}

void display_2()
{
    while(true)
    {
        system("cls");//清除屏幕内容
        cout<<"***************************"<<endl;
        cout<<"1.login"<<endl;
        cout<<"2.modify info"<<endl;
        cout<<"3.exit"<<endl;
        int t;
        cin>>t;
        switch(t)
        {
            case 1:getManage();break;//调用getManage()函数
//            case 2:reviseInformation();break;//调用reviseInformation()函数
            case 3:
                cout<<"Thank you"<<endl;//退出
                system("pause");
                exit(0);
            default :
                cout<<"Enter error"<<endl;//输入错误
        }
    }
}

void display_3()
{
    while(true)
    {
        system("cls");//清除屏幕内容
        cout<<"***************************"<<endl;
        cout<<"1.login"<<endl;
        cout<<"2.modify info"<<endl;
        cout<<"3.exit"<<endl;
        int t;
        cin>>t;
        switch(t)
        {
            case 1:getStudent();break;//调用getStudent()函数
//            case 2:reviseCode();break;//调用reviseCode()函数
            case 3:
                cout<<"Thank you"<<endl;//退出
                system("pause");
                exit(0);
            default :
                cout<<"failed！"<<endl;//错误提示
        }
    }
}

void display_1() {
    cout << "Select your standing: \n1.Manager\n2.Reader\n3.Exit\n" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Manager" << endl;
            display_2();
            break;
        case 2:
            cout << "Reader" << endl;
            display_3();
            break;
        case 3:
            cout << "Thank you" << endl;
            system("pause");
            exit(0);
        default:
            cout << "Invalid choice" << endl;
    }
}

int main() {
    // 一个简单的图书馆里系统，demo用
    cout << "*****************************" << endl;
    cout << "Welcome to BooksManageSystem!" << endl;


    while(true) {
        display_1();
        system("pause");
    }

    //    Manager manager;
//    while(!manager.getManage()) {
//        manager.getManage();
//    }
//    manager.addReader();

//    Reader reader;
//    while(!reader.getRead()) {
//        reader.getRead();
//    }

    return 0;
}
