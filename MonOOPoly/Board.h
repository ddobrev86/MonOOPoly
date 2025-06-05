#pragma once
#include "Field.h"
#include "MyVector.hpp"
#include "UniquePtr.hpp"

class Board
{
private:
	MyVector<UniquePtr<Field>> fields;
	size_t currentPos;
	size_t size;

public:
	Board(size_t size);

	UniquePtr<Field>& move(size_t positions);
	void addField(const UniquePtr<Field>& field);
};

