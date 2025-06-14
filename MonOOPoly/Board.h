#pragma once
#include "Field.h"
#include "MyVector.hpp"
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"
#include "IteratibleContainer.hpp"
#include "CardField.h"
#include "CardDeck.h"

class Board : public IteratibleContainer<SharedPtr<Field>>
{
private:
	//MyVector<SharedPtr<Field>> fields;
	size_t currentPos;
	size_t size;
	SharedPtr<CardDeck> deck;

public:
	size_t getTotalSize() const;

	Board(size_t size);

	SharedPtr<Field>& move(size_t positions);
	void addField(const SharedPtr<Field>& field);

	SharedPtr<Field>& operator[](size_t index);
	const SharedPtr<Field>& operator[](size_t index) const;

	void printBoard() const;

	void switchFields(size_t firstIndex, size_t secondIndex);

	void addCardFields(size_t count);
};

