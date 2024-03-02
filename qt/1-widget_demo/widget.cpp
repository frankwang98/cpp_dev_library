#include "widget.h"
#include "ui_widget.h"
#include "subwidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 可设置窗口位置、大小、标题、图标等，还可加入资源文件
    this->resize(400, 300); // setFixedSize()
    this->setMaximumSize(800, 600);
    this->setMinimumSize(400, 300);
//    this->move(100, 100);
    QRect rect = this->geometry();
    qDebug() << "size: " << rect.width() << rect.height();
    QString window_title = "widget_demo " + QString::number(rect.width()) + "*" + QString::number(rect.height());
    this->setWindowTitle(window_title);
    this->setWindowIcon(QIcon(":/icon/main.png"));

    ui->btn_login->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_register_clicked()
{
    username = ui->le_username->text();
    password = ui->le_password->text();
    qDebug() << "user: " << username << " " << password;

    if (username != "" && password != "")
    {
        qDebug() << "注册成功!";
        ui->btn_login->setEnabled(true);
        ui->btn_login->setText("可以登录"); // setText()
        // 还可以将账号密码存储在数据库中
    }
}

void Widget::on_btn_login_clicked()
{
    QString tmp_username = ui->le_username->text();
    QString tmp_password = ui->le_password->text();
    if (tmp_username == username && tmp_password == password)
    {
        // 可创建独立窗口、内嵌（子）窗口
        SubWidget *subWidget = new SubWidget();
//        SubWidget *subWidget = new SubWidget(this); // 内嵌
        subWidget->setWindowTitle("SubWidget_demo");
        subWidget->show(); // 独立
        this->close();
    } else {
        qDebug() << "账号不存在!";
    }

}
