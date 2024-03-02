#ifndef SQLITEBASIC_H
#define SQLITEBASIC_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

typedef struct
{
    int id;
    QString name;
    int age;
}w2dba;

class SqliteBasic : public QObject
{
    Q_OBJECT
public:
    explicit SqliteBasic(QObject *parent = nullptr);

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询全部数据
    void queryTable();
    // 插入数据
    void singleInsertData(w2dba &singleData); // 插入单条数据
    void moreInsertData(QList<w2dba> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(int id, QString name, int age);
    // 删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);

private:
    QSqlDatabase database;

signals:

public slots:
};

#endif // SQLITEBASIC_H
