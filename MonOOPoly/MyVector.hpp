//Dimitar Dobrev 3MI0600520
#pragma once
#include <utility>
#include <stdexcept>

template <typename T>
class MyVector
{
private:
	static const size_t INITIAL_CAPACITY;

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const MyVector& other);
	void moveFrom(MyVector&& other);

	void resize(size_t newCapacity);
	static size_t getNextPowerOfTwo(size_t number);

public:
	MyVector();
	MyVector(size_t size);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	MyVector(MyVector&& other) noexcept;
	MyVector& operator=(MyVector&& other) noexcept;
	~MyVector();

	void push_back(const T& element);
	void push_back(T&& element);

	void pop_back();

	void insertAt(size_t index, const T& element);
	void insertAt(size_t index, T&& element);
	void removeAt(size_t index);

	void shrink_to_fit();

	void clear();
	bool isEmpty() const;

	size_t getSize() const;
	size_t getCapacity() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

};

template <typename T>
const size_t MyVector<T>::INITIAL_CAPACITY = 4;

template <typename T>
size_t MyVector<T>::getNextPowerOfTwo(size_t v)
{
	v |= (v >> 1);
	v |= (v >> 2);
	v |= (v >> 4);
	v |= (v >> 8);
	v |= (v >> 16);
	//v |= (v >> 32);
	++v;
	return v;
}

template <typename T>
void MyVector<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < size; ++i)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
	capacity = newCapacity;
}

template <typename T>
void MyVector<T>::free()
{
	delete[] data;
	data = nullptr;

	size = 0;
	capacity = 0;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	data = new T[other.capacity];
	for (size_t i = 0; i < other.size; ++i)
	{
		data[i] = other.data[i];
	}

	size = other.size;
	capacity = other.capacity;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;
}

template <typename T>
MyVector<T>::MyVector()
{
	data = new T[INITIAL_CAPACITY];
	capacity = INITIAL_CAPACITY;
	size = 0;
}

template <typename T>
MyVector<T>::MyVector(size_t size)
{
	capacity = getNextPowerOfTwo(size);
	data = new T[capacity];
	this->size = size;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
	free();
}

template <typename T>
void MyVector<T>::push_back(const T& element)
{
	if (size == capacity)
	{
		resize(getNextPowerOfTwo(capacity));
	}
	data[size++] = element;
}

template<typename T>
void MyVector<T>::push_back(T&& elem)
{
	if (size == capacity)
		resize(capacity * 2);

	data[size++] = std::move(elem);
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (size > 0)
	{
		--size;
	}
}

template <typename T>
void MyVector<T>::insertAt(size_t index, const T& element)
{
	if (index >= size)
		throw std::invalid_argument("Invalid index");

	if (size == capacity)
		resize(getNextPowerOfTwo(capacity));

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	size++;
}

template <typename T>
void MyVector<T>::insertAt(size_t index, T&& element)
{
	if (index >= size)
		throw std::invalid_argument("Invalid index");

	if (size == capacity)
		resize(getNextPowerOfTwo(capacity));

	for (size_t i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = std::move(element);
	size++;
}

template <typename T>
void MyVector<T>::removeAt(size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Invalid index");

	for (size_t i = index; i < size - 1; ++i)
		data[i] = data[i + 1];

	--size;
}

template <typename T>
void MyVector<T>::clear()
{
	size = 0;
}

template <typename T>
void MyVector<T>::shrink_to_fit()
{
	capacity = size;
	T* newData = new T[capacity];

	for (size_t i = 0; i < size; ++i)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}

template <typename T>
bool MyVector<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
size_t MyVector<T>::getSize() const
{
	return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
T& MyVector<T>::operator[](size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Invalid index");

	return data[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const
{
	if (index >= size)
		throw std::invalid_argument("Invalid index");

	return data[index];
}

