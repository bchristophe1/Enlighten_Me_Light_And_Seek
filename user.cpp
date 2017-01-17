#include <QDebug>

#include "user.h"

/**
 * @brief User::User
 * @param ID
 * @param groupID
 * @param name
 *
 * TODO: Adding Json file attributes
 */
User::User(unsigned int ID, unsigned int groupID, QString name)
    : _ID(ID),
      _groupID(groupID),
      _name(name) { }

unsigned int User::GetID()
{
    return _ID;
}

unsigned int User::GetGroupID()
{
    return _groupID;
}

QString User::name() const
{
    return _name;
}

void User::setName(const QString &name)
{
    _name = name;
}

unsigned int User::groupID() const
{
    return _groupID;
}

void User::setGroupID(unsigned int groupID)
{
    _groupID = groupID;
}

unsigned int User::ID() const
{
    return _ID;
}

void User::setID(unsigned int ID)
{
    _ID = ID;
}


QJsonObject User::serialize()
{
    QJsonObject userJson;

    // QString::number because unsigned doesn't fit

    userJson["id"] = QString::number(this->_ID);
    userJson["name"] = this->_name;

    return userJson;
}




