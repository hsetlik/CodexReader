#include "contentreaderwidget.h"
#include "ui_textreader.h"

ContentReaderWidget::ContentReaderWidget(CodexContent* content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextReader),
    parentContent(content),
    transcript(parentContent->getFullTranscript())
{
    ui->setupUi(this);
    //create labels for each word
    int x = 5;
    int y = 5;
    auto transcriptWidget = new QWidget(this);
    for (auto & word : transcript)
    {
        CodexLabelBase* wordLabel = nullptr;
        if (word.second != nullptr)
        {
           wordLabel = new NewTermLabel(word.first, transcriptWidget);
        }
        else
        {
            wordLabel = new SeenTermLabel(word.second, transcriptWidget);
        }
        allLabels.push_back(wordLabel);
        wordLabel->move(x, y);
        wordLabel->show();
        wordLabel->setAttribute(Qt::WA_DeleteOnClose);
        x += wordLabel->width() + 2;
        if (x >= 245)
        {
            x = 5;
            y += wordLabel->height() + 2;
        }
        connect(wordLabel, &CodexLabelBase::wordClicked, this, &ContentReaderWidget::termSelected);
    }
    ui->scrollArea->setWidget(transcriptWidget);
}

ContentReaderWidget::~ContentReaderWidget()
{
    delete ui;
}

void ContentReaderWidget::termSelected(QString term)
{
    emit termToDictionary(term);
}
