#include "PropertyFamily.h"

PropertyFamily::PropertyFamily(const MyString& name)
{
	this->name = name;
}

void PropertyFamily::addProperty(const SharedPtr<Property>& property)
{
	properties.push_back(property);
}

bool PropertyFamily::containsProperty(const SharedPtr<Property>& property)
{
	for (size_t i = 0; i < properties.getSize(); i++)
	{
		if (properties[i].compareWith(property))
			return true;
	}
	return false;
}

size_t PropertyFamily::howManyBelongToPlayer(const SharedPtr<Player>& player)
{
	size_t count = 0;
	for (size_t i = 0; i < properties.getSize(); i++)
	{
		if (properties[i]->belongsToPlayer(player))
			count++;
	}

	return count;
}

bool PropertyFamily::ownsAll(const SharedPtr<Player>& player)
{
	for (size_t i = 0; i < properties.getSize(); i++)
	{
		if (!properties[i]->belongsToPlayer(player))
			return false;
	}

	return true;
}
