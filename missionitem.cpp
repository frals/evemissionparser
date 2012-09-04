#include "missionitem.h"
#include <QDateTime>
#include <QDebug>

MissionItem::MissionItem(QString date, QString time, QString standing, bool status, QString title, QObject *parent) :
    m_date(date), m_time(time), m_standing(standing), m_status(status), m_title(title),
    QObject(parent)
{
    m_duration = 0;
    dataChanged();
}

MissionItem::MissionItem() {}

void MissionItem::setDuration(const QString &prev)
{
    qDebug() << Q_FUNC_INFO << prev;
    // if declined, dont compute
    if(!m_status)
        return;

    QDateTime prevt = QDateTime::fromString(prev, "yyyy.MM.dd HH:mm");
    QDateTime curr = QDateTime::fromString(m_date + " " + m_time, "yyyy.MM.dd HH:mm");
    m_duration = prevt.secsTo(curr);
    if(m_duration > 60*60) /* longer than one hour -> dont care? */
        m_duration = 99999;
    dataChanged();
}
