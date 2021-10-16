#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QWidget>

namespace Ui {
class TextReader;
}

class TextReader : public QWidget
{
    Q_OBJECT

public:
    explicit TextReader(QWidget *parent = nullptr);
    ~TextReader();

private:
    Ui::TextReader *ui;
};

#endif // TEXTREADER_H
