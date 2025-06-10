#pragma once
#include "SharedPtr.hpp"
#include "Property.h"
#include "MyVector.hpp"
#include "MyString.h"

class PropertyFamily
{
private:
	MyString name;
	MyVector<SharedPtr<Property>> properties;
public:
	PropertyFamily(const MyString& name);

	void addProperty(const SharedPtr<Property>& property);
	bool containsProperty(const SharedPtr<Property>& property);

	size_t howManyBelongToPlayer(const SharedPtr<Player>& player);
	bool ownsAll(const SharedPtr<Player>& player);
};

