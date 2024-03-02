#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>

namespace Ui {
class SubWidget;
}

class SubWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubWidget(QWidget *parent = nullptr);
    ~SubWidget();

private slots:
    void on_btn_image_clicked();

    void on_btn_tv_clicked();

    void on_btn_ac_clicked();

    void on_pb_select_clicked();

private:
    Ui::SubWidget *ui;
};

#endif // SUBWIDGET_H
