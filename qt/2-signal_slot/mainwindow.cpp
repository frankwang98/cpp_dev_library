#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commander.h"
#include "soldier.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 标准信号槽 - 窗口操作
    connect(ui->btn_max, SIGNAL(clicked()), this, SLOT(showMaximized()));
    connect(ui->btn_normal, SIGNAL(clicked()), this, SLOT(showNormal()));
    connect(ui->btn_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));

    // 自定义信号槽 - 指挥官与士兵
    Commander commander;
    Soldier soldier;
    Soldier soldier2;

    connect(&commander, SIGNAL(go()), &soldier, SLOT(fight()));
//    connect(&commander, SIGNAL(go(QString)), &soldier, SLOT(fight(QString)));
    connect(&commander, SIGNAL(go()), &soldier2, SLOT(escape()));
    connect(&commander, SIGNAL(move()), &soldier2, SLOT(escape()));
    /* emit */commander.go();
    commander.move();
    commander.disconnect();
//    commander.go("freedom");

    // 定义函数指针，编译器自动推断，有参和无参
//    void (Commander::*pGo)() = &Commander::go;
//    void (Soldier::*pFight)() = &Soldier::fight;
//    connect(&commander, pGo, &soldier, pFight);
//    commander.go();
//    void (Commander::*pGoForFreedom)(QString) = &Commander::go;
//    void (Soldier::*pFightForFreedom)(QString) = &Soldier::fight;
//    connect(&commander, pGoForFreedom, &soldier, pFightForFreedom);
//    commander.go("for freedom!");

//    connect(ui->btn_bmi, SIGNAL(clicked()), this, SLOT(printBMI()));
    connect(ui->btn_bmi, &QPushButton::clicked, this, &MainWindow::printBMI); // Qt5，函数地址
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printBMI()
{
    QString text = "Hello, BMI Tool!";
    ui->tb_display->append(text);

    weight = ui->le_weight->text().toDouble();
    height = ui->le_height->text().toDouble();

    double bmi = calculateBMI(weight, height);
    QString strBMI = QVariant(bmi).toString();
    ui->tb_display->append(strBMI);

    interpretBMI(bmi);
}

double MainWindow::calculateBMI(double weight, double height)
{
    double bmi = weight / (height * height);
    return bmi;
}

void MainWindow::interpretBMI(double bmi)
{
    if (bmi < 18.5) {
        ui->tb_display->append("体重过轻");
    } else if (bmi >= 18.5 && bmi < 24) {
        ui->tb_display->append("正常范围");
    } else if (bmi >= 24 && bmi < 28) {
        ui->tb_display->append("体重过重");
    } else if (bmi >= 28 && bmi < 32) {
        ui->tb_display->append("肥胖");
    } else {
        ui->tb_display->append("非常肥胖");
    }
}
