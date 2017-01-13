#pragma once

#include <QString>

class User
{
public:
    User(unsigned int ID, unsigned int groupID, QString name);

    unsigned int GetID();
    unsigned int GetGroupID();

private:
    unsigned int _ID;
    unsigned int _groupID;
    QString _name;
};
