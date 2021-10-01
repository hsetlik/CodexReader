#include "flashcardview.h"
#include "ui_flashcardview.h"

FlashCardView::FlashCardView(CodexDatabase *db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::FlashCardView)
{
    ui->setupUi(this);
}

FlashCardView::~FlashCardView()
{
    delete ui;
}

void FlashCardView::on_ans1_clicked()
{

}
void FlashCardView::on_ans2_clicked()
{

}
void FlashCardView::on_ans3_clicked()
{

}
void FlashCardView::on_ans4_clicked()
{

}
void FlashCardView::on_ans5_clicked()
{

}



