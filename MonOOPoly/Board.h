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
	//SharedPtr<CardDeck> deck;

public:
	size_t getTotalSize() const;
	void setSize(size_t size);
	unsigned getMissingFields() const;

	bool isBoardFull() const;
	
	void setUpCorners();
	bool canAddCorners() const;

	Board(size_t size);

	SharedPtr<Field>& move(size_t positions);

	void addField(SharedPtr<Field>& field);
	void addField(SharedPtr<Field>&& field);
	void addCardFields(size_t count, const SharedPtr<CardDeck>& deck);

	SharedPtr<Field>& operator[](size_t index);
	const SharedPtr<Field>& operator[](size_t index) const;

	void printBoard() const;
	void printBoard(const MyVector<SharedPtr<Player>>& players) const;

	void switchFields(size_t firstIndex, size_t secondIndex);

	void randomiseBoard();
};

