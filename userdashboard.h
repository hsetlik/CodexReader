#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QWidget>

namespace Ui {
class UserDashboard;
}

class UserDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit UserDashboard(QWidget *parent = nullptr);
    ~UserDashboard();

private:
    Ui::UserDashboard *ui;
};

#endif // USERDASHBOARD_H
