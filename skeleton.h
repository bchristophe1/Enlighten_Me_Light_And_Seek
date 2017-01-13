#pragma once

#include <QMainWindow>

#include "qlwi_group.h"

namespace Ui {
class Skeleton;
}

class Skeleton : public QMainWindow
{
    Q_OBJECT

public:
    explicit Skeleton(QWidget *parent = 0);
    ~Skeleton();

public slots:
    void on_consoleNewElement(QString str, bool isHTMLTag = false);
    void on_groupsRefresh();
    void on_groupsRefresh(QLWI_Group *row);

private slots:
    void on_add_group_pushButton_clicked();
    void on_save_group_pushButton_clicked();

private:
    Ui::Skeleton *ui;
};
