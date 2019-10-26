#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QObject>
#include <QTreeWidgetItem>


class SearchWorker : public QObject
{
    Q_OBJECT

public:
    SearchWorker();

public slots:
    void startSearch(const QString query);

signals:
    void matchFound(QTreeWidgetItem *qtwItem);
    void finished();
};

#endif // SEARCHWORKER_H
