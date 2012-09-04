#include "cpwatcher.h"
#include <QClipboard>
#include <QDebug>
#include <QApplication>
#include <QRegExp>
#include <QStringList>
#include <QList>
#include "missionitem.h"

CPWatcher::CPWatcher(QObject *parent) :
   QObject(parent)
{
    m_completed = 0;
    m_declined = 0;
    m_clipboard = QApplication::clipboard();
    // yeah, totally stole murkelis regexp
    m_regexp = new QRegExp("(\\d{4}\\.\\d{2}\\.\\d{2})\\s(\\d{2}:\\d{2})\\s([-+]?[0-9]*\\.?[0-9]+)\\s%\\sMission\\s(Declined|Completed)\\s-\\s(.+)");
    connect(m_clipboard, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
    m_list = QList<QObject*>();
}

CPWatcher::~CPWatcher()
{
    qDebug() << Q_FUNC_INFO;
}

void CPWatcher::dataChanged()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << m_clipboard->text(QClipboard::Clipboard);
    parseShit(m_clipboard->text(QClipboard::Clipboard));
}

QStringList CPWatcher::parseShit(const QString &str)
{
    QStringList split = str.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    QString s;
    foreach(s, split) {
        m_regexp->indexIn(s); // why we have to do this is beyond me
        QStringList list = m_regexp->capturedTexts();
        qDebug() << list;
        m_list.append(new MissionItem(list[1], list[2], list[3], (list[4] == "Completed"), list[5]));
        if(list[4] == "Completed")
            m_completed++;
        else
            m_declined++;
    }
    MissionItem *curr = qobject_cast<MissionItem*>(m_list.at(0));
    MissionItem *prev;
    /* ugly stuff is ugly, but quick hack is quick */
    for(int i = 0; i < m_list.length(); i++) {
        // calc duration this mission was, taking value from prev
        if(i+2 > m_list.length())
            break;
        prev = qobject_cast<MissionItem*>(m_list.at(i+1));
        curr->setDuration(prev->date() + " " + prev->time());
        curr = prev;
    }
    clipboardListChanged();
}

QList<QObject*> CPWatcher::clipboardList()
{
    return m_list;
}
