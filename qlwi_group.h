#pragma once

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class QLWI_Group : public QWidget
{
    Q_OBJECT

public:
    QLWI_Group(QListWidget *view, QListWidgetItem *item, unsigned int ID);

    void SetName(QString name);
    unsigned int GetID();

private:
    QListWidget *_view;
    QListWidgetItem *_item;
    unsigned int _ID;

    QHBoxLayout *_baseLayout;
    QLabel *_name;
    QPushButton *_editButton;
    QPushButton *_deleteButton;

private slots:
    void on_edit_pushButton_clicked();
    void on_delete_pushButton_clicked();
};
