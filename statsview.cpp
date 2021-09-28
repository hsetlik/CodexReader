#include "statsview.h"
#include "ui_statsview.h"

StatsView::StatsView(CodexDatabase *db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::StatsView)
{
    ui->setupUi(this);
}

StatsView::~StatsView()
{
    delete ui;
}
