#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <QObject>
#include <QDateTime>

class MissionItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date NOTIFY dataChanged)
    Q_PROPERTY(QString time READ time NOTIFY dataChanged)
    Q_PROPERTY(QString standing READ standing NOTIFY dataChanged)
    Q_PROPERTY(bool status READ status NOTIFY dataChanged)
    Q_PROPERTY(QString title READ title NOTIFY dataChanged)
    Q_PROPERTY(int duration READ duration NOTIFY dataChanged)
public:
    explicit MissionItem(QString date, QString time, QString standing, bool status, QString title, QObject *parent = 0);
    MissionItem();

    QString date() { return m_date; }
    QString time() { return m_time; }
    QString standing() { return m_standing; }
    bool status() { return m_status; }
    QString title() { return m_title; }
    int duration() { return m_duration; }

    void setDuration(const QString& prev);

signals:
    void dataChanged();
    
public slots:
private:
    QString m_date;
    QString m_time;
    QString m_standing;
    QString m_title;
    bool m_status;
    int m_duration;
};

#endif // MISSIONITEM_H
