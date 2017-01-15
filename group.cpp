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
