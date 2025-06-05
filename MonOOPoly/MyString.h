//Dimitar Dobrev 3MI0600520
#pragma once
#include <iostream>
#include <fstream>

class MyString
{
	char* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);

	void resize(unsigned newCapacity);
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	size_t getSize() const;
	size_t getCapacity() const;

	const char* c_str() const;

	char& operator[](unsigned index);
	const char& operator[](unsigned indexs) const;

	MyString& operator+=(const MyString& other);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	void readLong();

	void readFromFile(std::ifstream& ifs);
	void saveToFile(std::ofstream& ofs) const;

	MyString substr(unsigned begin, unsigned howMany);
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);

