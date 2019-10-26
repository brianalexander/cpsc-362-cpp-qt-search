#ifndef FILECONTENTVIEW_H
#define FILECONTENTVIEW_H

#include <QWidget>

namespace Ui {
class FileContentView;
}

class FileContentView : public QWidget
{
    Q_OBJECT

public:
    explicit FileContentView(QWidget *parent = nullptr);
    ~FileContentView();
    void setText(QString fileContent);

private:
    Ui::FileContentView *ui;
};

#endif // FILECONTENTVIEW_H
