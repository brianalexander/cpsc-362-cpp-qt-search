#include <QDirIterator>
#include <QtDebug>
#include <QDateTime>
#include <QThread>
#include <QDebug>

#include "searchworker.h"

#include <QRegularExpression>


SearchWorker::SearchWorker()
{

}

void SearchWorker::startSearch(const QString query) {
    QRegularExpression re(".*" + query + ".*");
    qDebug() << "searching for " << ".*" + query + ".*";

    QStringList extensionFilter = QStringList();
    extensionFilter.append("*.cpp");

    QDirIterator it("/Users/local/ACAD/balexander28", extensionFilter, QDir::Files, QDirIterator::Subdirectories);

    QTreeWidgetItem *qtwItem;
    QStringList files;
    while (it.hasNext()) {
        QFile f(it.next());
        f.open(QFile::ReadOnly | QFile::Text);
        QString fileContentString = QString::fromStdString(f.readAll().toStdString());
        f.close();
        QRegularExpressionMatchIterator it = re.globalMatch(fileContentString);
        if(it.hasNext()) {
            QFileInfo fileInfo(f);

            QString createdOn = fileInfo.created().toString("MM/dd/yyyy");
            QString lastModified = fileInfo.lastModified().toString("MM/dd/yyyy");

            qtwItem = new QTreeWidgetItem();
            qtwItem->setText(0, fileInfo.fileName()); // name
            qtwItem->setText(1, fileInfo.suffix()); // type
            qtwItem->setText(2, QString::number(fileInfo.size()/1024)); // size
            qtwItem->setText(3, lastModified); // last mod
            qtwItem->setText(4, createdOn); // count
            qtwItem->setText(5, tr("... here is the context ...")); // context
            qtwItem->setText(6, fileInfo.filePath());

            emit matchFound(qtwItem);
        }
    }

    emit finished();
}

