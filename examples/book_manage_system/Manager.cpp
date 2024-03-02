//
// Created by dev on 17/1/2024.
//

#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager() {

}

int Manager::getManage() {
    string filename = "../manager.txt";
    ifstream ifile(filename);
    if (!ifile.is_open()) {
        cout << "Can't open the file: " << filename << endl;
        return 0;
    }

    cout << "Please enter your username:" << endl;
    cin >> username;
    cout << "Please enter your password:" << endl;
    cin >> password;

    string tmp_username, tmp_password;

    while (ifile >> tmp_username >> tmp_password) {
        if (tmp_username == username && tmp_password == password) {
            cout << "Login successfully!" << endl;
            return 1;
        } else {
            cout << "Username or password is not correct!" << endl;
            cout << "tips: " << tmp_username << " " << tmp_password << endl;
            return 0;
        }
    }

    ifile.close();

    return 0;
}

void Manager::addBook() {
    cout << "Add book." << endl;
    Book book1;//实例化对象
    ofstream fileout("../book.txt",ios::app);//打开文件
    if(!fileout)
    {
        cout<<"can't open "<<"book.txt"<<endl;
    }
    else
    {
        cout<<"Enter book's info: "<<endl;
        book1.readBookInformation();//读入信息
        fileout<<book1.getName()<<" "<<book1.getbookAuthor()<<" "<<book1.getbookISBN()<<" "<<book1.gettype()
               <<" "<<book1.getbookPress()<<" "<<book1.getbookStatue()<<endl;//写入信息
    }
    fileout.close();//关闭文件
}

void Manager::deleteBook() {
    cout << "Delete book." << endl;
    Book book2;//实例化对象
    ifstream filein("../book.txt");//打开文件
    if(!filein)
    {
        cout<<"open failed"<<endl;
    }
    else
    {
        cout<<"Enter delete's book: "<<endl;
        int n=0;//标签，是否有这本书
        string t;//输入书名
        cin>>t;
        do
        {   int v;//定义变量
            string x,y,z,u,w;
            string s;
            getline(filein,s);//读入每一行
            istringstream sin(s);
            sin>>x;//把s中第一个字符串给a
            ofstream fileout("restore.txt",ios::app);//写到新文件中去

            if(t!=x)//判断是否为删除的地方
                fileout<<s<<endl;//写入数据

            if(t==x)//判断是否为删除的地方
            {
                n=1;
                sin>>y>>z>>u>>w>>v;//将一行字符串读出
                book2.setName(x);//设定书名
                book2.setAuthor(y);//设定作者
                book2.setISBN(z);//设定ISBN码
                book2.settype(u);//设定书项
                book2.setPress(w);//设定出版社
                book2.setStatus(v);//设定状态
                cout<<"Original book's info: "<<endl;
                book2.printBookInformation();//输出

                cout<<"delete?(y / n)"<<endl;
                char a;//定义变量
                cin>>a;
                if(a=='y')
                {
                    cout<<"delete success"<<endl;
                }
                if(a=='n')
                {
                    cout<<"no delete"<<endl;
                    fileout<<book2.getName()<<" "<<book2.getbookAuthor()<<" "<<book2.getbookISBN()<<" "<<book2.gettype()
                           <<" "<<book2.getbookPress()<<" "<<book2.getbookStatue()<<endl;//写入到文件
                }
                if(a!='y'||a!='n')
                {
                    system("pause");
                }
                fileout.close();//关闭文件
            }

        }
        while(!filein.eof());//判断是否到文件尾
        if(n==0)//不存在这本书
            cout<<"Can't find"<<endl;
    }
    filein.close();//关闭

    ifstream filei("restore.txt");//打开文档
    ofstream fileout("store.txt",ios::out);//打开文档并清空内容

    for(string s;getline(filei,s);)//将修改后的内容写到文件中去
    {
        fileout<<s<<endl;
    }
    filei.close();//关闭文件
    fileout.close();//关闭文件
    system("del restore.txt");//删除文件副本
}

