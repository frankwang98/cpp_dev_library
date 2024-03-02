#include "widget.h"

#include <QDebug>
#include <QPainter>
#include <QRandomGenerator64>

#include "ui_widget.h"

// 温度曲线相关的宏
#define PADDING       50
#define INCREMENT     8     // 温度曲线像素增量
#define POINT_RADIUS  3     // 曲线描点的大小
#define TEXT_OFFSET_X 12    // 温度文本相对于点的偏移
#define TEXT_OFFSET_Y 10    // 温度文本相对于点的偏移

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    updateTemp();

    // 安装事件过滤器
    ui->lblHigh->installEventFilter(this);
    ui->lblLow->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if ( event->type() == QEvent::Paint ) {
        if ( watched == ui->lblHigh ) {
            paintHigh();
            //            qDebug() << "paint lblHigh";
        }
        if ( watched == ui->lblLow ) {
            paintLow();
            //            qDebug() << "paint lblLow";
        }
    } else if ( event->type() == QEvent::MouseButtonDblClick ) {
        updateTemp();
    }

    return QWidget::eventFilter(watched, event);
}

void Widget::paintHigh()
{
    QPainter painter(ui->lblHigh);
    painter.setRenderHint(QPainter::Antialiasing, true);    // 抗锯齿

    // 1. 计算 x 轴坐标
    int pointX[7] = {0};
    for ( int i = 0; i < 7; i++ ) {
        pointX[i] = ui->lblHigh->pos().x() + PADDING + (ui->lblHigh->width() - PADDING * 2) / 6 * i;
    }

    // 2. 计算 y 轴坐标
    // 2.1 计算平均值
    int tempSum     = 0;
    int tempAverage = 0;

    for ( int i = 0; i < 7; i++ ) {
        tempSum += mHighTemp[i];
    }

    tempAverage = tempSum / 7;    // 最高温平均值

    // 2.2 计算 y 轴坐标
    int pointY[7] = {0};
    int yCenter   = ui->lblHigh->height() / 2;
    int increment = ui->lblHigh->height() / 20;
    for ( int i = 0; i < 7; i++ ) {
        pointY[i] = yCenter - ((mHighTemp[i] - tempAverage) * increment);
    }

    // 3. 开始绘制
    // 3.1 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(2);                      //设置画笔宽度为1
    pen.setColor(QColor(255, 170, 0));    //设置颜色

    painter.setPen(pen);
    painter.setBrush(QColor(255, 170, 0));    //设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 3.2 画点、写文本
    for ( int i = 0; i < 7; i++ ) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), QString::number(mHighTemp[i]) + "°");
    }

    // 3.3 绘制曲线
    for ( int i = 0; i < 6; i++ ) {
        if ( i == 0 ) {
            pen.setStyle(Qt::DotLine);    //虚线
            painter.setPen(pen);
        } else {
            pen.setStyle(Qt::SolidLine);    // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
}

void Widget::paintLow()
{
    QPainter painter(ui->lblLow);
    painter.setRenderHint(QPainter::Antialiasing, true);    // 抗锯齿

    // 1. 计算 x 轴坐标
    int pointX[7] = {0};
    for ( int i = 0; i < 7; i++ ) {
        pointX[i] = ui->lblLow->pos().x() + PADDING + (ui->lblLow->width() - PADDING * 2) / 6 * i;
    }

    // 2. 计算 y 轴坐标
    // 2.1 计算平均值
    int tempSum     = 0;
    int tempAverage = 0;

    for ( int i = 0; i < 7; i++ ) {
        tempSum += mLowTemp[i];
    }

    tempAverage = tempSum / 7;    // 最高温平均值

    // 2.2 计算 y 轴坐标
    int pointY[7] = {0};
    int yCenter   = ui->lblLow->height() / 2;
    int increment = ui->lblLow->height() / 20;
    for ( int i = 0; i < 7; i++ ) {
        pointY[i] = yCenter - ((mLowTemp[i] - tempAverage) * increment);
    }

    // 3. 开始绘制
    // 3.1 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(2);                      // 设置画笔宽度为1
    pen.setColor(QColor(0, 255, 255));    // 设置颜色

    painter.setPen(pen);
    painter.setBrush(QColor(0, 255, 255));    //设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 3.2 画点、写文本
    for ( int i = 0; i < 7; i++ ) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), QString::number(mLowTemp[i]) + "°");
    }

    // 3.3 绘制曲线
    for ( int i = 0; i < 6; i++ ) {
        if ( i == 0 ) {
            pen.setStyle(Qt::DotLine);    //虚线
            painter.setPen(pen);

        } else {
            pen.setStyle(Qt::SolidLine);    // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
}

void Widget::updateTemp()
{
    for ( int i = 0; i < 7; i++ ) {
        mHighTemp[i] = 20 + QRandomGenerator::global()->generate() % 10;
        mLowTemp[i]  = -5 + QRandomGenerator::global()->generate() % 10;
    }

    ui->lblHigh->update();
    ui->lblLow->update();
}
