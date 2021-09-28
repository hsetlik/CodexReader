#include "vocabview.h"
#include "ui_vocabview.h"

VocabView::VocabView(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::VocabView)
{
    ui->setupUi(this);
}

VocabView::~VocabView()
{
    delete ui;
}
