#pragma once
#include <vector>
using std::vector;
template <typename T,typename F>
class Pair {
	T first;
	F second;
public:
	Pair() {
		first = T();
		second = F();
	}
	Pair(T _first,F _second) {
		first = _first;
		second = _second;
	}
	bool operator<(Pair other) {
		return first < other.first;
	}
	bool operator==(Pair other) {
		return first == other.first;
	}
	bool operator>(Pair other) {
		return first > other.first;
	}
};
template <typename T>
class NodeInterface {
	
public:
	T key;
	NodeInterface(T _key) {
		key = _key;
	}
};
template <typename T>
class Container {
public:
	virtual vector<T> get_all_values() = 0;
	Container() {};
	virtual void insert(const T& key)=0;
	virtual void remove(const T& key) = 0;
	virtual NodeInterface<T>* search_universal(const T& key) = 0;
};