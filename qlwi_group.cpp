#include "qlwi_group.h"

#include <QLabel>
#include <QDebug>

#include "manager_console.h"
#include "manager_group.h"

QLWI_Group::QLWI_Group(QListWidget* view, QListWidgetItem* item, unsigned int ID)
    : _view(view),
      _item(item),
      _ID(ID)
{
    _baseLayout = new QHBoxLayout();

    _name = new QLabel(GroupManager::GetInstance()->GetGroupByID(_ID)->GetName(), _baseLayout->widget());

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

void QLWI_Group::on_edit_pushButton_clicked()
{
    QString str = "Edit button for " + GroupManager::GetInstance()->GetGroupByID(_ID)->GetName() + " has been clicked.\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str, ConsoleTextType::ACTION);

    Group* group = GroupManager::GetInstance()->GetGroupByID(_ID);
    group->SetName("New Group Name " + QString::number(_ID));

    str = GroupManager::GetInstance()->GetGroupByID(_ID)->GetName() + " has been edited.\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);

    GroupManager::GetInstance()->refreshed(this);
}

void QLWI_Group::on_delete_pushButton_clicked()
{
    QString str = "Delete button for " + GroupManager::GetInstance()->GetGroupByID(_ID)->GetName() + " has been clicked.\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str, ConsoleTextType::ACTION);

    if(_view != nullptr && _item != nullptr)
        _view->takeItem(_view->row(_item));

    str = GroupManager::GetInstance()->GetGroupByID(_ID)->GetName() + " has been removed from the list.\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);
}

void QLWI_Group::SetName(QString name)
{
    _name->setText(name);
}

unsigned int QLWI_Group::GetID()
{
    return _ID;
}
