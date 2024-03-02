#include "widget.h"
#include "ui_widget.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    // 构建请求URL
    QString cityId = "101010100";  // 指定城市的ID
    QString apiUrl = "http://api.help.bj.cn/apis/weather/?id=" + cityId; // 好多都是不能用了

    // 发送GET请求
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(apiUrl)));

    // 连接信号与槽，处理请求完成事件
    connect(reply, &QNetworkReply::finished, this, &Widget::onWeatherDataReceived);
}

Widget::~Widget()
{
    delete networkManager;
    delete ui;
}

void Widget::onWeatherDataReceived()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        // 读取请求响应的数据
        QByteArray response = reply->readAll();

        // 解析JSON数据
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        // 提取天气数据
        QString cityName = jsonObject["city"].toString();
        QString temperature = jsonObject["temperature"].toString();
        QString weather = jsonObject["weather"].toString();

        // 输出城市天气预报
        qDebug() << "City: " << cityName;
        qDebug() << "Temperature: " << temperature;
        qDebug() << "Weather: " << weather;
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    // 清理资源
    reply->deleteLater();
}
