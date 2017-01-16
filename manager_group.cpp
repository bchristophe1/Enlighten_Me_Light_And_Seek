#include "manager_group.h"

#include <QThread>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>

#include "helper_settings.h"
#include "manager_console.h"

DEFINE_SINGLETON(GroupManager)

GroupManager::GroupManager() { }

GroupManager::~GroupManager() { }

/**
 * @brief GroupManager::on_loadFileRequest
 *
 */
void GroupManager::on_loadFileRequest()
{
    QString str = "Loading " + GroupManager::GetInstance()->GetDataFilePath() + "...\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);

    groups.clear();
    _groupCounter = STARTING_GROUP_COUNTER;
    _userCounter = STARTING_USER_COUNTER;

    // Move this code into LoadDataFromFile Methods

    _jsonFile.setFileName(DATA_FILE_PATH);
    _jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    _dataFilePath = _jsonFile.readAll();
    _jsonFile.close();
    _jsonDocument = QJsonDocument::fromJson(_dataFilePath.toUtf8());

    _GroupjsonObject = _jsonDocument.object();
    _GroupjsonArray = _GroupjsonObject["groups"].toArray();

    QJsonObject _obj;

    foreach (_GroupjsonValue, _GroupjsonArray) {

        _obj = _GroupjsonValue.toObject();

        Group group(_obj["id"].toString().toInt(), _obj["name"].toString());
        _UserjsonArray =  _obj["users"].toArray();

        foreach (_UserjsonValue, _UserjsonArray) {

           _UserjsonObject = _UserjsonValue.toObject();

           User user(_UserjsonObject["id"].toString().toInt(), _obj["id"].toString().toInt(), _UserjsonObject["name"].toString());
           group.users.append(user);

           _userCounter++;
        }

        group.serialize();

        groups.append(group);
        _groupCounter++;
    }

    emit refreshed();
}

void GroupManager::on_saveFileRequest()
{
    QString str = "Saving data to " + GroupManager::GetInstance()->GetDataFilePath() + "...\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);

    // TO DO

    str = "Data has been saved to " + GroupManager::GetInstance()->GetDataFilePath() + ".\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);
}

void GroupManager::LoadDataFromFile(QString filePath)
{
    QThread thread;

    connect(&thread, SIGNAL(started()), this, SLOT(on_loadFileRequest()));

    _dataFilePath = filePath;

    thread.start();
    thread.quit();
    thread.wait();
}

void GroupManager::SaveDataToFile(QString filePath)
{
    QThread thread;

    connect(&thread, SIGNAL(started()), this, SLOT(on_saveFileRequest()));

    _dataFilePath = filePath;

    thread.start();
    thread.quit();
    thread.wait();
}

Group* GroupManager::GetGroupByID(unsigned int ID)
{
    for (int i = 0 ; i < groups.size() ; i++)
    {
        if (groups[i].GetID() == ID)
            return &groups[i];
    }

    return nullptr;
}

QString GroupManager::GetDataFilePath()
{
    return _dataFilePath;
}
