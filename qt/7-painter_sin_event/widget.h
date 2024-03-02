#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    Ui::Widget *ui;

    int x;  // 当前点的x坐标
    int y;  // 当前点的y坐标
    QVector<QPoint> points;  // 存储绘制曲线的点
};

#endif // WIDGET_H
