#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 滑动条、滚动条

    ui->hs_r->setMaximum(255);
    ui->hs_r->setMinimum(0);
    ui->hs_r->setSingleStep(1);

    ui->hs_g->setMaximum(255);
    ui->hs_g->setMinimum(0);
    ui->hs_g->setSingleStep(1);

    ui->hs_b->setMaximum(255);
    ui->hs_b->setMinimum(0);
    ui->hs_b->setSingleStep(1);

//    background-color: rgb(170, 85, 255);
    QString style = "background-color: rgb(0, 0, 255);";
    ui->le_color->setStyleSheet(style);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_hs_r_valueChanged(int value)
{
    QString red = QString::number(value);
    QString green = QString::number(ui->hs_g->value());
    QString blue = QString::number(ui->hs_b->value());

    ui->le_red->setText(red);

    QString style = "background-color: rgb("+red+", "+green+", "+blue+");";
    ui->le_color->setStyleSheet(style);
}

void Widget::on_hs_g_valueChanged(int value)
{
    QString green = QString::number(value);
    QString red = QString::number(ui->hs_r->value());
    QString blue = QString::number(ui->hs_b->value());

    ui->le_green->setText(green);

    QString style = "background-color: rgb("+red+", "+green+", "+blue+");";
    ui->le_color->setStyleSheet(style);
}

void Widget::on_hs_b_valueChanged(int value)
{
    QString blue = QString::number(value);
    QString red = QString::number(ui->hs_r->value());
    QString green = QString::number(ui->hs_g->value());

    ui->le_blue->setText(blue);

    QString style = "background-color: rgb("+red+", "+green+", "+blue+");";
    ui->le_color->setStyleSheet(style);
}
