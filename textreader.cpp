#include "textreader.h"
#include "ui_textreader.h"

TextReader::TextReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextReader)
{
    ui->setupUi(this);
}

TextReader::~TextReader()
{
    delete ui;
}
