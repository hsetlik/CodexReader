#ifndef IMPORTVIEW_H
#define IMPORTVIEW_H

#include <QWidget>
#include "codexcontent.h"

namespace Ui {
class ImportView;
}

class ImportView : public QWidget
{
    Q_OBJECT

public:
    explicit ImportView(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~ImportView();

private:
    Ui::ImportView *ui;
};

#endif // IMPORTVIEW_H
