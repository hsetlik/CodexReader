#include "wordlabel.h"
#include <QMouseEvent>
#include <QPainter>
#include <qtutil.h>
WordLabel::WordLabel(Term* term, QWidget* parent) :
    QLabel(parent),
    parentTerm(term)
{
    auto txt = parentTerm->getTarget();
    setText(txt);
    ease = parentTerm->getNormalizedEase();
    background = colorForEase(ease);
}
void WordLabel::paintEvent (QPaintEvent*)
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
void WordLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::MouseButton::LeftButton)
    {
        emit wordClicked(text());
    }
}
void WordLabel::setEase(int ease)
{
    parentTerm->answerSM2(ease);
    ease = parentTerm->getNormalizedEase();
    background = colorForEase(ease);
    repaint();
    emit easeChanged(ease);
}
QColor WordLabel::colorForEase(float ease)
{
    const auto colorA = QColor(190, 100, 100, 200);
    const auto colorB = QColor(255, 255, 255, 200);
    return MyQtUtil::colorLerp(colorA, colorB, ease);
}
