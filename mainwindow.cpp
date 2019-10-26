#include <QDirIterator>
#include <QtDebug>
#include <QDateTime>
#include <QThread>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "searchworker.h"
#include "filecontentview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    SearchWorker *worker = new SearchWorker;
    worker->moveToThread(&searchThread);
    ui->setupUi(this);
    ui->treeWidget->hideColumn(6);

    // start search when clicked.
    connect(this, &MainWindow::forwardStartSearch, worker, &SearchWorker::startSearch);

    // change to search ui when clicked.
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleSearchButtonClicked);

    // update ui when a match is found.
    connect(worker, &SearchWorker::matchFound, this, &MainWindow::onMatchFound);

    // listen for search finished
    connect(worker, &SearchWorker::finished, this, &MainWindow::handleSearchFinished);

    // listen for doubleclicked items
    connect(ui->treeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::handleItemClicked);

    searchThread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    searchThread.quit();
    searchThread.wait();
}

void MainWindow::handleSearchButtonClicked() {
    ui->stackedWidget->setCurrentIndex(1);
    emit forwardStartSearch(ui->lineEdit->text());

}

void MainWindow::handleSearchFinished() {
    qDebug() << "Finished";
}

void MainWindow::onMatchFound(QTreeWidgetItem *qtwItem){
    ui->treeWidget->addTopLevelItem(qtwItem);
}

void MainWindow::handleItemClicked(QTreeWidgetItem *item, int column) {
    FileContentView *newWindow = new FileContentView();

    QFile file(item->text(6));
    file.open(QFile::ReadOnly | QFile::Text);

    QString fileContentString = QString::fromStdString(file.readAll().toStdString());

    newWindow->setText(fileContentString);
    newWindow->show();
    file.close();
}