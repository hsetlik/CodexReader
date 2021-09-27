#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "codexdatabase.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(CodexDatabase* db, QWidget *parent = nullptr);
    CodexDatabase* const linkedDatabase;
    ~LoginForm();
signals:
    void loginWithUser(QString name);

private slots:
    void on_login_btn_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
