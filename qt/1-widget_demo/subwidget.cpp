#include "subwidget.h"
#include "ui_subwidget.h"
#include <QTime>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

SubWidget::SubWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWidget)
{
    ui->setupUi(this);

    ui->le_time->setText(QTime::currentTime().toString());

    // label还可以显示图片

    // 单选框、复选框、组合框、微调框、滑动条
}

SubWidget::~SubWidget()
{
    delete ui;
}

int index = 0;

void SubWidget::on_btn_image_clicked()
{
    QPixmap px;
    if (index == 0)
    {
        px.load(":/icon/register.png");
        index++;
    }else {
        px.load(":/icon/login.png");
        index = 0;
    }
    ui->lb_image->setPixmap(px);
}

void SubWidget::on_btn_tv_clicked()
{
    QMessageBox::information(nullptr, "Information", "已打开小电视");
}

void SubWidget::on_btn_ac_clicked()
{
    qDebug() << "AC is opened.";
}

void SubWidget::on_pb_select_clicked()
{
    if (ui->rb_tv->isChecked())
    {
        ui->le_select->setText("选择看电视");
    }
    if (ui->rb_ac->isChecked())
    {
        ui->le_select->setText("选择开空调");
    }
}
