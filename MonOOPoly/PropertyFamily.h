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

	void addField(SharedPtr<BuyableField>& field) override;
	void addField(SharedPtr<BuyableField>&& field) override;

};

