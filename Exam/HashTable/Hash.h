#pragma once
#include "../Interface/Container.h"
#include "../Interface/ContainerStrategy.h"
#include <functional>
template <typename T>
class Hash:public Container<T>{
protected:
	bool enable_two_choice = false;
	int mod;
public:
	void set_choice(bool choice) {
		enable_two_choice = choice;
	}
	int get_hash(T key) {
		std::hash<T*> hash;
		return hash(&key)%mod;
	}
	
	Hash(int mod_) {
		mod = mod_;
	}
	virtual void insert(const T& key) = 0;
	virtual void remove(const T& key) = 0;
	virtual NodeInterface<T>* search_universal(const T& key) = 0;
};
int Hash<int>::get_hash(int key) {
	std::hash<int> hash;
	return hash(key) % mod;
}