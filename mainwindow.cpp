#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto mainView = new MasterStackedWidget(this);
    ui->verticalLayout->addWidget(mainView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

