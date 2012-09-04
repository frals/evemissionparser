#ifndef CPWATCHER_H
#define CPWATCHER_H

#include <QObject>
class QClipboard;
class QRegExp;
#include <QList>
class QStringList;

class CPWatcher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> clipboardList READ clipboardList NOTIFY clipboardListChanged)
    Q_PROPERTY(int completed READ completed NOTIFY clipboardListChanged)
    Q_PROPERTY(int declined READ declined NOTIFY clipboardListChanged)

public:
    explicit CPWatcher(QObject *parent = 0);
    ~CPWatcher();

    Q_INVOKABLE QList<QObject*> clipboardList();
    int completed() { return m_completed; }
    int declined() { return m_declined; }

signals:
    void clipboardListChanged();
    
public slots:
    void dataChanged();

private:
    QClipboard* m_clipboard;
    QRegExp* m_regexp;
    QList<QObject*> m_list;
    int m_completed;
    int m_declined;
    
    QStringList parseShit(const QString& str);
};

#endif // CPWATCHER_H
