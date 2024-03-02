#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <QList>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>

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
    void on_btnBind_clicked();

    void on_btnSend_clicked();

    void newConnectionSlot();

    void readyReadSlot();

    void on_btnConnect_clicked();

    void connectedSlot();

    void readyReadSlot_2();

    void on_btnSend_2_clicked();

private:
    Ui::Widget *ui;

    QTcpServer *tcpServer; //服务器类
    QTcpSocket *tcpClient; //客户端类
    QTcpSocket *tcpClient_2;
    QString myAddress; //服务器的ip地址和端口
    int myPort;
};

#endif // WIDGET_H
