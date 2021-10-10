#include "plainflashcardaddition.h"
#include "ui_lessonview.h"

PlainFlashcardAddition::PlainFlashcardAddition(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::PlainFlashcardAddition)
{
    ui->setupUi(this);
}

PlainFlashcardAddition::~PlainFlashcardAddition()
{
    delete ui;
}

void PlainFlashcardAddition::on_viewAllButton_clicked()
{

}


void PlainFlashcardAddition::on_addButton_clicked()
{
    auto targetStr = ui->targetEdit->text();
    auto nativeStr = ui->translationEdit->text();
    linkedDatabase->addTerm(targetStr, nativeStr);
}


void PlainFlashcardAddition::on_studyButton_clicked()
{
    emit startFlashCards();

}

