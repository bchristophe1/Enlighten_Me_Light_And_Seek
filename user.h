#pragma once

#include <QString>
#include <QJsonObject>

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

    QJsonObject serialize();

private:
    unsigned int _ID;
    unsigned int _groupID;
    QString _name;
};
