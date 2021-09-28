#include "loginform.h"
#include "ui_loginform.h"
#include <QtWidgets>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

LoginForm::LoginForm(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);


}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_login_btn_clicked()
{
    auto usrString = ui->usr_edit->text();
    auto pswdString = ui->pswd_edit->text();
    if (linkedDatabase->attemptLogin(usrString, pswdString))
    {
        if (ui->remember_checkbox->isChecked())
        {
            setKeychain(usrString, pswdString);
        }
        printf ("login successful\n");
        emit loginWithUser(usrString);
    }

}

bool LoginForm::hasKeychain()
{
    auto dir = QDir::current();
    auto path = dir.filePath("codex_keychain.json");
    QFile file(path);
    if(!file.exists())
        return false;
    file.open(QIODevice::ReadWrite);
    QByteArray bytes = file.readAll();
    file.close();
    printf("File has size: %d bytes\n", bytes.size());
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    auto obj = doc.object();
    if(obj["UseKeychain"].toBool())
        return true;
    return false;
}

void LoginForm::setKeychain(QString username, QString password)
{
    auto dir = QDir::current();
    auto path = dir.filePath("codex_keychain.json");
    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QJsonObject obj;
        obj["UseKeychain"] = true;
        obj["User"] = username;
        obj["Password"] = password;
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    }
    else
        printf ("file not opened\n");

}

