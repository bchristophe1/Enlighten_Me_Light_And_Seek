#pragma once

#include <QList>
#include <QString>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "helper_macro.h"
#include "group.h"
#include "user.h"
#include "qlwi_group.h"

class GroupManager : public QObject
{
    Q_OBJECT
    DECLARE_SINGLETON(GroupManager)

public:
    QList<Group> groups;

    void LoadDataFromFile(QString filePath);
    void SaveDataToFile(QString filePath);
    Group* GetGroupByID(unsigned int ID);

    QString GetDataFilePath();


public slots:
    void on_loadFileRequest();
    void on_saveFileRequest();

private:
    QString _dataFilePath;
    QFile _jsonFile;
    QJsonDocument _jsonDocument;
    QJsonObject _jsonObject;
    QJsonArray _jsonArray;
    QJsonValue _jsonValue;
    unsigned int _groupCounter;
    unsigned int _userCounter;

signals:
    void refreshed();
    void refreshed(QLWI_Group *row);
};
