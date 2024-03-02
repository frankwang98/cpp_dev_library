#include "sqlitebasic.h"

SqliteBasic::SqliteBasic(QObject *parent) : QObject(parent)
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("MyDataBase.db");
    }
}

bool SqliteBasic::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Open database.";
    }

    return true;
}

void SqliteBasic::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery;
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE student (\
                          id INT PRIMARY KEY NOT NULL,\
                          name TEXT NOT NULL,\
                          age INT NOT NULL)");
    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

bool SqliteBasic::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

void SqliteBasic::queryTable()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM student");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString name = sqlQuery.value(1).toString();
            int age = sqlQuery.value(2).toInt();
            qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
        }
    }
}

void SqliteBasic::singleInsertData(w2dba &singledb)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO student VALUES(:id,:name,:age)");
    sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":name", singledb.name);
    sqlQuery.bindValue(":age", singledb.age);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "singleInsert.";
    }
}

void SqliteBasic::moreInsertData(QList<w2dba>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO student VALUES(?,?,?)");
    QVariantList idList,nameList,ageList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        nameList << moredb.at(i).name;
        ageList << moredb.at(i).age;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(ageList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "moreInsert.";
    }
}

void SqliteBasic::modifyData(int id, QString name, int age)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE student SET name=?,age=? WHERE id=?");
    sqlQuery.addBindValue(name);
    sqlQuery.addBindValue(age);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

void SqliteBasic::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM student WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

void SqliteBasic::deleteTable(QString& tableName)
{
    QSqlQuery query;
    QString deleteTableQuery = QString("DROP TABLE IF EXISTS %1").arg(tableName);
    if (query.exec(deleteTableQuery)) {
        qDebug() << "Table deleted successfully.";
    } else {
        qDebug() << "Error: Failed to delete table.";
    }
}

void SqliteBasic::closeDb(void)
{
    database.close();
    qDebug() << "close success";
}
