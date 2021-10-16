#include "wordlabel.h"
#include <QMouseEvent>
#include <QPainter>
#include <qtutil.h>
SeenTermLabel::SeenTermLabel(Term* term, QWidget* parent) :
    CodexLabelBase(parent),
    parentTerm(term)
{
    auto txt = parentTerm->getTarget();
    setText(txt);
    ease = parentTerm->getNormalizedEase();
    background = colorForEase(ease);
}
void SeenTermLabel::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QBrush brush(background);
    auto cornerSize = (float)frameRect().height() / 5.0f;
    auto bounds = QRectF(frameRect());
    painter.setBrush(brush);
    painter.drawRoundedRect(bounds, cornerSize, cornerSize);
    QPen pen(Qt::black, 1.8f, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
    painter.setPen(pen);
    auto textCorner = QPointF(cornerSize, cornerSize * 3.3f);
    painter.drawText(textCorner, text());
}
void SeenTermLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::MouseButton::LeftButton)
    {
        emit wordClicked(text());
    }
}
void SeenTermLabel::setEase(int ease)
{
    parentTerm->answerSM2(ease);
    ease = parentTerm->getNormalizedEase();
    background = colorForEase(ease);
    repaint();
    emit easeChanged(ease);
}
QColor SeenTermLabel::colorForEase(float ease)
{
    const auto colorA = QColor(190, 100, 100, 200);
    const auto colorB = QColor(255, 255, 255, 200);
    return MyQtUtil::colorLerp(colorA, colorB, ease);
}
NewTermLabel::NewTermLabel(const QString& word, QWidget* parent) :
    CodexLabelBase(parent)
{
    setText(word);
    background = Qt::blue;
}
void NewTermLabel::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QBrush brush(background);
    auto cornerSize = (float)frameRect().height() / 5.0f;
    auto bounds = QRectF(frameRect());
    painter.setBrush(brush);
    painter.drawRoundedRect(bounds, cornerSize, cornerSize);
    QPen pen(Qt::black, 1.8f, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
    painter.setPen(pen);
    auto textCorner = QPointF(cornerSize, cornerSize * 3.3f);
    painter.drawText(textCorner, text());
}
void NewTermLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::MouseButton::LeftButton)
    {
        emit wordClicked(text());
    }
}

