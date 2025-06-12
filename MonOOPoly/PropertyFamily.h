#pragma once
#include "SharedPtr.hpp"
#include "Property.h"
#include "MyVector.hpp"
#include "MyString.h"
#include "UniquePtr.hpp"
#include "MortgageManager.h"
#include "Castle.h"
#include "Cottage.h"
#include "IteratibleContainer.hpp"
#include "FieldFamily.h"

class PropertyFamily : public FieldFamily
{
private:
	//MyVector<SharedPtr<Property>> properties;
	//MyString name;
	//UniquePtr<MortgageManager> mortgages;

	SharedPtr<Mortgage> castle;
	SharedPtr<Mortgage> cottage;

public:
	PropertyFamily(const MyString& name, 
		unsigned cottagePrice, unsigned castlePrice);

	void addProperty(const SharedPtr<Property>& property);
	//bool containsProperty(const SharedPtr<Property>& property);

	//size_t howManyBelongToPlayer(const SharedPtr<Player>& player);
	//bool ownsAll(const SharedPtr<Player>& player);

	//void buyProperty(const SharedPtr<Player>& player, bool isCottage);

};

