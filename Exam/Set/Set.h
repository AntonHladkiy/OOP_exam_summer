#pragma once
#include "../Interface/Container.h"
#include "../Interface/ContainerStrategy.h"
template <typename T>
class Set {

	Container<T>* container;
public:
	bool include(const T& key);
	void insert(const T& key);
	void remove(const T& key);
	Set<T> operator + (const Set<T>& other);//обєднання
	Set<T> operator ^ (const Set<T>& other);//перетин
};

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
inline Set<T> Set<T>::operator+(const Set<T>& other)
{	
	return Set<T>();
}

template<typename T>
inline Set<T> Set<T>::operator^(const Set<T>& other)
{
	return Set<T>();
}
