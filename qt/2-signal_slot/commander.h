#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = nullptr);

signals:
    // 自定义信号
    void go();
    void go(QString); // 函数重载
    void move();

public slots:
};

#endif // COMMANDER_H
