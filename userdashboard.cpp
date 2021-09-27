#include "userdashboard.h"
#include "ui_userdashboard.h"

UserDashboard::UserDashboard(QString usr, CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    username(usr),
    ui(new Ui::UserDashboard)
{
    ui->setupUi(this);
    QTabWidget* tabWidget = ui->tabWidget;
    tabWidget->clear();
    //call insertTab(int index, QWidget* content, const QString& name); for each view
    tabWidget->insertTab(0, new QWidget(this), "My Lessons");
    tabWidget->insertTab(1, new QWidget(this), "Vocab");
    tabWidget->insertTab(2, new QWidget(this), "Browse");
    tabWidget->insertTab(3, new QWidget(this), "Stats");
}

UserDashboard::~UserDashboard()
{
    delete ui;
}

void UserDashboard::on_tabWidget_currentChanged(int index)
{

}

