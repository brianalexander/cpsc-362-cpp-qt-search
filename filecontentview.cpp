#include "filecontentview.h"
#include "ui_filecontentview.h"

#include <QDebug>

FileContentView::FileContentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileContentView)
{
    ui->setupUi(this);
}

FileContentView::~FileContentView()
{
    delete ui;
}

void FileContentView::setText(QString fileContent) {
    qDebug() << "setting text";
    ui->plainTextEdit->setPlainText(fileContent);
}
