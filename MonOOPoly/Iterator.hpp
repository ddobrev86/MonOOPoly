#pragma once
#include "MyVector.hpp"

template <typename T>
class Iterator {
private:
    const MyVector<T>& data;
    size_t index = 0;

public:
    Iterator(const MyVector<T>& data);

    bool hasNext() const;
    //T next();
    const T& next() const;
    void toStart();
};

template <typename T>
Iterator<T>::Iterator(const MyVector<T>& data) : data(data)
{}

template <typename T>
bool Iterator<T>::hasNext() const
{
    return index < data.size();
}

//template <typename T>
//T Iterator<T>::next()
//{
//    return data[index++];
//}

template <typename T>
const T& Iterator<T>::next() const
{
    return data[index++];
}

template <typename T>
void Iterator<T>::toStart()
{
    index = 0;
}