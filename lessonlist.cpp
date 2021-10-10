#include "lessonlist.h"
#include "ui_lessonlist.h"
#include <QDebug>
ContentListEntry::ContentListEntry(QString& name, QWidget* parent) :
    QWidget(parent),
    contentName(name)
{
    vBox = new QVBoxLayout(this);
    setLayout(vBox);
    nameLabel = new QLabel(contentName, this);
    vBox->addWidget(nameLabel);
}
//==================================================================
LessonList::LessonList(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::LessonList)
{
    ui->setupUi(this);
    auto content_names = linkedDatabase->getContentNames();
    for (auto& name : content_names)
    {
        qDebug() << "Content with name: " << name;
        contentEntries.push_back(new ContentListEntry(name, this));
        ui->contentEntryLayout->addWidget(contentEntries.back());
    }
}

LessonList::~LessonList()
{
    delete ui;
}
