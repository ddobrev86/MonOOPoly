#include "FieldFamily.h"

FieldFamily::FieldFamily(const MyString& name)
{
	this->name = name;
}

void FieldFamily::addField(const SharedPtr<BuyableField>& field)
{
	this->add(field);
}

bool FieldFamily::containsField(const SharedPtr<BuyableField>& property)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i].compareWith(property))
			return true;
	}
	return false;
}

size_t FieldFamily::howManyBelongToPlayer(const SharedPtr<Player>& player)
{
	size_t count = 0;
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i]->belongsToPlayer(player))
			count++;
	}

	return count;
}

bool FieldFamily::ownsAll(const SharedPtr<Player>& player)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (!data[i]->belongsToPlayer(player))
			return false;
	}

	return true;
}