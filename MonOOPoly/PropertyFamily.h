#pragma once
#include "SharedPtr.hpp"
#include "Property.h"
#include "MyVector.hpp"
#include "MyString.h"
#include "UniquePtr.hpp"
#include "MortgageManager.h"
#include "Castle.h"
#include "Cottage.h"

class PropertyFamily
{
private:
	MyString name;
	MyVector<SharedPtr<Property>> properties;
	UniquePtr<MortgageManager> mortgages;

	SharedPtr<Castle> castle;
	SharedPtr<Cottage> cottage;

public:
	PropertyFamily(const MyString& name, 
		unsigned cottagePrice, unsigned castlePrice);

	void addProperty(const SharedPtr<Property>& property);
	bool containsProperty(const SharedPtr<Property>& property);

	size_t howManyBelongToPlayer(const SharedPtr<Player>& player);
	bool ownsAll(const SharedPtr<Player>& player);

	void buyProperty(const SharedPtr<Player>& player, bool isCottage);

};

