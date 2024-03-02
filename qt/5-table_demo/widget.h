#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTableWidgetItem>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);
    ~Widget();

public:

    void appendOneRow(QString name,
                      QString gender,
                      int     age,
                      QString province);

    void insertOneRow(int     row,
                      QString name,
                      QString gender,
                      int     age,
                      QString province);

private slots:

    void on_btnAppend_clicked();
    void on_btnInsert_clicked();
    void on_btnDelete_clicked();
    void on_btnModify_clicked();

    void onItemClicked(QTableWidgetItem *item);
    void on_btnStyleSheet_clicked();

    void onSelectionRadioButtonClicked();

private:

    Ui::Widget *ui;

    QButtonGroup *mButtonGroupSelection;
};
#endif // WIDGET_H
