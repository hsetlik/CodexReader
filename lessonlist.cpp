#include "lessonlist.h"
#include "ui_lessonlist.h"

LessonList::LessonList(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::LessonList)
{
    ui->setupUi(this);
}

LessonList::~LessonList()
{
    delete ui;
}
