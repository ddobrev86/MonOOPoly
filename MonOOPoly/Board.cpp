#include "Board.h"
#include <stdexcept>

Board::Board(size_t size)
{
	this->size = size;
	currentPos = 0;
	data = MyVector<SharedPtr<Field>>(getTotalSize());
	//fields = MyVector<SharedPtr<Field>>(getTotalSize());
}

size_t Board::getTotalSize() const
{
	return 4 * (size - 1);
}

SharedPtr<Field>& Board::move(size_t positions)
{
	currentPos += positions;
	currentPos %= getTotalSize();

	return data[currentPos];
}

void Board::addField(const SharedPtr<Field>& field)
{
	if (data.getSize() < getTotalSize())
	{
		this->add(field);
		//data.push_back(field);
		return;
	}

	throw std::logic_error("Board has all fields, cannot add a new one");
}

SharedPtr<Field>& Board::operator[](size_t index)
{
	if (index > getTotalSize())
		throw std::invalid_argument("Invalid index");

	return data[index];
}

const SharedPtr<Field>& Board::operator[](size_t index) const
{
	if (index > getTotalSize())
		throw std::invalid_argument("Invalid index");

	return data[index];
}
