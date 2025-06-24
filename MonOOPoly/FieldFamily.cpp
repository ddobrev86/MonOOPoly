#include "FieldFamily.h"

FieldFamily::FieldFamily(const MyString& name)
{
	this->name = name;
}

void FieldFamily::addField(SharedPtr<BuyableField>& field)
{
	this->add(field);
}

void FieldFamily::addField(SharedPtr<BuyableField>&& field)
{
	this->add(std::move(field));
}

void FieldFamily::addField(const BuyableField* field)
{
	this->add(SharedPtr<BuyableField>(field->clone()));
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

size_t FieldFamily::howManyBelongToPlayer(const SharedPtr<Player>& player) const
{
	size_t count = 0;
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i]->belongsToPlayer(player))
			count++;
	}

	return count;
}

bool FieldFamily::ownsAll(const SharedPtr<Player>& player) const
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (!data[i]->belongsToPlayer(player))
			return false;
	}

	return true;
}

void FieldFamily::printFamilyInfo() const
{
	std::cout << name << '\n';
	for (size_t i = 0; i < data.getSize(); i++)
	{
		std::cout << '\t';
		data[i]->printFieldInfo();
		std::cout << '\n';
	}
}

bool FieldFamily::comapreName(const SharedPtr<FieldFamily>& other) const
{
	return name == other->name;
}

void FieldFamily::removeOwner(const SharedPtr<Player>& player)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i]->belongsToPlayer(player))
			data[i]->sell();
	}
}

bool FieldFamily::comapreName(const MyString& name) const
{
	return this->name == name;
}

bool FieldFamily::canBuyMortgages() const
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (!data[i]->canBuyMortgages())
			return false;
	}

	return true;
}

void FieldFamily::findOwnedFields(MyVector<SharedPtr<BuyableField>>& ownedFields,
	const SharedPtr<Player>& owner) const
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		if (data[i]->belongsToPlayer(owner))
			ownedFields.push_back(data[i]);
	}
}
