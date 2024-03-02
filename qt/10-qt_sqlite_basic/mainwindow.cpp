#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlitebasic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("sqlite基础");

    SqliteBasic sqliteBasic;
    sqliteBasic.openDb();
    sqliteBasic.createTable();

     // 判断数据表是否存在
    QString str1 = QString("student");
    qDebug() << "isTabelExist：" << sqliteBasic.isTableExist(str1);

    // 插入单条数据
    w2dba w2dbaTest1 = {1, "zhangsan", 24};
    w2dba w2dbaTest2 = {2, "lisi", 28};
    sqliteBasic.singleInsertData(w2dbaTest1);
    sqliteBasic.singleInsertData(w2dbaTest2);

    // 插入多条数据
    QList<w2dba> list;
    w2dba w2dbaTest3 = {3, "liwu", 26};
    w2dba w2dbaTest4 = {4, "zhaoliu", 27};
    list.append(w2dbaTest3);
    list.append(w2dbaTest4);
    sqliteBasic.moreInsertData(list);

    // 查询全部数据
    sqliteBasic.queryTable();
    qDebug() << endl;

    // 修改数据
    sqliteBasic.modifyData(2, "modify", 10);
    sqliteBasic.modifyData(3, "modify-2", 20);
    // 查询全部数据
    sqliteBasic.queryTable();
    qDebug() << endl;

    // 删除数据
    sqliteBasic.deleteData(2);
    // 查询全部数据
    sqliteBasic.queryTable();
    qDebug() << endl;

    // 删除数据表
    QString str2 = QString("student");
    qDebug() << "isTabelExist：" << sqliteBasic.isTableExist(str2);

    sqliteBasic.deleteTable(str2);

    qDebug() << "isTabelExist：" << sqliteBasic.isTableExist(str2);

    //关闭数据库
    sqliteBasic.closeDb();

}

MainWindow::~MainWindow()
{
    delete ui;
}
