#pragma once

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include "user.h"

class Group
{
public:
    Group(unsigned int ID, QString name);

    QList<User> users;

    unsigned int GetID();
    QString GetName();
    void SetName(QString name);

    QJsonObject serialize();

private:
    unsigned int _ID;
    QString _name;
};
