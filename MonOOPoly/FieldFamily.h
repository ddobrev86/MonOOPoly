#pragma once
#include "MyString.h"
#include "IteratibleContainer.hpp"
#include "BuyableField.h"
#include "SharedPtr.hpp"

class FieldFamily : public IteratibleContainer<SharedPtr<BuyableField>>
{
protected:
	MyString name;
public:
	FieldFamily(const MyString& name);

	void addField(const SharedPtr<BuyableField>& property);
	bool containsField(const SharedPtr<BuyableField>& property);

	size_t howManyBelongToPlayer(const SharedPtr<Player>& player);
	bool ownsAll(const SharedPtr<Player>& player);
};

