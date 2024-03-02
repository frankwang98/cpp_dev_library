#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(400, 300);
    startTimer(10);  // 设置定时器，每10毫秒触发一次timerEvent

    // 设置初始位置
    x = 0;
    y = height() / 2;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    int width = this->width();
    int height = this->height();
    int padding = 0;

    painter.drawLine(padding, height / 2, width - padding, height / 2);  // X 轴
    painter.drawLine(padding, padding, padding, height - padding);       // Y 轴

    // 绘制正弦函数曲线
    painter.setPen(Qt::blue);
    painter.drawPolyline(points);
}

void Widget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    // 计算下一个点的位置
    x += 1;
    y = height() / 2 - 50 * qSin(qDegreesToRadians(static_cast<double>(x)));

    // 添加点到曲线上
    points.append(QPoint(x, y));

    // 如果超出窗口宽度，清空曲线重新开始
    if (x > width()) {
        x = 0;
        points.clear();
    }

    update();  // 更新绘图
}
