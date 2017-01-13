#pragma once

#include <QList>
#include <QString>
#include <QObject>

#include "helper_macro.h"
#include "group.h"
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
    unsigned int _groupCounter;
    unsigned int _userCounter;

signals:
    void refreshed();
    void refreshed(QLWI_Group *row);
};