void Manager::reviseBook() {
    cout << "Modify book." << endl;
    Book book1;//实例化对象
    ifstream filein("../book.txt");//打开文件
    if(!filein)
    {
        cout<<"open failed"<<endl;
    }
    else
    {
        cout<<"Enter revise book's name:"<<endl;
        int n=0;//标签，是否有这本书
        string t;//输入书名
        cin>>t;
        do
        {   int v;//定义变量
            string x,y,z,u,w;
            string s;
            getline(filein,s);//读入每一行
            istringstream sin(s);
            sin>>x;//把s中第一个字符串给a
            ofstream fileout("restore.txt",ios::app);//写到新文件中去

            if(t!=x)//判断是否为修改的地方
                fileout<<s<<endl;//写入数据

            if(t==x)//判断是否为修改的地方
            {
                n=1;
                sin>>y>>z>>u>>w>>v;//将一行字符串读出
                book1.setName(x);//设定书名
                book1.setAuthor(y);//设定作者
                book1.setISBN(z);//设定ISBN码
                book1.settype(u);//设定书项
                book1.setPress(w);//设定出版社
                book1.setStatus(v);//设定状态
                cout<<"Orignal book's info:"<<endl;
                book1.printBookInformation();//输出

                cout<<"Current book's info:"<<endl;
                book1.readBookInformation();//重新读入
                fileout<<book1.getName()<<" "<<book1.getbookAuthor()<<" "<<book1.getbookISBN()<<" "<<book1.gettype()
                       <<" "<<book1.getbookPress()<<" "<<book1.getbookStatue()<<endl;//写入到文件
                fileout.close();//关闭文件
            }

        }
        while(!filein.eof());//判断是否到文件尾
        if(n==0)//不存在这本书
            cout<<"Can't find book"<<endl;
    }
    filein.close();//关闭

    ifstream filei("restore.txt");//打开文档
    ofstream fileout("store.txt",ios::out);//打开文档并清空内容

    for(string s;getline(filei,s);)//将修改后的内容写到文件中去
    {
        fileout<<s<<endl;
    }
    filei.close();//关闭文件
    fileout.close();//关闭文件
    system("del restore.txt");//删除文件副本
}

void Manager::addReader() {
    cout << "Add reader." << endl;
    string filename = "../reader.txt";
    ofstream file(filename, ios::app); // 打开文本文件，追加模式

    if (!file.is_open()) {
        cout << "Can't open " << filename << endl;
    }

    string name, number;
    cout << "Enter reader's name: ";
    cin >> name;
    cout << "Enter reader's number: ";
    cin >> number;

    file << name << " " << number << endl;

    file.close();
}

void Manager::deleteReader() {
    cout << "Delete reader." << endl;
    ifstream filein("../reader.txt");//打开文件
    if(!filein)
    {
        cout<<"open failed"<<endl;
    }
    else
    {
        string t,m;
        int n=0;//标签，是否有这个读者
        cout<<"name:"<<endl;
        cin>>m;
        cout<<"number:"<<endl;
        cin>>t;
        do
        {
            string x,y,z;//定义变量
            string s;
            getline(filein,s);//读入每一行
            istringstream sin(s);
            sin>>x>>y>>z;//把s中第一个字符串给a
            ofstream fileout("../reader1.txt",ios::app);//写到新文件中去

            if(m!=x||t!=y)//判断是否为删除的地方
                fileout<<s<<endl;//写入数据

//            if(m==x&&t==y)//判断是否为删除的地方
//            {
//                n=1;
//                cout<<"原学生信息为:"<<endl;
//                cout<<"姓名："<<x<<endl;
//                cout<<"学号："<<y<<endl;
//                cout<<"密码："<<z<<endl;
//                cout<<"是否删除？（Y：是，N：否）"<<endl;
//                char a;//定义变量
//                cin>>a;
//                if(a=='Y')
//                {
//                    cout<<"删除成功！"<<endl;
//                }
//                if(a=='N')
//                {
//                    cout<<"未删除！"<<endl;
//                    fileout<<x<<" "<<y<<" "<<z<<endl;//写入到文件
//                }
//                if(a!='Y'||a!='N')
//                {
//                    system("pause");
//                }
//                fileout.close();//关闭文件
//            }
        }
        while(!filein.eof());//判断是否到文件尾
        if(n==0)//不存在这个学生
            cout<<"Can't find"<<endl;
    }
    filein.close();//关闭

    ifstream filei("../reader1.txt");//打开文档
    ofstream fileout("../reader.txt",ios::out);//打开文档并清空内容

    for(string s;getline(filei,s);)//将修改后的内容写到文件中去
    {
        fileout<<s<<endl;
    }
    filei.close();//关闭文件
    fileout.close();//关闭文件
    system("del student1.txt");//删除文件副本
}
