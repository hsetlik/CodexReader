#ifndef CONTENTREADERWIDGET_H
#define CONTENTREADERWIDGET_H

#include <QWidget>
#include "codexcontent.h"
#include "wordlabel.h"
namespace Ui {
class TextReader;
}

class ContentReaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentReaderWidget(CodexContent* content, QWidget *parent = nullptr);
    ~ContentReaderWidget();
public slots:
    void termSelected(QString term);
signals:
    void termToDictionary(QString term);
private:
    Ui::TextReader *ui;
    CodexContent* const parentContent;
    std::map<QString, Term*> transcript;
    std::vector<CodexLabelBase*> allLabels;
    OrderedTranscript fullTranscript;
};

#endif // CONTENTREADERWIDGET_H
