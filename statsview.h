#ifndef STATSVIEW_H
#define STATSVIEW_H

#include <QWidget>
#include "codexcontent.h"

namespace Ui {
class StatsView;
}

class StatsView : public QWidget
{
    Q_OBJECT

public:
    explicit StatsView(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~StatsView();

private:
    Ui::StatsView *ui;
};

#endif // STATSVIEW_H
