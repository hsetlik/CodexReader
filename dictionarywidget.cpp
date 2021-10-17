#include "dictionarywidget.h"
#include "ui_dictionarywidget.h"

DictionaryWidget::DictionaryWidget(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDb(db),
    ui(new Ui::DictionaryWidget)
{
    ui->setupUi(this);
}

DictionaryWidget::~DictionaryWidget()
{
    delete ui;
}
void DictionaryWidget::view(const QString& trm)
{
    auto term = linkedDb->getTerm(trm);
    if (term != nullptr) // determine whether the term is seen or not
    {
        //set the target label
        ui->targetLabel->setText(term->getTarget());
        delete term;
    }
    else
    {

    }

}

void DictionaryWidget::on_addButton_clicked()
{

}

