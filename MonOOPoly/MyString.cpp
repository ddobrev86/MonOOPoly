//Dimitar Dobrev 3MI0600520
#include "MyString.h"
#include <algorithm>
#include <stdexcept>
#include <utility>
#pragma warning (disable : 4996)

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void MyString::copyFrom(const MyString& other)
{
	capacity = other.capacity;
	data = new char[capacity + 1];
	strcpy(data, other.data);
	size = other.size;
}

void MyString::moveFrom(MyString&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;
}

void MyString::resize(unsigned newCapacity)
{
	char* newData = new char[newCapacity + 1];
	strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

static unsigned roundToPowerOfTwo(unsigned v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static unsigned getMaxResizeCapacity(unsigned v)
{
	return std::max(roundToPowerOfTwo(v), 16u);
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
	if (!str)
		throw std::invalid_argument("Empty string given!");

	size = strlen(str);
	capacity = getMaxResizeCapacity(size);
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getSize() const
{
	return size;
}

size_t MyString::getCapacity() const
{
	return capacity - 1;
}

const char* MyString::c_str() const
{
	return data;
}

char& MyString::operator[](unsigned index)
{
	if (index >= size)
		throw std::invalid_argument("Invalid index!");

	return data[index];
}

const char& MyString::operator[](unsigned index) const
{
	if (index >= size)
		throw std::invalid_argument("Invalid index!");

	return data[index];
}

MyString& MyString::operator+=(const MyString& other)
{
	if (size + other.size + 1 > capacity)
		resize(getMaxResizeCapacity(size + other.size));

	strncat(data, other.data, other.size);

	size += other.size;

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;

	return res;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.data;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	size_t buffStringSize = strlen(buff);
	if (buffStringSize >= str.capacity)
		str.resize(getMaxResizeCapacity(buffStringSize));

	strcpy(str.data, buff);
	str.size = buffStringSize;

	return is;
}

void MyString::readLong()
{
	char buff[1024];

	std::cin.getline(buff, 1024);

	size_t buffStringSize = strlen(buff);
	size = buffStringSize;
	capacity = getMaxResizeCapacity(buffStringSize);

	delete[] data;
	data = new char[capacity + 1];
	strcpy(data, buff);
}

void MyString::readFromFile(std::ifstream& ifs)
{
	if (!ifs.is_open())
		throw std::runtime_error("Can't open file");

	char buff[1024]{};
	size_t len = 0;

	ifs.read((char*)&len, sizeof(size_t));
	ifs.read((char*)buff, len);
	buff[len] = '\0';

	delete[] data;
	data = new char[len + 1];
	strcpy(data, buff);

	size = capacity = len;
}

void MyString::saveToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		throw std::runtime_error("Can't open file");

	ofs.write((const char*)&size, sizeof(size_t));
	ofs.write(data, size);
}

MyString MyString::substr(unsigned begin, unsigned howMany)
{
	if (begin + howMany > size)
		return MyString("");

	MyString res;
	res.capacity = getMaxResizeCapacity(howMany + 1);
	res.data = new char[res.capacity];
	strncat(res.data, data + begin, howMany);
	res.size = howMany;

	return res;
}


bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}