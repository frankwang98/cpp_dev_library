#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QRandomGenerator>

QStringList iconStringList = {
    ":/icon/apple.ico",
    ":/icon/banana.ico",
    ":/icon/orange.ico",
    ":/icon/peach.ico",
    ":/icon/strawberry.ico"
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 默认是列表模式
    mBtnGroup = new QButtonGroup(this);
    mBtnGroup->addButton(ui->rbListMode, 0);
    mBtnGroup->addButton(ui->rbIconMode, 1);
    connect(ui->rbListMode, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbIconMode, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    ui->rbListMode->setChecked(true);
    ui->lwProvince->setViewMode(QListView::ListMode);

    // 条目单击和双击的信号槽
    connect(ui->lwProvince, &QListWidget::itemClicked, this, &Widget::onItemClicked);
    connect(ui->lwProvince, &QListWidget::itemDoubleClicked, this, &Widget::onItemDoubleClicked);

    // add/insert/delete
    connect(ui->btnAdd, &QPushButton::clicked, this, &Widget::onBtnAddClicked);
    connect(ui->btnInsert, &QPushButton::clicked, this, &Widget::onBtnInsertClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &Widget::onBtnDeleteClicked);
}

Widget::~Widget()
{
    delete ui;
}

// 切换显示模式：列表模式、图标模式
void Widget::onRadioButtonClicked()
{
    int checkedId = mBtnGroup->checkedId();
    if(checkedId == 0) {
        ui->lwProvince->setViewMode(QListView::ListMode);
    } else if(checkedId == 1) {
        ui->lwProvince->setViewMode(QListView::IconMode);
    }
}

// 条目单击时，显示到文本框
void Widget::onItemClicked(QListWidgetItem *item)
{
    ui->leCurrentItem->setText(item->text());
}

// 双击条目时，变为可编辑模式
void Widget::onItemDoubleClicked(QListWidgetItem *item)
{
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

// 在最后插入
void Widget::onBtnAddClicked()
{
    int iconIndex = QRandomGenerator::global()->generate()%5; //产生5以内的随机数 0-4
    qDebug() << iconIndex;

    QIcon icon(iconStringList[iconIndex]);
    QString text = ui->leInput->text();

    QListWidgetItem* item = new QListWidgetItem(icon, text);
    ui->lwProvince->addItem(item);
}

// 在当前行之前插入
void Widget::onBtnInsertClicked()
{
    int iconIndex = QRandomGenerator::global()->generate()%5; //产生5以内的随机数 0-4

    QIcon icon(iconStringList[iconIndex]);
    QString text = ui->leInput->text();

    QListWidgetItem* item = new QListWidgetItem(icon, text);

    int currentRow = ui->lwProvince->currentRow();
    ui->lwProvince->insertItem(currentRow, item);
}

// 删除选定的条目
void Widget::onBtnDeleteClicked()
{
#if 0
    // 方法一
    QListWidgetItem* item = ui->lwProvince->currentItem();
    ui->lwProvince->removeItemWidget(item);
    delete item;
#else
    // 方法二
    int row = ui->lwProvince->currentRow();
    QListWidgetItem* item = ui->lwProvince->takeItem(row);
    delete item;
#endif
}

