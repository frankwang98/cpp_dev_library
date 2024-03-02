#include "soldier.h"
#include <QDebug>

Soldier::Soldier(QObject *parent) : QObject(parent)
{

}

void Soldier::fight()
{
    qDebug() << "fight!";
}

void Soldier::fight(QString s)
{
    qDebug() << "fight for " << s << " !";
}

void Soldier::escape()
{
    qDebug() << "I am afraid of death, escape...";
}
