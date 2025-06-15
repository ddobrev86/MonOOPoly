#pragma once
#include "Field.h"

class CornerField : public Field
{
protected:
	static size_t count;
public:
	CornerField();
	bool canCreate() const;
	static size_t getCornerCount();
};

