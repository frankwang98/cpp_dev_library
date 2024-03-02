#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QListWidgetItem>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onRadioButtonClicked();

    void onItemClicked(QListWidgetItem* item);
    void onItemDoubleClicked(QListWidgetItem* item);

    void onBtnAddClicked();
    void onBtnInsertClicked();
    void onBtnDeleteClicked();

private:
    Ui::Widget *ui;
    QButtonGroup* mBtnGroup;

};
#endif // WIDGET_H
