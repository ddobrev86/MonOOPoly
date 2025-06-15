#pragma once
#include "Iterator.hpp"

template <typename T>
class IteratibleContainer {
    //friend class Iterator<T, Container>;
protected:
    MyVector<T> data;

public:
    void add(const T& obj);

    Iterator<T>* createIterator() const;
};

template<typename T>
void IteratibleContainer<T>::add(const T& obj)
{
    data.push_back(obj);
}

template<typename T>
Iterator<T>* IteratibleContainer<T>::createIterator() const
{
    return new Iterator<T>(this->data);
}