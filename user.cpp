#include "user.h"

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
