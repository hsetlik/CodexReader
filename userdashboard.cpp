#include "userdashboard.h"
#include "ui_userdashboard.h"

UserDashboard::UserDashboard(QString usr, CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    username(usr),
    ui(new Ui::UserDashboard),
    importView(new ImportView(db, this)),
    vocabView(new VocabView(db, this)),
    statsView(new StatsView(db, this)),
    lessonList(new LessonList(db, this))
{
    ui->setupUi(this);
    QTabWidget* tabWidget = ui->tabWidget;
    tabWidget->clear();
    //call insertTab(int index, QWidget* content, const QString& name); for each view
    tabWidget->insertTab(0, lessonList, "Lessons");
    tabWidget->insertTab(1, vocabView, "Vocab");
    tabWidget->insertTab(2, importView, "Import");
    tabWidget->insertTab(3, statsView, "Stats");
    //connect(lessonList, &PlainFlashcardAddition::startFlashCards, this, &UserDashboard::sendFlashCardStart);
}

UserDashboard::~UserDashboard()
{
    delete ui;
}

void UserDashboard::on_tabWidget_currentChanged(int index)
{

}


void UserDashboard::on_profileButton_clicked()
{

}


void UserDashboard::on_settingsButton_clicked()
{

}

