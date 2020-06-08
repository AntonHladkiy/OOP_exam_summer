#pragma once
#include "Hash.h"
#include "../Interface/Container.h"

template <typename T>
class SeparateChaning :public Hash<T> {
private:
	ContainerStrategy<T>* strategy;
public:
	SeparateChaning(int _mod) :Hash<T>(_mod) {
		hash_table.resize(mod);
		strategy = new ListContainer<T>();
		for (int i = 0; i < hash_table.size(); i++) {
			hash_table[i] = strategy->get_container();
		}
	}
	vector<Container<T>*> hash_table;
	void set_container(ContainerStrategy<T>* _strategy) {
		strategy = _strategy;
	}
	void insert(const T& key) override;
	void remove(const T& key)override;
	NodeInterface<T>* search_universal(const T& key)override;
};

template<typename T>
inline void SeparateChaning<T>::insert(const T& key)
{
	int index = get_hash(key);
	hash_table[index]->insert(key);
}

template<typename T>
inline void SeparateChaning<T>::remove(const T& key)
{
	int index = get_hash(key);
	hash_table[index]->remove(key);
}

template<typename T>
inline NodeInterface<T>* SeparateChaning<T>::search_universal(const T& key)
{
	int index = get_hash(key);
	return hash_table[index]->search_universal(key);
	
}
