#include "importview.h"
#include "ui_importview.h"

ImportView::ImportView(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::ImportView)
{
    ui->setupUi(this);
}

ImportView::~ImportView()
{
    delete ui;
}
