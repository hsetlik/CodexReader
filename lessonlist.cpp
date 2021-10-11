#include "lessonlist.h"
#include "ui_lessonlist.h"
#include <QDebug>
 ContentNameLabel::ContentNameLabel(const QString& text, QWidget* parent) :
     QLabel(text, parent),
     mouseIsOver(false)
 {
     highlightColor = QColor(180, 180, 180);
     normalColor = highlightColor.darker();
 }
void ContentNameLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::MouseButton::LeftButton)
        emit labelClicked();
}
void ContentNameLabel::enterEvent(QEvent*)
{
    mouseIsOver = true;
    repaint();
}
void ContentNameLabel::leaveEvent(QEvent*)
{
    mouseIsOver = false;
    repaint();
}
void ContentNameLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    auto brushColor = (mouseIsOver) ? highlightColor : normalColor;
    QPen pen(brushColor, 1.8f, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
    painter.setPen(pen);
    const auto rectangle = QRect(0, 0., 500, 50);
    QRect bounds;
    painter.drawText(rectangle, 0, text(), &bounds);
}
//==================================================================
ContentListEntry::ContentListEntry(QString& name, QWidget* parent) :
    QWidget(parent),
    contentName(name)
{
    vBox = new QVBoxLayout(this);
    setLayout(vBox);
    label = new ContentNameLabel(contentName, this);
    vBox->addWidget(label);
    setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Fixed);
}
//==================================================================
LessonList::LessonList(CodexDatabase* db, QWidget *parent) :
    QWidget(parent),
    linkedDatabase(db),
    ui(new Ui::LessonList)
{
    ui->setupUi(this);
    auto content_names = linkedDatabase->getContentNames();
    for (auto& name : content_names)
    {
        qDebug() << "Content with name: " << name;
        auto entry = new ContentListEntry(name, this);
        contentEntries.push_back(entry);
        ui->contentEntryLayout->addWidget(entry);
        connect(entry->label, &ContentNameLabel::labelClicked, this, &LessonList::contentClicked);
    }
}
void LessonList::contentClicked()
{
    auto label = qobject_cast<ContentNameLabel*>(sender());
    auto toOpen = label->text();
    qDebug() << "Opening: " << toOpen;
    emit openContentBrowser(toOpen);
}

LessonList::~LessonList()
{
    delete ui;
}
