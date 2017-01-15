#include <QDebug>

#include "skeleton.h"
#include "ui_skeleton.h"

#include "qlwi_group.h"
#include "helper_macro.h"
#include "helper_settings.h"
#include "manager_group.h"
#include "manager_console.h"

Skeleton::Skeleton(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Skeleton)
{
    ui->setupUi(this);

    connect(ConsoleManager::GetInstance()->consoleThread, SIGNAL(newElement(QString, bool)), this, SLOT(on_consoleNewElement(QString, bool)));
    connect(GroupManager::GetInstance(), SIGNAL(refreshed()), this, SLOT(on_groupsRefresh()));
    connect(GroupManager::GetInstance(), SIGNAL(refreshed(QLWI_Group*)), this, SLOT(on_groupsRefresh(QLWI_Group*)));

    GroupManager::GetInstance()->LoadDataFromFile(DATA_FILE_PATH);
}

Skeleton::~Skeleton()
{
    GroupManager::DestroyInstance();
    ConsoleManager::DestroyInstance();

    delete ui;
}

void Skeleton::on_consoleNewElement(QString str, bool isHTMLTag)
{
    ui->console_textEdit->moveCursor(QTextCursor::End);

    if (isHTMLTag)
        ui->console_textEdit->insertHtml(str);
    else
        ui->console_textEdit->insertPlainText(str);
}

void Skeleton::on_groupsRefresh()
{
    ui->entity_listWidget->clear();

    QListWidgetItem *widgetItem;
    QLWI_Group *widgetItemTemplate;

    foreach(Group group, GroupManager::GetInstance()->groups)
    {
        widgetItem = new QListWidgetItem(ui->entity_listWidget);
        widgetItemTemplate = new QLWI_Group(ui->entity_listWidget, widgetItem, group.GetID());

        ui->entity_listWidget->addItem(widgetItem);
        ui->entity_listWidget->setItemWidget(widgetItem, widgetItemTemplate);

        widgetItem->setSizeHint(widgetItemTemplate->sizeHint());

        QString str = GroupManager::GetInstance()->GetGroupByID(group.GetID())->GetName() + " has been added to the list.\n";
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);
    }

    QString str = GroupManager::GetInstance()->GetDataFilePath() + " has been loaded.\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);
}

void Skeleton::on_groupsRefresh(QLWI_Group *row)
{
    if(row != nullptr)
    {
        Group* group = GroupManager::GetInstance()->GetGroupByID(row->GetID());

        if (group != nullptr)
            row->SetName(group->GetName());
    }
}

void Skeleton::on_add_group_pushButton_clicked() { }

void Skeleton::on_save_group_pushButton_clicked()
{
    GroupManager::GetInstance()->SaveDataToFile(DATA_FILE_PATH);
}
