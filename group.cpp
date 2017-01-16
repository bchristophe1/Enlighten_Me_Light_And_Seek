#include <QDebug>

#include "group.h"

/**
 * @brief Group::Group
 * @param ID
 * @param name
 *
 * TODO: Adding Json file attributes
 */
Group::Group(unsigned int ID, QString name)
    : _ID(ID),
      _name(name) { }

unsigned int Group::GetID()
{
    return _ID;
}

QString Group::GetName()
{
    return _name;
}

void Group::SetName(QString name)
{
    _name = name;
}

QJsonObject Group::serialize()
{
    QJsonObject groupJson;
    QJsonArray usersJsonArray;

    groupJson["id"] = QString::number(this->_ID);
    groupJson["name"] = this->_name;

    foreach (User user, this->users) {
        QJsonObject obj = user.serialize();
        usersJsonArray.append(obj);
    }

    groupJson["users"] = usersJsonArray;

    qDebug() << "Serialized Group looks like : " << groupJson;

    return groupJson;
}
