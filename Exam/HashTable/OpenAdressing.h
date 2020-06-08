#pragma once
#include "Hash.h"
template <typename T>
class OpenAdressingHash :public Hash<T> {
public:
	OpenAdressingHash(int _mod):Hash<T>(_mod) {
		hash_table.resize(mod);
		for (int i = 0; i < hash_table.size(); i++) {
			hash_table[i] = nullptr;
		}
	}
	vector<NodeInterface<T>*> hash_table;
	void insert(const T& key) override;
	void remove(const T& key)override;
	vector<T> get_all_values() override;
	NodeInterface<T>* search_universal(const T& key)override;
};

template<typename T>
inline void OpenAdressingHash<T>::insert(const T& key)
{
	if (search_universal(key)) {
		return;
	}
	int index = get_hash(key);
	int i=1;
	int temp = index;
	while (hash_table[temp] != nullptr) {
		temp = (index + i + i * i) % mod; i++;
		if (i == mod) {
			break;
		}
	}
	if (hash_table[temp] == nullptr) {
		hash_table[temp] = new NodeInterface<T>(key);
	}
}

template<typename T>
inline void OpenAdressingHash<T>::remove(const T& key)
{
	int index = get_hash(key);
	int i=1;
	int temp = index;
	while (hash_table[temp] == nullptr) {
		temp = (index + i + i * i) % mod; i++;
		if (i == mod) {
			return;
		}
	}
	while (hash_table[temp]->key !=key) {
		temp = (index + i + i * i) % mod; i++;
		while (hash_table[temp] == nullptr) {
			temp = (index + i + i * i) % mod; i++;
			if (i == mod) {
				break;
			}
		}
		if (i == mod) {
			break;
		}
	}
	if (hash_table[temp]->key == key) {
		hash_table[temp] = nullptr;
	}
}

template<typename T>
inline vector<T> OpenAdressingHash<T>::get_all_values()
{
	vector<T> res;
	for (int i = 0; i < hash_table.size(); i++) {
		if(hash_table[i])
		res.push_back(hash_table[i]->key);
	}
}

template<typename T>
inline NodeInterface<T>* OpenAdressingHash<T>::search_universal(const T& key)
{
	int index = get_hash(key);
	int i=1;
	int temp = index;
	while (hash_table[temp] == nullptr) {
		temp = (index + i + i * i) % mod; i++;
		if (i == mod) {
			return nullptr;
		}
	}
	while (hash_table[temp]->key != key) {
		temp = (index + i+i * i) % mod; i++;
		while (hash_table[temp] == nullptr) {
			temp = (index + i + i * i) % mod; i++;
			if (i == mod) {
				break;
			}
		}
		if (i == mod) {
			break;
		}
	}
	if (hash_table[temp]->key == key) {
		return new NodeInterface<T>(key);
	}
	else {
		return nullptr;
	}
}
