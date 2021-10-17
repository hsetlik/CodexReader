#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H
#include "codexcontent.h"
#include <QWidget>

namespace Ui {
class DictionaryWidget;
}

class DictionaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DictionaryWidget(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDb;
    ~DictionaryWidget();
public slots:
    void view(const QString& trm);

private slots:
    void on_addButton_clicked();

private:
    Ui::DictionaryWidget *ui;
};

#endif // DICTIONARYWIDGET_H
