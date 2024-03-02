#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

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
    void on_hs_r_valueChanged(int value);

    void on_hs_g_valueChanged(int value);

    void on_hs_b_valueChanged(int value);

private:
    Ui::Widget *ui;

    QTimer *mTimerTest;
};

#endif // WIDGET_H
