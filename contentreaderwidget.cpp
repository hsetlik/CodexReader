#include "contentreaderwidget.h"
#include "ui_textreader.h"
#include <QtWidgets>
ContentReaderWidget::ContentReaderWidget(CodexContent* content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextReader),
    parentContent(content),
    transcript(parentContent->getFullTranscript())
{
    ui->setupUi(this);
    auto fullText = FullText(parentContent->fullContent());
    fullTranscript = fullText.getTranscript(parentContent->linkedDatabase);

    //create labels for each word
    auto transcriptWidget = new QWidget(this);
    auto masterLayout = new QVBoxLayout;
    auto currentLine = new QHBoxLayout;
    int currentLineLength = 0;
    for (auto & word : fullTranscript)
    {
        CodexLabelBase* wordLabel = nullptr;
        if (word.second != nullptr)
        {
           wordLabel = new SeenTermLabel(word.second, transcriptWidget);
        }
        else
        {
            wordLabel = new NewTermLabel(word.first, transcriptWidget);
        }
        allLabels.push_back(wordLabel);
        currentLine->addWidget(wordLabel, wordLabel->width());
        currentLine->setAlignment(wordLabel, Qt::AlignLeft);
        currentLineLength += wordLabel->width() + 1;
        if (currentLineLength > 260)
        {
            auto spacer = new QSpacerItem( width() - currentLineLength, wordLabel->height(), QSizePolicy::Maximum, QSizePolicy::Maximum);
            currentLine->addSpacerItem(spacer);
            masterLayout->addLayout(currentLine);
            currentLine = new QHBoxLayout;
            currentLineLength = 0;
        }
        connect(wordLabel, &CodexLabelBase::wordClicked, this, &ContentReaderWidget::termSelected);
    }
    transcriptWidget->setLayout(masterLayout);
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
