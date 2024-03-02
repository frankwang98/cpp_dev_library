#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_register_clicked();

    void on_btn_login_clicked();

private:
    Ui::Widget *ui;

    QString username;
    QString password;
};

#endif // WIDGET_H
