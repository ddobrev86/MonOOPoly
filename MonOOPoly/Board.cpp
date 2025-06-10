#include "Board.h"
#include <stdexcept>

Board::Board(size_t size)
{
	this->size = size;
	currentPos = 0;
	fields = MyVector<UniquePtr<Field>>(getTotalSize());
}

size_t Board::getTotalSize() const
{
	return 4 * (size - 1);
}

UniquePtr<Field>& Board::move(size_t positions)
{
	currentPos += positions;
	currentPos %= getTotalSize();

	return fields[currentPos];
}

void Board::addField(const UniquePtr<Field>& field)
{
	if (fields.getSize() < getTotalSize())
	{
		fields.push_back(field);
		return;
	}

	throw std::logic_error("Board has all fields, cannot add a new one");
}
