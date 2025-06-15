#include "CornerField.h"

size_t CornerField::count = 0;

CornerField::CornerField()
{
	if (!canCreate())
		throw std::runtime_error("Cannot create more than 4 Corner Fields");
	
	count++;
}

bool CornerField::canCreate() const
{
	return (count <= 4? true: false);
}

size_t CornerField::getCornerCount()
{
	return count;
}

