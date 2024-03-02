#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class QCustomPlot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupQuadraticDemo(QCustomPlot *customPlot);

private:
    Ui::MainWindow *ui;

private slots:
    void selectionChanged();

    void mousePress();

    void mouseWheel();
};

#endif // MAINWINDOW_H
