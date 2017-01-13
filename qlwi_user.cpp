#include "qlwi_user.h"

#include <QLabel>
#include <QDebug>

#include "manager_console.h"

QLWI_User::QLWI_User(QListWidget* view, QListWidgetItem* item, unsigned int ID)
    : _view(view),
      _item(item),
      _ID(ID)
{
    _baseLayout = new QHBoxLayout();

    _name = new QLabel("User " + QString::number(ID), _baseLayout->widget());

    _editButton = new QPushButton("E", _baseLayout->widget());
    _editButton->setMinimumWidth(24);
    _editButton->setMaximumWidth(24);
    _deleteButton = new QPushButton("D", _baseLayout->widget());
    _deleteButton->setMinimumWidth(24);
    _deleteButton->setMaximumWidth(24);
    connect(_editButton, SIGNAL(clicked()), this, SLOT(on_edit_pushButton_clicked()));
    connect(_deleteButton, SIGNAL(clicked()), this, SLOT(on_delete_pushButton_clicked()));

    _baseLayout->addWidget(_name);
    _baseLayout->addWidget(_editButton);
    _baseLayout->addWidget(_deleteButton);

    setLayout(_baseLayout);
}

void QLWI_User::on_edit_pushButton_clicked()
{
    // TO DO
}

void QLWI_User::on_delete_pushButton_clicked()
{
    // TO DO
}
