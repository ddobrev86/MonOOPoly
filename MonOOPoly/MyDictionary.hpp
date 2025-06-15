#pragma once
#include "MyPair.hpp"
#include "MyVector.hpp"

template <typename T, typename D>
class MyDictionary
{
private:
	MyVector<MyPair<T, D>> dict;
public:
	MyDictionary() = default;

	void addPair(const T& key, const D& value);
	void addPair(const MyPair<T, D>& pair);

	const D& operator[](const T& key) const;
	D& operator[](const T& key);

	bool containsKey(const T& key) const;
};

template <typename T, typename D>
void MyDictionary<T, D>::addPair(const T& key, const D& value)
{
	dict.push_back(MyPair<T, D>(key, value));
}

template <typename T, typename D>
void MyDictionary<T, D>::addPair(const MyPair<T, D>& pair)
{
	dict.push_back(pair);
}

template <typename T, typename D>
const D& MyDictionary<T, D>::operator[](const T& key) const
{
	for (size_t i = 0; i < dict.getSize(); i++)
	{
		if (dict[i].key == key)
			return dict[i].value;
	}

	throw std::invalid_argument("There isn't an element with this key");
}

template <typename T, typename D>
D& MyDictionary<T, D>::operator[](const T& key)
{
	for (size_t i = 0; i < dict.getSize(); i++)
	{
		if (dict[i].key == key)
			return dict[i].value;
	}

	throw std::invalid_argument("There isn't an element with this key");
}

template<typename T, typename D>
inline bool MyDictionary<T, D>::containsKey(const T& key) const
{
	for (size_t i = 0; i < dict.getSize(); i++)
	{
		if (dict[i].key == key)
			return true;
	}

	return false;
}
