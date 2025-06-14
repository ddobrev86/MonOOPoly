#include "Board.h"
#include <stdexcept>
#include "Start.h"
#include "Jail.h"
#include "GoToJail.h"
#include "FreeParking.h"

const size_t MIN_BOARD_SIZE = 3;

Board::Board(size_t size)
{
	setSize(size);
	currentPos = 0;
	data = MyVector<SharedPtr<Field>>(getTotalSize());
	//fields = MyVector<SharedPtr<Field>>(getTotalSize());
}

size_t Board::getTotalSize() const
{
	return 4 * (size - 1);
}

void Board::setUpCorners()
{
	data.insertAt(0, SharedPtr<Field>(new Start()));
	data.insertAt(size - 1, SharedPtr<Field>(new Jail()));
	data.insertAt((size - 1) * 2, SharedPtr<Field>(new FreeParking()));
	data.insertAt((size - 1) * 3, SharedPtr<Field>(new GoToJail(size)));
}

bool Board::canAddCorners() const
{
	return data.getSize() == getTotalSize() - 4;
}

void Board::setSize(size_t size)
{
	if (size < MIN_BOARD_SIZE)
		throw std::invalid_argument("Size is below the minimum allowed size");
	
	this->size = size;
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
		for (size_t i = 0; i < data.getSize(); i++)
		{
			if (data[i] == field)
				throw std::runtime_error("This field is already on the board");
		}

		this->add(field);
		if (canAddCorners())
			setUpCorners();

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

void Board::printBoard() const
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		data[i]->printFieldInfo();
		std::cout << '\n';
	}
}

void Board::switchFields(size_t firstIndex, size_t secondIndex)
{
	if (firstIndex >= getTotalSize() || secondIndex >= getTotalSize())
		throw std::invalid_argument("Indexes exceed board size");

	if (firstIndex % (size - 1) == 0 || secondIndex % (size - 1) == 0)
		throw std::invalid_argument("Cannot switch corner fields");

	std::swap(data[firstIndex], data[secondIndex]);
}

void Board::addCardFields(size_t count)
{
	size_t current = data.getSize();
	while (current < getTotalSize() && count > 0)
	{
		addField(SharedPtr<Field>(new CardField(deck)));
		current++;
		count--;
	}
}

const SharedPtr<Field>& Board::operator[](size_t index) const
{
	if (index > getTotalSize())
		throw std::invalid_argument("Invalid index");

	return data[index];
}
