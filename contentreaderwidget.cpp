#include "contentreaderwidget.h"
#include "ui_textreader.h"
#include <QtWidgets>
ContentReaderWidget::ContentReaderWidget(CodexContent* content, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextReader),
    parentContent(content),
    transcript(parentContent->getFullTranscript())
{
    const int readerWidth = 250;
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
        wordLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        allLabels.push_back(wordLabel);
        currentLine->addWidget(wordLabel);
        currentLine->setAlignment(wordLabel, Qt::AlignLeft);
        if (currentLineLength > readerWidth)
        {
            qDebug() << "Line Length: " << currentLineLength;
            //currentLine->addSpacing(width() - currentLineLength);
            masterLayout->addLayout(currentLine);
            currentLine = new QHBoxLayout;
            currentLineLength = 0;
        }
        qDebug() << "Label: " << wordLabel->text() << " has width: " << wordLabel->width();
        currentLineLength += wordLabel->width() + 1;
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
    qDebug() << "Term Selected: " << term;
    emit termToDictionary(term);
}
