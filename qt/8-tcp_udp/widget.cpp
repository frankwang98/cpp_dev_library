#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#define MAXConnect 10
// 未完成

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    myPort = 8888;
    ui->btnSend->setEnabled(false);

    tcpClient_2 = new QTcpSocket(this);
    connect(tcpClient_2, SIGNAL(readyRead()), this, SLOT(readyReadSlot())); //关联读取数据函数
}

Widget::~Widget()
{
    delete ui;
}

// tcpserver

void Widget::on_btnBind_clicked()
{
    myAddress = ui->serverIP->text();

    if(tcpServer->listen(QHostAddress(myAddress),myPort))  //绑定IP和端口
    {
        ui->recvMsg->setPlainText("端口绑定成功!");
        ui->btnBind->setEnabled(false);
    }
    else
    {
       ui->recvMsg->setPlainText("端口绑定失败!");
       ui->btnBind->setEnabled(true);
    }

    tcpServer->setMaxPendingConnections(MAXConnect);  //设置最大的绑定数目为10

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
}

void Widget::on_btnSend_clicked()
{
    // if(tcpClient->peerAddress().toString() == ui->clientIP->text())
    if(tcpClient->peerPort() == ui->clientPort->text().toUInt())
    {
        tcpClient->write(ui->sendMsg->toPlainText().toLatin1()); //发送数据
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("error"));
    }
}

void Widget::newConnectionSlot()
{
    tcpClient = tcpServer->nextPendingConnection(); //连接对象
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));  //关联读信息的槽函数

    ui->clientIP->setText(tcpClient->peerAddress().toString());  //得到远程连接上的计算机IP地址
    ui->clientPort->setText(QString::number(tcpClient->peerPort())); //得到远程的端口地址
    ui->btnSend->setEnabled(true);  //可以发送数据
}

void Widget::readyReadSlot()
{
    QTcpSocket *client=(QTcpSocket *)this->sender();
    while(!client->atEnd())
    {
        ui->recvMsg->appendPlainText(QString(client->readAll())); //读取接收到的数据
    }
}

// tcpclient

void Widget::on_btnConnect_clicked()
{

    QString serverIP = ui->serverIP_2->text();  //获得服务器的IP地址
    QString serverPort = ui->serverPort_2->text(); //获得服务器的端口号
    tcpClient_2->connectToHost(QHostAddress(serverIP), serverPort.toUInt());  //和服务器建立连接
    connect(tcpClient_2, SIGNAL(connected()), this, SLOT(connectedSlot()));  //连接成功的信号处理
    qDebug() << "客户端连接";
}

void Widget::connectedSlot()
{
    ui->recvMsg_2->setPlainText("客户端连接成功");
    qDebug() << "客户端连接成功";
}

void Widget::readyReadSlot_2()
{
    while(!tcpClient_2->atEnd())
    {
        ui->recvMsg_2->appendPlainText(tcpClient_2->readAll()); //读取数据内容
    }
}

void Widget::on_btnSend_2_clicked()
{
    tcpClient_2->write(ui->sendMsg_2->toPlainText().toLatin1()); //发送数据
}
