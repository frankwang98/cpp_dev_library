#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

    /**
     * @brief calculateBMI
     * @param weight
     * @param height
     * @return double
     */
    double calculateBMI(double weight, double height);

    /**
     * @brief interpretBMI
     * @param bmi
     */
    void interpretBMI(double bmi);

private:
    Ui::MainWindow *ui;

    double weight, height;

public slots:
    void printBMI();
};

#endif // MAINWINDOW_H
