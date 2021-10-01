#include "flashcardview.h"
#include "ui_flashcardview.h"

FlashCardView::FlashCardView(CodexDatabase *db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::FlashCardView)
{
    ui->setupUi(this);
    linkedDatabase->termsDueNow(termsToReview);
    if(toNextTerm())
        ui->viewerLayout->addWidget(viewer.get());
}

FlashCardView::~FlashCardView()
{
    delete ui;
}

bool FlashCardView::toNextTerm() // returns true if 1 or more due terms left
{
    if (termsToReview.begin() == termsToReview.end())
        return false;
    else
    {
        viewer.reset(ViewerFactory::viewerFor(&termsToReview.front(), this));
        termsToReview.erase(termsToReview.begin());
        return true;
    }
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



