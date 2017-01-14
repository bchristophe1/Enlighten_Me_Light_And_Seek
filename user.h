#pragma once

#include <QString>

class User
{
public:
    User(unsigned int ID, unsigned int groupID, QString name);

    unsigned int GetID();
    unsigned int GetGroupID();

    QString name() const;
    void setName(const QString &name);

    unsigned int groupID() const;
    void setGroupID(unsigned int groupID);

    unsigned int ID() const;
    void setID(unsigned int ID);

private:
    unsigned int _ID;
    unsigned int _groupID;
    QString _name;
};
