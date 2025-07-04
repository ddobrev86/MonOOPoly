#pragma once
#include "MyString.h"
#include "IteratibleContainer.hpp"
#include "SharedPtr.hpp"
#include "BuyableField.h"

class FieldFamily : public IteratibleContainer<SharedPtr<BuyableField>>
{
protected:
	MyString name;
public:
	FieldFamily(const MyString& name);

	virtual void addField(SharedPtr<BuyableField>& property);
	virtual void addField(SharedPtr<BuyableField>&& field);
	void addField(const BuyableField* field);

	bool containsField(const SharedPtr<BuyableField>& property);

	size_t howManyBelongToPlayer(const SharedPtr<Player>& player) const;
	bool ownsAll(const SharedPtr<Player>& player) const;

	bool canBuyMortgages() const;

	virtual void printFamilyInfo() const;

	bool comapreName(const SharedPtr<FieldFamily>& other) const;
	bool comapreName(const MyString& name) const;

	void findOwnedFields(MyVector<SharedPtr<BuyableField>>& ownedFields, 
		const SharedPtr<Player>& owner) const;

	void removeOwner(const SharedPtr<Player>& player);
};

