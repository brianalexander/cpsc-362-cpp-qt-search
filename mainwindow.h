#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSearchButtonClicked();
    void handleSearchFinished();
    void onMatchFound(QTreeWidgetItem *qtwItem);
    void handleItemClicked(QTreeWidgetItem *item, int column);

signals:
    void forwardStartSearch(QString searchQuery);

private:
    Ui::MainWindow *ui;
    QThread searchThread;
};
#endif // MAINWINDOW_H
