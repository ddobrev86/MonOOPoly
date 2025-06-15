#pragma once

template <typename T, typename D >
struct MyPair
{
	T key;
	D value;

	MyPair(const T& key, const D& value);
	MyPair() = default;
};

template <typename T, typename D >
MyPair<T, D>::MyPair(const T& key, const D& value)
{
	this->key = key;
	this->value = value;
}