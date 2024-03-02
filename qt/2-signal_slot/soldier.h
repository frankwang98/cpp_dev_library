#ifndef SOLDIER_H
#define SOLDIER_H

#include <QObject>

class Soldier : public QObject
{
    Q_OBJECT
public:
    explicit Soldier(QObject *parent = nullptr);

signals:

public slots:
    // 自定义槽函数 - 返回值和参数与信号保持一致
    void fight();
    void fight(QString);
    void escape();
};

#endif // SOLDIER_H
