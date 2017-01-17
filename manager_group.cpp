#include "manager_group.h"

#include <QThread>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <QMessageBox>

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

    _jsonFile.setFileName(DATA_FILE_PATH);

    // Checking if json folder existing
    if (QDir("json").exists()) {
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer("Json Folder Has Been Found\n");
    } else {
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer("Json Folder Has Been Not Found...\n");
        QDir().mkdir("json");
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer("Json Folder Has Been Created\n");
    }

    // Checking if json file exist
    if (_jsonFile.exists()) {
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer("Json Config File Has Been Found\n");
        qDebug() << "Json Config File Found";
    } else {
        ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer("Json Config File Has Been NOT Found\n");
        qDebug() << "Json Config File NOT Found";
        QMessageBox::critical(NULL, "Configuration File Not Found", "The configuration file doesn't exist !");
    }

    _jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    _dataFilePath = _jsonFile.readAll();
    _jsonFile.close();
    _jsonDocumentParsing = QJsonDocument::fromJson(_dataFilePath.toUtf8());

    _GroupjsonObject = _jsonDocumentParsing.object();
    _GroupjsonArray = _GroupjsonObject["Groups"].toArray();

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

        groups.append(group);
        _groupCounter++;
    }

    this->serialize();

    emit refreshed();

    this->on_saveFileRequest();
}

void GroupManager::on_saveFileRequest()
{
    QString str = "Saving data to " + GroupManager::GetInstance()->GetDataFilePath() + "...\n";
    ConsoleManager::GetInstance()->consoleThread->AppendConsoleBuffer(str);

    _jsonIndented = _jsonDocumentSerialize.toJson(QJsonDocument::Indented);

    _jsonFile.setFileName("json/var.json");
    _jsonFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    _jsonFile.write(_jsonDocumentSerialize.toJson());
    _jsonFile.close();

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

QJsonDocument GroupManager::serialize()
{
    QJsonArray groupsArray;
    QJsonObject jsonObject;

    foreach (Group oGroup, this->groups) {

        QJsonObject obj = oGroup.serialize();
        groupsArray.append(obj);
    }

    jsonObject["Groups"] = groupsArray;

    _jsonDocumentSerialize = QJsonDocument(jsonObject);

    qDebug() << "Serialized Groups Document looks like " << _jsonDocumentSerialize;

    return _jsonDocumentSerialize;

}
