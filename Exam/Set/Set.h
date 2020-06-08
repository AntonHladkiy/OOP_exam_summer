#pragma once
#include "../Interface/Container.h"
#include "../Interface/ContainerStrategy.h"
template <typename T>
class Set {
private:
	ContainerStrategy<T>* strategy;
	Container<T>* container;
public:
	Set( ContainerStrategy<T>* _strategy = new AVLTreeContainer<T>()) {
		strategy = _strategy;
		container = strategy->get_container();
	}
	void show();
	bool include(const T& key);
	void insert(const T& key);
	void remove(const T& key);
	void operator = (const Set<T>& other);
	Set<T> operator + (const Set<T>& other);//обЇднанн€
	Set<T> operator ^ (const Set<T>& other);
	Set<T> operator/(const Set<T>& other);
	Set<T> operator-(const Set<T>& other);
	//перетин
};

template<typename T>
inline void Set<T>::show()
{
	vector<T> temp = container->get_all_values();
	for (int i = 0; i < temp.size(); i++) {
		std::cout << temp[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
inline bool Set<T>::include(const T& key)
{
	return container->search_universal(key);
}

template<typename T>
inline void Set<T>::insert(const T& key)
{
	container->insert(key);
}

template<typename T>
inline void Set<T>::remove(const T& key)
{
	container->remove(key);
}

template<typename T>
inline void Set<T>::operator=(const Set<T>& other)
{
	strategy = other.strategy;
	vector<T> others = other.container->get_all_values();
	container = nullptr;
	container = strategy->get_container();
	for (int i = 0; i < others.size(); i++) {
		container->insert(others[i]);
	}
}

template<typename T>
inline Set<T> Set<T>::operator+(const Set<T>& other)
{
	Set<T> result(strategy);
	result = *this;
	vector<T> others = other.container->get_all_values();
	for (int i = 0; i < others.size(); i++) {
		result.container->insert(others[i]);
	}
	return result;
}

template<typename T>
inline Set<T> Set<T>::operator^(const Set<T>& other)//обЇднанн€
{
	Set<T> result = *this;
	Set<T> temp = *this - other;
	result = result - temp;
	return result;
}
template<typename T>
inline Set<T> Set<T>::operator/(const Set<T>& other) //р≥зниц€
{
	Set<T> result(strategy);
	result = *this;
	vector<T> others = other.container->get_all_values();
	for (int i = 0; i < others.size(); i++) {
		result.container->remove(others[i]);
	}
	return result;
}
template<typename T>
inline Set<T> Set<T>::operator-(const Set<T>& other)
{
	Set<T> result(strategy);
	result = *this + other;
	result = result - (*this ^ other);
	return result;
}